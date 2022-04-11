#include "rot_matrix3.hh"

#include <cmath>

namespace vectors {
    RotMatrix3::RotMatrix3(double x, double y, double z) {
        matrix[0][0] = cos(x) * cos(y);
        matrix[0][1] = cos(x) * sin(y) * sin(z) - sin(x) * cos(z);
        matrix[0][2] = cos(x) * sin(y) * cos(z) + sin(x) * sin(y);
        matrix[1][0] = sin(x) * cos(y);
        matrix[1][1] = sin(x) * sin(y) * sin(z) + cos(x) * cos(z);
        matrix[1][2] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z);
        matrix[2][0] = - sin(y);
        matrix[2][1] = cos(y) * sin(z);
        matrix[2][2] = cos(y) * cos(z);
    }

    RotMatrix3 RotMatrix3::Identity() {
        return RotMatrix3(0.,0.,0.);
    }

    Vector3 RotMatrix3::operator*(const Vector3 &v) const {
        return Vector3(
            matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z,
            matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z,
            matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z
        );
    }

    points::Point3 RotMatrix3::operator*(const points::Point3 &v) const {
        return points::Point3(
            matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z,
            matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z,
            matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z
        );
    }
}