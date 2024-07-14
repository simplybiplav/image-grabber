#include "ImageHandler.hpp"
#include <sys/stat.h>
#include <sys/types.h>

namespace imggrab {

    ImageHandler::ImageHandler(ImageQueue& imageQ,std::string& dir):mImageQ(imageQ),mDir(dir){

    }
    void ImageHandler::threadFunc(){

        std::string mDir("grabbed-images");
        const int mode = S_IRWXG | S_IRWXU | S_IRWXO;
        if( mkdir(mDir.c_str(), mode) != 0 && errno != EEXIST)
        {
            std::cerr << "failed to create directory:" << mDir << std::endl;
        }
        while(1) {

            if (mImageQ.size() < 1){
                mImageQ.wait();
            }
            try {
                auto entry = mImageQ.pop();
                std::string imgFileName(std::to_string(entry.first.count())+ ".jpg");
                std::string imgFullPath(mDir + imgFileName);
                if(! cv::imwrite(imgFullPath, entry.second))
                {
                    std::cerr << "Failed to write File:" << imgFullPath <<std::endl;
                }
            }
            catch(...) {
                std::cerr << "Caught Exception:" << std::endl;
            }
        }


    }

}
