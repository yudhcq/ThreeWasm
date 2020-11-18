#include "Matrix4.h"
#include "Vector3.h"
#include "Euler.h"
#include "MathUtil.h"

using namespace std;

namespace Three::Math
{
    inline Matrix4::Matrix4() noexcept
    {
        mElements[0] = 1., mElements[1] = 0., mElements[2] = 0., mElements[3] = 0.;
        mElements[4] = 0., mElements[5] = 1., mElements[6] = 0., mElements[7] = 0.;
        mElements[8] = 0., mElements[9] = 0., mElements[10] = 1., mElements[11] = 0.;
        mElements[12] = 0., mElements[13] = 0., mElements[14] = 0., mElements[15] = 1.;
    }

    inline Matrix4::Matrix4(double n11,
                            double n12,
                            double n13,
                            double n14,
                            double n21,
                            double n22,
                            double n23,
                            double n24,
                            double n31,
                            double n32,
                            double n33,
                            double n34,
                            double n41,
                            double n42,
                            double n43,
                            double n44) noexcept
    {
        mElements[0] = n11;
        mElements[4] = n12;
        mElements[8] = n13;
        mElements[12] = n14;
        mElements[1] = n21;
        mElements[5] = n22;
        mElements[9] = n23;
        mElements[13] = n24;
        mElements[2] = n31;
        mElements[6] = n32;
        mElements[10] = n33;
        mElements[14] = n34;
        mElements[3] = n41;
        mElements[7] = n42;
        mElements[11] = n43;
        mElements[15] = n44;
    }

    inline void Matrix4::Set(double n11,
                             double n12,
                             double n13,
                             double n14,
                             double n21,
                             double n22,
                             double n23,
                             double n24,
                             double n31,
                             double n32,
                             double n33,
                             double n34,
                             double n41,
                             double n42,
                             double n43,
                             double n44) noexcept
    {
        mElements[0] = n11;
        mElements[4] = n12;
        mElements[8] = n13;
        mElements[12] = n14;
        mElements[1] = n21;
        mElements[5] = n22;
        mElements[9] = n23;
        mElements[13] = n24;
        mElements[2] = n31;
        mElements[6] = n32;
        mElements[10] = n33;
        mElements[14] = n34;
        mElements[3] = n41;
        mElements[7] = n42;
        mElements[11] = n43;
        mElements[15] = n44;
    }
    inline void Matrix4::Identity() noexcept
    {
        *this = Matrix4();
    }

    inline bool Matrix4::IsIndentity() const noexcept
    {
        return *this == Matrix4();
    }

    inline void Matrix4::CopyPosition(const Matrix4 &m) noexcept
    {
        mElements[12] = m[12];
        mElements[13] = m[13];
        mElements[14] = m[14];
    }

