#pragma once
#include "opencv2/opencv.hpp"
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace imggrab{

    typedef std::pair <std::chrono::nanoseconds, cv::Mat> TimeMatPair; //<!

    /*! \class ImageQueue ImageQueue.hpp
     *   \brief Queue to maintain pair of timestamp and cv::Mat 
     *
     */
    class ImageQueue {
        private:
            std::queue<TimeMatPair> mTsMatQ; //<! timestamp mat queue
            std::mutex mQMutex; //<! mutex for Q
            std::condition_variable mCondVar; //<! variable to wait
            int mQMaxSize; //<! max size of the Queue

        public:

            ImageQueue(int qSize);

            /// @brief push entry to the queue
            /// @param[in] entry TimeMatPair reference
            /// @return bool True if success else false
            bool push(TimeMatPair& entry);

            /// @brief push entry to the queue
            /// @param[in] entry TimeMatPair reference
            /// @return TImeMatPair value if success else throws exception
            TimeMatPair pop();

            /// @brief timed wait for queue
            /// @param[in] nanoSec wait time in nanoseconds
            /// @return bool True if an entry is pushed to queue
            bool timedWait(std::chrono::nanoseconds nanoSec);

            /// @brief blocking wait for queue
            /// @return void
            void wait();

            /// @brief returns size of Queue
            /// @return int size of Queuee
            int size();
    };


}
