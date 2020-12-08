/**
 * @file Ray.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 射线类头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */
#pragma once
#include <memory>
#include <ostream>

#include "Vector3.h"

namespace Three
{
    class Sphere;
    class Plane;
    class Box3;
    class Triangle;
    class Matrix4;

    /**
     * @brief Ray
     * 射线类
     */
    class Ray
    {
    public:
        Ray() noexcept;
        Ray(const Vector3 &origin, const Vector3 &direction) noexcept;

        const Vector3 &Origin() const noexcept;

        const Vector3 &Direction() const noexcept;

        void SetOrigin(const Vector3 &o) noexcept;

        void SetDirection(const Vector3 &d) noexcept;

        void Set(const Vector3 &o, const Vector3 &d) noexcept;

        Vector3 At(double t) const noexcept;

        void LookAt(const Vector3 &v) noexcept;

        void Recast(double t) noexcept;
        Ray Recasted(double t) const noexcept;

        Vector3 ClosestPointToPoint(const Vector3 &point) const;

        double DistanceTo(const Vector3 &point) const;

        double DistanceSqTo(const Vector3 &point) const;

        double DistanceSqTo(const Vector3 &v0,
                                  const Vector3 &v1,
                                  std::shared_ptr<Vector3> optionalPointOnRaySPtr = nullptr,
                                  std::shared_ptr<Vector3> optionalPointOnSegmentSPtr = nullptr) const;

        std::shared_ptr<const Vector3> Intersect(const Sphere &sphere) const;

        bool Intersects(const Sphere &sphere) const;

        double DistanceTo(const Plane &plane) const;

        std::shared_ptr<const Vector3> Intersect(const Plane &plane) const;

        bool Intersects(const Plane &plane) const;

        std::shared_ptr<const Vector3> Intersect(const Box3 &box) const;

        bool Intersects(const Box3 &box) const;

        std::shared_ptr<const Vector3> Intersect(const Vector3 &a,
                                                       const Vector3 &b,
                                                       const Vector3 &c,
                                                       bool backfaceCulling) const;

        std::shared_ptr<const Vector3> Intersect(const Triangle &triangle,
                                                       bool backfaceCulling) const;

        void operator*=(const Matrix4 &matrix);

        Ray operator*(const Matrix4 &matrix) const;

        bool Equals(const Ray &ray, uint32_t ulp = 4u) const;

        bool operator==(const Ray &ray) const;

        friend std::ostream &operator<<(std::ostream &os, const Ray &ray);

    private:
        /**
         * @brief origin
         * 射线的起始点
         */
        Vector3 mOrigin;
        /**
         * @brief direction
         * 射线的方向
         */
        Vector3 mDirection;
    };
} // namespace Three

#include "Ray.inl"