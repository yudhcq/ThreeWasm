#include <float.h>
#include <exception>

#include "Box3.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Matrix4.h"

#include "../Core/BufferAttribute.h"

using namespace std;

namespace Three
{
    inline Box3::Box3() noexcept : mMin(DBL_MAX, DBL_MAX, DBL_MAX),
                                   mMax(-DBL_MAX, -DBL_MAX, -DBL_MAX)
    {
    }

    inline Box3::Box3(const Vector3 &min, const Vector3 &max) noexcept : mMin(min),
                                                                         mMax(max)
    {
    }

    inline void Box3::Set(const Vector3 &min, const Vector3 &max) noexcept
    {
        mMin = min;
        mMax = max;
    }

    inline const Vector3 &Box3::Min() const noexcept
    {
        return mMin;
    }

    inline const Vector3 &Box3::Max() const noexcept
    {
        return mMax;
    }

    inline void Box3::SetMax(const Vector3 &max) noexcept
    {
        mMax = max;
    }

    inline void Box3::SetMin(const Vector3 &min) noexcept
    {
        mMin = min;
    }

    inline void Box3::SetFromPoints(const std::vector<Vector3> &points) noexcept
    {
        MakeEmpty();
        for (const auto &_point : points)
        {
            ExpandByPoint(_point);
        }
    }

    inline void Box3::SetFromCenterAndSize(const Vector3 &center, const Vector3 &size) noexcept
    {
        const auto _halfSize = size / 2.0;
        mMin = center - _halfSize;
        mMax = center + _halfSize;
    }

    inline void Box3::MakeEmpty() noexcept
    {
        mMax.Set(-DBL_MAX, -DBL_MAX, -DBL_MAX);
        mMin.Set(DBL_MAX, DBL_MAX, DBL_MAX);
    }

    inline bool Box3::IsEmpty() const noexcept
    {
        return mMax.X() < mMin.X() ||
               mMax.Y() < mMin.Y() ||
               mMax.Z() < mMin.Z();
    }

    inline Vector3 Box3::GetCenter() const noexcept
    {
        if (IsEmpty())
        {
            return Vector3();
        }
        else
        {
            return (mMax + mMin) / 2.0;
        }
    }

    inline Vector3 Box3::GetSize() const noexcept
    {
        if (IsEmpty())
        {
            return Vector3();
        }
        else
        {
            return mMax - mMin;
        }
    }

    inline void Box3::ExpandByPoint(const Vector3 &point) noexcept
    {
        mMin.Min(point);
        mMax.Max(point);
    }

    inline void Box3::ExpandByVector(const Vector3 &vector) noexcept
    {
        mMin -= vector;
        mMax += vector;
    }

    inline void Box3::ExpandByScalar(double scalar) noexcept
    {
        mMin -= scalar;
        mMax += scalar;
    }

    inline bool Box3::ContainsPoint(const Vector3 &point) const noexcept
    {
        return !(point.X() < mMin.X() ||
                 point.Y() < mMin.Y() ||
                 point.Z() < mMin.Z() ||
                 point.X() > mMax.X() ||
                 point.Y() > mMax.Y() ||
                 point.Z() > mMax.Z());
    }

    inline bool Box3::ContainsBox(const Box3 &box) const noexcept
    {
        return box.mMin.X() >= mMin.X() &&
            box.mMin.Y() >= mMin.Y() &&
            box.mMin.Z() >= mMin.Z() &&
            box.mMax.X() <= mMax.X() &&
            box.mMax.Y() <= mMax.Y() &&
            box.mMax.Z() <= mMax.Z();
    }

    inline Vector3 Box3::GetParamter(const Vector3 &point) const
    {
        const auto &_size = GetSize();
        if (_size.X() == 0. || _size.Y() == 0.)
        {
            throw logic_error("二维盒子的某一维度尺寸为0");
        }
        return (point - mMin) / _size;
    }

    inline bool Box3::IntersectsBox(const Box3 &box) const noexcept
    {
        return !(box.mMax.X() < mMin.X() ||
                 box.mMax.Y() < mMin.Y() ||
                 box.mMax.Z() < mMin.Z() ||
                 box.mMin.X() > mMax.X() ||
                 box.mMin.Y() > mMax.Y() ||
                 box.mMin.Z() > mMax.Z());
    }

    inline bool Box3::IntersectsSphere(const Sphere &sphere) const noexcept
    {
        return DistanceToPoint(sphere.Center()) <= sphere.Radius();
    }

    inline bool Box3::IntersectsPlane(const Plane &plane) const
    {
        if (IsEmpty())
        {
            return false;
        }
        double _minDot = 0., _maxDot = 0.;
        const auto &_planeNormal = plane.Normal();
        for (size_t _i = 0; _i < 3; ++_i)
        {
            const double _pnIndex(_planeNormal[_i]);
            _minDot += _pnIndex * (_pnIndex > 0. ? mMin[_i] : mMax[_i]);
            _maxDot += _pnIndex * (_pnIndex > 0. ? mMax[_i] : mMin[_i]);
        }
        const auto planeConstantN = -plane.Constant();
        return _minDot <= planeConstantN && _maxDot >= planeConstantN;
    }

