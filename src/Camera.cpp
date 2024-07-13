#include "Camera.hpp"


namespace imggrab {

    void Camera::threadFunc() {
        cv::VideoCapture cam(mCamId);
        cam.set( cv::CAP_PROP_FPS, mFps);
        cam.set( cv::CAP_PROP_FRAME_WIDTH, mFrameWidth);
        cam.set( cv::CAP_PROP_FRAME_HEIGHT, mFrameHeight);
        cam.set( cv::CAP_PROP_BRIGHTNESS, mBrightness);

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

    Camera::Camera(int camId,ImageQueue& imageQ):mFps(30),mFrameWidth(480),mFrameHeight(360),mBrightness(1),mCamId(camId),mImageQ(imageQ){
    }

    void Camera::setParams(int fps, int width, int height, int brightness) {
        mFps = fps;
        mFrameWidth = width;
        mFrameHeight = height;
        mBrightness = brightness;
    }


}
