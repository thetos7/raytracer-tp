#include "shader_material.hh"

#include "intersection/intersection.hh"

namespace raytracer::materials
{
    using ShaderProgram = ShaderMaterial::ShaderProgram;

    ShaderMaterial::ShaderMaterial(ShaderProgram shader)
        : shader_{ shader }
    {}

    const MaterialProperties
    ShaderMaterial::get_point_properties(Intersection intersection) const
    {
        using namespace vectors;
        MaterialProperties props(Vector3::zero(), Vector3::zero(), 0,
                                 Vector3::zero());
        shader_(intersection, props);
        return props;
    }
} // namespace raytracer::materials
