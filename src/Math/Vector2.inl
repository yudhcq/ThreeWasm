
#include <exception>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector2.h"
#include "Matrix3.h"
#include "MathUtil.h"
#include "../Core/BufferAttribute.h"

using namespace std;

namespace Three
{
    inline Vector2::Vector2() noexcept : mX(0.),
                                         mY(0.)
    {
    }

    inline Vector2::Vector2(double scalar) noexcept : mX(scalar),
                                                      mY(scalar)
    {
    }

    inline Vector2::Vector2(double x, double y) noexcept : mX(x),
                                                           mY(y)
    {
    }

    inline void Vector2::SetX(double x) noexcept
    {
        mX = x;
    }

    inline void Vector2::SetY(double y) noexcept
    {
        mY = y;
    }

    inline void Vector2::Set(double x, double y) noexcept
    {
        mX = x;
        mY = y;
    }

    inline void Vector2::Set(double scalar) noexcept
    {
        mX = scalar;
        mY = scalar;
    }

    inline double Vector2::X() const noexcept
    {
        return mX;
    }

    inline double Vector2::Y() const noexcept
    {
        return mY;
    }

    inline double Vector2::Width() const noexcept
    {
        return mX;
    }

    inline double Vector2::Height() const noexcept
    {
        return mY;
    }

    inline void Vector2::SetWidth(double width) noexcept
    {
        mX = width;
    }

    inline void Vector2::SetHeight(double height) noexcept
    {
        mY = height;
    }

    inline double Vector2::operator[](const size_t index) const
    {
        if (index >= 2)
        {
            throw range_error("const Vector2 operator[] 索引项超过2");
        }
        else
        {
            return reinterpret_cast<const double *>(this)[index];
        }
    }

    inline double &Vector2::operator[](const size_t index)
    {
        if (index >= 2)
        {
            throw range_error("Vector2 operator[] 索引项超过2");
        }
        else
        {
            return reinterpret_cast<double *>(this)[index];
        }
    }

    inline void Vector2::operator+=(const Vector2 &v) noexcept
    {
        mX += v.mX;
        mY += v.mY;
    }

    inline void Vector2::operator+=(double s) noexcept
    {
        mX += s;
        mY += s;
    }

    inline Vector2 Vector2::operator+(const Vector2 &v) const noexcept
    {
        return Vector2(mX + v.mX, mY + v.mY);
    }

    inline void Vector2::AddScaledVector(const Vector2 &v, double s) noexcept
    {
        mX += v.mX * s;
        mY += v.mY * s;
    }

    inline Vector2 Vector2::AddedScaleVector(const Vector2 &v, double s) const noexcept
    {
        return Vector2(mX + v.mX * s, mY + v.mY * s);
    }

    inline void Vector2::operator-=(const Vector2 &v) noexcept
    {
        mX -= v.mX;
        mY -= v.mY;
    }

    inline void Vector2::operator-=(double s) noexcept
    {
        mX -= s;
        mY -= s;
    }

    inline Vector2 Vector2::operator-(const Vector2 &v) const noexcept
    {
        return Vector2(mX - v.mX, mY - v.mY);
    }

    inline Vector2 Vector2::operator-(double s) const noexcept
    {
        return Vector2(mX - s, mY - s);
    }

    inline void Vector2::operator*=(const Vector2 &v) noexcept
    {
        mX *= v.mX;
        mY *= v.mY;
    }

    inline void Vector2::operator*=(double s) noexcept
    {
        mX *= s;
        mY *= s;
    }

    inline Vector2 Vector2::operator*(const Vector2 &v) const noexcept
    {
        return Vector2(mX * v.mX, mY * v.mY);
    }

    inline void Vector2::operator/=(const Vector2 &v)
    {
        if (v.mX == 0 || v.mY == 0)
        {
            throw logic_error("Vector2 operator/=(Vector2) 除0操作");
        }

        mX /= v.mX;
        mY /= v.mY;
    }

    inline void Vector2::operator/=(double s)
    {
        if (s == 0)
        {
            throw logic_error("Vector2 operator/=(double) 除0操作");
        }

        mX /= s;
        mY /= s;
    }

    inline Vector2 Vector2::operator/(const Vector2 &v) const
    {
        if (v.mX == 0 || v.mY == 0)
        {
            throw logic_error("Vector2 operator/(Vector2) 除0操作");
        }

        return Vector2(mX / v.mX, mY / v.mY);
    }

