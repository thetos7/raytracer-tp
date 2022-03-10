#include "engine.hh"

#include <cmath>
#include <memory>

#include "colors/rgb.hh"
#include "image/linear_image.hh"
#include "intersection/intersection.hh"
#include "lights/illumination.hh"
#include "lights/light.hh"
#include "materials/material_properties.hh"
#include "objects/object.hh"
#include "ray/ray.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    using Image = image::LinearImage;

    // TODO: change to linear image and apply correction later
    std::shared_ptr<Image> raytrace(const Scene &scene, const int &height,
                                    const int max_depth,
                                    const vectors::Vector3 &background_color)
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
                const auto color = scene.sample_color(ray, max_depth);

                // painting
                if (color)
                {
                    output->pixel_set(x, y, *color);
                }
            }
        }

        return output;
    }
} // namespace raytracer
