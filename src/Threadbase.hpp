#pragma once
#include <mutex>
#include <thread>
#include <atomic>

/*! \class Threadbase Threadbase.hpp
 *   \brief abstract class for running a thread
 *
 */
class Threadbase{

    protected:
        std::atomic<bool> mRun; //!< execute value
        std::thread mThread; //!< store thread object

        /// @brief virtual function which derived class has to define to run a thread
        virtual void threadFunc() = 0;
    public:
        /// @brief spwan a thread
        /// @return bool if success
        bool run(){
            try {
                if (mRun) throw "Already Running";
                mThread = std::thread(&Threadbase::threadFunc, this);
                mRun = true;
                return true;
            }
            catch(...) {

                return false;
            }
        }
        void stop(){
            mRun = false;
        }
        void join(){
            mThread.join();
        }

};
