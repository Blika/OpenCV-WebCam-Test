#include "stream_handler.hpp"
#include "../utils/frame_helper.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdexcept>

namespace webcam_test{

    StreamHandler::StreamHandler(){
        // open default camera
        cam = cv::VideoCapture(0);
        if(!cam.isOpened()){
			throw std::runtime_error("no camera found");
        }
        // create a window for stream
        cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

        frameHelper = new FrameHelper();
    }

    StreamHandler::~StreamHandler(){
        if(!stopped) shutdown();
    }

    // cleaning up
    void StreamHandler::shutdown(){
        stopped = true;
        cv::destroyWindow(WINDOW_NAME);
        delete frameHelper;
    }

    // main loop
    void StreamHandler::run(){
        while(true){
            // check if program should stop
            if(stopped) break;
            // get frame from camera
            cam >> frame;
            if(frame.empty()){
                shutdown();
                break;
            }
            // crop by red
            cv::Mat cropped;
            frameHelper->cropByColorHue(&frame, &cropped, 0);
            if(cropped.empty()){
                frame.release();
                continue;
            }
            // display cropped image
            cv::imshow(WINDOW_NAME, cropped);
            // a little delay so the image is displayed and input is processed if given
            char k = cv::waitKey(10);
            // esc to quit
            if(k == 27){
                shutdown();
                break;
            }
            frame.release();
        }
    }

}