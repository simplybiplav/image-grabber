#include "Camera.hpp"


namespace imggrab {

    void Camera::threadFunc() {
        cv::VideoCapture cam(mCamId);
        if(mFps != 0 ){
            cam.set( cv::CAP_PROP_FPS, mFps);
        }
        if(mFrameWidth != 0 && mFrameHeight !=0){
            cam.set( cv::CAP_PROP_FRAME_WIDTH, mFrameWidth);
            cam.set( cv::CAP_PROP_FRAME_HEIGHT, mFrameHeight);
        }
        while(mRun) {

            try {
                cv::Mat frame;
                cam >> frame;
                std::chrono::nanoseconds ts = std::chrono::duration_cast<std::chrono::nanoseconds> ( std::chrono::system_clock::now().time_since_epoch());
                auto entry =std::make_pair(ts,frame);
                mImageQ.push(entry);
            }
            catch(...) {
                std::cerr << "Caught error while caputring image "<<std::endl;
            }

        }
    }

    Camera::Camera(int camId,int fps, int width, int height,ImageQueue& imageQ):mFps(fps),mFrameWidth(width),mFrameHeight(height),mCamId(camId),mImageQ(imageQ){
    }


}
