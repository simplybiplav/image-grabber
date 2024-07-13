#pragma once
#include <thread>
#include "ImageQueue.hpp"
#include "Threadbase.hpp"

/*! \class Camera Camera.hpp
 *   \brief for video source
 *
 */

namespace imggrab {

class Camera:public Threadbase {

    private:
        int mFps; //!< Fps Of camera
        int mFrameWidth; //!< Image Frame Width
        int mFrameHeight; //!< Image Frame Height
        int mBrightness; //!< camera's Brightness
        int mCamId; //!< camera Source Id
        std::thread mThread; //!< thread object
        ImageQueue& mImageQ;
        void threadFunc();
    public:
        /*! A constructor
            \param[in] video source index
            \param[in] imageQ queue for image
        */
        Camera(int camId,ImageQueue& imageQ);


        /*! Sets parameters for camera and frame

            \param[in] fps The fps of camera     
            \param[in] width The width of the image frame
            \param[in] height The Height of the image frame
            \param[in] brightness The brightness of the camera
            \return void returns nothingd

        */
        void setParams(int fps, int width, int height, int brightness);

};









}
