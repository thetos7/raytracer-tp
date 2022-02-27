#include "point3.hh"

#include <ostream>
#include <string>

#include "vectors/vector3.hh"

namespace points
{

    Point3 Point3::origin()
    {
        return Point3{ 0, 0, 0 };
    }

    Point3::Point3(double x, double y, double z)
        : x{ x }
        , y{ y }
        , z{ z }
    {}

    Point3 Point3::operator+(const vectors::Vector3 &vect) const
    {
        return Point3{ this->x + vect.x, this->y + vect.y, this->z + vect.z };
    }

    Point3 Point3::operator-(const vectors::Vector3 &vect) const
    {
        return Point3{ this->x - vect.x, this->y - vect.y, this->z - vect.z };
    }

    std::ostream &operator<<(std::ostream &out, Point3 &point)
    {
        return out << "Point3{" << point.x << ", " << point.y << ", " << point.z
                   << "}";
    }
} // namespace points