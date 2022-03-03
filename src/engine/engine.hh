#pragma once

#include <memory>

#include "colors/rgb.hh"
#include "image/fwd.hh"
#include "scene/fwd.hh"

namespace raytracer
{

    std::shared_ptr<image::Image>
    raytrace(const Scene &scene, const int &height,
             const colors::RGB &background_color = colors::RGB::black());
} // namespace raytracer
