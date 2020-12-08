/**
 * @file Sphere.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 球类头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */

#pragma once
#include <vector>
#include <ostream>

#include "Vector3.h"

/**
 * @brief Three
 * 数学类命名空间
 */
namespace Three
{
    class Box3;
    class Plane;
    class Matrix4;

    /**
     * @brief Sphere
     * 球
     */
    class Sphere
    {
    public:
        Sphere() noexcept;
        Sphere(const Vector3 &center, double radius) noexcept;

        const Vector3 &Center() const noexcept;

        double Radius() const noexcept;

        void SetCenter(const Vector3 &center) noexcept;

        void SetRadius(double radius) noexcept;

        void Set(const Vector3 &center, double radius) noexcept;

        void SetFromPoints(const std::vector<Vector3> &points) noexcept;
        void SetFromPoints(const std::vector<Vector3> &points,
                           const Vector3 &optionalCenter) noexcept;

        double Empty() const noexcept;

        bool ContainsPoint(const Vector3 &point) const noexcept;

        double DistanceTo(const Vector3 &point) const noexcept;

        bool Intersects(const Sphere &s) const noexcept;
        bool Intersects(const Box3 &box) const noexcept;
        bool Intersects(const Plane &plane) const noexcept;

        Vector3 ClampPoint(const Vector3 &point) const noexcept;

        Box3 GetBoundingBox() const noexcept;

        void operator*=(const Matrix4 &m) noexcept;

        Sphere operator*(const Matrix4 &m) const noexcept;

        void Translate(const Vector3 &offset) noexcept;
        Sphere Translated(const Vector3 &offset) const noexcept;

        bool Equals(const Sphere &sphere, uint32_t ulp = 4u) const noexcept;
        bool operator==(const Sphere &sphere) const noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere);

    private:
        /**
         * @brief center
         * 球心
         */
        Vector3 mCenter;
        /**
         * @brief radius
         * 半径
         */
        double mRadius;
    };
} // namespace Three

#include "Sphere.inl"