#include <exception>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "MathUtil.h"
#include "../Core/BufferAttribute.h"

using namespace std;

namespace Three
{
    inline Vector4::Vector4() noexcept : mX(0.),
                                         mY(0.),
                                         mZ(0.),
                                         mW(1.)
    {
    }

    inline Vector4::Vector4(double scalar) noexcept : mX(scalar),
                                                      mY(scalar),
                                                      mZ(scalar),
                                                      mW(scalar)
    {
    }

    inline Vector4::Vector4(double x,
                            double y,
                            double z,
                            double w) noexcept : mX(x),
                                                 mY(y),
                                                 mZ(z),
                                                 mW(w)
    {
    }

    inline double Vector4::X() const noexcept
    {
        return mX;
    }

    inline double Vector4::Y() const noexcept
    {
        return mY;
    }

    inline double Vector4::Z() const noexcept
    {
        return mZ;
    }

    inline double Vector4::W() const noexcept
    {
        return mW;
    }

    inline double Vector4::Width() const noexcept
    {
        return mZ;
    }

    inline double Vector4::Height() const noexcept
    {
        return mW;
    }

    inline void Vector4::SetX(double value) noexcept
    {
        mX = value;
    }

    inline void Vector4::SetY(double value) noexcept
    {
        mY = value;
    }

    inline void Vector4::SetZ(double value) noexcept
    {
        mZ = value;
    }

    inline void Vector4::SetW(double value) noexcept
    {
        mW = value;
    }

    inline void Vector4::SetWidth(double value) noexcept
    {
        mZ = value;
    }

    inline void Vector4::SetHeight(double value) noexcept
    {
        mW = value;
    }

    inline void Vector4::Set(double x, double y, double z, double w) noexcept
    {
        mX = x;
        mY = y;
        mZ = z;
        mW = w;
    }

    inline void Vector4::Set(double scalar) noexcept
    {
        mX = scalar;
        mY = scalar;
        mZ = scalar;
        mW = scalar;
    }

    inline double Vector4::operator[](const size_t index) const
    {
        if (index > 3)
        {
            throw range_error("vector4 const operator[] 下标超出限制");
        }
        else
        {
            return reinterpret_cast<const double *>(this)[index];
        }
    }

    inline double &Vector4::operator[](const size_t index)
    {
        if (index > 3)
        {
            throw range_error("vector4 operator[] 下标超出限制");
        }
        else
        {
            return reinterpret_cast<double *>(this)[index];
        }
    }

    inline void Vector4::operator+=(const Vector4 &v) noexcept
    {
        mX += v.mX;
        mY += v.mY;
        mZ += v.mZ;
        mW += v.mW;
    }

    inline void Vector4::operator+=(double s) noexcept
    {
        mX += s;
        mY += s;
        mZ += s;
        mW += s;
    }

    inline void Vector4::AddScaledVector(const Vector4 &v, double scalar) noexcept
    {
        mX += v.mX * scalar;
        mY += v.mY * scalar;
        mZ += v.mZ * scalar;
        mW += v.mW * scalar;
    }

    inline Vector4 Vector4::operator+(const Vector4 &v) const noexcept
    {
        return Vector4(
            mX + v.mX,
            mY + v.mY,
            mZ + v.mZ,
            mW + v.mW);
    }

    inline Vector4 Vector4::operator+(double s) const noexcept
    {
        return Vector4(
            mX + s,
            mY + s,
            mZ + s,
            mW + s);
    }

    inline Vector4 Vector4::AddedScaledVector(const Vector4 &v, double scalar) const noexcept
    {
        return Vector4(
            mX + v.mX * scalar,
            mY + v.mY * scalar,
            mZ + v.mZ * scalar,
            mW + v.mW * scalar);
    }

    inline void Vector4::operator-=(const Vector4 &v) noexcept
    {
        mX -= v.mX;
        mY -= v.mY;
        mZ -= v.mZ;
        mW -= v.mW;
    }

    inline void Vector4::operator-=(double s) noexcept
    {
        mX -= s;
        mY -= s;
        mZ -= s;
        mW -= s;
    }

