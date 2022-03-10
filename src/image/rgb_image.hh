#pragma once

#include <vector>

#include "colors/fwd.hh"

namespace image
{
    class RgbImage
    {
    public:
        using PixelColorType = colors::RGB;
        RgbImage(int width, int height);

        const PixelColorType &pixel_get(int x, int y) const;
        PixelColorType &pixel_get(int x, int y);

        void pixel_set(int x, int y, const PixelColorType &color);

        void save_ppm(const char *filename) const;

        void fill(PixelColorType color);

    private:
        size_t pixel_index(int x, int y) const;

        int width_;
        int height_;
        std::vector<PixelColorType> pixels_;
    };
} // namespace image
