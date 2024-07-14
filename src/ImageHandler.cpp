#include "ImageHandler.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>

namespace imggrab {

    ImageHandler::ImageHandler(ImageQueue& imageQ,std::string& dir):mImageQ(imageQ),mDir(dir){
        mRun = false;
    }
    void ImageHandler::threadFunc(){
        StartEndPrint threadStatus(std::string("Image Handler Thread")); 
        const int mode = S_IRWXG | S_IRWXU | S_IRWXO;
        if( mkdir(mDir.c_str(), mode) != 0 && errno != EEXIST)
        {
            std::cerr << "failed to create directory:" << mDir << std::endl;
            throw std::runtime_error("Unable to create directory");
        }
        while(mRun) {

            if (mImageQ.size() < 1){
                mImageQ.wait();
            }
            try {
                auto entry = mImageQ.pop();
                std::string imgFileName(std::to_string(entry.first.count())+ ".jpg");
                std::string imgFullPath(mDir +"/"+ imgFileName);
                if(! cv::imwrite(imgFullPath, entry.second))
                {
                    std::cerr << "Failed to write File:" << imgFullPath <<std::endl;
                }
                else{
                    std::cout << "File created:" << imgFullPath <<std::endl;
                }
            }
            catch (const std::exception &exc)
            {
                std::cerr << "ImageHandler thread:" << exc.what() << std::endl;
            }
            catch(...) {

                std::cerr << "ImageHandler: caught exception" <<std::endl;
            }
        }

        std::cout << "Image Handler Thread: ended" <<std::endl;

    }

}
