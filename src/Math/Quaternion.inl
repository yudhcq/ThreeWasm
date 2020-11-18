#include "Quaternion.h"
#include "../Core/BufferAttribute.h"
#include "Euler.h"
#include "Vector3.h"

using namespace std;

namespace Three::Math
{
    inline Quaternion::Quaternion() noexcept : mX(0.),
                                               mY(0.),
                                               mZ(0.),
                                               mW(1.)
    {
    }

    inline Quaternion::Quaternion(const Euler &e) noexcept
    {
        SetFromEuler(e);
    }

    inline Quaternion::Quaternion(const Vector3 &axis,
                                  double angle) noexcept
    {
        SetFromAxisAngle(axis, angle);
    }

    inline Quaternion::Quaternion(double x,
                                  double y,
                                  double z,
                                  double w) noexcept : mX(x),
                                                       mY(y),
                                                       mZ(z),
                                                       mW(w)
    {
    }

    inline double Quaternion::X() const noexcept
    {
        return mX;
    }

    inline double Quaternion::Y() const noexcept
    {
        return mY;
    }

    inline double Quaternion::Z() const noexcept
    {
        return mZ;
    }

    inline double Quaternion::W() const noexcept
    {
        return mW;
    }

    inline void Quaternion::SetX(double x) noexcept
    {
        mX = x;
    }

    inline void Quaternion::SetY(double y) noexcept
    {
        mY = y;
    }

    inline void Quaternion::SetZ(double z) noexcept
    {
        mZ = z;
    }

    inline void Quaternion::SetW(double w) noexcept
    {
        mW = w;
    }

    inline void Quaternion::Set(double x,
                                double y,
                                double z,
                                double w) noexcept
    {
        mX = x;
        mY = y;
        mZ = z;
        mW = w;
    }

    inline void Quaternion::SetFromEuler(const Euler &euler) noexcept
    {
        const double _c1 = cos(euler.X() / 2.);
        const double _c2 = cos(euler.Y() / 2.);
        const double _c3 = cos(euler.Z() / 2.);

        const double _s1 = sin(euler.X() / 2.);
        const double _s2 = sin(euler.Y() / 2.);
        const double _s3 = sin(euler.Z() / 2.);

        switch (euler.Order())
        {
        case EulerOrder::XYZ:
            mX = _s1 * _c2 * _c3 + _c1 * _s2 * _s3;
            mY = _c1 * _s2 * _c3 - _s1 * _c2 * _s3;
            mZ = _c1 * _c2 * _s3 + _s1 * _s2 * _c3;
            mW = _c1 * _c2 * _c3 - _s1 * _s2 * _s3;
            break;
        case EulerOrder::YXZ:
            mX = _s1 * _c2 * _c3 + _c1 * _s2 * _s3;
            mY = _c1 * _s2 * _c3 - _s1 * _c2 * _s3;
            mZ = _c1 * _c2 * _s3 - _s1 * _s2 * _c3;
            mW = _c1 * _c2 * _c3 + _s1 * _s2 * _s3;
            break;
        case EulerOrder::ZXY:
            mX = _s1 * _c2 * _c3 - _c1 * _s2 * _s3;
            mY = _c1 * _s2 * _c3 + _s1 * _c2 * _s3;
            mZ = _c1 * _c2 * _s3 + _s1 * _s2 * _c3;
            mW = _c1 * _c2 * _c3 - _s1 * _s2 * _s3;
            break;
        case EulerOrder::ZYX:
            mX = _s1 * _c2 * _c3 - _c1 * _s2 * _s3;
            mY = _c1 * _s2 * _c3 + _s1 * _c2 * _s3;
            mZ = _c1 * _c2 * _s3 - _s1 * _s2 * _c3;
            mW = _c1 * _c2 * _c3 + _s1 * _s2 * _s3;
            break;
        case EulerOrder::XZY:
            mX = _s1 * _c2 * _c3 + _c1 * _s2 * _s3;
            mY = _c1 * _s2 * _c3 + _s1 * _c2 * _s3;
            mZ = _c1 * _c2 * _s3 - _s1 * _s2 * _c3;
            mW = _c1 * _c2 * _c3 - _s1 * _s2 * _s3;
            break;
        case EulerOrder::YZX:
            mX = _s1 * _c2 * _c3 - _c1 * _s2 * _s3;
            mY = _c1 * _s2 * _c3 - _s1 * _c2 * _s3;
            mZ = _c1 * _c2 * _s3 + _s1 * _s2 * _c3;
            mW = _c1 * _c2 * _c3 + _s1 * _s2 * _s3;
            break;
        default:
            break;
        }
    }

