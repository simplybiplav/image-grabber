#pragma once
#include "ImageQueue.hpp"
#include "Threadbase.hpp"

namespace imggrab {



    /*! \class ImageHandler ImageHandler.hpp
     *   \brief for parsing argument
     *
     */
    class ImageHandler: public Threadbase {
        ImageQueue& mImageQ; //!< image queue
        std::string mDir; //!< directory to save images

        /// @brief arguments passed
        /// @param[in] argc count
        /// @param[in] argv arguments
        void threadFunc();
        public:

        /// @brief constructor
        ImageHandler(ImageQueue& imageQ,std::string& dir);

    };


}
