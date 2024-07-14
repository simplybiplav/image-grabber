#include "Camera.hpp"
#include "QrFinder.hpp"
#include "ImageHandler.hpp"
#include "Config.hpp"
using namespace std;
using namespace cv;


int main(int argc,char** argv){

    imggrab::Config config;
    config.parse(argc,argv);
    imggrab::ImageQueue camQ(2000), qrQ(2000);

    imggrab::ImageHandler imgHander(qrQ,config.mDirectory);
    imgHander.run();
    imggrab::QrFinder qrFinder(config.mQrList,camQ,qrQ);
    qrFinder.run();
    imggrab::Camera cam(config.mCamIdx,config.mFps,config.mWidth,config.mHeight,camQ);
    cam.run();
    imgHander.join(); 
    qrFinder.join();
    cam.join();
    return 0;
}
