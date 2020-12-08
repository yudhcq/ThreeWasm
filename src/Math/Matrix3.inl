#include "Matrix3.h"
#include "Vector3.h"
#include "Matrix4.h"

using namespace std;

namespace Three
{
    inline Matrix3::Matrix3() noexcept
    {
        mElements[0] = 1., mElements[1] = 0., mElements[2] = 0.;
        mElements[3] = 0., mElements[4] = 1., mElements[5] = 0.;
        mElements[6] = 0., mElements[7] = 0., mElements[8] = 1.;
    }

    inline Matrix3::Matrix3(double n11,
                            double n12,
                            double n13,
                            double n21,
                            double n22,
                            double n23,
                            double n31,
                            double n32,
                            double n33) noexcept
    {
        mElements[0] = n11, mElements[1] = n21, mElements[2] = n31;
        mElements[3] = n12, mElements[4] = n22, mElements[5] = n32;
        mElements[6] = n13, mElements[7] = n23, mElements[8] = n33;
    }

    inline void Matrix3::Set(double n11,
                             double n12,
                             double n13,
                             double n21,
                             double n22,
                             double n23,
                             double n31,
                             double n32,
                             double n33) noexcept
    {
        mElements[0] = n11, mElements[1] = n21, mElements[2] = n31;
        mElements[3] = n12, mElements[4] = n22, mElements[5] = n32;
        mElements[6] = n13, mElements[7] = n23, mElements[8] = n33;
    }