    inline bool Box3::IntersectsTriangle(const Triangle &triangle) const
    {
        if (IsEmpty())
        {
            return false;
        }
        const auto &_triA = triangle.A();
        const auto &_triB = triangle.B();
        const auto &_triC = triangle.C();

        const auto _isContainA = ContainsPoint(_triA);
        const auto _isContainB = ContainsPoint(_triB);
        const auto _isContainC = ContainsPoint(_triC);

        // 表示三角形在盒子中心
        if (_isContainA && _isContainB && _isContainC)
        {
            return false;
        }
        else if (!_isContainA && !_isContainB && !_isContainC)
        {
            const Plane _triPlane(_triA, _triB, _triC);
            // 如果盒子不和该三角形构成的平面相交，则盒子也不会和该三角形相交
            if (!IntersectsPlane(_triPlane))
            {
                return false;
            }
            // 求取出该平面对应的盒子的最大点和最小点在平面上的投影需至少有一个在盒子内部
            Vector3 _minVec, _maxVec;
            const Vector3 &_triPlaneNormal = _triPlane.Normal();
            for (size_t _i = 0; _i < 3; ++_i)
            {
                double _tpnValue = _triPlaneNormal[_i];
                _minVec[_i] = _tpnValue > 0 ? mMin[_i] : mMax[_i];
                _maxVec[_i] = _tpnValue > 0 ? mMax[_i] : mMin[_i];
            }
            _minVec = _triPlane.ProjectPoint(_minVec);
            _maxVec = _triPlane.ProjectPoint(_maxVec);
            if (ContainsPoint(_minVec) || ContainsPoint(_maxVec))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else // 任意有一个点在盒子内部，则表示该三角形和盒子相交
        {
            return true;
        }
    }

    inline Vector3 Box3::ClampPoint(const Vector3 &point) const noexcept
    {
        return point.Clamped(mMin, mMax);
    }
    inline double Box3::DistanceToPoint(const Vector3 &point) const noexcept
    {
        return point.DistanceTo(ClampPoint(point));
    }
    inline Sphere Box3::GetBoundingSphere() const noexcept
    {
        return Sphere(GetCenter(), GetSize().Length() / 2.0);
    }

    inline void Box3::operator&=(const Box3 &box) noexcept
    {
        mMin.Max(box.mMin);
        mMax.Min(box.mMax);
        if (IsEmpty())
        {
            MakeEmpty();
        }
    }
    inline void Box3::operator|=(const Box3 &box) noexcept
    {
        mMin.Min(box.mMin);
        mMax.Max(box.mMax);
    }

    inline Box3 Box3::operator&(const Box3 &box) const noexcept
    {
        return Box3(mMin.Maxed(box.mMin), mMax.Mined(box.mMax));
    }

    inline Box3 Box3::operator|(const Box3 &box) const noexcept
    {
        return Box3(mMin.Mined(box.mMin), mMax.Maxed(box.mMax));
    }
    inline void Box3::operator*=(const Matrix4 &matrix) noexcept
    {
        if (IsEmpty())
        {
            return;
        }
        const double _minX = mMin.X(), _minY = mMin.Y(), _minZ = mMin.Z();
        const double _maxX = mMax.X(), _maxY = mMax.Y(), _maxZ = mMax.Z();
        MakeEmpty();
        for (size_t _i = 0; _i < 8; ++_i)
        {
            Vector3 _p((_i / 4) == 0 ? _minX : _maxX,
                       ((_i / 2) % 2) == 0 ? _minY : _maxY,
                       ((_i % 2) == 0) ? _minZ : _maxZ);
            _p.Apply(matrix);
            ExpandByPoint(_p);
        }
    }

    inline Box3 Box3::operator*(const Matrix4 &matrix) const noexcept
    {
        auto _box = *this;
        _box *= matrix;
        return _box;
    }

    inline void Box3::Translate(const Vector3 &offset) noexcept
    {
        mMin += offset;
        mMax += offset;
    }

    inline Box3 Box3::Translated(const Vector3& offset) const noexcept
    {
        return Box3(mMin + offset, mMax + offset);
    }

    inline bool Box3::Equals(const Box3 &box, const uint8_t ulp) const noexcept
    {
        return mMax.Equals(box.mMax, ulp) && mMin.Equals(box.mMin, ulp);
    }

    inline bool Box3::operator==(const Box3 &box) const noexcept
    {
        return Equals(box);
    }
    inline ostream &operator<<(ostream &os, const Box3 &box)
    {
        os << "{type:'Box3',"
           << "min:"
           << box.Min()
           << ","
           << "max:"
           << box.Max()
           << "}";

        return os;
    }
} // namespace Three
