#include "Cylindrical.h"
#include "Vector3.h"

using namespace std;

namespace Three::Math
{
    inline Cylindrical::Cylindrical() noexcept : mRadius(1.),
                                               mTheta(0.),
                                               mY(0.)
    {
    }

    inline Cylindrical::Cylindrical(double radius,
                                  double theta,
                                  double y) noexcept : mRadius(radius),
                                                             mTheta(theta),
                                                             mY(y)
    {
    }

    inline double Cylindrical::Radius() const noexcept
    {
        return mRadius;
    }

    inline double Cylindrical::Theta() const noexcept
    {
        return mTheta;
    }

    inline double Cylindrical::Y() const noexcept
    {
        return mY;
    }

    inline void Cylindrical::SetRadius(double radius) noexcept
    {
        mRadius = radius;
    }

    inline void Cylindrical::SetTheta(double theta) noexcept
    {
        mTheta = theta;
    }

    inline void Cylindrical::SetY(double y) noexcept
    {
        mY = y;
    }

    inline void Cylindrical::Set(double radius, double theta, double y) noexcept
    {
        mRadius = radius;
        mTheta = theta;
        mY = y;
    }

    inline void Cylindrical::SetFromVector3(const Vector3 &v) noexcept
    {
        SetFromCartesianCoords(v.X(), v.Y(), v.Z());
    }

    inline void Cylindrical::SetFromCartesianCoords(double x, double y, double z) noexcept
    {
        mRadius = sqrt(x * x + z * z);
        mTheta = atan2(x, z);
        mY = y;
    }

    inline std::ostream &operator<<(std::ostream &os, const Cylindrical &c)
    {
        os << "{type:'Cylindrical',"
           << "radius:" << c.Radius() << ","
           << "theta:" << c.Theta() << ","
           << "y:" << c.Y() << "}";
        return os;
    }
} // namespace Three::Math