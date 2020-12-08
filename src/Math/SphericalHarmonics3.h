/**
 * @file SphericalHarmonics3.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 球谐类头文件
 * @version 0.0.1
 * @date 2020-04-25
 * 
 */
#pragma once
#include <vector>
#include <ostream>

#include "Vector3.h"

namespace Three
{
    /**
     * @brief SphericalHarmonics3
     * 球谐类
     */
    class SphericalHarmonics3
    {
    public:
        SphericalHarmonics3() noexcept;
        SphericalHarmonics3(const std::vector<Vector3> &coefficients) noexcept;

        void Set(const std::vector<Vector3> &coefficients) noexcept;

        void Zero() noexcept;

        void operator+=(const SphericalHarmonics3 &sh) noexcept;

        SphericalHarmonics3 operator+(const SphericalHarmonics3 &sh) const noexcept;

        void AddScaledSH(const SphericalHarmonics3 &sh, double s) noexcept;

        SphericalHarmonics3 AddedScaledSH(const SphericalHarmonics3 &sh, double s) const noexcept;

        void Scale(double s) noexcept;

        SphericalHarmonics3 Scaled(double s) const noexcept;

        void Lerp(const SphericalHarmonics3 &sh, double alpha) noexcept;

        SphericalHarmonics3 Lerped(const SphericalHarmonics3 &sh, double alpha) const noexcept;

        bool Equals(const SphericalHarmonics3 &sh, uint32_t ulp = 4u) const noexcept;
        bool operator==(const SphericalHarmonics3 &sh) const noexcept;

        Vector3 GetAt(const Vector3 &normal) const noexcept;

        Vector3 GetIrradianceAt(const Vector3 &normal) noexcept;

        static void GetBasisAt(const Vector3 &normal, std::vector<double> &shBasis);

        friend std::ostream &operator<<(std::ostream &os, const SphericalHarmonics3 &sphere);

    private:
        /**
         * @brief coefficients
         * 相关系数
         */
        Vector3 mCoefficients[9];
    };
} // namespace Three

#include "SphericalHarmonics3.inl"