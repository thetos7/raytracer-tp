
#include <fstream>
#include <iostream>

#include "colors/rgb.hh"
#include "image/image.hh"

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
    return 0;
}