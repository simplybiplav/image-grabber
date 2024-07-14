#include "Config.hpp"
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

namespace imggrab {

    Config::Config() {
        mCamIdx = 0;
        mFps = 0;
        mWidth = 0;
        mHeight = 0;

    }
    void Config::help(){
        std::cout << " -h | --help" <<std::endl;
        std::cout << " --cam [camera Index]" <<std::endl;
        std::cout << " --fps [fps value]" <<std::endl;
        std::cout << " --width [frame width value]" <<std::endl;
        std::cout << " --height [frame height value]" <<std::endl;
        std::cout << " --dir [directory name to save image]" <<std::endl;
        std::cout << " --qr [QR value to grab]" <<std::endl;

    }
    bool Config::valid(){
        if(mCamIdx < 0 || mDirectory.empty() || mQrList.empty() || mFps < 0 || mWidth < 0 || mHeight < 0) return false;

        if(( mWidth >0 && mHeight == 0) || (mWidth == 0 && mHeight > 0)) return false;
        return true;

    }

    void Config::exit(){
        _exit(-1);
    }

    void Config::parse(int argc, char** argv){
        try{
            std::vector<std::string> args(argv + 1, argv + argc);
            std::vector<std::string>::iterator it;
            for(it= args.begin(); it != args.end(); ++it){
                if (it->compare("--help")==0 || it->compare("-h") == 0){
                    throw "Invalid Argument";
                }else if(it->compare("--cam")==0){
                    if(++it == args.end()) throw "Invalid Argument";
                    mCamIdx = std::stoi((*it).c_str());

                }else if(it->compare("--fps")==0){
                    if(++it == args.end()) throw "Invalid Argument";
                    mFps = std::stoi((*it).c_str());

                }else if(it->compare("--width")==0){
                    if(++it == args.end()) throw "Invalid Argument";
                    mWidth = std::stoi((*it).c_str());

                }else if(it->compare("--height")==0){
                    if(++it == args.end()) throw "Invalid Argument";
                    mHeight = std::stoi((*it).c_str());

                }else if(it->compare("--dir")==0){
                    if(++it == args.end()) throw "Invalid Argument";
                    mDirectory = *it;

                }else if(it->compare("--qr")==0){
                    if(++it == args.end()) throw "Invalid Argument";
                    mQrList.insert(*it);

                }
                else {
                    throw "Invalid Argument";
                }

            }
            if(!valid()) throw "Invalid Argument";
        }
        catch(...){
            help();
            exit();
        }

    }


}
