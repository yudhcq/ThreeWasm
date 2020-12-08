#include <exception>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Euler.h"
#include "Matrix4.h"
#include "../Cameras/Camera.h"
#include "Plane.h"
#include "MathUtil.h"
#include "Spherical.h"
#include "Cylindrical.h"
#include "../Core/BufferAttribute.h"

using namespace std;

namespace Three
{
    inline const Vector3 Vector3::UINT_X(1., 0., 0.);
    inline const Vector3 Vector3::UINT_Y(0., 1., 0.);
    inline const Vector3 Vector3::UINT_Z(0., 0., 1.);

    inline Vector3::Vector3() noexcept : mX(0.),
        mY(0.),
        mZ(0.)
    {
    }

    inline Vector3::Vector3(double scalar) noexcept : mX(scalar),
        mY(scalar),
        mZ(scalar)
    {
    }

    inline Vector3::Vector3(double x, double y, double z) noexcept : mX(x),
        mY(y),
        mZ(z)
    {
    }

    inline double Vector3::X() const noexcept
    {
        return mX;
    }

    inline double Vector3::Y() const noexcept
    {
        return mY;
    }

    inline double Vector3::Z() const noexcept
    {
        return mZ;
    }

    inline void Vector3::SetX(double value) noexcept
    {
        mX = value;
    }

    inline void Vector3::SetY(double value) noexcept
    {
        mY = value;
    }

    inline void Vector3::SetZ(double value) noexcept
    {
        mZ = value;
    }

    inline void Vector3::Set(double x, double y, double z) noexcept
    {
        mX = x;
        mY = y;
        mZ = z;
    }

    inline void Vector3::Set(double scalar) noexcept
    {
        mX = mY = mZ = scalar;
    }

    inline double Vector3::operator[](const size_t index) const
    {
        if (index > 2)
        {
            throw range_error("const Vector3 operator[] 下标超出索引");
        }
        else
        {
            return reinterpret_cast<const double*>(this)[index];
        }
    }

    inline double& Vector3::operator[](const size_t index)
    {
        if (index > 2)
        {
            throw range_error("Vector3 operator[] 下标超出索引");
        }
        else
        {
            return reinterpret_cast<double*>(this)[index];
        }
    }

    inline void Vector3::operator+=(const Vector3& v) noexcept
    {
        mX += v.mX;
        mY += v.mY;
        mZ += v.mZ;
    }

    inline void Vector3::operator+=(double s) noexcept
    {
        mX += s;
        mY += s;
        mZ += s;
    }

    inline void Vector3::AddScaledVector(const Vector3& v, double s) noexcept
    {
        mX += v.mX * s;
        mY += v.mY * s;
        mZ += v.mZ * s;
    }

    inline Vector3 Vector3::operator+(const Vector3& v) const noexcept
    {
        return Vector3(mX + v.mX, mY + v.mY, mZ + v.mZ);
    }

    inline Vector3 Vector3::operator+(double s) const noexcept
    {
        return Vector3(mX + s, mY + s, mZ + s);
    }

    inline Vector3 Vector3::AddedScaledVector(const Vector3& v, double s)
    {
        return Vector3(mX + v.mX * s, mY + v.mY * s, mZ + v.mZ * s);
    }

    inline void Vector3::operator-=(const Vector3& v) noexcept
    {
        mX -= v.mX;
        mY -= v.mY;
        mZ -= v.mZ;
    }

    inline void Vector3::operator-=(double s) noexcept
    {
        mX -= s;
        mY -= s;
        mZ -= s;
    }

    inline Vector3 Vector3::operator-(const Vector3& v) const noexcept
    {
        return Vector3(mX - v.mX, mY - v.mY, mZ - v.mZ);
    }

    inline Vector3 Vector3::operator-(double s) const noexcept
    {
        return Vector3(mX - s, mY - s, mZ - s);
    }

    inline void Vector3::operator*=(const Vector3& v) noexcept
    {
        mX *= v.mX;
        mY *= v.mY;
        mZ *= v.mZ;
    }

    inline void Vector3::operator*=(double s) noexcept
    {
        mX *= s;
        mY *= s;
        mZ *= s;
    }

