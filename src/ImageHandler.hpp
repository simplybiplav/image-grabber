#pragma once
#include "ImageQueue.hpp"
#include "Threadbase.hpp"

namespace imggrab {
class ImageHandler: public Threadbase {
    ImageQueue& mImageQ;
    void threadFunc();
    public:
        ImageHandler(ImageQueue& imageQ);

};


}