    inline Vector2 Vector2::operator/(double s) const
    {
        if (s == 0)
        {
            throw logic_error("Vector2 operator/=(double) 除0操作");
        }

        return Vector2(mX / s, mY / s);
    }

    inline void Vector2::Apply(const Matrix3 &m) noexcept
    {
        const double _x = mX, _y = mY;
        mX = _x * m[0] + _y * m[3] + m[6];
        mY = _x * m[1] + _y * m[4] + m[7];
    }

    inline Vector2 Vector2::Applied(const Matrix3 &m) const noexcept
    {
        Vector2 _vec(*this);
        _vec.Apply(m);
        return _vec;
    }

    inline void Vector2::Min(const Vector2 &v) noexcept
    {
        mX = min(mX, v.mX);
        mY = min(mY, v.mY);
    }

    inline void Vector2::Max(const Vector2 &v) noexcept
    {
        mX = max(mX, v.mX);
        mY = max(mY, v.mY);
    }

    inline Vector2 Vector2::Mined(const Vector2 &v) const noexcept
    {
        return Vector2(min(mX, v.mX), min(mY, v.mY));
    }

    inline Vector2 Vector2::Maxed(const Vector2 &v) const noexcept
    {
        return Vector2(max(mX, v.mX), max(mY, v.mY));
    }

    inline void Vector2::Clamp(const Vector2 &minVec, const Vector2 &maxVec) noexcept
    {
        mX = max(minVec.mX, min(maxVec.mX, mX));
        mY = max(minVec.mY, min(maxVec.mY, mY));
    }

    inline void Vector2::Clamp(double minVal, double maxVal) noexcept
    {
        mX = max(minVal, min(maxVal, mX));
        mY = max(minVal, min(maxVal, mY));
    }

    inline Vector2 Vector2::Clamped(const Vector2 &minVec, const Vector2 &maxVec) const noexcept
    {
        return Vector2(max(minVec.mX, min(maxVec.mX, mX)),
                       max(minVec.mY, min(maxVec.mY, mY)));
    }

    inline Vector2 Vector2::Clamped(double minVal, double maxVal) const noexcept
    {
        return Vector2(max(minVal, min(maxVal, mX)),
                       max(minVal, min(maxVal, mY)));
    }

    inline void Vector2::ClampLength(double minVal, double maxVal) noexcept
    {
        SetLength(max(minVal, min(maxVal, Length())));
    }

    inline Vector2 Vector2::ClampedLength(double minVal, double maxVal) noexcept
    {
        Vector2 _vec(*this);
        _vec.ClampLength(minVal, maxVal);
        return _vec;
    }

    inline void Vector2::Floor() noexcept
    {
        mX = floor(mX);
        mY = floor(mY);
    }

    inline Vector2 Vector2::Floored() const noexcept
    {
        return Vector2(floor(mX), floor(mY));
    }

    inline void Vector2::Ceil() noexcept
    {
        mX = ceil(mX);
        mY = ceil(mY);
    }

    inline Vector2 Vector2::Ceiled() const noexcept
    {
        return Vector2(ceil(mX), ceil(mY));
    }

    inline void Vector2::Round() noexcept
    {
        mX = round(mX);
        mY = round(mY);
    }

    inline Vector2 Vector2::Rounded() const noexcept
    {
        return Vector2(round(mX), round(mY));
    }

    inline void Vector2::RoundToZero() noexcept
    {
        mX = mX < 0 ? ceil(mX) : floor(mX);
        mY = mY < 0 ? ceil(mY) : floor(mY);
    }

    inline Vector2 Vector2::RoundedToZero() const noexcept
    {
        return Vector2(mX < 0 ? ceil(mX) : floor(mX),
                       mY < 0 ? ceil(mY) : floor(mY));
    }

    inline void Vector2::Negate() noexcept
    {
        mX = -mX;
        mY = -mY;
    }

    inline Vector2 Vector2::operator-(void) const noexcept
    {
        return Vector2(-mX, -mY);
    }

    inline double Vector2::Dot(const Vector2 &v) const noexcept
    {
        return mX * v.mX + mY * v.mY;
    }

    inline double Vector2::Cross(const Vector2 &v) const noexcept
    {
        return mX * v.mY - mY * v.mX;
    }

    inline double Vector2::Length() const noexcept
    {
        return sqrt(LengthSq());
    }

