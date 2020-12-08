/**
 * @file Frustum.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 视锥类头文件
 * @version 0.0.1
 * @date 2020-04-18
 * 
 */

#pragma once
#include <vector>
#include <ostream>

#include "Plane.h"

/**
 * @brief Three
 * 数学类命名空间
 */
namespace Three
{
    class Object3D;
    class Matrix4;
    class Sprite;
    class Sphere;
    class Box3;
    class Vector3;
    /**
     * @brief Frustum
     * 视锥类
     */
    class Frustum
    {
    public:
        Frustum() noexcept;
        Frustum(const Plane &p0, const Plane &p1,
                const Plane &p2, const Plane &p3,
                const Plane &p4, const Plane &p5) noexcept;

        void Set(const Plane &p0, const Plane &p1,
                 const Plane &p2, const Plane &p3,
                 const Plane &p4, const Plane &p5) noexcept;

        const Plane &operator[](const size_t index) const;
        Plane &operator[](const size_t index);

        void SetFromProjectionMatrix(const Matrix4 &m);

        bool IntersectsObject(const Object3D &object) const;
        bool IntersectsSprite(const Sprite &sprite) const;
        bool IntersectsSphere(const Sphere &sphere) const;
        bool IntersectsBox(const Box3 &box) const;

        bool ContainsPoint(const Vector3 &point) const;

        friend std::ostream &operator<<(std::ostream &os, const Frustum &frustum);

    private:
        Plane mPlanes[6];
    };
} // namespace Three

#include "Frustum.inl"