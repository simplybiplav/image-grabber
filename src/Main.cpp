#include "Camera.hpp"
#include "QrFinder.hpp"
using namespace std;
using namespace cv;


int main(int argc,char** argv){

    imggrab::ImageQueue camQ(2000), qrQ(2000);

    std::set<std::string> qrValues = { "https://biplav.com","https://karna.com"};
    imggrab::QrFinder qrFinder(qrValues);

    qrFinder.run(camQ,qrQ);
    imggrab::Camera cam(0);
    cam.run(camQ);
    
    return 0;
}
