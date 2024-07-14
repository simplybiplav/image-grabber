#pragma once
#include <thread>
#include "ImageQueue.hpp"
#include "Threadbase.hpp"

namespace imggrab {


    /*! \class QrFinder QrFinder.hpp
     *   \brief finds QR values in image frames and outs those frame
     *
     */
    class QrFinder: public Threadbase {

        private:
            std::set<std::string> mQrSet; //!< set to store qr strings
            ImageQueue& inQ; //!< incoming queue
            ImageQueue& outQ; //!< outgoing queue

            /// @brief processed incoming queue and finds image frame which has any qr value
            /// @return void
            void threadFunc();
        public:

            /// @brief constructor
            /// @param[in] qrSet set of QR to be found
            /// @param[in] inQueue queue to be processed
            /// @param[inout] outQueue queue of frame which has any of the qr value
            QrFinder(const std::set<std::string>& qrSet,ImageQueue& inQueue, ImageQueue& outQueue);
    };


}
