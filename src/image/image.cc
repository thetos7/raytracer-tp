#include "image.hh"

#include <fstream>
#include <iostream>
#include <vector>

#include "colors/rgb.hh"

namespace image
{
    Image::Image(int width, int height)
        : width_{ width }
        , height_{ height }
        , pixels_{ std::vector<colors::RGB>(width * height) }
    {}

    size_t Image::pixel_index(int x, int y)
    {
        return x + y * width_;
    }

    colors::RGB &Image::pixel_get(int x, int y)
    {
        return pixels_[pixel_index(x, y)];
    }

    void Image::pixel_set(int x, int y, const colors::RGB &color)
    {
        pixels_[pixel_index(x, y)] = color;
    }

    void Image::save_ppm(const char *filename) const
    {
        using std::ios;
        std::ofstream outfile;
        outfile.open(filename, ios::out | ios::trunc);
        if (outfile.is_open())
        {
            outfile << "P6\n" << width_ << " " << height_ << "\n255\n";
            for (auto it = pixels_.begin(); it != pixels_.end(); it++)
            {
                colors::RGB pixel = *it;
                outfile << static_cast<char>(pixel.r)
                        << static_cast<char>(pixel.g)
                        << static_cast<char>(pixel.b);
            }
            outfile.close();
        }
    }

    void Image::fill(colors::RGB color)
    {
        for (auto &pixel : pixels_)
        {
            pixel = color;
        }
    }

} // namespace image