    inline Vector4 Vector4::operator-(const Vector4 &v) const noexcept
    {
        return Vector4(
            mX - v.mX,
            mY - v.mY,
            mZ - v.mZ,
            mW - v.mW);
    }

    inline Vector4 Vector4::operator-(double s) const noexcept
    {
        return Vector4(
            mX - s,
            mY - s,
            mZ - s,
            mW - s);
    }

    inline void Vector4::operator*=(double scalar) noexcept
    {
        mX *= scalar;
        mY *= scalar;
        mZ *= scalar;
        mW *= scalar;
    }

    inline Vector4 Vector4::operator*(double scalar) const noexcept
    {
        return Vector4(
            mX * scalar,
            mY * scalar,
            mZ * scalar,
            mW * scalar);
    }

    inline void Vector4::Apply(const Matrix4 &m) noexcept
    {
        const double _x = mX, _y = mY, _z = mZ, _w = mW;
        mX = m[0] * _x + m[4] * _y + m[8] * _z + m[12] * _w;
        mY = m[1] * _x + m[5] * _y + m[9] * _z + m[13] * _w;
        mZ = m[2] * _x + m[6] * _y + m[10] * _z + m[14] * _w;
        mW = m[3] * _x + m[7] * _y + m[11] * _z + m[15] * _w;
    }

    inline Vector4 Vector4::Applied(const Matrix4 &m) const noexcept
    {
        Vector4 _vec(*this);
        _vec.Apply(m);
        return _vec;
    }

    inline void Vector4::operator/=(double scalar)
    {
        if (scalar == 0.)
        {
            throw logic_error("vector4 operator/= scalar为0");
        }
        mX /= scalar;
        mY /= scalar;
        mZ /= scalar;
        mW /= scalar;
    }

    inline Vector4 Vector4::operator/(double scalar) const
    {
        if (scalar == 0.)
        {
            throw logic_error("vector4 operator/ scalar为0");
        }
        return Vector4(mX / scalar, mY / scalar, mZ / scalar, mW / scalar);
    }

    inline void Vector4::SetAxisAngle(const Quaternion &q) noexcept
    {
        const double _qw = q.W();
        mW = 2 * acos(_qw);
        const double _s = sqrt(1.0 - _qw * _qw);
        if (_s < 0.0001)
        {
            mX = 1.;
            mY = 0.;
            mZ = 0.;
        }
        else
        {
            mX = q.X() / _s;
            mY = q.Y() / _s;
            mZ = q.Z() / _s;
        }
    }

    inline void Vector4::SetAxisAngle(const Matrix4 &m) noexcept
    {
        const double _epsilon = 0.01;
        const double _m11 = m[0], _m12 = m[4], _m13 = m[8],
                     _m21 = m[1], _m22 = m[5], _m23 = m[9],
                     _m31 = m[2], _m32 = m[6], _m33 = m[10];
        if (abs(_m12 - _m21) < _epsilon &&
            abs(_m13 - _m31) < _epsilon &&
            abs(_m23 - _m32) < _epsilon)
        {
            double _epsilon2 = 0.1;
            if (abs(_m12 + _m21) < _epsilon2 &&
                abs(_m13 + _m31) < _epsilon2 &&
                abs(_m23 + _m32) < _epsilon2 &&
                abs(_m11 + _m22 + _m33 - 3.) < _epsilon2)
            {
                Set(1., 0., 0., 0.);
                return;
            }
            const double _xx = (_m11 + 1.) / 2.;
            const double _yy = (_m22 + 1.) / 2.;
            const double _zz = (_m33 + 1.) / 2.;
            const double _xy = (_m12 + _m21) / 4.;
            const double _xz = (_m13 + _m31) / 4.;
            const double _yz = (_m23 + _m32) / 4.;
            if (_xx > _yy && _xx > _zz)
            {
                if (_xx < _epsilon)
                {
                    Set(0., 0.707106781, 0.707106781, M_PI);
                }
                else
                {
                    double _x = sqrt(_xx);
                    Set(_x, _xy / _x, _xz / _x, M_PI);
                }
            }
            else if (_yy > _zz)
            {
                if (_yy < _epsilon)
                {
                    Set(0.707106781, 0., 0.707106781, M_PI);
                }
                else
                {
                    double _y = sqrt(_yy);
                    Set(_xy / _y, _y, _yz / _y, M_PI);
                }
            }
            else
            {
                if (_zz < _epsilon)
                {
                    double _z = sqrt(_zz);
                    Set(_xz / _z, _yz / _z, _z, M_PI);
                }
            }
            return;
        }

        double _s = sqrt(pow(_m32 - _m23, 2.) +
                         pow(_m13 - _m31, 2.) +
                         pow(_m21 - _m12, 2.));
        if (_s < _epsilon)
        {
            _s = 1.;
        }
        Set((_m32 - _m23) / _s,
            (_m13 - _m31) / _s,
            (_m21 - _m12) / _s,
            acos((_m11 + _m22 + _m33 - 1.) / 2.));
    }

