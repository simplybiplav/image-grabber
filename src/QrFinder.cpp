#include <zbar.h>
#include "QrFinder.hpp"


namespace imggrab {


    QrFinder::QrFinder(const std::set<std::string>& qrSet) {
        mQrSet = qrSet;
        mRun = false;
    }

    bool QrFinder::run(ImageQueue& processingQueue, ImageQueue& outQueue){
        std::unique_lock<std::mutex> lock(mLock);
        if (mRun) {
            return false;
        }
        mThread = std::thread(&QrFinder::threadFunc, this, std::ref(processingQueue), std::ref(outQueue));
        //std::thread t = std::thread(&QrFinder::threadFunc, this, processingQueue, outQueue);
        mRun = true;
        return true;
    }

    void QrFinder::threadFunc(ImageQueue& processingQueue, ImageQueue& outQueue){
        zbar::ImageScanner scanner;
        // Configure scanner
        scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

        // Convert image to grayscale
        while(1) {

            if (processingQueue.size() < 1){
                processingQueue.wait();
            }
            try {
                auto tsFrame = processingQueue.pop();
                cv::Mat imGray;
                cv::cvtColor(tsFrame.second, imGray,cv::COLOR_BGR2GRAY);

                // Wrap image data in a zbar image
                zbar::Image image(tsFrame.second.cols, tsFrame.second.rows, "Y800", (uchar *)imGray.data, tsFrame.second.cols * tsFrame.second.rows);

                // Scan the image for barcodes and QRCodes
                int n = scanner.scan(image);

                // Print results
                for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
                {
                    if(mQrSet.find(symbol->get_data()) != mQrSet.end())
                    {
                        outQueue.push(tsFrame);
                    }

                }
            }
            catch(...){
                std::cerr << "Caught exception processing frame for QR" <<std::endl;
            }
        }
        {
            std::unique_lock<std::mutex> lock(mLock);
            mRun = false;
        }

    }

    void QrFinder::join() {
        if(mRun){
            mThread.join();
        }
    }


}