    inline void Matrix4::ExtractBasis(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const noexcept
    {
        xAxis.SetFromMatrixColumn(*this, 0);
        yAxis.SetFromMatrixColumn(*this, 1);
        zAxis.SetFromMatrixColumn(*this, 2);
    }

    inline void Matrix4::MakeBasis(const Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) noexcept
    {
        Set(xAxis.X(), yAxis.X(), zAxis.X(), 0.,
            xAxis.Y(), yAxis.Y(), zAxis.Y(), 0.,
            xAxis.Z(), yAxis.Z(), zAxis.Z(), 0.,
            0., 0., 0., 1.);
    }

    inline void Matrix4::ExtractRotation(const Matrix4 &m) noexcept
    {
        Vector3 _v;
        _v.SetFromMatrixColumn(m, 0);
        const double _scaleX = _v.Length();
        _v.SetFromMatrixColumn(m, 1);
        const double _scaleY = _v.Length();
        _v.SetFromMatrixColumn(m, 2);
        const double _scaleZ = _v.Length();

        mElements[0] = m[0] * _scaleX;
        mElements[1] = m[1] * _scaleX;
        mElements[2] = m[2] * _scaleX;
        mElements[3] = 0.;

        mElements[4] = m[4] * _scaleY;
        mElements[5] = m[5] * _scaleY;
        mElements[6] = m[6] * _scaleY;
        mElements[7] = 0.;

        mElements[8] = m[8] * _scaleZ;
        mElements[9] = m[9] * _scaleZ;
        mElements[10] = m[10] * _scaleZ;
        mElements[11] = 0.;

        mElements[12] = 0.;
        mElements[13] = 0.;
        mElements[14] = 0.;
        mElements[15] = 1.;
    }

    inline void Matrix4::MakeRotationFromEuler(const Euler &euler) noexcept
    {
        const double _x = euler.X(), _y = euler.Y(), _z = euler.Z();
        const double _a = cos(_x), _b = sin(_x);
        const double _c = cos(_y), _d = sin(_y);
        const double _e = cos(_z), _f = sin(_z);

        switch (euler.Order())
        {
        case EulerOrder::XYZ:
        {
            const double _ae = _a * _e, _af = _a * _f, _be = _b * _e, _bf = _b * _f;
            mElements[0] = _c * _e;
            mElements[4] = -_c * _f;
            mElements[8] = _d;

            mElements[1] = _af + _be * _d;
            mElements[5] = _ae - _bf * _d;
            mElements[9] = -_b * _c;

            mElements[2] = _bf - _ae * _d;
            mElements[6] = _be + _af * _d;
            mElements[10] = _a * _c;
            break;
        }
        case EulerOrder::YXZ:
        {
            const double _ce = _c * _c, _cf = _c * _f, _de = _d * _c, df = _d * _f;

            mElements[0] = _ce + df * _b;
            mElements[4] = _de * _b - _cf;
            mElements[8] = _a * _d;

            mElements[1] = _a * _f;
            mElements[5] = _a * _c;
            mElements[9] = -_b;

            mElements[2] = _cf * _b - _de;
            mElements[6] = df + _ce * _b;
            mElements[10] = _a * _c;
            break;
        }
        case EulerOrder::ZXY:  
        {
            const double _ce = _c * _e, _cf = _c * _f, _de = _d * _e, _df = _d * _f;

            mElements[0] = _ce - _df * _b;
            mElements[4] = -_a * _f;
            mElements[8] = _de + _cf * _b;

            mElements[1] = _cf + _de * _b;
            mElements[5] = _a * _e;
            mElements[9] = _df - _ce * _b;

            mElements[2] = -_a * _d;
            mElements[6] = _b;
            mElements[10] = _a * _c;
            break;
        }
        case EulerOrder::ZYX:
        {
            const double _ae = _a * _e, _af = _a * _f, _be = _b * _e, _bf = _b * _f;

            mElements[0] = _c * _e;
            mElements[4] = _be * _d - _af;
            mElements[8] = _ae * _d + _bf;

            mElements[1] = _c * _f;
            mElements[5] = _bf * _d + _ae;
            mElements[9] = _af * _d - _be;

            mElements[2] = -_d;
            mElements[6] = _b * _c;
            mElements[10] = _a * _c;
            break;
        }
        case EulerOrder::YZX:
        {
            const double _ac = _a * _c, _ad = _a * _d, _bc = _b * _c, _bd = _b * _d;

            mElements[0] = _c * _e;
            mElements[4] = _bd - _ac * _f;
            mElements[8] = _bc * _f + _ad;

            mElements[1] = _f;
            mElements[5] = _a * _e;
            mElements[9] = -_b * _e;
            
            mElements[2] = -_d * _e;
            mElements[6] = _ad * _f + _bc;
            mElements[10] = _ac - _bd * _f;
            break;
        }
        case EulerOrder::XZY:
        {
            const double _ac = _a * _c, _ad = _a * _d, _bc = _b * _c, _bd = _b * _d;

            mElements[0] = _c * _e;
            mElements[4] = -_f;
            mElements[8] = _d * _e;

            mElements[1] = _ac * _f + _bd;
            mElements[5] = _a * _e;
            mElements[9] = _ad * _f - _bc;
                           
            mElements[2] = _bc * _f - _ad;
            mElements[6] = _b * _e;
            mElements[10] = _bd * _f + _ac;

            break;
        }
        default:
            break;
        }
        // bottom row
        mElements[3] = 0.;
        mElements[7] = 0.;
        mElements[11] = 0.;
        // last column
        mElements[12] = 0.;
        mElements[13] = 0.;
        mElements[14] = 0.;
        mElements[15] = 1.;
    }

    inline void Matrix4::MakeRotationFromQuaternion(const Quaternion &q) noexcept
    {
        const Vector3 _p, _s(1., 1., 1.);
        Compose(_p, q, _s);
    }

    inline void Matrix4::LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up) noexcept
    {
        Vector3 _z(eye - target);
        if (_z.LengthSq() == 0.)
        {
            _z.SetZ(0.);
        }
        _z.Normalize();
        Vector3 _x(up.Crossed(_z));
        if (_x.LengthSq() == 0.)
        {
            if (abs(up.Z()) == 1.)
            {
                _z[0] += 0.0001;
            }
            else
            {
                _z[2] += 0.0001;
            }
            _z.Normalize();
            _x = up.Crossed(_z);
        }
        _x.Normalize();
        const Vector3 _y(_z.Crossed(_x));
        mElements[0] = _x.X();
        mElements[4] = _y.X();
        mElements[8] = _z.X();
        mElements[1] = _x.Y();
        mElements[5] = _y.Y();
        mElements[9] = _z.Y();
        mElements[2] = _x.Z();
        mElements[6] = _y.Z();
        mElements[10] = _z.Z();
    }

