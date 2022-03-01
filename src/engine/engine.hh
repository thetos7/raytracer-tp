#pragma once

#include <memory>

#include "image/image.hh"
#include "scene/scene.hh"
#include "colors/rgb.hh"

namespace raytracer
{

    std::shared_ptr<image::Image>
    raytrace(const Scene &scene, const int &height,
             const colors::RGB &background_color = colors::RGB::black());
} // namespace raytracer
