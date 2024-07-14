#pragma once
#include <thread>
#include "ImageQueue.hpp"
#include "Threadbase.hpp"

/*! \class Camera Camera.hpp
 *   \brief for video source
 *
 *  Intiate camera and put frames in queue
 */

namespace imggrab {

    class Camera:public Threadbase {

        private:
            int mFps; //!< Fps Of camera
            int mFrameWidth; //!< Image Frame Width
            int mFrameHeight; //!< Image Frame Height
            int mCamId; //!< camera Source Id
            std::thread mThread; //!< thread object
            ImageQueue& mImageQ; //!< queue to put frames

            /// @brief function to capture frame and put into queue
            void threadFunc();
        public:

            /// @brief constructor
            /// @param[in] camId camera index
            /// @param[in] fps fps of camera
            /// @param[in] width frame width
            /// @param[in] height camera height
            /// @param[in] imageQ image Queue
            Camera(int camId,int fps, int width, int height, ImageQueue& imageQ); //!< constructor

    };





}