    inline void Quaternion::SetFromAxisAngle(const Vector3 &axis, double angle) noexcept
    {
        const double _s = sin(angle / 2.);
        mX = axis.X() * _s;
        mY = axis.Y() * _s;
        mZ = axis.Z() * _s;
        mW = cos(angle / 2.);
    }

    inline void Quaternion::SetFromRotationMatrix(const Matrix4 &m) noexcept
    {
        const double _m11 = m[0], _m12 = m[4], _m13 = m[8];
        const double _m21 = m[1], _m22 = m[5], _m23 = m[9];
        const double _m31 = m[2], _m32 = m[6], _m33 = m[10];
        const double _trace = _m11 + _m22 + _m33;
        if (_trace > 0)
        {
            const double _s = 0.5 / sqrt(_trace + 1.0);
            mW = 0.25 / _s;
            mX = (_m32 - _m23) * _s;
            mY = (_m13 - _m31) * _s;
            mZ = (_m21 - _m12) * _s;
        }
        else if (_m11 > _m22 && _m11 > _m33)
        {
            const double _s = 2.0 * sqrt(1.0 + _m11 - _m22 - _m33);
            mW = (_m32 - _m23) / _s;
            mX = 0.25 * _s;
            mY = (_m12 + _m21) / _s;
            mZ = (_m13 + _m31) / _s;
        }
        else if (_m22 > _m33)
        {
            const double _s = 2.0 * sqrt(1.0 + _m22 - _m11 - _m33);
            mW = (_m13 - _m31) / _s;
            mX = (_m12 + _m21) / _s;
            mY = 0.25 * _s;
            mZ = (_m23 + _m32) / _s;
        }
        else
        {
            const double _s = 2.0 * sqrt(1.0 + _m33 - _m11 - _m22);
            mW = (_m21 - _m12) / _s;
            mX = (_m13 + _m31) / _s;
            mY = (_m23 + _m32) / _s;
            mZ = 0.25 * _s;
        }
    }

    inline void Quaternion::SetFromUnitVectors(const Vector3 &vFrom, const Vector3 &vTo) noexcept
    {
        const double _eps = 0.000001;
        double _r = vFrom.Dot(vTo) + 1.;
        if (_r < _eps)
        {
            _r = 0.;
            if (abs(vFrom.X()) > abs(vFrom.Z()))
            {
                mX = -vFrom.Y();
                mY = vFrom.X();
                mZ = 0.;
                mW = _r;
            }
            else
            {
                mX = 0.;
                mY = -vFrom.Z();
                mZ = vFrom.Y();
                mW = _r;
            }
        }
        else
        {
            const Vector3 _vec(vFrom.Crossed(vTo));
            mX = _vec.X();
            mY = _vec.Y();
            mZ = _vec.Z();
            mW = _r;
        }

        Normalize();
    }

    inline double Quaternion::AngleTo(const Quaternion &q) const noexcept
    {
        return 2. * acos(abs(MathUtil::Clamp(Dot(q), -1., 1.)));
    }

    inline void Quaternion::RotateTowards(const Quaternion &q, double step) noexcept
    {
        const double _angle = AngleTo(q);
        if (_angle == 0)
        {
            return;
        }
        const double _t = min(1., step / _angle);
        Slerp(q, _t);
    }

    inline void Quaternion::Inverse() noexcept
    {
        Conjugate();
    }

    inline void Quaternion::Conjugate() noexcept
    {
        mX *= -1.;
        mY *= -1.;
        mZ *= -1.;
    }

    inline Quaternion Quaternion::Conjugated() const noexcept
    {
        Quaternion _q(*this);
        _q.Conjugate();
        return _q;
    }

    inline double Quaternion::Dot(const Quaternion &q) const noexcept
    {
        return mX * q.mX + mY * q.mY + mZ * q.mZ + mW * q.mW;
    }

    inline double Quaternion::LengthSq() const noexcept
    {
        return Dot(*this);
    }

    inline double Quaternion::Length() const noexcept
    {
        return sqrt(LengthSq());
    }