    inline void Matrix4::operator*=(const Matrix4 &m) noexcept
    {
        const double _a11 = mElements[0], _a12 = mElements[4], _a13 = mElements[8], _a14 = mElements[12];
        const double _a21 = mElements[1], _a22 = mElements[5], _a23 = mElements[9], _a24 = mElements[13];
        const double _a31 = mElements[2], _a32 = mElements[6], _a33 = mElements[10], _a34 = mElements[14];
        const double _a41 = mElements[3], _a42 = mElements[7], _a43 = mElements[11], _a44 = mElements[15];

        const double _b11 = m[0], _b12 = m[4], _b13 = m[8], _b14 = m[12];
        const double _b21 = m[1], _b22 = m[5], _b23 = m[9], _b24 = m[13];
        const double _b31 = m[2], _b32 = m[6], _b33 = m[10], _b34 = m[14];
        const double _b41 = m[3], _b42 = m[7], _b43 = m[11], _b44 = m[15];

        mElements[0] = _a11 * _b11 + _a12 * _b21 + _a13 * _b31 + _a14 * _b41;
        mElements[4] = _a11 * _b12 + _a12 * _b22 + _a13 * _b32 + _a14 * _b42;
        mElements[8] = _a11 * _b13 + _a12 * _b23 + _a13 * _b33 + _a14 * _b43;
        mElements[12] = _a11 * _b14 + _a12 * _b24 + _a13 * _b34 + _a14 * _b44;

        mElements[1] = _a21 * _b11 + _a22 * _b21 + _a23 * _b31 + _a24 * _b41;
        mElements[5] = _a21 * _b12 + _a22 * _b22 + _a23 * _b32 + _a24 * _b42;
        mElements[9] = _a21 * _b13 + _a22 * _b23 + _a23 * _b33 + _a24 * _b43;
        mElements[13] = _a21 * _b14 + _a22 * _b24 + _a23 * _b34 + _a24 * _b44;

        mElements[2] = _a31 * _b11 + _a32 * _b21 + _a33 * _b31 + _a34 * _b41;
        mElements[6] = _a31 * _b12 + _a32 * _b22 + _a33 * _b32 + _a34 * _b42;
        mElements[10] = _a31 * _b13 + _a32 * _b23 + _a33 * _b33 + _a34 * _b43;
        mElements[14] = _a31 * _b14 + _a32 * _b24 + _a33 * _b34 + _a34 * _b44;

        mElements[3] = _a41 * _b11 + _a42 * _b21 + _a43 * _b31 + _a44 * _b41;
        mElements[7] = _a41 * _b12 + _a42 * _b22 + _a43 * _b32 + _a44 * _b42;
        mElements[11] = _a41 * _b13 + _a42 * _b23 + _a43 * _b33 + _a44 * _b43;
        mElements[15] = _a41 * _b14 + _a42 * _b24 + _a43 * _b34 + _a44 * _b44;
    }

