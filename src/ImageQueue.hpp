#pragma once
#include "opencv2/opencv.hpp"
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace imggrab{ 

typedef std::pair <std::chrono::nanoseconds, cv::Mat> TimeMatPair; //<! 

class ImageQueue {
    private:
        std::queue<TimeMatPair> mTsMatQ; //<! timestamp mat queue 
        std::mutex mQMutex; //<! mutex for Q 
        std::condition_variable mCondVar; //<! variable to wait
        int mQMaxSize; //<! max size of the Queue 

    public:
        /*!
            \param[in] qSize size for Q 
        */
        
        ImageQueue(int qSize);

        /*!
            \param[in] entry pair to push into queue
        */
        bool push(TimeMatPair& entry);

        /*!
            \param[inout] entry get pair
        */
        TimeMatPair pop();

        /*!
        */
        bool timedWait(std::chrono::nanoseconds nanoSec);
        void wait();
        int size();
};


}
