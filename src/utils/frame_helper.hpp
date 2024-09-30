#pragma once

#include <unordered_map>
#include <vector>
#include <opencv2/core/mat.hpp>

namespace webcam_test{
    // utility class to work with frames
    class FrameHelper{
        public:
            FrameHelper();
            ~FrameHelper();

            // hue value from traditional color picker needs to be divided by 2
            void cropByColorHue(const cv::Mat* frame, cv::Mat* output, const short& hue);

        private:
            // second and third values in hsv define saturation and brightness. Ideally they shouldn't be hardcoded but calibrated accordingly
            // because different cameras have different specs, thus you get different images quality-wise
            const short MIN_SATURATION = 180;
            const short MAX_SATURATION = 255;
            const short MIN_BRIGHTNESS = 30;
            const short MAX_BRIGHTNESS = 255;
            // store boundaries for each color so we don't have to recalculate them each tick
            // this memory is going to be stored in cpu cache and thus accessed very quickly
            std::unordered_map<short,std::vector<short>> cachedValues;
    };
}
