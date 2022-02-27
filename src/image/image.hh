#pragma once

#include <vector>

#include "colors/rgb.hh"

namespace image
{
    class Image
    {
    public:
        Image(int width, int height);
        colors::RGB &pixel_get(int x, int y);
        void pixel_set(int x, int y, const colors::RGB &color);

        void save_ppm(const char *filename);

    private:
        size_t pixel_index(int x, int y);

        int width_;
        int height_;
        std::vector<colors::RGB> pixels_;
    };
} // namespace image
