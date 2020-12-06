#include "Triangle.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Box3.h"

using namespace std;

namespace Three::Math
{
    inline Triangle::Triangle() noexcept
    {
    }

    inline Triangle::Triangle(const Vector3 &a,
                              const Vector3 &b,
                              const Vector3 &c) noexcept : mA(a),
                                                           mB(b),
                                                           mC(c)
    {
    }

    inline const Vector3 &Triangle::A() const noexcept
    {
        return mA;
    }

    inline const Vector3 &Triangle::B() const noexcept
    {
        return mB;
    }

    inline const Vector3 &Triangle::C() const noexcept
    {
        return mC;
    }

    inline void Triangle::SetA(const Vector3 &p) noexcept
    {
        mA = p;
    }

    inline void Triangle::SetB(const Vector3 &p) noexcept
    {
        mB = p;
    }

    inline void Triangle::SetC(const Vector3 &p) noexcept
    {
        mC = p;
    }

    inline void Triangle::Set(const Vector3 &a,
                              const Vector3 &b,
                              const Vector3 &c) noexcept
    {
        mA = a;
        mB = b;
        mC = c;
    }

    inline void Triangle::SetFromPointAndIndices(const vector<Vector3> &points,
                                                 size_t i0,
                                                 size_t i1,
                                                 size_t i2)
    {
        if (points.size() <= max(i0, max(i1, i2)))
        {
            throw range_error("Triangle SetFromPointAndIndices points size is less than max(i0, i1, i2)");
        }
        mA = points[i0];
        mB = points[i1];
        mC = points[i2];
    }

    inline double Triangle::GetArea() const noexcept
    {
        return (mC - mB).Crossed(mA - mC).Length() * 0.5;
    }

    inline Vector3 Triangle::GetMidpoint() const noexcept
    {
        return (mA + mB + mC) / 3.;
    }

    inline Vector3 Triangle::GetNormal() const noexcept
    {
        return GetNormal(mA, mB, mC);
    }

    inline Plane Triangle::GetPlane() const noexcept
    {
        return Plane(mA, mB, mC);
    }

    inline Vector3 Triangle::GetBarycoord(const Vector3 &point) const noexcept
    {
        return GetBarycoord(point, mA, mB, mC);
    }

    inline Vector2 Triangle::GetUV(const Vector3 &point,
                                   const Vector2 &uv1,
                                   const Vector2 &uv2,
                                   const Vector2 &uv3) const noexcept
    {
        const Vector3 _baryCoord = GetBarycoord(point);
        return uv1 * _baryCoord.X() + uv2 * _baryCoord.Y() + uv3 * _baryCoord.Z();
    }

    inline bool Triangle::ContainPoint(const Vector3 &point) const noexcept
    {
        const Vector3 _baryCoord = GetBarycoord(point);
        return _baryCoord.X() >= 0. &&
               _baryCoord.Y() >= 0. &&
               (_baryCoord.X() + _baryCoord.Y()) <= 1.;
    }

    inline bool Triangle::Intersects(const Box3 &box) const noexcept
    {
        return box.IntersectsTriangle(*this);
    }

    inline bool Triangle::IsFrontFacing(const Vector3 &direction) const noexcept
    {
        return direction.Dot(GetNormal()) < 0.;
    }

    inline Vector3 Triangle::ClosesPointToPoint(const Vector3 &p) const noexcept
    {
        const auto _vab = mB - mA;
        const auto _vac = mC - mA;
        const auto _vap = p - mA;

        const double _d1 = _vab.Dot(_vap);
        const double _d2 = _vac.Dot(_vap);
        if (_d1 <= 0. && _d2 <= 0.)
        {
            return mA;
        }

        const auto _vbp = p - mB;
        const double _d3 = _vab.Dot(_vbp);
        const double _d4 = _vac.Dot(_vbp);
        if (_d3 >= 0. && _d4 <= _d3)
        {
            return mB;
        }
        const double _vc = _d1 * _d4 - _d3 * _d2;
        if (_vc <= 0. && _d1 >= 0. && _d3 <= 0.)
        {
            return mA + _vab * _d1 / (_d1 - _d3);
        }
        const auto _vcp = p - mC;
        const double _d5 = _vab.Dot(_vcp);
        const double _d6 = _vac.Dot(_vcp);
        if (_d6 >= 0. && _d5 <= _d6)
        {
            return mC;
        }
        const double _vb = _d5 * _d2 - _d1 * _d6;
        if (_vb <= 0. && _d2 >= 0. && _d6 <= 0.)
        {
            return mA + _vac * _d2 / (_d2 - _d6);
        }
        const double _va = _d3 * _d6 - _d5 * _d4;
        if (_va <= 0 && (_d4 - _d3) >= 0 && (_d5 - _d6) >= 0)
        {
            // edge region of BC; barycentric coords (0, 1-w, w)
            return mB + (mC - mB) * (_d4 - _d3) / ((_d4 - _d3) + (_d5 - _d6));
        }
        const double _denom = 1. / (_va + _vb + _vc);
        return mA + _vab * (_vb * _denom) + _vac * (_vc * _denom);
    }

    inline bool Triangle::Equals(const Triangle &triangle, uint32_t ulp) const noexcept
    {
        return mA.Equals(triangle.mA, ulp) &&
               mB.Equals(triangle.mB, ulp) &&
               mC.Equals(triangle.mC, ulp);
    }

    inline bool Triangle::operator==(const Triangle &triangle) const noexcept
    {
        return Equals(triangle);
    }

    inline Vector3 Triangle::GetNormal(const Vector3 &a,
                                       const Vector3 &b,
                                       const Vector3 &c) noexcept
    {
        return (a - b).Crossed(a - c).Normalized();
    }

    inline Vector3 Triangle::GetBarycoord(const Vector3 &point,
                                          const Vector3 &a,
                                          const Vector3 &b,
                                          const Vector3 &c)
    {
        const Vector3 _v0 = c - a;
        const Vector3 _v1 = b - a;
        const Vector3 _v2 = point - a;

        double _dot00 = _v0.Dot(_v0);
        double _dot01 = _v0.Dot(_v1);
        double _dot02 = _v0.Dot(_v2);
        double _dot11 = _v1.Dot(_v1);
        double _dot12 = _v1.Dot(_v2);

        double _denom = (_dot00 * _dot11 - _dot01 * _dot01);

        if (_denom == 0.)
        {
            return Vector3(-2., -1., -1.);
        }
        else
        {
            double _u = (_dot11 * _dot02 - _dot01 * _dot12) / _denom;
            double _v = (_dot00 * _dot12 - _dot01 * _dot02) / _denom;
            return Vector3(1.0 - _u - _v, _v, _u);
        }
    }

    inline bool Triangle::IsFrontFacing(const Vector3 &a,
                                        const Vector3 &b,
                                        const Vector3 &c,
                                        const Vector3 &direction)
    {
        const Triangle _tri(a, b, c);
        return _tri.IsFrontFacing(direction);
    }

    inline ostream &operator<<(ostream &os, const Triangle &triangle)
    {
        os << "{type:'Triangle'"
           << ",a:" << triangle.A()
           << ",b:" << triangle.B()
           << ",c:" << triangle.C()
           << "}";
        return os;
    }

} // namespace Three::Math
