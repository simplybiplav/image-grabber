#include <zbar.h>
#include "QrFinder.hpp"


namespace imggrab {


    QrFinder::QrFinder(const std::set<std::string>& qrSet,ImageQueue& inQueue, ImageQueue& outQueue):mQrSet(qrSet),inQ(inQueue),outQ(outQueue) {
        mRun = false;
    }

    void QrFinder::threadFunc(){
        StartEndPrint threadStatus(std::string("QrFinder Thread")); 
        zbar::ImageScanner scanner;
        // Configure scanner
        scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

        // Convert image to grayscale
        while(mRun) {

            if (inQ.size() < 1){
                inQ.wait();
            }
            try {
                auto tsFrame = inQ.pop();
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
                        outQ.push(tsFrame);
                    }

                }
            }
            catch (const std::exception &exc)
            {
                // catch anything thrown within try block that derives from std::exception
                std::cerr << "QR Thread:" << exc.what();
            }
            catch(...){
                std::cerr << "Caught exception processing frame for QR" <<std::endl;
            }
        }

    }


}

