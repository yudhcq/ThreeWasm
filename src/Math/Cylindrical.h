/**
 * @file Cylindrical.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 圆柱坐标
 * @version 0.0.1
 * @date 2020-04-18
 * 
 */

#pragma once
#ifndef _ThreeMath_Cylindical_HeadFile
#define _ThreeMath_Culindical_HeadFile
#include <ostream>
/**
 * @brief Three::Math
 * 属性类命名空间
 */
namespace Three::Math
{
    class Vector3;
    /**
     * @brief Cylindrical
     * 圆柱坐标
     */
    class Cylindrical
    {
    public:
        Cylindrical() noexcept;
        Cylindrical(double radius, double theta, double y) noexcept;

        double Radius() const noexcept;

        double Theta() const noexcept;

        double Y() const noexcept;

        void SetRadius(double radius) noexcept;

        void SetTheta(double theta) noexcept;

        void SetY(double y) noexcept;

        void Set(double radius, double theta, double y) noexcept;

        void SetFromVector3(const Vector3 &v) noexcept;

        void SetFromCartesianCoords(double x, double y, double z) noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Cylindrical &c);

    private:
        /**
         * @brief radius
         * 圆柱半径
         */
        double mRadius;
        /**
         * @brief theta
         * 绕圆柱中心旋转角
         */
        double mTheta;
        /**
         * @brief y
         * 距离x-z平面的高度1
         */
        double mY;
    };
} // namespace Three::Math

#include "Cylindrical.inl"
#endif