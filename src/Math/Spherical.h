/**
 * @file Spherical.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 球面坐标系类头文件
 * @version 0.0.1
 * @date 2020-04-25
 * 
 */

#pragma once
#include <ostream>

namespace Three::Math
{
    class Vector3;
    /**
     * @brief Spherical
     * 球面坐标系
     */
    class Spherical
    {
    public:
        Spherical() noexcept;
        Spherical(double radius, double phi, double theta) noexcept;

        double Radius() const noexcept;

        double Phi() const noexcept;

        double Theta() const noexcept;

        void SetRadius(double radius) noexcept;

        void SetPhi(double phi) noexcept;

        void SetTheta(double theta) noexcept;

        void Set(double radius, double phi, double theta) noexcept;

        void MakeSafe() noexcept;

        void SetFromVector3(const Vector3 &v) noexcept;

        void SetFromCartesianCoords(double x, double y, double z) noexcept;

        bool Equals(Spherical dst) const noexcept;

        bool operator==(Spherical dst) const noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Spherical &sphere);

    private:
        /**
         * @brief radius
         * 半径
         */
        double mRadius;
        /**
         * @brief phi
         * 水平面内角度
         */
        double mPhi;
        /**
         * @brief theta
         * 竖直面内角度
         */
        double mTheta;
    };

} // namespace Three::Math

#include "Spherical.inl"