    inline Vector3 Vector3::operator*(const Vector3& v) const noexcept
    {
        return Vector3(mX * v.mX, mY * v.mY, mZ * v.mZ);
    }

    inline Vector3 Vector3::operator*(double s) const noexcept
    {
        return Vector3(mX * s, mY * s, mZ * s);
    }

    inline void Vector3::Apply(const Euler& e) noexcept
    {
        Apply(Quaternion(e));
    }

    inline void Vector3::Apply(const Vector3& axis, double angle) noexcept
    {
        Apply(Quaternion(axis, angle));
    }

    inline void Vector3::Apply(const Matrix3& m) noexcept
    {
        const double _x = mX, _y = mY, _z = mZ;
        mX = m[0] * _x + m[3] * _y + m[6] * _z;
        mY = m[1] * _x + m[4] * _y + m[7] * _z;
        mZ = m[2] * _x + m[5] * _y + m[8] * _z;
    }

    inline void Vector3::ApplyNormalMatrix(const Matrix3& m) noexcept
    {
        Apply(m);
        Normalize();
    }

    inline void Vector3::Apply(const Matrix4& m)
    {
        const double _x = mX, _y = mY, _z = mZ;
        const double _w = m[3] * _x + m[7] * _y + m[11] * _z + m[15];
        if (_w == 0.)
        {
            throw logic_error("Vector3 apply matri4矩阵数据异常");
        }
        mX = (m[0] * _x + m[4] * _y + m[8] * _z + m[12]) / _w;
        mY = (m[1] * _x + m[5] * _y + m[9] * _z + m[13]) / _w;
        mZ = (m[2] * _x + m[6] * _y + m[10] * _z + m[14]) / _w;
    }

    inline void Vector3::Apply(const Quaternion& q) noexcept
    {
        const double _x = mX, _y = mY, _z = mZ;
        const double _qx = q.X(), _qy = q.Y(), _qz = q.Z(), _qw = q.W();

        const double _ix = _qw * _x + _qy * _z - _qz * _y;
        const double _iy = _qw * _y + _qz * _x - _qx * _z;
        const double _iz = _qw * _z + _qx * _y - _qy * _x;
        const double _iw = -_qx * _x - _qy * _y - _qz * _z;

        mX = _ix * _qw + _iw * -_qx + _iy * -_qz - _iz * -_qy;
        mY = _iy * _qw + _iw * -_qy + _iz * -_qx - _ix * -_qz;
        mZ = _iz * _qw + _iw * -_qz + _ix * -_qy - _iy * -_qx;
    }

