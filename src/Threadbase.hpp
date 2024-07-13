#pragma once
#include <mutex>
#include <thread>
class Threadbase{

    protected:
        std::mutex mLock;
        bool mRun;
        std::thread mThread;
        virtual void threadFunc() = 0;
    public:
        bool run(){
            try {
                std::unique_lock<std::mutex> lock(mLock);
                mThread = std::thread(&Threadbase::threadFunc, this);
                mRun = true;
                return true;
            }
            catch(...) {

                return false;
            }
        }
        void stop(){
            std::unique_lock<std::mutex> lock(mLock);
            mRun = false;
        }
        void join(){
            mThread.join();
        }

};
