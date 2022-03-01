#pragma once

#include <memory>

#include "image/image.hh"
#include "scene/scene.hh"

namespace raytracer
{

    std::shared_ptr<image::Image> raytrace(const Scene &scene,
                                           const int &height);
} // namespace raytracer