    inline void Vector4::Min(const Vector4 &v) noexcept
    {
        mX = min(v.mX, mX);
        mY = min(v.mY, mY);
        mZ = min(v.mZ, mZ);
        mW = min(v.mW, mW);
    }

    inline void Vector4::Max(const Vector4 &v) noexcept
    {
        mX = max(v.mX, mX);
        mY = max(v.mY, mY);
        mZ = max(v.mZ, mZ);
        mW = max(v.mW, mW);
    }

    inline void Vector4::Clamp(const Vector4 &minVec, const Vector4 &maxVec) noexcept
    {
        mX = max(minVec.mX, min(maxVec.mX, mX));
        mY = max(minVec.mY, min(maxVec.mY, mY));
        mZ = max(minVec.mZ, min(maxVec.mZ, mZ));
        mW = max(minVec.mW, min(maxVec.mW, mW));
    }

    inline void Vector4::Clamp(double minVal, double maxVal) noexcept
    {
        mX = max(minVal, min(maxVal, mX));
        mY = max(minVal, min(maxVal, mY));
        mZ = max(minVal, min(maxVal, mZ));
        mW = max(minVal, min(maxVal, mW));
    }

    inline void Vector4::Floor() noexcept
    {
        mX = floor(mX);
        mY = floor(mY);
        mZ = floor(mZ);
        mW = floor(mW);
    }

    inline void Vector4::Ceil() noexcept
    {
        mX = ceil(mX);
        mY = ceil(mY);
        mZ = ceil(mZ);
        mW = ceil(mW);
    }

    inline void Vector4::Round() noexcept
    {
        mX = round(mX);
        mY = round(mY);
        mZ = round(mZ);
        mW = round(mW);
    }

    inline void Vector4::RoundToZero() noexcept
    {
        mX = mX < 0. ? ceil(mX) : round(mX);
        mY = mY < 0. ? ceil(mY) : round(mY);
        mZ = mZ < 0. ? ceil(mZ) : round(mZ);
        mW = mW < 0. ? ceil(mW) : round(mW);
    }

    inline Vector4 Vector4::Mined(const Vector4 &v) const noexcept
    {
        return Vector4(min(v.mX, mX),
                       min(v.mY, mY),
                       min(v.mZ, mZ),
                       min(v.mW, mW));
    }

    inline Vector4 Vector4::Maxed(const Vector4 &v) const noexcept
    {
        return Vector4(max(v.mX, mX),
                       max(v.mY, mY),
                       max(v.mZ, mZ),
                       max(v.mW, mW));
    }

    inline Vector4 Vector4::Clamped(const Vector4 &minVec, const Vector4 &maxVec) const noexcept
    {
        return Vector4(max(minVec.mX, min(maxVec.mX, mX)),
                       max(minVec.mY, min(maxVec.mY, mY)),
                       max(minVec.mZ, min(maxVec.mZ, mZ)),
                       max(minVec.mW, min(maxVec.mW, mW)));
    }