    inline void Matrix4::operator*=(double s) noexcept
    {
        mElements[0] *= s;
        mElements[4] *= s;
        mElements[8] *= s;
        mElements[12] *= s;
        mElements[1] *= s;
        mElements[5] *= s;
        mElements[9] *= s;
        mElements[13] *= s;
        mElements[2] *= s;
        mElements[6] *= s;
        mElements[10] *= s;
        mElements[14] *= s;
        mElements[3] *= s;
        mElements[7] *= s;
        mElements[11] *= s;
        mElements[15] *= s;
    }

    inline void Matrix4::Premultiply(const Matrix4 &m) noexcept
    {
        *this = m * *this;
    }

    inline Matrix4 Matrix4::operator*(const Matrix4 &m) const noexcept
    {
        Matrix4 _m(*this);
        _m *= m;
        return _m;
    }

    inline Matrix4 Matrix4::Premultiplied(const Matrix4 &m) const noexcept
    {
        return m * *this;
    }

    inline Matrix4 Matrix4::operator*(double s) const noexcept
    {
        Matrix4 _m(*this);
        _m *= s;
        return _m;
    }

    inline double Matrix4::Determinant() const noexcept
    {
        const double _n11 = mElements[0], _n12 = mElements[4], _n13 = mElements[8], _n14 = mElements[12];
        const double _n21 = mElements[1], _n22 = mElements[5], _n23 = mElements[9], _n24 = mElements[13];
        const double _n31 = mElements[2], _n32 = mElements[6], _n33 = mElements[10], _n34 = mElements[14];
        const double _n41 = mElements[3], _n42 = mElements[7], _n43 = mElements[11], _n44 = mElements[15];

        //TODO: make this more efficient
        //( based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm )

        return _n41 * (+_n14 * _n23 * _n32 - _n13 * _n24 * _n32 - _n14 * _n22 * _n33 + _n12 * _n24 * _n33 + _n13 * _n22 * _n34 - _n12 * _n23 * _n34) +
               _n42 * (+_n11 * _n23 * _n34 - _n11 * _n24 * _n33 + _n14 * _n21 * _n33 - _n13 * _n21 * _n34 + _n13 * _n24 * _n31 - _n14 * _n23 * _n31) +
               _n43 * (+_n11 * _n24 * _n32 - _n11 * _n22 * _n34 - _n14 * _n21 * _n32 + _n12 * _n21 * _n34 + _n14 * _n22 * _n31 - _n12 * _n24 * _n31) +
               _n44 * (-_n13 * _n22 * _n31 - _n11 * _n23 * _n32 + _n11 * _n22 * _n33 + _n13 * _n21 * _n32 - _n12 * _n21 * _n33 + _n12 * _n23 * _n31);
    }

    inline void Matrix4::Transpose() noexcept
    {
        double _tmp;
        _tmp = mElements[1];
        mElements[1] = mElements[4];
        mElements[4] = _tmp;
        _tmp = mElements[2];
        mElements[2] = mElements[8];
        mElements[8] = _tmp;
        _tmp = mElements[6];
        mElements[6] = mElements[9];
        mElements[9] = _tmp;
        _tmp = mElements[3];
        mElements[3] = mElements[12];
        mElements[12] = _tmp;
        _tmp = mElements[7];
        mElements[7] = mElements[13];
        mElements[13] = _tmp;
        _tmp = mElements[11];
        mElements[11] = mElements[14];
        mElements[14] = _tmp;
    }

