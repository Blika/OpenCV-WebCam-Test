#pragma once

#include <opencv2/videoio.hpp>

namespace webcam_test{
    
    class FrameHelper;
    class StreamHandler{
        public:
			StreamHandler();
			~StreamHandler();

            void shutdown();
            void run();

        private:
            const char* WINDOW_NAME = "webcam_test";
            bool stopped = false;
            FrameHelper* frameHelper;
            cv::VideoCapture cam;
            cv::Mat frame;
    };
}