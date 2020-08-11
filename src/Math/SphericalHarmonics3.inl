
#include "SphericalHarmonics3.h"

namespace Three::Math
{
    inline SphericalHarmonics3::SphericalHarmonics3() noexcept
    {
    }

    inline SphericalHarmonics3::SphericalHarmonics3(const std::vector<Vector3> &coefficients) noexcept
    {
        for (size_t _i = 0, _size = coefficients.size(); _i < _size && _i < 9; ++_i)
        {
            mCoefficients[_i] = coefficients[_i];
        }
    }

    inline void SphericalHarmonics3::Set(const std::vector<Vector3> &coefficients) noexcept
    {
        for (size_t _i = 0, _size = coefficients.size(); _i < _size && _i < 9; ++_i)
        {
            mCoefficients[_i] = coefficients[_i];
        }
    }

    inline void SphericalHarmonics3::Zero() noexcept
    {
        for (auto &coefficient : mCoefficients)
        {
            coefficient.Set(0., 0., 0.);
        }
    }

    inline void SphericalHarmonics3::operator+=(const SphericalHarmonics3 &sh) noexcept
    {
        for (size_t _i = 0; _i < 9; ++_i)
        {
            mCoefficients[_i] += sh.mCoefficients[_i];
        }
    }

    inline SphericalHarmonics3 SphericalHarmonics3::operator+(const SphericalHarmonics3 &sh) const noexcept
    {
        SphericalHarmonics3 _sh(*this);
        _sh += sh;
        return _sh;
    }

    inline void SphericalHarmonics3::AddScaledSH(const SphericalHarmonics3 &sh, double s) noexcept
    {
        for (size_t _i = 0; _i < 9; ++_i)
        {
            mCoefficients[_i] += sh.mCoefficients[_i] * s;
        }
    }

    inline SphericalHarmonics3 SphericalHarmonics3::AddedScaledSH(const SphericalHarmonics3 &sh, double s) const noexcept
    {
        SphericalHarmonics3 _sh(*this);
        _sh.AddScaledSH(sh, s);
        return _sh;
    }

    inline void SphericalHarmonics3::Scale(double s) noexcept
    {
        for (size_t _i = 0; _i < 9; ++_i)
        {
            mCoefficients[_i] *= s;
        }
    }

    inline SphericalHarmonics3 SphericalHarmonics3::Scaled(double s) const noexcept
    {
        SphericalHarmonics3 _sh(*this);
        _sh.Scale(s);
        return _sh;
    }

    inline void SphericalHarmonics3::Lerp(const SphericalHarmonics3 &sh, double alpha) noexcept
    {
        for (size_t _i = 0; _i < 9; ++_i)
        {
            mCoefficients[_i].Lerp(sh.mCoefficients[_i], alpha);
        }
    }

    inline SphericalHarmonics3 SphericalHarmonics3::Lerped(const SphericalHarmonics3 &sh, double alpha) const noexcept
    {
        SphericalHarmonics3 _sh(*this);
        _sh.Lerp(sh, alpha);
        return _sh;
    }

    inline bool SphericalHarmonics3::Equals(const SphericalHarmonics3 &sh, uint32_t ulp) const noexcept
    {
        for (size_t _i = 0; _i < 9; ++_i)
        {
            if (!mCoefficients[_i].Equals(sh.mCoefficients[_i], ulp))
            {
                return false;
            }
        }
        return true;
    }

    inline bool SphericalHarmonics3::operator==(const SphericalHarmonics3 &sh) const noexcept
    {
        Equals(sh);
    }

    inline Vector3 SphericalHarmonics3::GetAt(const Vector3 &normal) const noexcept
    {
        const double _x = normal.X(), _y = normal.Y(), _z = normal.Z();
        Vector3 _target(mCoefficients[0]);
        _target *= 0.282095;
        // band 1
        _target.AddScaledVector(mCoefficients[1], 0.488603 * _y);
        _target.AddScaledVector(mCoefficients[2], 0.488603 * _z);
        _target.AddScaledVector(mCoefficients[3], 0.488603 * _x);

        // band 2
        _target.AddScaledVector(mCoefficients[4], 1.092548 * (_x * _y));
        _target.AddScaledVector(mCoefficients[5], 1.092548 * (_y * _z));
        _target.AddScaledVector(mCoefficients[6], 0.315392 * (3.0 * _z * _z - 1.0));
        _target.AddScaledVector(mCoefficients[7], 1.092548 * (_x * _z));
        _target.AddScaledVector(mCoefficients[8], 0.546274 * (_x * _x - _y * _y));
        return _target;
    }

    inline Vector3 SphericalHarmonics3::GetIrradianceAt(const Vector3 &normal) noexcept
    {
        const double _x = normal.X(), _y = normal.Y(), _z = normal.Z();
        Vector3 _target(mCoefficients[0]);
        _target *= 0.886227;
        // band 1
        _target.AddScaledVector(mCoefficients[1], 2.0 * 0.511664 * _y);
        _target.AddScaledVector(mCoefficients[2], 2.0 * 0.511664 * _z);
        _target.AddScaledVector(mCoefficients[3], 2.0 * 0.511664 * _x);
        // band 2
        _target.AddScaledVector(mCoefficients[4], 2.0 * 0.429043 * (_x * _y));
        _target.AddScaledVector(mCoefficients[5], 2.0 * 0.429043 * (_y * _z));
        _target.AddScaledVector(mCoefficients[6], 0.743125 * _z * _z - 0.247708);
        _target.AddScaledVector(mCoefficients[7], 2.0 * 0.429043 * _x * _z);
        _target.AddScaledVector(mCoefficients[8], 0.429043 * (_x * _x - _y * _y));
        return _target;
    }

    inline void SphericalHarmonics3::GetBasisAt(const Vector3 &normal,
                                                vector<double> &shBasis)
    {
        if (shBasis.size() <= 9)
        {
            throw range_error("SphericalHarmonics3 GetBasisAt shBasis's size is less than 9");
        }

        const double _x = normal.X(), _y = normal.Y(), _z = normal.Z();
        // band 0
        shBasis[0u] = 0.282095;

        // band 1
        shBasis[1u] = 0.488603 * _y;
        shBasis[2u] = 0.488603 * _z;
        shBasis[3u] = 0.488603 * _x;

        // band 2
        shBasis[4u] = 1.092548 * _x * _y;
        shBasis[5u] = 1.092548 * _y * _z;
        shBasis[6u] = 0.315392 * (3. * _z * _z - 1.);
        shBasis[7u] = 1.092548 * _x * _z;
        shBasis[8u] = 0.546274 * (_x * _x - _y * _y);
    }

    inline std::ostream &operator<<(std::ostream &os, const SphericalHarmonics3 &sphere)
    {
        os << "{type:SphericalHarmonics3,"
           << "coefficients:[";
        for (size_t i = 0; i < 9; ++i)
        {
            os << sphere.mCoefficients[i];
            if (i != 8)
            {
                os << ",";
            }
        }
        os << "]}";
        return os;
    }

} // namespace Three::Math
