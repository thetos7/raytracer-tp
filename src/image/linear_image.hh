#pragma once

#include <memory>
#include <vector>

#include "fwd.hh"
#include "vectors/vector3.hh"

namespace image
{
    class LinearImage
    {
    public:
        using PixelColorType = vectors::Vector3;
        LinearImage(int width, int height);
        const PixelColorType &pixel_get(int x, int y) const;
        PixelColorType &pixel_get(int x, int y);
        void pixel_set(int x, int y, const PixelColorType &color);

        void save_ppm(const char *filename) const;

        void fill(PixelColorType color);

        RgbImage to_rgb() const;

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
