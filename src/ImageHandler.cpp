#include "ImageHandler.hpp"
#include <sys/stat.h>
#include <sys/types.h>

namespace imggrab {

    ImageHandler::ImageHandler(ImageQueue& imageQ):mImageQ(imageQ){

    }
    void ImageHandler::threadFunc(){

        std::string dir("grabbed-images");
        const int mode = S_IRWXG | S_IRWXU | S_IRWXO;
        if( mkdir(dir.c_str(), mode) != 0 && errno != EEXIST)
        {
            std::cerr << "failed to create directory:" << dir << std::endl;
        }
        while(1) {

            if (mImageQ.size() < 1){
                mImageQ.wait();
            }
            try {
                auto entry = mImageQ.pop();
                std::string imgFileName(std::to_string(entry.first.count())+ ".jpg");
                std::string imgFullPath(dir + imgFileName);
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
