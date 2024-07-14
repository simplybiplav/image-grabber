#include "ImageQueue.hpp"
#include <exception>

namespace imggrab {

    ImageQueue::ImageQueue(int qSize):mQMaxSize(qSize) {
    }

    int ImageQueue::size() {
        std::unique_lock<std::mutex> lock(mQMutex);
        return mTsMatQ.size();

    }

    TimeMatPair ImageQueue::pop(){
        std::unique_lock<std::mutex> lock(mQMutex);
        if ( mTsMatQ.size() > 0 ) {
            TimeMatPair val = mTsMatQ.front();
            mTsMatQ.pop();
            return val;
        }
        else {
            throw std::underflow_error("No item in Queue");
        }
    }

    bool ImageQueue::push(TimeMatPair& entry){
        std::unique_lock<std::mutex> lock(mQMutex);
        if ( mTsMatQ.size() >= mQMaxSize ) {
            return false;
        }
        else {
            mTsMatQ.push(entry);
            mCondVar.notify_all();
            return true;
        }
    }


    bool ImageQueue::timedWait(std::chrono::nanoseconds nanoSec){
        std::unique_lock<std::mutex> lock(mQMutex);
        if (mCondVar.wait_for(lock,nanoSec) == std::cv_status::timeout ){
            return false;
        }
        return true;
    }

    void ImageQueue::wait(){
        std::unique_lock<std::mutex> lock(mQMutex);
        mCondVar.wait(lock);
    }


}
