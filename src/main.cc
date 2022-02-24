
#include <fstream>
#include <iostream>

#include "utils/colors/rgb.hh"
#include "utils/image/image.hh"

int main(int argc, char *argv[])
{
    using Image = image::Image;
    constexpr int width = 256;
    constexpr int height = 256;
    Image img = Image{ width, height };
    const colors::RGB white = colors::RGB{ 255, 255, 255 };
    for (int i = 0; i < width; ++i)
    {
        img.pixel_set(i, i, white);
    }
    std::cout << "white = " << white << std::endl;
    std::cout << "pixel 0,0 = " << img.pixel_get(0, 0) << std::endl;
    std::cout << "pixel 1,0 = " << img.pixel_get(1, 0) << std::endl;

    img.save_ppm("./test.ppm");
    std::ofstream debug_file("pixels.txt", std::ios::out | std::ios::trunc);
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            debug_file << img.pixel_get(x, y) << (x == (width - 1) ? "" : ", ");
        }
        debug_file << "\n";
    }
    debug_file.close();
    return 0;
}