    inline Vector4 Vector4::Clamped(double minVal, double maxVal) const noexcept
    {
        return Vector4(max(minVal, min(maxVal, mX)),
                       max(minVal, min(maxVal, mY)),
                       max(minVal, min(maxVal, mZ)),
                       max(minVal, min(maxVal, mW)));
    }

    inline Vector4 Vector4::Floored() const noexcept
    {
        return Vector4(floor(mX),
                       floor(mY),
                       floor(mZ),
                       floor(mW));
    }

    inline Vector4 Vector4::Ceiled() const noexcept
    {
        return Vector4(ceil(mX),
                       ceil(mY),
                       ceil(mZ),
                       ceil(mW));
    }

    inline Vector4 Vector4::Rounded() const noexcept
    {
        return Vector4(round(mX),
                       round(mY),
                       round(mZ),
                       round(mW));
    }

    inline Vector4 Vector4::RoundedToZero() const noexcept
    {
        return Vector4(mX < 0. ? ceil(mX) : round(mX),
                       mY < 0. ? ceil(mY) : round(mY),
                       mZ < 0. ? ceil(mZ) : round(mZ),
                       mW < 0. ? ceil(mW) : round(mW));
    }

    inline void Vector4::Negate() noexcept
    {
        mX = -mX;
        mY = -mY;
        mZ = -mZ;
        mW = -mW;
    }

    inline Vector4 Vector4::operator-(void) const noexcept
    {
        return Vector4(-mX,
                       -mY,
                       -mZ,
                       -mW);
    }

    inline double Vector4::Dot(const Vector4 &v) const noexcept
    {
        return mX * v.mX + mY * v.mY + mZ * v.mZ + mW * v.mW;
    }

    inline double Vector4::LengthSq() const noexcept
    {
        return mX * mX + mY * mY + mZ * mZ + mW * mW;
    }

    inline double Vector4::Length() const noexcept
    {
        return sqrt(LengthSq());
    }

    inline double Vector4::MamhattanLength() const noexcept
    {
        return abs(mX) + abs(mY) + abs(mZ) + abs(mW);
    }

    inline void Vector4::Normalize() noexcept
    {
        double _l = Length();
        if (_l == 0.)
        {
            _l = 1.;
        }
        operator/=(_l);
    }

    inline Vector4 Vector4::Normalized() const noexcept
    {
        double _l = Length();
        if (_l == 0.)
        {
            _l = 1.;
        }
        return operator/(_l);
    }

    inline void Vector4::SetLength(double l) noexcept
    {
        Normalize();
        operator*=(l);
    }

    inline void Vector4::Lerp(const Vector4 &v, double alpha) noexcept
    {
        mX += (v.mX - mX) * alpha;
        mY += (v.mY - mY) * alpha;
        mZ += (v.mZ - mZ) * alpha;
        mW += (v.mW - mW) * alpha;
    }

    inline Vector4 Vector4::Lerped(const Vector4 &v, double alpha) const noexcept
    {
        return Vector4(mX + (v.mX - mX) * alpha,
                       mY + (v.mY - mY) * alpha,
                       mZ + (v.mZ - mZ) * alpha,
                       mW + (v.mW - mW) * alpha);
    }

    inline bool Vector4::Equals(const Vector4 &v, uint32_t ulp) const noexcept
    {
        return MathUtil::AlmosetEquals(mX, v.mX, ulp) &&
               MathUtil::AlmosetEquals(mY, v.mY, ulp) &&
               MathUtil::AlmosetEquals(mZ, v.mZ, ulp) &&
               MathUtil::AlmosetEquals(mW, v.mW, ulp);
    }

    inline bool Vector4::operator==(const Vector4 &v) const noexcept
    {
        return Equals(v);
    }

    inline std::ostream &operator<<(std::ostream &os, const Vector4 &v)
    {
        os << "{type:Vector4,"
           << "x:"
           << v.mX
           << ",y:"
           << v.mY
           << ",z:"
           << v.mZ
           << ",w:"
           << v.mW
           << "}";
        return os;
    }

} // namespace Three
#undef _USE_MATH_DEFINES