    inline void Matrix3::ExtracBasis(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const noexcept
    {
        xAxis.SetFromMatrix3Column(*this, 0);
        yAxis.SetFromMatrix3Column(*this, 1);
        zAxis.SetFromMatrix3Column(*this, 2);
    }

    inline void Matrix3::SetFromMatrix4(const Matrix4 &m) noexcept
    {
        Set(m[0], m[4], m[8],
            m[1], m[5], m[9],
            m[2], m[6], m[10]);
    }

    inline void Matrix3::Identity() noexcept
    {
        mElements[0] = 1., mElements[1] = 0., mElements[2] = 0.;
        mElements[3] = 0., mElements[4] = 1., mElements[5] = 0.;
        mElements[6] = 0., mElements[7] = 0., mElements[8] = 1.;
    }

    inline void Matrix3::operator*=(double s) noexcept
    {
        mElements[0] *= s, mElements[3] *= s, mElements[6] *= s;
        mElements[1] *= s, mElements[4] *= s, mElements[7] *= s;
        mElements[2] *= s, mElements[5] *= s, mElements[8] *= s;
    }

    inline void Matrix3::operator*=(const Matrix3& m) noexcept
    {
        double _a11 = mElements[0], _a12 = mElements[3], _a13 = mElements[6];
        double _a21 = mElements[1], _a22 = mElements[4], _a23 = mElements[7];
        double _a31 = mElements[2], _a32 = mElements[5], _a33 = mElements[8];

        double _b11 = m[0], _b12 = m[3], _b13 = m[6];
        double _b21 = m[1], _b22 = m[4], _b23 = m[7];
        double _b31 = m[2], _b32 = m[5], _b33 = m[8];

        mElements[0] = _a11 * _b11 + _a12 * _b21 + _a13 * _b31;
        mElements[3] = _a11 * _b12 + _a12 * _b22 + _a13 * _b32;
        mElements[6] = _a11 * _b13 + _a12 * _b23 + _a13 * _b33;

        mElements[1] = _a21 * _b11 + _a22 * _b21 + _a23 * _b31;
        mElements[4] = _a21 * _b12 + _a22 * _b22 + _a23 * _b32;
        mElements[7] = _a21 * _b13 + _a22 * _b23 + _a23 * _b33;

        mElements[2] = _a31 * _b11 + _a32 * _b21 + _a33 * _b31;
        mElements[5] = _a31 * _b12 + _a32 * _b22 + _a33 * _b32;
        mElements[8] = _a31 * _b13 + _a32 * _b23 + _a33 * _b33;
    }

    inline Matrix3 Matrix3::operator*(double s) const noexcept
    {
        Matrix3 _m(*this);
        _m *= s;
        return _m;
    }

    inline Matrix3 Matrix3::operator*(const Matrix3 &m) const noexcept
    {
        Matrix3 _m(*this);
        _m *= m;
        return _m;
    }

    inline double Matrix3::Determinant() const
    {
        return mElements[0] * mElements[4] * mElements[8] +
               mElements[3] * mElements[7] * mElements[2] +
               mElements[6] * mElements[1] * mElements[5] -
               mElements[2] * mElements[4] * mElements[6] -
               mElements[1] * mElements[3] * mElements[8] -
               mElements[0] * mElements[5] * mElements[7];
    }

    inline Matrix3 Matrix3::GetInverse() const
    {
        const double _n11 = mElements[0], _n21 = mElements[1], _n31 = mElements[2],
               _n12 = mElements[3], _n22 = mElements[4], _n32 = mElements[5],
               _n13 = mElements[6], _n23 = mElements[7], _n33 = mElements[8];
        const double _t11 = _n33 * _n22 - _n32 * _n23,
               _t12 = _n32 * _n13 - _n33 * _n12,
               _t13 = _n23 * _n12 - _n22 * _n13;
        const double _det = _n11 * _t11 + _n21 * _t12 + _n31 * _t13;
        if (_det == 0.)
        {
            return Matrix3(0., 0., 0., 0., 0., 0., 0., 0., 0.);
        }
        else
        {
            Matrix3 _m;
            const double _detInv = 1. / _det;
            _m[0] = _t11 * _detInv;
            _m[1] = (_n31 * _n23 - _n33 * _n21) * _detInv;
            _m[2] = (_n32 * _n21 - _n31 * _n22) * _detInv;
            _m[3] = _t12 * _detInv;
            _m[4] = (_n33 * _n11 - _n31 * _n13) * _detInv;
            _m[5] = (_n31 * _n12 - _n32 * _n11) * _detInv;
            _m[6] = _t13 * _detInv;
            _m[7] = (_n21 * _n13 - _n23 * _n11) * _detInv;
            _m[8] = (_n22 * _n11 - _n21 * _n12) * _detInv;
            return _m;
        }
    }

    inline void Matrix3::Transpose() noexcept
    {
        double _temp;
        _temp = mElements[1];
        mElements[1] = mElements[3];
        mElements[3] = _temp;
        _temp = mElements[2];
        mElements[2] = mElements[6];
        mElements[6] = _temp;
        _temp = mElements[5];
        mElements[5] = mElements[7];
        mElements[7] = _temp;
    }

    inline void Matrix3::GetNormalMatrix(const Matrix4 &m)
    {
        SetFromMatrix4(m);
        *this = GetInverse();
        Transpose();
    }

    inline void Matrix3::SetUvTransform(double tx,
                                        double ty,
                                        double sx,
                                        double sy,
                                        double rotation,
                                        double cx,
                                        double cy)
    {
        const double _c = cos(rotation);
        const double _s = sin(rotation);

        Set(sx * _c, sx * _s, -sx * (_c * cx + _s * cy) + cx + tx,
            -sy * _s, sy * _c, -sy * (-_s * cx + _c * cy) + cy + ty,
            0, 0, 1);
    }

    inline void Matrix3::Scale(double sx, double sy) noexcept
    {
        mElements[0] *= sx, mElements[3] *= sx, mElements[6] *= sx;
        mElements[1] *= sy, mElements[4] *= sy, mElements[7] *= sy;
    }

    inline void Matrix3::Rotate(double theta)
    {
        const double _c = cos(theta);
        const double _s = sin(theta);

        const double _a11 = mElements[0], _a12 = mElements[3], _a13 = mElements[6];
        const double _a21 = mElements[1], _a22 = mElements[4], _a23 = mElements[7];

        mElements[0] = _c * _a11 + _s * _a21;
        mElements[3] = _c * _a12 + _s * _a22;
        mElements[6] = _c * _a13 + _s * _a23;

        mElements[1] = -_s * _a11 + _c * _a21;
        mElements[4] = -_s * _a12 + _c * _a22;
        mElements[7] = -_s * _a13 + _c * _a23;
    }

    inline void Matrix3::Translate(double tx, double ty) noexcept
    {
        mElements[0] += tx * mElements[2], mElements[3] += tx * mElements[5], mElements[6] += tx * mElements[8];
        mElements[1] += ty * mElements[2], mElements[4] += ty * mElements[5], mElements[7] += ty * mElements[8];
    }

    inline Matrix3 Matrix3::Scaled(double sx, double sy) const noexcept
    {
        Matrix3 _m(*this);
        _m.Scale(sx, sy);
        return _m;
    }

    inline Matrix3 Matrix3::Rotated(double theta) const noexcept
    {
        Matrix3 _m(*this);
        _m.Rotate(theta);
        return _m;
    }

    inline Matrix3 Matrix3::Translated(double tx, double ty) const noexcept
    {
        Matrix3 _m(*this);
        _m.Translate(tx, ty);
        return _m;
    }

    inline bool Matrix3::Equals(const Matrix3 &m, uint32_t ulp) const noexcept
    {
        for (int _i = 0; _i < 9; ++_i)
        {
            if (!MathUtil::AlmosetEquals(mElements[_i], m[_i], ulp))
            {
                return false;
            }
        }
        return true;
    }

    inline bool Matrix3::operator==(const Matrix3 &m) const noexcept
    {
        return Equals(m);
    }  

    inline void Matrix3::Premultiply(const Matrix3 &m) noexcept
    {
        *this = m * *this;
    }

    inline Matrix3 Matrix3::Premultiplyed(const Matrix3 &m) const noexcept
    {
        return m * *this;
    }

    inline const double *Matrix3::Elements() const noexcept
    {
        return mElements;
    }

    inline bool Matrix3::IsIdentity() const noexcept
    {
        return *this == Matrix3();
    }

    inline double &Matrix3::operator[](const size_t index)
    {
        if (index >= 9)
        {
            throw range_error("matrix3 operator[] index >= 9");
        }
        else
        {
            return mElements[index];
        }
    }

    inline double Matrix3::operator[](const size_t index) const
    {
        if (index >= 9)
        {
            throw range_error("const matrix3 operator[] index >= 9");
        }
        else
        {
            return mElements[index];
        }
    }

    inline std::ostream &operator<<(std::ostream &os, const Matrix3 &m)
    {
        os << "{type:'Matrix3',"
           << "elements:["
           << m[0] << ","
           << m[1] << ","
           << m[2] << ","
           << m[3] << ","
           << m[4] << ","
           << m[5] << ","
           << m[6] << ","
           << m[7] << ","
           << m[8] << "]}";
        return os;
    }

} // namespace Three