    inline Matrix4 Matrix4::Transposed() const noexcept
    {
        Matrix4 _m(*this);
        _m.Transpose();
        return _m;
    }

    inline void Matrix4::SetPosition(double x, double y, double z) noexcept
    {
        mElements[12] = x;
        mElements[13] = y;
        mElements[14] = z;
    }

    inline void Matrix4::SetPosition(const Vector3 &v) noexcept
    {
        SetPosition(v.X(), v.Y(), v.Z());
    }

    inline Matrix4 Matrix4::GetInverse() const noexcept
    {
        Matrix4 _m;

        const double _n11 = mElements[0], _n21 = mElements[1], _n31 = mElements[2], _n41 = mElements[3];
        const double _n12 = mElements[4], _n22 = mElements[5], _n32 = mElements[6], _n42 = mElements[7];
        const double _n13 = mElements[8], _n23 = mElements[9], _n33 = mElements[10], _n43 = mElements[11];
        const double _n14 = mElements[12], _n24 = mElements[13], _n34 = mElements[14], _n44 = mElements[15];

        const double _t11 = _n23 * _n34 * _n42 - _n24 * _n33 * _n42 + _n24 * _n32 * _n43 - _n22 * _n34 * _n43 - _n23 * _n32 * _n44 + _n22 * _n33 * _n44;
        const double _t12 = _n14 * _n33 * _n42 - _n13 * _n34 * _n42 - _n14 * _n32 * _n43 + _n12 * _n34 * _n43 + _n13 * _n32 * _n44 - _n12 * _n33 * _n44;
        const double _t13 = _n13 * _n24 * _n42 - _n14 * _n23 * _n42 + _n14 * _n22 * _n43 - _n12 * _n24 * _n43 - _n13 * _n22 * _n44 + _n12 * _n23 * _n44;
        const double _t14 = _n14 * _n23 * _n32 - _n13 * _n24 * _n32 - _n14 * _n22 * _n33 + _n12 * _n24 * _n33 + _n13 * _n22 * _n34 - _n12 * _n23 * _n34;

        const double _det = _n11 * _t11 + _n21 * _t12 + _n31 * _t13 + _n41 * _t14;

        if (_det == 0.)
        {
            _m.Set(0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);
        }
        else
        {
            const double _detInv = 1 / _det;

            _m[0] = _t11 * _detInv;
            _m[1] = (_n24 * _n33 * _n41 - _n23 * _n34 * _n41 - _n24 * _n31 * _n43 + _n21 * _n34 * _n43 + _n23 * _n31 * _n44 - _n21 * _n33 * _n44) * _detInv;
            _m[2] = (_n22 * _n34 * _n41 - _n24 * _n32 * _n41 + _n24 * _n31 * _n42 - _n21 * _n34 * _n42 - _n22 * _n31 * _n44 + _n21 * _n32 * _n44) * _detInv;
            _m[3] = (_n23 * _n32 * _n41 - _n22 * _n33 * _n41 - _n23 * _n31 * _n42 + _n21 * _n33 * _n42 + _n22 * _n31 * _n43 - _n21 * _n32 * _n43) * _detInv;

            _m[4] = _t12 * _detInv;
            _m[5] = (_n13 * _n34 * _n41 - _n14 * _n33 * _n41 + _n14 * _n31 * _n43 - _n11 * _n34 * _n43 - _n13 * _n31 * _n44 + _n11 * _n33 * _n44) * _detInv;
            _m[6] = (_n14 * _n32 * _n41 - _n12 * _n34 * _n41 - _n14 * _n31 * _n42 + _n11 * _n34 * _n42 + _n12 * _n31 * _n44 - _n11 * _n32 * _n44) * _detInv;
            _m[7] = (_n12 * _n33 * _n41 - _n13 * _n32 * _n41 + _n13 * _n31 * _n42 - _n11 * _n33 * _n42 - _n12 * _n31 * _n43 + _n11 * _n32 * _n43) * _detInv;

            _m[8] = _t13 * _detInv;
            _m[9] = (_n14 * _n23 * _n41 - _n13 * _n24 * _n41 - _n14 * _n21 * _n43 + _n11 * _n24 * _n43 + _n13 * _n21 * _n44 - _n11 * _n23 * _n44) * _detInv;
            _m[10] = (_n12 * _n24 * _n41 - _n14 * _n22 * _n41 + _n14 * _n21 * _n42 - _n11 * _n24 * _n42 - _n12 * _n21 * _n44 + _n11 * _n22 * _n44) * _detInv;
            _m[11] = (_n13 * _n22 * _n41 - _n12 * _n23 * _n41 - _n13 * _n21 * _n42 + _n11 * _n23 * _n42 + _n12 * _n21 * _n43 - _n11 * _n22 * _n43) * _detInv;

            _m[12] = _t14 * _detInv;
            _m[13] = (_n13 * _n24 * _n31 - _n14 * _n23 * _n31 + _n14 * _n21 * _n33 - _n11 * _n24 * _n33 - _n13 * _n21 * _n34 + _n11 * _n23 * _n34) * _detInv;
            _m[14] = (_n14 * _n22 * _n31 - _n12 * _n24 * _n31 - _n14 * _n21 * _n32 + _n11 * _n24 * _n32 + _n12 * _n21 * _n34 - _n11 * _n22 * _n34) * _detInv;
            _m[15] = (_n12 * _n23 * _n31 - _n13 * _n22 * _n31 + _n13 * _n21 * _n32 - _n11 * _n23 * _n32 - _n12 * _n21 * _n33 + _n11 * _n22 * _n33) * _detInv;
        }
        return _m;
    }

