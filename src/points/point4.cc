#include "point4.hh"

#include <ostream>
#include <string>

#include "vectors/vector4.hh"

namespace points
{

    Point4 Point4::origin()
    {
        return Point4{ 0, 0, 0, 0 };
    }

    Point4::Point4(double x, double y, double z, double w)
        : x{ x }
        , y{ y }
        , z{ z }
        , w{ w }
    {}

    Point4 Point4::operator+(const vectors::Vector4 &vect)
    {
        return Point4{ this->x + vect.x, this->y + vect.y, this->z + vect.z,
                       this->w + vect.w };
    }
    Point4 Point4::operator-(const vectors::Vector4 &vect)
    {
        return Point4{ this->x - vect.x, this->y - vect.y, this->z - vect.z,
                       this->w - vect.w };
    }

    std::ostream &operator<<(std::ostream &out, Point4 &point)
    {
        return out << "Point4(" << point.x << ", " << point.y << ", " << point.z
                   << ", " << point.w << ")";
    }
} // namespace points
