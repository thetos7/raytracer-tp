#include "rgb_image.hh"

#include <fstream>
#include <ostream>
#include <vector>

#include "colors/rgb.hh"
#include "image/lodepng.hh"

namespace image
{
    using PixelColorType = RgbImage::PixelColorType;

    RgbImage::RgbImage(int width, int height)
        : width_{ width }
        , height_{ height }
        , pixels_{ std::vector<PixelColorType>(width * height) }
    {}

    RgbImage RgbImage::load_from_png(const std::string &path)
    {
        std::vector<unsigned char> raw_image; // RGBA,RGBA,RGBA... vector
        unsigned width;
        unsigned height;
        lodepng::decode(raw_image, width, height, path);
        auto rgb_image = RgbImage(width, height);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++) {
                int index = i * (4 * width) + (j * 4);
                PixelColorType c = PixelColorType(raw_image[index], raw_image[index + 1], raw_image[index + 2]);
                rgb_image.pixel_set(j, i, c);
            }
        }
        return rgb_image;
    }

    size_t RgbImage::pixel_index(int x, int y) const
    {
        return x + y * width_;
    }

    const PixelColorType &RgbImage::pixel_get(int x, int y) const
    {
        return pixels_[pixel_index(x, y)];
    }

    PixelColorType &RgbImage::pixel_get(int x, int y)
    {
        return pixels_[pixel_index(x, y)];
    }

    void RgbImage::pixel_set(int x, int y, const PixelColorType &color)
    {
        pixels_[pixel_index(x, y)] = color;
    }

    void RgbImage::save_ppm(const char *filename) const
    {
        using std::ios;
        std::ofstream outfile;
        outfile.open(filename, ios::out | ios::trunc);
        if (outfile.is_open())
        {
            outfile << "P6\n" << width_ << " " << height_ << "\n255\n";
            for (auto it = pixels_.begin(); it != pixels_.end(); it++)
            {
                PixelColorType pixel = *it;
                outfile << static_cast<char>(pixel.r)
                        << static_cast<char>(pixel.g)
                        << static_cast<char>(pixel.b);
            }
            outfile.close();
        }
    }

    void RgbImage::fill(PixelColorType color)
    {
        for (auto &pixel : pixels_)
        {
            pixel = color;
        }
    }

} // namespace image
