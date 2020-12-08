#include "Euler.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "MathUtil.h"
#include "Vector3.h"

using namespace std;

namespace Three
{
    inline Euler::Euler() noexcept : mX(0.),
                                     mY(0.),
                                     mZ(0.),
                                    mOrder(EulerOrder::XYZ)
    {
    }

    inline Euler::Euler(double x,
                        double y,
                        double z,
                        const EulerOrder order) noexcept : mX(x),
                                                           mY(y),
                                                           mZ(z),
                                                           mOrder(order)
    {
    }

    inline double Euler::X() const noexcept
    {
        return mX;
    }

    inline double Euler::Y() const noexcept
    {
        return mY;
    }

    inline double Euler::Z() const noexcept
    {
        return mZ;
    }

    inline EulerOrder Euler::Order() const noexcept
    {
        return mOrder;
    }

    inline void Euler::SetX(double x) noexcept
    {
        mX = x;
    }

    inline void Euler::SetY(double y) noexcept
    {
        mY = y;
    }

    inline void Euler::SetZ(double z) noexcept
    {
        mZ = z;
    }

    inline void Euler::SetOrder(const EulerOrder order) noexcept
    {
        mOrder = order;
    }

    inline void Euler::SetFromVector3(const Vector3& vec, EulerOrder order) noexcept
    {
        mX = vec.X();
        mY = vec.Y();
        mZ = vec.Z();
        mOrder = order == EulerOrder::NONE ? mOrder : order;
    }

    inline void Euler::Set(double x, double y, double z,
                           const EulerOrder order) noexcept
    {
        mX = x;
        mY = y;
        mZ = z;
        mOrder = order == EulerOrder::NONE ? mOrder : order;
    }

    inline void Euler::SetFromRotationMatrix(const Matrix4 &m,
                           const EulerOrder order)
    {
        const double _m11 = m[0], _m12 = m[4], _m13 = m[8];
        const double _m21 = m[1], _m22 = m[5], _m23 = m[9];
        const double _m31 = m[2], _m32 = m[6], _m33 = m[10];
        const EulerOrder _order = order == EulerOrder::NONE ? mOrder : order;
        switch (_order)
        {
        case EulerOrder::XYZ:
            mY = asin(MathUtil::Clamp(_m13, -1., 1.));
            if (abs(_m13) < 0.9999999)
            {
                mX = atan2(-_m23, _m33);
                mZ = atan2(-_m12, _m11);
            }
            else
            {
                mX = atan2(_m32, _m22);
                mZ = 0.;
            }
            break;
        case EulerOrder::YXZ:
            mX = asin(-MathUtil::Clamp(_m23, -1., 1.));
            if (abs(_m23) < 0.9999999)
            {
                mY = atan2(_m13, _m33);
                mZ = atan2(_m21, _m22);
            }
            else
            {
                mY = atan2(-_m31, _m11);
                mZ = 0.;
            }
            break;
        case EulerOrder::ZXY:
            mX = asin(MathUtil::Clamp(_m32, -1., 1.));
            if (abs(_m32) < 0.9999999)
            {
                mY = atan2(-_m31, _m33);
                mZ = atan2(-_m12, _m22);
            }
            else
            {
                mY = 0.;
                mZ = atan2(-_m21, _m11);
            }
            break;
        case EulerOrder::ZYX:
            mY = asin(-MathUtil::Clamp(_m31, -1., 1.));
            if (abs(_m31) < 0.9999999)
            {
                mX = atan2(_m32, _m33);
                mZ = atan2(_m21, _m11);
            }
            else
            {
                mX = 0.;
                mZ = atan2(-_m12, _m22);
            }
            break;
        case EulerOrder::YZX:
            mZ = asin(MathUtil::Clamp(_m21, -1., 1.));
            if (abs(_m21) < 0.9999999)
            {
                mX = atan2(-_m23, _m22);
                mY = atan2(-_m31, _m11);
            }
            else
            {
                mX = 0.;
                mY = atan2(_m13, _m33);
            }
            break;
        case EulerOrder::XZY:
            mZ = asin(-MathUtil::Clamp(_m12, -1., 1.));
            if (abs(_m12) < 0.9999999)
            {
                mX = atan2(_m32, _m22);
                mY = atan2(_m13, _m11);
            }
            else
            {
                mX = atan2(-_m23, _m33);
                mY = 0.;
            }
            break;
        default:
            break;
        }
        mOrder = _order;
    }

    inline void Euler::SetFromQuaternion(const Quaternion &q,
                           const EulerOrder order)
    {
        Matrix4 _m;
        _m.MakeRotationFromQuaternion(q);
        SetFromRotationMatrix(_m, order);
    }

    inline void Euler::ReOrder(const EulerOrder newOrder)
    {
        const Quaternion _q(*this);
        SetFromQuaternion(_q, newOrder);
    }

    inline bool Euler::Equals(const Euler& euler, uint32_t ulp) const noexcept
    {
        return MathUtil::AlmosetEquals(euler.mX, mX, ulp) &&
            MathUtil::AlmosetEquals(euler.mY, mY, ulp) &&
            MathUtil::AlmosetEquals(euler.mZ, mZ, ulp) &&
            euler.mOrder == mOrder;
    }

    inline bool Euler::operator==(const Euler& euler) const noexcept
    {
        return Equals(euler);
    }

    inline Vector3 Euler::ToVector3() const
    {
        return Vector3(mX, mY, mZ);
    }

    inline string Euler::GetOrderString() const noexcept
    {
        switch (mOrder)
        {
        case Three::EulerOrder::NONE:
            return "XYZ";
        case Three::EulerOrder::XYZ:
            return "XYZ";
        case Three::EulerOrder::YZX:
            return "YZX";
        case Three::EulerOrder::ZXY:
            return "ZXY";
        case Three::EulerOrder::XZY:
            return "XZY";
        case Three::EulerOrder::YXZ:
            return "YXZ";
        case Three::EulerOrder::ZYX:
            return "ZYX";
        case Three::EulerOrder::XYX:
            return "XYX";
        case Three::EulerOrder::YZY:
            return "YZY";
        case Three::EulerOrder::ZXZ:
            return "ZXZ";
        case Three::EulerOrder::XZX:
            return "XZX";
        case Three::EulerOrder::YXY:
            return "YXY";
        case Three::EulerOrder::ZYZ:
            return "ZYZ";
        default:
            return "XYZ";
        }
    }

    inline std::ostream &operator<<(std::ostream &os, const Euler &e)
    {
        os << "{type:'Euler',"
           << "x:" << e.X() << ","
           << "y:" << e.Y() << ","
           << "z:" << e.Z() << ","
           << "order:" << "'" << e.GetOrderString() << "'" << "}";
        return os;
    }

} // namespace Three
