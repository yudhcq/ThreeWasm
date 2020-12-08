#include "Sphere.h"
#include "Box3.h"

using namespace std;

namespace Three
{
    inline Sphere::Sphere() noexcept : mRadius(0.)
    {
    }

    inline Sphere::Sphere(const Vector3 &center,
                          double radius) noexcept : mCenter(center),
                                                    mRadius(radius)
    {
    }

    inline const Vector3 &Sphere::Center() const noexcept
    {
        return mCenter;
    }

    inline double Sphere::Radius() const noexcept
    {
        return mRadius;
    }

    inline void Sphere::SetCenter(const Vector3 &center) noexcept
    {
        mCenter = center;
    }

    inline void Sphere::SetRadius(double radius) noexcept
    {
        mRadius = radius;
    }

    inline void Sphere::Set(const Vector3 &center, double radius) noexcept
    {
        mCenter = center;
        mRadius = radius;
    }

    inline void Sphere::SetFromPoints(const vector<Vector3> &points) noexcept
    {
        Box3 _box;
        _box.SetFromPoints(points);
        SetFromPoints(points, _box.GetCenter());
    }

    inline void Sphere::SetFromPoints(const vector<Vector3> &points,
                                      const Vector3 &optionalCenter) noexcept
    {
        mCenter = optionalCenter;
        double _maxRadiusSq = 0.;
        for (const auto &_point : points)
        {
            _maxRadiusSq = max(_maxRadiusSq, mCenter.DistanceToSquared(_point));
        }
        mRadius = sqrt(_maxRadiusSq);
    }

    inline double Sphere::Empty() const noexcept
    {
        return mRadius <= 0.;
    }

    inline bool Sphere::ContainsPoint(const Vector3 &point) const noexcept
    {
        return mCenter.DistanceTo(point) <= mRadius;
    }

    inline double Sphere::DistanceTo(const Vector3 &point) const noexcept
    {
        return mCenter.DistanceTo(point) - mRadius;
    }

    inline bool Sphere::Intersects(const Sphere &s) const noexcept
    {
        return mCenter.DistanceTo(s.mCenter) <= mRadius + s.mRadius;
    }

    inline bool Sphere::Intersects(const Box3 &box) const noexcept
    {
        return box.IntersectsSphere(*this);
    }

    inline bool Sphere::Intersects(const Plane &plane) const noexcept
    {
        return abs(plane.DistanceTo(mCenter)) <= mRadius;
    }

    inline Vector3 Sphere::ClampPoint(const Vector3 &point) const noexcept
    {
        const double _deltaLength = mCenter.DistanceTo(point);
        // 如果点到球心的距离大于半径，则需将点投影到球上
        if (_deltaLength > mRadius)
        {
            Vector3 _target = (point - mCenter).Normalized();
            _target *= mRadius;
            _target += mCenter;
            return _target;
        }
        else
        {
            return point;
        }
    }

    inline Box3 Sphere::GetBoundingBox() const noexcept
    {
        Box3 _box;
        _box.Set(mCenter, mCenter);
        _box.ExpandByScalar(mRadius);
        return _box;
    }

    inline void Sphere::operator*=(const Matrix4 &m) noexcept
    {
        mCenter.Apply(m);
        mRadius *= m.GetMaxScaleOnAxis();
    }

    inline Sphere Sphere::operator*(const Matrix4 &m) const noexcept
    {
        Sphere _s(*this);
        _s *= m;
        return _s;
    }

    inline void Sphere::Translate(const Vector3 &offset) noexcept
    {
        mCenter += offset;
    }

    inline Sphere Sphere::Translated(const Vector3& offset) const noexcept
    {
        Sphere _s = *this;
        _s.Translate(offset);
        return _s;
    }


    inline bool Sphere::Equals(const Sphere &sphere, uint32_t ulp) const noexcept
    {
        return mCenter.Equals(sphere.mCenter, ulp) && MathUtil::AlmosetEquals(mRadius, sphere.mRadius, ulp);
    }

    inline bool Sphere::operator==(const Sphere &sphere) const noexcept
    {
        return Equals(sphere);
    }

    inline ostream &operator<<(ostream &os, const Sphere &sphere)
    {
        os << "{type:'Sphere',center:" << sphere.Center()
           << ",radius:" << sphere.Radius() << "}";
        return os;
    }

} // namespace Three
