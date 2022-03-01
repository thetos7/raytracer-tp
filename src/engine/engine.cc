#include "engine.hh"

#include <cmath>
#include <memory>

#include "image/image.hh"
#include "scene/scene.hh"

namespace raytracer
{
    using image::Image;
    std::shared_ptr<Image> raytrace(const Scene &scene, const int &height)
    {
        using namespace colors;
        const auto &camera = scene.camera();
        const auto width =
            static_cast<int>(std::round(camera.aspectRatio * height));
        auto output = std::make_shared<Image>(width, height);
        const auto imagePlaneWidthHalf =
            std::tan(camera.fov / 2.) * camera.zMin;
        const auto imagePlaneWidth = imagePlaneWidthHalf * 2;
        const auto pixelSize = imagePlaneWidth / width;
        const auto imagePlaneCenter =
            camera.position + camera.forward * camera.zMin;
        const auto floatImageWidthHalf = static_cast<double>(width) / 2;
        const auto floatImageHeightHalf = static_cast<double>(height) / 2;

        for (auto y = 0; y < height; ++y)
        {
            for (auto x = 0; x < width; ++x)
            {
                const auto rayOrigin = imagePlaneCenter
                    + (x - floatImageWidthHalf) * camera.right * pixelSize
                    + (y - floatImageHeightHalf) * camera.up * pixelSize;
                // std::cout << "ray origin: " << rayOrigin << "\n";
                const auto rayDirection = rayOrigin - camera.position;

                const Ray ray{ rayOrigin, rayDirection };
                auto intersection = scene.cast_ray(ray);
                if (intersection)
                {
                    output->pixel_set(x, y, RGB::white());
                }
            }
        }

        return output;
    }
} // namespace raytracer
