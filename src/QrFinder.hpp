#pragma once
#include <thread>
#include "ImageQueue.hpp"

namespace imggrab {


class QrFinder {

    private:
        std::mutex mLock;
        std::set<std::string> mQrSet;
        std::thread mThread;
        bool mRun;
        void threadFunc(ImageQueue& processingQueue, ImageQueue& outQueue);
    public:
       QrFinder(const std::set<std::string>& qrSet);

       bool run(ImageQueue& processingQueue, ImageQueue& outQueue);

       void join();
};


}
