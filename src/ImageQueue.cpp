#include "ImageQueue.hpp"

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
            TimeMatPair& val = mTsMatQ.front();
            mTsMatQ.pop();
            return val;
        }
        else {
            throw "No item in Queue";
        }
    }

    bool ImageQueue::push(TimeMatPair& entry){
        std::unique_lock<std::mutex> lock(mQMutex);
        if ( mTsMatQ.size() >= mQMaxSize ) {
            return false;
        }
        else {
            mTsMatQ.push(entry);
            return true;
        }
        mCondVar.notify_all();
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
        mCondVar.notify_all();
    }


}