    inline void Matrix4::Scale(const Vector3 &s) noexcept
    {
        const double _x = s.X(), _y = s.Y(), _z = s.Z();

        mElements[0] *= _x;
        mElements[4] *= _y;
        mElements[8] *= _z;
        mElements[1] *= _x;
        mElements[5] *= _y;
        mElements[9] *= _z;
        mElements[2] *= _x;
        mElements[6] *= _y;
        mElements[10] *= _z;
        mElements[3] *= _x;
        mElements[7] *= _y;
        mElements[11] *= _z;
    }

    inline Matrix4 Matrix4::Scaled(const Vector3 &s) const noexcept
    {
        Matrix4 _m(*this);
        _m.Scale(s);
        return _m;
    }

    inline double Matrix4::GetMaxScaleOnAxis() const noexcept
    {
        const double _scaleXSq = mElements[0] * mElements[0] + mElements[1] * mElements[1] + mElements[2] * mElements[2];
        const double _scaleYSq = mElements[4] * mElements[4] + mElements[5] * mElements[5] + mElements[6] * mElements[6];
        const double _scaleZSq = mElements[8] * mElements[8] + mElements[9] * mElements[9] + mElements[10] * mElements[10];

        return sqrt(max(_scaleXSq, max(_scaleYSq, _scaleZSq)));
    }

    inline void Matrix4::MakeTranslation(double x,
                                         double y,
                                         double z) noexcept
    {
        Set(1., 0., 0., x,
            0., 1., 0., y,
            0., 0., 1., z,
            0., 0., 0., 1.);
    }

    inline void Matrix4::MakeRotationX(double theta) noexcept
    {
        const double _c = cos(theta), _s = sin(theta);
        Set(1., 0, 0, 0,
            0., _c, -_s, 0,
            0., _s, _c, 0,
            0., 0, 0, 1);
    }

    inline void Matrix4::MakeRotationY(double theta) noexcept
    {
        const double _c = cos(theta), _s = sin(theta);
        Set(_c, 0., _s, 0.,
            0., 1., 0., 0.,
            -_s, 0., _c, 0.,
            0., 0., 0., 1.);
    }

