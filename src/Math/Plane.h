/**
 * @file Plane.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 平面类头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */
#pragma once
#include <memory>
#include <ostream>

#include "Vector3.h"

/**
 * @brief Three::Math
 * 数学类命名空间
 */
namespace Three::Math
{
    class Sphere;
    class Line3;
    class Box3;
    class Matrix4;

    /**
     * @brief Plane
     * 平面类
     */
    class Plane
    {
    public:
        Plane() noexcept;
        Plane(const Vector3 &normal, double constant) noexcept;
        Plane(const Vector3 &normal, const Vector3 &point) noexcept;
        Plane(const Vector3 &a, const Vector3 &b, const Vector3 &c) noexcept;

        const Vector3 &Normal() const noexcept;

        double Constant() const noexcept;

        void SetNormal(const Vector3 &normal) noexcept;

        void SetConstant(double constant) noexcept;

        void Set(const Vector3 &normal, double constant) noexcept;

        void Set(double nx, double ny, double nz, double constant) noexcept;

        void SetFromNormalAndCopanarPoint(const Vector3 &normal, const Vector3 &point) noexcept;

        void SetFromCoplanarPoints(const Vector3 &a, const Vector3 &b, const Vector3 &c) noexcept;

        void Normalize() noexcept;

        void Negate() noexcept;

        double DistanceTo(const Vector3 &point) const noexcept;

        double DistanceToSphere(const Sphere &sphere) const noexcept;

        Vector3 ProjectPoint(const Vector3 &point) const noexcept;

        bool IntersectLine(const Line3 &line, Vector3 &target) const noexcept;

        bool IntersectsLine(const Line3 &line) const noexcept;

        bool IntersectsBox(const Box3 &box) const noexcept;

        bool IntersectsSphere(const Sphere &sphere) const noexcept;

        Vector3 CoplanarPoint() const noexcept;

        void ApplyMatrix4(const Matrix4 &matrix,
                          const Matrix3 &optionalNormalMatrix) noexcept;
        void operator*=(const Matrix4 &matrix) noexcept;

        Plane operator*(const Matrix4 &m) const noexcept;
        Plane AppliedMatrix4(const Matrix4 &m,
                                   const Matrix3 &optionalNormalMatrix) const noexcept;

        void Translate(const Vector3 &offset) noexcept;

        bool Equals(const Plane &plane, uint32_t ulp = 4u) const noexcept;
        bool operator==(const Plane &plane) const noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Plane &plane) noexcept;

    private:
        /**
         * @brief normal
         * 平面法向量
         */
        Vector3 mNormal;
        /**
         * @brief constant
         * 平面上的点距离原点的最近距离
         */
        double mConstant;
    };
} // namespace Three::Math

#include "Plane.inl"
