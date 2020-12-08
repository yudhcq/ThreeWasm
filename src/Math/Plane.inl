#include "Plane.h"
#include "Sphere.h"
#include "Line3.h"
#include "Box3.h"

namespace Three
{
    inline Plane::Plane() noexcept : mNormal(1., 0., 0.),
        mConstant(0.)
    {
    }

    inline Plane::Plane(const Vector3& normal,
        double constant) noexcept : mNormal(normal),
        mConstant(constant)
    {
    }

    inline Plane::Plane(const Vector3& normal,
        const Vector3& point) noexcept : mNormal(normal),
        mConstant(-point.Dot(normal))
    {
    }

    inline Plane::Plane(const Vector3& a,
        const Vector3& b,
        const Vector3& c) noexcept : mNormal((c - b).Crossed(a - b).Normalized()),
        mConstant(-a.Dot(mNormal))
    {
    }

    inline const Vector3& Plane::Normal() const noexcept
    {
        return mNormal;
    }

    inline double Plane::Constant() const noexcept
    {
        return mConstant;
    }

    inline void Plane::SetNormal(const Vector3& normal) noexcept
    {
        mNormal = normal;
    }

    inline void Plane::SetConstant(double constant) noexcept
    {
        mConstant = constant;
    }

    inline void Plane::Set(const Vector3& normal, double constant) noexcept
    {
        mNormal = normal;
        mConstant = constant;
    }

    inline void Plane::Set(double nx, double ny, double nz, double constant) noexcept
    {
        mNormal.Set(nx, ny, nz);
        mConstant = constant;
    }

    inline double Plane::operator[](size_t index) const
    {
        if (index > 3)
        {
            throw range_error("const Plane operator[] 下标超出限制");
        }
        else
        {
            return reinterpret_cast<const double*>(this)[index];
        }
    }

    inline double& Plane::operator[](size_t index)
    {
        if (index > 3)
        {
            throw range_error("Plane operator[] 下标超出限制");
        }
        else
        {
            return reinterpret_cast<double*>(this)[index];
        }
    }

    inline void Plane::SetFromNormalAndCopanarPoint(const Vector3& normal, const Vector3& point) noexcept
    {
        mNormal = normal;
        mConstant = -point.Dot(normal);
    }

    inline void Plane::SetFromCoplanarPoints(const Vector3& a, const Vector3& b, const Vector3& c) noexcept
    {
        mNormal = (c - b).Crossed(a - b).Normalized();
        mConstant = -a.Dot(mNormal);
    }

    inline void Plane::Normalize() noexcept
    {
        const double _l = mNormal.Length();
        if (_l == 0.)
        {
            return;
        }
        mNormal *= 1. / _l;
        mConstant *= 1. / _l;
    }

    inline Plane Plane::Normalized() const noexcept
    {
        Plane _p(*this);
        _p.Normalize();
        return _p;
    }

    inline void Plane::Negate() noexcept
    {
        mConstant *= -1.;
        mNormal.Negate();
    }

    inline Plane Plane::Negated() const noexcept
    {
        Plane _p(*this);
        _p.Negate();
        return _p;
    }

    inline double Plane::DistanceTo(const Vector3& point) const noexcept
    {
        return mNormal.Dot(point) + mConstant;
    }

    inline double Plane::DistanceTo(const Sphere& sphere) const noexcept
    {
        return DistanceTo(sphere.Center()) - sphere.Radius();
    }

    inline Vector3 Plane::ProjectPoint(const Vector3& point) const noexcept
    {
        return (mNormal * -DistanceTo(point)) + point;
    }

    inline bool Plane::IntersectLine(const Line3& line, Vector3& target) const noexcept
    {
        const Vector3 _lineDirection = line.Delta();
        const double _denominator = _lineDirection.Dot(mNormal);
        if (_denominator == 0.)
        {
            if (DistanceTo(line.Start()) == 0.)
            {
                target = line.Start();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            double _t = -DistanceTo(line.Start()) / _denominator;
            if (_t < 0. || _t > 1.)
            {
                return false;
            }
            else
            {
                target = _lineDirection * _t + line.Start();
                return true;
            }
        }
    }

    inline bool Plane::IntersectsLine(const Line3& line) const noexcept
    {
        double _startSign = DistanceTo(line.Start());
        double _endSign = DistanceTo(line.End());

        return (_startSign < 0 && _endSign > 0) || (_endSign < 0 && _startSign > 0);
    }

    inline bool Plane::IntersectsBox(const Box3& box) const noexcept
    {
        return box.IntersectsPlane(*this);
    }

    inline bool Plane::IntersectsSphere(const Sphere& sphere) const noexcept
    {
        return sphere.Intersects(*this);
    }

    inline Vector3 Plane::CoplanarPoint() const noexcept
    {
        return mNormal * -mConstant;
    }

    inline void Plane::ApplyMatrix4(const Matrix4& matrix,
        const Matrix3& optionalNormalMatrix) noexcept
    {
        const Vector3 _refrencePoint = CoplanarPoint().Applied(matrix);
        mNormal.Apply(optionalNormalMatrix);
        mNormal.Normalize();
        mConstant = -_refrencePoint.Dot(mNormal);
    }

    inline void Plane::operator*=(const Matrix4& matrix) noexcept
    {
        const Vector3 _refrencePoint = CoplanarPoint().Applied(matrix);
        Matrix3 _normalMatrix;
        _normalMatrix.GetNormalMatrix(matrix);
        mNormal.Apply(_normalMatrix);
        mNormal.Normalize();
        mConstant = -_refrencePoint.Dot(mNormal);
    }

    inline Plane Plane::operator*(const Matrix4& m) const noexcept
    {
        Plane _p(*this);
        _p *= m;
        return _p;
    }

    inline Plane Plane::AppliedMatrix4(const Matrix4& m,
        const Matrix3& optionalNormalMatrix) const noexcept
    {
        Plane _p(*this);
        _p.ApplyMatrix4(m, optionalNormalMatrix);
        return _p;
    }

    inline void Plane::Translate(const Vector3& offset) noexcept
    {
        mConstant -= offset.Dot(mNormal);
    }

    inline Plane Plane::Translated(const Vector3& offset) const noexcept
    {
        Plane _p(*this);
        _p.Translate(offset);
        return _p;
    }

    inline bool Plane::Equals(const Plane& plane, uint32_t ulp) const noexcept
    {
        return mNormal.Equals(plane.mNormal, ulp) && MathUtil::AlmosetEquals(mConstant, plane.mConstant, ulp);
    }

    inline bool Plane::operator==(const Plane& plane) const noexcept
    {
        return Equals(plane);
    }

    inline std::ostream& operator<<(std::ostream& os, const Plane& plane) noexcept
    {
        os << "{type:'Plane',"
            << "normal:" << plane.Normal()
            << ",constant:" << plane.Constant()
            << "}";
        return os;
    }

} // namespace Three
