#include "point3.hh"

#include <ostream>
#include <string>

#include "utils/utils.hh"
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

    Point3 &Point3::operator+=(const vectors::Vector3 &vect)
    {
        x += vect.x;
        y += vect.y;
        z += vect.z;
        return *this;
    }

    Point3 &Point3::operator-=(const vectors::Vector3 &vect)
    {
        x += vect.x;
        y += vect.y;
        z += vect.z;
        return *this;
    }

    Point3 Point3::operator+(const vectors::Vector3 &vect) const
    {
        auto copy = *this;
        copy += vect;
        return copy;
    }

    Point3 Point3::operator-(const vectors::Vector3 &vect) const
    {
        auto copy = *this;
        copy -= vect;
        return copy;
    }

    vectors::Vector3 Point3::operator-(const Point3 &other) const
    {
        return vectors::Vector3{ x - other.x, y - other.y, z - other.z };
    }

    std::ostream &operator<<(std::ostream &out, const Point3 &point)
    {
        if (utils::compact_enabled(out))
        {
            return out << "(" << point.x << ", " << point.y << ", " << point.z
                       << ")";
        }
        return out << "Point3(" << point.x << ", " << point.y << ", " << point.z
                   << ")";
    }
} // namespace points
