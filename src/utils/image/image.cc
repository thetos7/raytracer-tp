#include "image.hh"

#include <fstream>
#include <iostream>
#include <vector>

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

    void Image::save_ppm(const char *filename)
    {
        using std::ios;
        std::ofstream outfile;
        outfile.open(filename, ios::out | ios::trunc);
        if (outfile.is_open())
        {
            outfile << "P6 " << width_ << " " << height_ << " 255\n";
            for (size_t y = 0; y < height_; ++y)
            {
                for (size_t x = 0; x < width_; ++x)
                {
                    colors::RGB pixel = pixel_get(x, y);
                    outfile << static_cast<char>(pixel.r)
                            << static_cast<char>(pixel.g)
                            << static_cast<char>(pixel.b);
                }
                outfile << '\n';
            }
            outfile.close();
        }
    }

} // namespace image