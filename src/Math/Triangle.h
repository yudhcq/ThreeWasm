/**
 * @file Triangle.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 三角形类头文件
 * @version 0.0.1
 * @date 2020-04-25
 * 
 */
#pragma once
#include <vector>
#include <ostream>

#include "Vector3.h"

namespace Three::Math
{
    class Plane;
    class Vector2;
    class Box3;

    struct SplineControlPoint
    {
        double x = 0.;
        double y = 0.;
        double z = 0.;
    };
    /**
     * @brief Triangle
     * 三角形类
     */
    class Triangle
    {
    public:
        Triangle() noexcept;
        Triangle(const Vector3 &a,
                 const Vector3 &b,
                 const Vector3 &c) noexcept;

        const Vector3 &A() const noexcept;
        const Vector3 &B() const noexcept;
        const Vector3 &C() const noexcept;

        void SetA(const Vector3 &p) noexcept;
        void SetB(const Vector3 &p) noexcept;
        void SetC(const Vector3 &p) noexcept;

        void Set(const Vector3 &a, const Vector3 &b, const Vector3 &c) noexcept;

        void SetFromPointAndIndices(const std::vector<Vector3> &points,
                                    size_t i0,
                                    size_t i1,
                                    size_t i2);

        double GetArea() const noexcept;

        Vector3 GetMidpoint() const noexcept;

        Vector3 GetNormal() const noexcept;

        Plane GetPlane() const noexcept;

        Vector3 GetBarycoord(const Vector3 &point) const noexcept;

        Vector2 GetUV(const Vector3 &point,
                      const Vector2 &uv1,
                      const Vector2 &uv2,
                      const Vector2 &uv3) const noexcept;

        bool ContainPoint(const Vector3 &point) const noexcept;

        bool Intersects(const Box3 &box) const noexcept;

        bool IsFrontFacing(const Vector3 &direction) const noexcept;

        Vector3 ClosesPointToPoint(const Vector3 &point) const noexcept;

        bool Equals(const Triangle &triangle,
                    uint32_t ulp = 4) const noexcept;
        bool operator==(const Triangle &triangle) const noexcept;

        static Vector3 GetNormal(const Vector3 &a,
                                 const Vector3 &b,
                                 const Vector3 &c) noexcept;

        static Vector3 GetBarycoord(const Vector3 &point,
                                    const Vector3 &a,
                                    const Vector3 &b,
                                    const Vector3 &c);

        static bool IsFrontFacing(const Vector3 &a,
                                  const Vector3 &b,
                                  const Vector3 &c,
                                  const Vector3 &direction);

        friend std::ostream &
        operator<<(std::ostream &os, const Triangle &triangle);

    private:
        /**
         * @brief a
         * 顶点A
         */
        Vector3 mA;
        /**
         * @brief b
         * 顶点b
         */
        Vector3 mB;
        /**
         * @brief c
         * 顶点c
         */
        Vector3 mC;
    };
} // namespace Three::Math

#include "Triangle.inl"