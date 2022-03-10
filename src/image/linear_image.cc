#include "linear_image.hh"

#include "colors/rgb.hh"
#include "rgb_image.hh"

namespace image
{
    using PixelColorType = LinearImage::PixelColorType;

    LinearImage::LinearImage(int width, int height)
        : width_{ width }
        , height_{ height }
        , pixels_{ std::vector<PixelColorType>(width * height) }
    {}

    size_t LinearImage::pixel_index(int x, int y) const
    {
        return x + y * width_;
    }

    const PixelColorType &LinearImage::pixel_get(int x, int y) const
    {
        return pixels_[pixel_index(x, y)];
    }

    PixelColorType &LinearImage::pixel_get(int x, int y)
    {
        return pixels_[pixel_index(x, y)];
    }

    void LinearImage::pixel_set(int x, int y, const PixelColorType &color)
    {
        pixels_[pixel_index(x, y)] = color;
    }

    void LinearImage::save_ppm(const char *filename) const
    {
        to_rgb().save_ppm(filename);
    }

    RgbImage LinearImage::to_rgb() const
    {
        RgbImage out(width_, height_);
        for (auto y = 0; y < height_; ++y)
        {
            for (auto x = 0; x < width_; ++x)
            {
                out.pixel_set(x, y, colors::RGB::from_linear(pixel_get(x, y)));
            }
        }
        return out;
    }

    void LinearImage::fill(PixelColorType color)
    {
        for (auto &pixel : pixels_)
        {
            pixel = color;
        }
    }

} // namespace image