    inline void Matrix4::MakeRotationZ(double theta) noexcept
    {
        const double _c = cos(theta), _s = sin(theta);
        Set(_c, -_s, 0., 0.,
            _s, _c, 0., 0.,
            0., 0., 1., 0.,
            0., 0., 0., 1.);
    }

    inline void Matrix4::MakeRotationAxis(const Vector3 &axis, double angle) noexcept
    {
        const double _c = cos(angle);
        const double _s = sin(angle);
        const double _t = 1 - _c;
        const double _x = axis.X(), _y = axis.Y(), _z = axis.Z();
        const double _tx = _t * _x, _ty = _t * _y;

        Set(_tx * _x + _c, _tx * _y - _s * _z, _tx * _z + _s * _y, 0.,
            _tx * _y + _s * _z, _ty * _y + _c, _ty * _z - _s * _x, 0.,
            _tx * _z - _s * _y, _ty * _z + _s * _x, _t * _z * _z + _c, 0.,
            0., 0., 0., 1.);
    }

    inline void Matrix4::MakeScale(double x, double y, double z) noexcept
    {
        Set(x, 0., 0., 0.,
            0., y, 0., 0.,
            0., 0., z, 0.,
            0., 0., 0., 1.);
    }

    inline void Matrix4::MakeScale(const Vector3 &s) noexcept
    {
        MakeScale(s.X(), s.Y(), s.Z());
    }

    inline void Matrix4::MakeShear(double x, double y, double z) noexcept
    {
        Set(1., y, z, 0.,
            x, 1., z, 0.,
            x, y, 1., 0.,
            0., 0., 0., 1.);
    }

    inline void Matrix4::MakeShear(const Vector3 &s) noexcept
    {
        MakeShear(s.X(), s.Y(), s.Z());
    }

    inline void Matrix4::Compose(const Vector3 &p, const Quaternion &q, const Vector3 &s) noexcept
    {
        const double _x = q.X(), _y = q.Y(), _z = q.Z(), _w = q.W();
        const double _x2 = _x + _x, _y2 = _y + _y, _z2 = _z + _z;
        const double _xx = _x * _x2, _xy = _x * _y2, _xz = _x * _z2;
        const double _yy = _y * _y2, _yz = _y * _z2, _zz = _z * _z2;
        const double _wx = _w * _x2, _wy = _w * _y2, _wz = _w * _z2;

        const double _sx = s.X(), _sy = s.Y(), _sz = s.Z();

        mElements[0] = (1. - (_yy + _zz)) * _sx;
        mElements[1] = (_xy + _wz) * _sx;
        mElements[2] = (_xz - _wy) * _sx;
        mElements[3] = 0.;

        mElements[4] = (_xy - _wz) * _sy;
        mElements[5] = (1. - (_xx + _zz)) * _sy;
        mElements[6] = (_yz + _wx) * _sy;
        mElements[7] = 0.;

        mElements[8] = (_xz + _wy) * _sz;
        mElements[9] = (_yz - _wx) * _sz;
        mElements[10] = (1. - (_xx + _yy)) * _sz;
        mElements[11] = 0.;

        mElements[12] = p.X();
        mElements[13] = p.Y();
        mElements[14] = p.Z();
        mElements[15] = 1.;
    }

    inline void Matrix4::Decompose(Vector3 &p, Quaternion &q, Vector3 &s) const noexcept
    {
        Vector3 _v(mElements[0], mElements[1], mElements[2]);
        double _sx = _v.Length();
        _v.Set(mElements[4], mElements[5], mElements[6]);
        const double _sy = _v.Length();
        _v.Set(mElements[8], mElements[9], mElements[10]);
        const double _sz = _v.Length();

        // if determine is negative, we need to invert one scale
        double _det = Determinant();
        if (_det < 0)
            _sx = -_sx;

        p[0] = mElements[12];
        p[1] = mElements[13];
        p[2] = mElements[14];

        // scale the rotation part
        Matrix4 _m1(*this);

        double _invSX = 1 / _sx;
        double _invSY = 1 / _sy;
        double _invSZ = 1 / _sz;

        _m1[0] *= _invSX;
        _m1[1] *= _invSX;
        _m1[2] *= _invSX;

        _m1[4] *= _invSY;
        _m1[5] *= _invSY;
        _m1[6] *= _invSY;

        _m1[8] *= _invSZ;
        _m1[9] *= _invSZ;
        _m1[10] *= _invSZ;
        q.SetFromRotationMatrix(_m1);
        s[0] = _sx;
        s[1] = _sy;
        s[2] = _sz;
    }

