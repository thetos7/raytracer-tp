#pragma once

#include <memory>

#include "image/fwd.hh"
#include "scene/fwd.hh"
#include "vectors/vector3.hh"

namespace raytracer
{

    std::shared_ptr<image::LinearImage>
    raytrace(const Scene &scene, const int &height,
    const int max_depth, bool debug_print = false, int progress_print_step = 5,
             const vectors::Vector3 &background_color = vectors::Vector3::zero());
} // namespace raytracer
