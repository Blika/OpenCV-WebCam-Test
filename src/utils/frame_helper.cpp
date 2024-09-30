#include "frame_helper.hpp"
#include <opencv2/imgproc.hpp>

namespace webcam_test{

    FrameHelper::FrameHelper(){};
    FrameHelper::~FrameHelper(){};
    
    void FrameHelper::cropByColorHue(const cv::Mat* frame, cv::Mat* output, const short& hue){
        cv::Mat mask,hsv;
        // with hsv it's easier to get boundaries for colors
        cv::cvtColor(*frame, hsv, cv::COLOR_BGR2HSV);
        // check if we've already calculated boundaries
        if(cachedValues.count(hue) == 0){
            short c1 = hue - 10;
            short c2 = hue + 10;
            // with reddish colors we need to get 2 masks
            if(c2 > 180 || c1 < 0){
                cv::Mat m1,m2;
                short c21,c22;
                // define both masks boundaries
                if(c2 > 180){
                    c22 = c2 - 180;
                    c2 = 180;
                }
                if(c1 < 0){
                    c21 = 180 + c1;
                    c1 = 0;
                }
                cachedValues[hue] = {(short)2,c1,c2,c21,c22};
                cv::inRange(hsv, cv::Scalar(c1, MIN_SATURATION, MIN_BRIGHTNESS), cv::Scalar(c2, MAX_SATURATION, MAX_BRIGHTNESS), m1);
                cv::inRange(hsv, cv::Scalar(c21, MIN_SATURATION, MIN_BRIGHTNESS), cv::Scalar(c22, MAX_SATURATION, MAX_BRIGHTNESS), m2);
                mask = m1 + m2;
            }else{
                cv::inRange(hsv, cv::Scalar(c1, MIN_SATURATION, MIN_BRIGHTNESS), cv::Scalar(c2, MAX_SATURATION, MAX_BRIGHTNESS), mask);
                cachedValues[hue] = {(short)1,c1,c2};
            }
        }else{
            // check if color should have two masks
            if(cachedValues[hue][0] == 1){
                cv::inRange(hsv, cv::Scalar(cachedValues[hue][1], MIN_SATURATION, MIN_BRIGHTNESS), cv::Scalar(cachedValues[hue][2], MAX_SATURATION, MAX_BRIGHTNESS), mask);
            }else{
                cv::Mat m1,m2;
                cv::inRange(hsv, cv::Scalar(cachedValues[hue][1], MIN_SATURATION, MIN_BRIGHTNESS), cv::Scalar(cachedValues[hue][2], MAX_SATURATION, MAX_BRIGHTNESS), m1);
                cv::inRange(hsv, cv::Scalar(cachedValues[hue][3], MIN_SATURATION, MIN_BRIGHTNESS), cv::Scalar(cachedValues[hue][4], MAX_SATURATION, MAX_BRIGHTNESS), m2);
                mask = m1 + m2;
            }
        }
        // crop image by mask
        frame->copyTo(*output,mask);
    }

}