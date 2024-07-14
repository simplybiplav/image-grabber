#include "Camera.hpp"
#include <exception>


namespace imggrab {

    void Camera::threadFunc() {
        StartEndPrint threadStatus(std::string("Camera Thread")); 
        cv::VideoCapture cam(mCamId,cv::CAP_V4L2);
        if(mFps != 0 ){
            cam.set( cv::CAP_PROP_FPS, mFps);
        }
        if(mFrameWidth != 0 && mFrameHeight !=0){
            cam.set( cv::CAP_PROP_FRAME_WIDTH, mFrameWidth);
            cam.set( cv::CAP_PROP_FRAME_HEIGHT, mFrameHeight);
        }
        if(!cam.isOpened()){
            std::cerr << "camera is not opened" <<std::endl;
            throw std::runtime_error("Unable to create directory");
        }
        while(mRun) {

            try {
                cv::Mat frame;
                cam >> frame;
                if(!frame.empty()) {
                    std::chrono::nanoseconds ts = std::chrono::duration_cast<std::chrono::nanoseconds> ( std::chrono::system_clock::now().time_since_epoch());
                    auto entry =std::make_pair(ts,frame);
                    mImageQ.push(entry);
                }
                else{
                    std::cerr << "Empty Frame "<<std::endl;
                }
            }
            catch (const std::exception &exc)
            {
                std::cerr << "Camera thread:" << exc.what() << std::endl;
            }
            catch(...) {
                std::cerr << "Caught error while caputring image "<<std::endl;
            }

        }
    }

    Camera::Camera(int camId,int fps, int width, int height,ImageQueue& imageQ):mFps(fps),mFrameWidth(width),mFrameHeight(height),mCamId(camId),mImageQ(imageQ){
        mRun = false;
    }


}
