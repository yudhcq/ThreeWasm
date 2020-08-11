/**
 * @file Quaternion.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 四元数类头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */
#pragma once
#ifndef _ThreeMath_Quaternion_HeadFile
#define _ThreeMath_Quaternion_HeadFile
#include <vector>
#include <ostream>

namespace Three::Core
{
    class BufferAttribute;
} // namespace Three::Core

namespace Three::Math
{
    class Euler;
    class Vector3;
    class Matrix4;
    /**
     * @brief Quaternion
     * 四元素
     */
    class Quaternion
    {
    public:
        Quaternion() noexcept;
        explicit Quaternion(const Euler &e) noexcept;
        Quaternion(const Vector3 &axis, double angle) noexcept;
        Quaternion(double x, double y, double z, double w) noexcept;

        double X() const noexcept;

        double Y() const noexcept;

        double Z() const noexcept;

        double W() const noexcept;

        void SetX(double x) noexcept;

        void SetY(double y) noexcept;

        void SetZ(double z) noexcept;

        void SetW(double w) noexcept;

        void Set(double x, double y, double z, double w) noexcept;

        void SetFromEuler(const Euler &euler) noexcept;

        void SetFromAxisAngle(const Vector3 &axis, double angle) noexcept;

        void SetFromRotationMatrix(const Matrix4 &m) noexcept;

        void SetFromUnitVectors(const Vector3 &vFrom, const Vector3 &vTo) noexcept;

        double AngleTo(const Quaternion &q) const noexcept;

        void RotateTowards(const Quaternion &q, double step) noexcept;

        void Inverse() noexcept;

        void Conjugate() noexcept;

        double Dot(const Quaternion &q) const noexcept;

        double LengthSq() const noexcept;

        double Length() const noexcept;

        void Normalize() noexcept;

        void operator*=(const Quaternion &q) noexcept;

        void Premultiply(const Quaternion &q) noexcept;

        Quaternion PreMultiplied(const Quaternion &q) const noexcept;

        Quaternion operator*(const Quaternion &q) const noexcept;

        void FromBufferAttribute(const Core::BufferAttribute &attrbute, const size_t offset = 0);

        void Slerp(const Quaternion &qb, double t) noexcept;

        Quaternion Slerped(const Quaternion &qb, double t) const noexcept;

        bool Equals(const Quaternion &q, uint32_t ulp = 4u) const noexcept;
        bool operator==(const Quaternion &q) const noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Quaternion &q);

    private:
        /**
         * @brief x
         * 
         */
        double mX;
        /**
         * @brief y
         * 
         */
        double mY;
        /**
         * @brief z
         * 
         */
        double mZ;
        /**
         * @brief w
         * 
         */
        double mW;
    };
} // namespace Three::Math

#include "Quaternion.inl"
#endif