    inline void Matrix4::MakePerspective(double left,
                                         double right,
                                         double top,
                                         double bottom,
                                         double near,
                                         double far) noexcept
    {
        const double _x = 2 * near / (right - left);
        const double _y = 2 * near / (top - bottom);
        const double _a = (right + left) / (right - left);
        const double _b = (top + bottom) / (top - bottom);
        const double _c = -(far + near) / (far - near);
        const double _d = -2 * far * near / (far - near);

        mElements[0] = _x, mElements[4] = 0., mElements[8] = _a, mElements[12] = 0.;
        mElements[1] = 0., mElements[5] = _y, mElements[9] = _b, mElements[13] = 0.;
        mElements[2] = 0., mElements[6] = 0., mElements[10] = _c, mElements[14] = _d;
        mElements[3] = 0., mElements[7] = 0., mElements[11] = -1., mElements[15] = 0.;
    }

    inline void Matrix4::MakeOrthographic(double left,
                                          double right,
                                          double top,
                                          double bottom,
                                          double near,
                                          double far) noexcept
    {
        const double _w = 1.0 / (right - left);
        const double _h = 1.0 / (top - bottom);
        const double _p = 1.0 / (far - near);

        const double _x = (right + left) * _w;
        const double _y = (top + bottom) * _h;
        const double _z = (far + near) * _p;

        mElements[0] = 2 * _w, mElements[4] = 0, mElements[8] = 0, mElements[12] = -_x;
        mElements[1] = 0, mElements[5] = 2 * _h, mElements[9] = 0, mElements[13] = -_y;
        mElements[2] = 0, mElements[6] = 0, mElements[10] = -2 * _p, mElements[14] = -_z;
        mElements[3] = 0, mElements[7] = 0, mElements[11] = 0, mElements[15] = 1;
    }

    inline bool Matrix4::Equals(const Matrix4 &m, uint32_t ulp) const noexcept
    {
        for (size_t i = 0; i < 16; ++i)
        {
            if (!MathUtil::AlmosetEquals(mElements[i], m[i], ulp))
            {
                return false;
            }
        }
        return true;
    }

    inline bool Matrix4::operator==(const Matrix4 &m) const noexcept
    {
        return Equals(m);
    }

    inline const double *Matrix4::Elements() const noexcept
    {
        return mElements;
    }

    inline double &Matrix4::operator[](const size_t index)
    {
        if (index >= 16)
        {
            throw range_error("matrix4 operator[] index >= 16");
        }
        else
        {
            return mElements[index];
        }
    }

    inline double Matrix4::operator[](const size_t index) const
    {
        if (index >= 16)
        {
            throw range_error("matrix4 const operator[] index >= 16");
        }
        else
        {
            return mElements[index];
        }
    }

    inline std::ostream &operator<<(std::ostream &os, const Matrix4 &m)
    {
        os << "{type:'Matrix4',"
           << "elements:["
           << m[0] << ","
           << m[1] << ","
           << m[2] << ","
           << m[3] << ","
           << m[4] << ","
           << m[5] << ","
           << m[6] << ","
           << m[7] << ","
           << m[8] << ","
           << m[9] << ","
           << m[10] << ","
           << m[11] << ","
           << m[12] << ","
           << m[13] << ","
           << m[14] << ","
           << m[15] << "]}";
        return os;
    }

} // namespace Three::Math
