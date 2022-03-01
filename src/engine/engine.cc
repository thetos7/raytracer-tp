#include "engine.hh"

#include <cmath>
#include <memory>

#include "colors/rgb.hh"
#include "image/image.hh"
#include "scene/scene.hh"

namespace raytracer
{
    using image::Image;
    std::shared_ptr<Image> raytrace(const Scene &scene, const int &height,
                                    const colors::RGB &background_color)
    {
        using namespace colors;
        const auto &camera = scene.camera();
        const auto width =
            static_cast<int>(std::round(camera.aspectRatio * height));
        auto output = std::make_shared<Image>(width, height);
        output->fill(background_color);

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
                    + ((height - y) - floatImageHeightHalf) * camera.up
                        * pixelSize;

                const auto rayDirection = rayOrigin - camera.position;

                const Ray ray{ rayOrigin, rayDirection };
                auto intersection = scene.cast_ray(ray);
                if (intersection)
                {
                    auto &props =
                        intersection->object->get_texture(*intersection);
                    auto color = vectors::Vector3::zero();
                    for (const auto &light : scene.lights())
                    {
                        color += props.diffuse
                            * light->get_illumination(*intersection);
                    }
                    output->pixel_set(x, y, RGB::from_linear(color));
                }
            }
        }

        return output;
    }
} // namespace raytracer
