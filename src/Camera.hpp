#pragma once
#include <thread>
#include "ImageQueue.hpp"

/*! \class Camera Camera.hpp
 *   \brief for video source
 *
 */

namespace imggrab {

class Camera {

    private:
        int mFps; //!< Fps Of camera
        int mFrameWidth; //!< Image Frame Width
        int mFrameHeight; //!< Image Frame Height
        int mBrightness; //!< camera's Brightness
        int mCamId; //!< camera Source Id
        std::thread mThread; //!< thread object
        bool mThreadRun; //!< variable to run while loop
        void capture(ImageQueue& outQueue);
    public:
        /*! A constructor
            \param[in] video source index
        */
        Camera(int camId);


        /*! Sets parameters for camera and frame

            \param[in] fps The fps of camera     
            \param[in] width The width of the image frame
            \param[in] height The Height of the image frame
            \param[in] brightness The brightness of the camera
            \param[in] autoExposure The auto exposure of the camera
            \param[in] exposureTime The exposure time of the camera
            \param[in] gain The gain of the camera
            \return void returns nothingd

        */
        void setParams(int fps, int width, int height, int brightness);


        bool run(ImageQueue& outQueue); 
        void stop();
        void join();


};









}
