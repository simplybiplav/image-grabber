#pragma once
#include <mutex>
#include <thread>
#include <atomic>
#include <exception>

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
                if (mRun) throw std::runtime_error("Already Running a Thread");
                mThread = std::thread(&Threadbase::threadFunc, this);
                mRun = true;
                return true;
            }
            catch (const std::exception &exc)
            {
                std::cerr << "ThreadBase:"<< exc.what() << std::endl;
                return false;
            }
            catch(...) {

                std::cerr << "ThreadBase: caught exception" <<std::endl;
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

class StartEndPrint{
        std::string mPrint;
    public:
        StartEndPrint(std::string val){
            mPrint = val;
            std::cout << "Started: " <<mPrint<<std::endl;
        }
        ~StartEndPrint(){
            std::cout << "Ended: " <<mPrint<<std::endl;
        }

};
