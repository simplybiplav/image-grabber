#include "Camera.hpp"
#include "QrFinder.hpp"
#include "ImageHandler.hpp"
using namespace std;
using namespace cv;


int main(int argc,char** argv){

    imggrab::ImageQueue camQ(2000), qrQ(2000);

    std::set<std::string> qrValues = { "https://biplav.com","https://karna.com"};

    imggrab::ImageHandler imgHander(qrQ);
    imgHander.run();
    imggrab::QrFinder qrFinder(qrValues,camQ,qrQ);
    qrFinder.run();
    imggrab::Camera cam(0,camQ);
    cam.run();
   
    imgHander.join(); 
    qrFinder.join();
    cam.join();
    return 0;
}