    inline Vector3 Vector3::Applied(const Euler& e) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Apply(e);
        return _vec;
    }

    inline Vector3 Vector3::Applied(const Vector3& axis, double angle) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Apply(axis, angle);
        return _vec;
    }

    inline Vector3 Vector3::Applied(const Matrix3& m) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Apply(m);
        return _vec;
    }

    inline Vector3 Vector3::AppliedNormalMatrix(const Matrix3& m) const noexcept
    {
        Vector3 _vec(*this);
        _vec.AppliedNormalMatrix(m);
        return _vec;
    }

    inline Vector3 Vector3::Applied(const Matrix4& m) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Apply(m);
        return _vec;
    }

    inline Vector3 Vector3::Applied(const Quaternion& q) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Apply(q);
        return _vec;
    }

    inline void Vector3::Unproject(const Camera& camera) noexcept
    {
        // todo
    }

    inline Vector3 Vector3::Unprojected(const Camera& camera) const noexcept
    {
        //todo
    }

    inline void Vector3::TransformDirection(const Matrix4& m) noexcept
    {
        const double _x = mX, _y = mY, _z = mZ;
        mX = m[0] * _x + m[4] * _y + m[8] * _z;
        mY = m[1] * _x + m[5] * _y + m[9] * _z;
        mZ = m[2] * _x + m[6] * _y + m[10] * _z;
    }

    inline Vector3 Vector3::TransformedDirection(const Matrix4& m) const noexcept
    {
        Vector3 _vec(*this);
        _vec.TransformDirection(m);
        return _vec;
    }

    inline void Vector3::operator/=(const Vector3& v)
    {
        if (v.mX == 0. || v.mY == 0. || v.mZ == 0.)
        {
            throw logic_error("Vector3 operator/= Vector3 除0操作");
        }
        mX /= v.mX;
        mY /= v.mY;
        mZ /= v.mZ;
    }

    inline void Vector3::operator/=(double s)
    {
        if (s == 0.)
        {
            throw logic_error("Vector3 operator/= scalar 除0操作");
        }
        mX /= s;
        mY /= s;
        mZ /= s;
    }

    inline Vector3 Vector3::operator/(const Vector3& v) const
    {
        if (v.mX == 0. || v.mY == 0. || v.mZ == 0.)
        {
            throw logic_error("Vector3 operator/ Vector3 除0操作");
        }
        return Vector3(mX / v.mX, mY / v.mY, mZ / v.mZ);
    }

    inline Vector3 Vector3::operator/(double s) const
    {
        if (s == 0.)
        {
            throw logic_error("Vector3 operator/= scalar 除0操作");
        }
        return Vector3(mX / s, mY / s, mZ / s);
    }

    inline void Vector3::Min(const Vector3& v) noexcept
    {
        mX = min(mX, v.mX);
        mY = min(mY, v.mY);
        mZ = min(mZ, v.mZ);
    }

    inline void Vector3::Max(const Vector3& v) noexcept
    {
        mX = max(mX, v.mX);
        mY = max(mY, v.mY);
        mZ = max(mZ, v.mZ);
    }

    inline Vector3 Vector3::Mined(const Vector3& v) const noexcept
    {
        return Vector3(min(mX, v.mX), min(mY, v.mY), min(mZ, v.mZ));
    }

    inline Vector3 Vector3::Maxed(const Vector3& v) const noexcept
    {
        return Vector3(max(mX, v.mX), max(mY, v.mY), max(mZ, v.mZ));
    }

    inline void Vector3::Clamp(const Vector3& minVec, const Vector3& maxVec) noexcept
    {
        mX = max(minVec.mX, min(maxVec.mX, mX));
        mY = max(minVec.mY, min(maxVec.mY, mY));
        mZ = max(minVec.mZ, min(maxVec.mZ, mZ));
    }

    inline void Vector3::Clamp(double minVal, double maxVal) noexcept
    {
        mX = max(minVal, min(maxVal, mX));
        mY = max(minVal, min(maxVal, mY));
        mZ = max(minVal, min(maxVal, mZ));
    }

    inline void Vector3::ClampLength(double minVal, double maxVal) noexcept
    {
        SetLength(max(minVal, min(maxVal, Length())));
    }

    inline Vector3 Vector3::Clamped(const Vector3& minVec, const Vector3& maxVec) const noexcept
    {
        return Vector3(
            max(minVec.mX, min(maxVec.mX, mX)),
            max(minVec.mY, min(maxVec.mY, mY)),
            max(minVec.mZ, min(maxVec.mZ, mZ)));
    }

    inline Vector3 Vector3::Clamped(double minVal, double maxVal) const noexcept
    {
        return Vector3(
            max(minVal, min(maxVal, mX)),
            max(minVal, min(maxVal, mY)),
            max(minVal, min(maxVal, mZ)));
    }

    inline Vector3 Vector3::ClampedLength(double min, double max) const noexcept
    {
        Vector3 _vec(*this);
        _vec.ClampLength(min, max);
        return _vec;
    }

    inline void Vector3::Floor() noexcept
    {
        mX = floor(mX);
        mY = floor(mY);
        mZ = floor(mZ);
    }

    inline void Vector3::Round() noexcept
    {
        mX = round(mX);
        mY = round(mY);
        mZ = round(mZ);
    }

    inline void Vector3::RoundToZero() noexcept
    {
        mX = mX < 0. ? ceil(mX) : floor(mX);
        mY = mY < 0. ? ceil(mY) : floor(mY);
        mZ = mZ < 0. ? ceil(mZ) : floor(mZ);
    }

    inline void Vector3::Ceil() noexcept
    {
        mX = ceil(mX);
        mY = ceil(mY);
        mZ = ceil(mZ);
    }

    inline Vector3 Vector3::Floored() const noexcept
    {
        return Vector3(
            floor(mX),
            floor(mY),
            floor(mZ));
    }

    inline Vector3 Vector3::Rounded() const noexcept
    {
        return Vector3(
            round(mX),
            round(mY),
            round(mZ));
    }

    inline Vector3 Vector3::Ceiled() const noexcept
    {
        return Vector3(
            ceil(mX),
            ceil(mY),
            ceil(mZ));
    }

    inline Vector3 Vector3::RoundedToZero() const noexcept
    {
        return Vector3(
            mX < 0. ? ceil(mX) : floor(mX),
            mY < 0. ? ceil(mY) : floor(mY),
            mZ < 0. ? ceil(mZ) : floor(mZ));
    }

    inline void Vector3::Negate() noexcept
    {
        mX = -mX;
        mY = -mY;
        mZ = -mZ;
    }

    inline Vector3 Vector3::Negated() const noexcept
    {
        Vector3 _v(*this);
        _v.Negate();
        return _v;
    }

    inline Vector3 Vector3::operator-(void) const noexcept
    {
        return Vector3(
            -mX,
            -mY,
            -mZ);
    }

    inline double Vector3::Dot(const Vector3& v) const noexcept
    {
        return mX * v.mX + mY * v.mY + mZ * v.mZ;
    }

    inline double Vector3::LengthSq() const noexcept
    {
        return mX * mX + mY * mY + mZ * mZ;
    }

    inline double Vector3::Length() const noexcept
    {
        return sqrt(LengthSq());
    }

    inline double Vector3::Manhattanlength() const noexcept
    {
        return abs(mX) + abs(mY) + abs(mZ);
    }

    inline double Vector3::ManhattanDistanceTo(const Vector3& v) const noexcept
    {
        return abs(mX - v.mX) + abs(mY - v.mY) + abs(mZ - v.mZ);
    }

    inline void Vector3::Normalize() noexcept
    {
        double _l = Length();
        if (_l == 0.)
        {
            _l = 1.;
        }
        operator/=(_l);
    }

    inline Vector3 Vector3::Normalized() const noexcept
    {
        double _l = Length();
        if (_l == 0.)
        {
            _l = 1.;
        }
        return operator/(_l);
    }

    inline void Vector3::SetLength(double l) noexcept
    {
        Normalize();
        operator*=(l);
    }

    inline void Vector3::Lerp(const Vector3& v, double alpha) noexcept
    {
        mX += (v.mX - mX) * alpha;
        mY += (v.mY - mY) * alpha;
        mZ += (v.mZ - mZ) * alpha;
    }

    inline Vector3 Vector3::Lerped(const Vector3& v, double alpha) const noexcept
    {
        return Vector3(
            mX + (v.mX - mX) * alpha,
            mY + (v.mY - mY) * alpha,
            mZ + (v.mZ - mZ) * alpha);
    }

    inline void Vector3::Cross(const Vector3& v) noexcept
    {
        double _x = mX, _y = mY, _z = mZ;
        double _vx = v.mX, _vy = v.mY, _vz = v.mZ;

        mX = _y * _vz - _z * _vy;
        mY = -_x * _vz + _z * _vx;
        mZ = _x * _vy - _y * _vx;
    }

    inline Vector3 Vector3::Crossed(const Vector3& v) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Cross(v);
        return _vec;
    }

    inline void Vector3::Project(const Vector3& v) noexcept
    {
        double _denominator = v.LengthSq();
        if (_denominator == 0.)
        {
            Set(0., 0., 0.);
        }
        else
        {
            *this = v * Dot(v) / _denominator;
        }
    }

    inline void Vector3::Project(const Plane& plane) noexcept
    {
        operator-=(Projected(plane.Normal()));
    }

    inline void Vector3::Project(const Camera& camera) noexcept
    {
        // todo
    }

    inline Vector3 Vector3::Projected(const Vector3& v) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Project(v);
        return _vec;
    }

    inline Vector3 Vector3::Projected(const Plane& plane) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Project(plane);
        return _vec;
    }

    inline Vector3 Vector3::Projected(const Camera& camera) const noexcept
    {
        Vector3 _vec(*this);
        _vec.Project(camera);
        return _vec;
    }

    inline void Vector3::Reflect(const Plane& plane) noexcept
    {
        const Vector3& _pn = plane.Normal();
        operator-=(_pn * Dot(_pn) * 2.);
    }

    inline const Vector3 Vector3::Reflected(const Plane& plane) const noexcept
    {
        const Vector3& _pn = plane.Normal();
        return operator-(_pn * Dot(_pn) * 2.);
    }

    inline double Vector3::AngleTo(const Vector3& v) const noexcept
    {
        const double _denominator = sqrt(LengthSq() * v.LengthSq());
        if (_denominator == 0.)
        {
            return M_PI_2;
        }
        return acos(MathUtil::Clamp(Dot(v) / _denominator, -1., 1.));
    }

    inline double Vector3::DistanceTo(const Vector3& v) const noexcept
    {
        return sqrt(DistanceToSquared(v));
    }

    inline double Vector3::DistanceToSquared(const Vector3& v) const noexcept
    {
        return pow(mX - v.mX, 2.) + pow(mY - v.mY, 2.) + pow(mZ - v.mZ, 2.);
    }

    inline void Vector3::SetFromSpherical(const Spherical& s) noexcept
    {
        SetFromSpherical(s.Radius(), s.Phi(), s.Theta());
    }

    inline void Vector3::SetFromSpherical(double radius, double phi, double theta) noexcept
    {
        const double _sinPhiRadius = sin(phi) * radius;
        mX = _sinPhiRadius * sin(theta);
        mY = cos(phi) * radius;
        mZ = _sinPhiRadius * cos(theta);
    }

    inline void Vector3::SetFromCylindrical(const Cylindrical& c) noexcept
    {
        SetFromCylindrical(c.Radius(), c.Theta(), c.Y());
    }

    inline void Vector3::SetFromCylindrical(double radius, double theta, double y) noexcept
    {
        mX = radius * sin(theta);
        mY = y;
        mZ = radius * cos(theta);
    }

    inline void Vector3::SetFromMatrixPosition(const Matrix4& m) noexcept
    {
        Set(m[12], m[13], m[14]);
    }

    inline void Vector3::SetFromMatrixScale(const Matrix4& m) noexcept
    {
        Vector3 _vec;
        _vec.SetFromMatrixColumn(m, 0);
        const double _sx = _vec.Length();
        _vec.SetFromMatrixColumn(m, 1);
        const double _sy = _vec.Length();
        _vec.SetFromMatrixColumn(m, 2);
        Set(_sx, _sy, _vec.Length());
    }

    inline void Vector3::SetFromMatrixColumn(const Matrix4& m, const size_t index)
    {
        if (index < 4)
        {
            const size_t _offset = index * 4;
            Set(m[_offset], m[_offset + 1], m[_offset + 2]);
        }
        else
        {
            throw range_error("Vector3 SetFromMatrixColumn index range error");
        }
    }

    inline void Vector3::SetFromMatrix3Column(const Matrix3& m, const size_t index)
    {
        if (index < 3)
        {
            const size_t _offset = index * 3;
            Set(m[_offset], m[_offset + 1], m[_offset + 2]);
        }
        else
        {
            throw range_error("Vector3 SetFromMatrix3Column index range error");
        }
    }

    inline bool Vector3::Equals(const Vector3& v, uint32_t ulp) const noexcept
    {
        return MathUtil::AlmosetEquals(mX, v.mX, ulp) &&
            MathUtil::AlmosetEquals(mY, v.mY, ulp) &&
            MathUtil::AlmosetEquals(mZ, v.mZ, ulp);
    }

    inline bool Vector3::operator==(const Vector3& v) const noexcept
    {
        return Equals(v);
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector3& v)
    {
        os << "{type:'Vector3',"
            << "x:"
            << v.mX
            << ",y:"
            << v.mY
            << ",z:"
            << v.mZ
            << "}";
        return os;
    }

} // namespace Three
#undef _USE_MATH_DEFINES