    inline void Quaternion::Normalize() noexcept
    {
        const double _l = Length();
        if (_l == 0.)
        {
            mX = mY = mZ = 0.;
            mW = 1.;
        }
        else
        {
            mX /= _l;
            mY /= _l;
            mZ /= _l;
            mW /= _l;
        }
    }

    inline Quaternion Quaternion::Normalized() const noexcept
    {
        Quaternion _q(*this);
        _q.Normalize();
        return _q;
    }

    inline void Quaternion::operator*=(const Quaternion &q) noexcept
    {
        *this = *this * q;
    }

    inline void Quaternion::Premultiply(const Quaternion &q) noexcept
    {
        *this = q * *this;
    }

    inline Quaternion Quaternion::Premultiplied(const Quaternion &q) const noexcept
    {
        return q * *this;
    }

    inline Quaternion Quaternion::operator*(const Quaternion &q) const noexcept
    {
        return Quaternion(mX * q.mW + mW * q.mX + mY * q.mZ - mZ * q.mY,
                          mY * q.mW + mW * q.mY + mZ * q.mX - mX * q.mZ,
                          mZ * q.mW + mW * q.mZ + mX * q.mY - mY * q.mX,
                          mW * q.mW - mX * q.mX - mY * q.mY - mZ * q.mZ);
    }

    inline void Quaternion::FromBufferAttribute(const Core::BufferAttribute &attrbute, const size_t)
    {
        // todo
    }

    inline void Quaternion::Slerp(const Quaternion &qb, double t) noexcept
    {
        if (t == 0.)
        {
            return;
        }
        if (t == 1.)
        {
            *this = qb;
        }

        const double _x = mX, _y = mY, _z = mZ, _w = mW;
        double _cosHalfTheta = _w * qb.mW + mX * qb.mX + mY * qb.mY + mZ * qb.mZ;
        if (_cosHalfTheta < 0.)
        {
            mW = -qb.mW;
            mX = -qb.mX;
            mY = -qb.mY;
            mZ = -qb.mZ;

            _cosHalfTheta = -_cosHalfTheta;
        }
        else
        {
            *this = qb;
        }
        if (_cosHalfTheta >= 1.)
        {
            mW = _w;
            mX = _x;
            mY = _y;
            mZ = _z;
            return;
        }

        const double _sqrSinHalfTheta = 1.0 - _cosHalfTheta * _cosHalfTheta;
        if (_sqrSinHalfTheta <= DBL_EPSILON)
        {

            double _s = 1 - t;
            mW = _s * _w + t * mW;
            mX = _s * _x + t * mX;
            mY = _s * _y + t * mY;
            mZ = _s * _z + t * mZ;

            Normalize();
        }

        const double _sinHalfTheta = sqrt(_sqrSinHalfTheta);
        const double _halfTheta = atan2(_sinHalfTheta, _cosHalfTheta);
        const double _ratioA = sin((1. - t) * _halfTheta) / _sinHalfTheta,
               _ratioB = sin(t * _halfTheta) / _sinHalfTheta;

        mW = (_w * _ratioA + mW * _ratioB);
        mX = (_x * _ratioA + mX * _ratioB);
        mY = (_y * _ratioA + mY * _ratioB);
        mZ = (_z * _ratioA + mZ * _ratioB);
    }

    inline Quaternion Quaternion::Slerped(const Quaternion &qb, double t) const noexcept
    {
        Quaternion _q(*this);
        _q.Slerp(qb, t);
        return _q;
    }

    inline void Quaternion::Identity() noexcept
    {
        mX = 0.;
        mY = 0.;
        mZ = 0.;
        mW = 1.;
    }

    inline bool Quaternion::Equals(const Quaternion &q, uint32_t ulp) const noexcept
    {
        return MathUtil::AlmosetEquals(mX, q.mX, ulp) &&
               MathUtil::AlmosetEquals(mY, q.mY, ulp) &&
               MathUtil::AlmosetEquals(mZ, q.mZ, ulp) &&
               MathUtil::AlmosetEquals(mW, q.mW, ulp);
    }

    inline bool Quaternion::operator==(const Quaternion &q) const noexcept
    {
        return Equals(q);
    }

    inline ostream &operator<<(ostream &os, const Quaternion &q)
    {
        os << "{type:'Quaternion',x:"
           << q.X()
           << ",y:"
           << q.Y()
           << ",z:"
           << q.Z()
           << ",w:"
           << q.W()
           << "}";
        return os;
    }

} // namespace Three::Math
