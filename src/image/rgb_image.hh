#pragma once

#include <string>
#include <vector>

#include "colors/fwd.hh"

namespace image
{
    class RgbImage
    {
    public:
        using PixelColorType = colors::RGB;
        RgbImage(int width, int height);

        static RgbImage load_from_png(const std::string &);
        const PixelColorType &pixel_get(int x, int y) const;
        PixelColorType &pixel_get(int x, int y);

        void pixel_set(int x, int y, const PixelColorType &color);

        void save_ppm(const char *filename) const;

        void fill(PixelColorType color);

        int get_width() const
        {
            return width_;
        };
        int get_heigth() const
        {
            return height_;
        };

    private:
        size_t pixel_index(int x, int y) const;

        int width_;
        int height_;
        std::vector<PixelColorType> pixels_;
    };
} // namespace image
