#pragma once
#include <thread>
#include "ImageQueue.hpp"
#include "Threadbase.hpp"

namespace imggrab {


class QrFinder: public Threadbase {

    private:
        std::set<std::string> mQrSet;
        ImageQueue& inQ;
        ImageQueue& outQ;
        void threadFunc();
    public:
       QrFinder(const std::set<std::string>& qrSet,ImageQueue& inQueue, ImageQueue& outQueue);
};


}