    inline double Vector2::LengthSq() const noexcept
    {
        return mX * mX + mY * mY;
    }

    inline double Vector2::ManhattanLength() const noexcept
    {
        return abs(mX) + abs(mY);
    }

    inline void Vector2::Normalize() noexcept
    {
        double _l = Length();
        if (_l == 0)
        {
            _l = 1;
        }
        operator/=(_l);
    }

    inline Vector2 Vector2::Normalized() const noexcept
    {
        Vector2 _vec(*this);
        _vec.Normalize();
        return _vec;
    }

    inline double Vector2::Angle() const noexcept
    {
        return atan2(-mY, -mX) + M_PI;
    }

    inline double Vector2::DistanceTo(const Vector2 &v) const noexcept
    {
        return sqrt(DistanceToSquared(v));
    }

    inline double Vector2::DistanceToSquared(const Vector2 &v) const noexcept
    {
        return pow(mX - v.mX, 2.) + pow(mY - v.mY, 2.);
    }

    inline double Vector2::ManhattanDistanceTo(const Vector2 &v) const noexcept
    {
        return abs(mX - v.mX) + abs(mY - v.mY);
    }

    inline void Vector2::SetLength(double length) noexcept
    {
        Normalize();
        operator*=(length);
    }

    inline void Vector2::Lerp(const Vector2 &v, double alpha) noexcept
    {
        mX += (v.mX - mX) * alpha;
        mY += (v.mY - mY) * alpha;
    }

    inline Vector2 Vector2::Lerped(const Vector2 &v, double alpha) const noexcept
    {
        return Vector2(mX + (v.mX - mX) * alpha, mY + (v.mY - mY) * alpha);
    }

    inline bool Vector2::Equals(const Vector2 &v, uint32_t ulp) const noexcept
    {
        return MathUtil::AlmosetEquals(mX, v.mX, ulp) && MathUtil::AlmosetEquals(mY, v.mY, ulp);
    }

    inline bool Vector2::operator==(const Vector2 &v) const noexcept
    {
        return Equals(v);
    }

    /*inline void Vector2::FromArray(const std::vector<double> &array, const size_t offset)
    {
        if (array.size() < offset + 2)
        {
            throw range_error("vector2 fromArray array size error");
        }
        mX = array[offset];
        mX = array[offset + 1];
    }

    inline void Vector2::ToArray(std::vector<double> &array, const size_t offset)
    {
        const size_t _arraySize = array.size();
        if (_arraySize < offset)
        {
            throw range_error("vector2 fromArray array size error");
        }
        else if (_arraySize == offset)
        {
            array.push_back(mX);
            array.push_back(mY);
        }
        else if (_arraySize == offset + 1)
        {
            array[offset] = mX;
            array.push_back(mY);
        }
        else
        {
            array[offset] = mX;
            array[offset + 1] = mY;
        }
    }*/

    //inline void Vector2::FromBufferAttribute(const Core::BufferAttribute &attribute, const size_t index) noexcept
    //{
    //    // todo
    //}

    inline void Vector2::RotateAround(const Vector2 &center, double angle) noexcept
    {
        const double _s = sin(angle), _c = cos(angle);
        const double _x = mX - center.mX, _y = mY - center.mY;
        mX = _x * _c - _y * _s + center.mX;
        mY = _x * _s + _y * _c + center.mY;
    }

    inline Vector2 Vector2::RotatedAround(const Vector2& center, double angle) const noexcept
    {
        Vector2 _v(*this);
        _v.RotateAround(center, angle);
        return _v;
    }

    inline std::ostream &operator<<(std::ostream &os, const Vector2 &v)
    {
        os << "{type:'Vector2',"
           << "x:"
           << v.mX
           << ","
           << "y:"
           << v.mY
           << "}";
        return os;
    }

    inline Vector2 operator*(const Vector2 &v, double s) noexcept
    {
        return Vector2(v.X() * s, v.Y() * s);
    }

    inline Vector2 operator*(double s, const Vector2 &v) noexcept
    {
        return v * s;
    }

    inline Vector2 operator+(const Vector2 &v, double s) noexcept
    {
        return Vector2(v.X() + s, v.Y() + s);
    }

    inline Vector2 operator+(double s, const Vector2 &v) noexcept
    {
        return v + s;
    }

} // namespace Three
#undef _USE_MATH_DEFINES
