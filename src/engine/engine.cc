#include "engine.hh"

#include <cmath>
#include <memory>

#include "colors/rgb.hh"
#include "image/image.hh"
#include "intersection/intersection.hh"
#include "lights/illumination.hh"
#include "lights/light.hh"
#include "materials/material_properties.hh"
#include "objects/object.hh"
#include "ray/ray.hh"
#include "scene/scene.hh"
#include "utils/utils.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    using image::Image;

    // TODO: change to linear image and apply correction later
    std::shared_ptr<Image> raytrace(const Scene &scene, const int &height,
                                    const colors::RGB &background_color)
    {
        using namespace colors;
        using utils::EPSILON;

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
                    // shading
                    // TODO: extract to shader function/object
                    const auto normal = intersection->normal();
                    const auto reflect_direction =
                        ray.direction - 2 * normal * ray.direction.dot(normal);
                    const auto intersection_point =
                        intersection->intersection_point();
                    const Ray reflected_ray(intersection_point
                                                + reflect_direction * EPSILON,
                                            reflect_direction);
                    const auto &props =
                        intersection->object->get_texture(*intersection);
                    auto color = vectors::Vector3::zero();
                    for (const auto &light : scene.lights())
                    {
                        const auto illumination =
                            light->get_illumination(*intersection);
                        color += props.diffuse * illumination.light_intensity;
                        if (illumination.light_direction
                            && reflect_direction.dot(
                                   *illumination.light_direction)
                                >= 0.)
                        {
                            color += props.specular
                                * illumination.light_intensity
                                * std::pow(reflect_direction.dot(
                                               *illumination.light_direction),
                                           props.specular_spread);
                        }
                    }

                    // painting
                    output->pixel_set(x, y, RGB::from_linear(color));
                }
            }
        }

        return output;
    }
} // namespace raytracer
