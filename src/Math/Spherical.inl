#include "Spherical.h"
#include "Vector3.h"
#include "MathUtil.h"

namespace Three::Math
{
    inline Spherical::Spherical() noexcept : mRadius(1.),
                                             mPhi(0.),
                                             mTheta(0.)
    {
    }

    inline Spherical::Spherical(double radius,
                                double phi,
                                double theta) noexcept : mRadius(radius),
                                                               mPhi(phi),
                                                               mTheta(theta)
    {
    }

    inline double Spherical::Radius() const noexcept
    {
        return mRadius;
    }

    inline double Spherical::Phi() const noexcept
    {
        return mPhi;
    }

    inline double Spherical::Theta() const noexcept
    {
        return mTheta;
    }

    inline void Spherical::SetRadius(double radius) noexcept
    {
        mRadius = radius;
    }

    inline void Spherical::SetPhi(double phi) noexcept
    {
        mPhi = phi;
    }

    inline void Spherical::SetTheta(double theta) noexcept
    {
        mTheta = theta;
    }

    inline void Spherical::Set(double radius,
                               double phi,
                               double theta) noexcept
    {
        mRadius = radius;
        mPhi = phi;
        mTheta = theta;
    }

    inline void Spherical::MakeSafe() noexcept
    {
        double _eps = 0.000001;
        mPhi = max(_eps, min(M_PI - _eps, mPhi));
    }

    inline void Spherical::SetFromVector3(const Vector3 &v) noexcept
    {
        SetFromCartesianCoords(v.X(), v.Y(), v.Z());
    }

    inline void Spherical::SetFromCartesianCoords(double x, double y, double z) noexcept
    {
        mRadius = sqrt(x * x + y * y + z * z);
        if (mRadius == 0.)
        {
            mTheta = 0.;
            mPhi = 0.;
        }
        else
        {
            mTheta = atan2(x, z);
            mPhi = acos(MathUtil::Clamp(y / mRadius, -1., 1.));
        }
    }

    inline ostream &operator<<(ostream &os, const Spherical &sphere)
    {
        os << "{type:Spherical,radius:" << sphere.Radius()
           << ",phi:" << sphere.Phi()
           << ",theta" << sphere.Theta() << "}";
        return os;
    }

} // namespace Three::Math
