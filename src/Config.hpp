#pragma once
#include <set>
#include <string>

namespace imggrab {


    /*! \class Config Config.hpp
     *   \brief parses argument , validates and prints help
     *
     */
    struct Config {

        int mCamIdx; //!< camera index
        int mFps; //!< fps camera
        int mWidth; //!< frame width
        int mHeight; //!< frame height
        std::string mDirectory; //!< directory to save image
        std::set<std::string> mQrList; //!< qr values to scan

        /// @brief default constructor
        Config();

        /// @brief prints help about argument
        void help();

        /// @brief exit program
        void exit();

        /// @brief check if configuration is good
        bool valid();

        /// @brief arguments passed
        /// @param[in] argc count
        /// @param[in] argv arguments
        void parse(int argc, char** argv);

    };

}
