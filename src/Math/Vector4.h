/**
 * @file Vector4.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 四位向量类头文件
 * @version 0.0.1
 * @date 2020-04-25
 * 
 */
#pragma once
#ifndef _ThreeMath_Vector4_HeadFile
#define _ThreeMath_Vector4_HeadFile
#include <ostream>
#include <vector>

namespace Three::Core
{
    class BufferAttribute;
} // namespace Three::Core

namespace Three::Math
{
    class Matrix4;
    class Quaternion;
    /**
     * @brief Vector4
     * 四维向量
     */
    class Vector4
    {
    public:
        Vector4() noexcept;
        explicit Vector4(double scalar) noexcept;
        Vector4(double x, double y, double z, double w) noexcept;

        double X() const noexcept;
        double Y() const noexcept;
        double Z() const noexcept;
        double W() const noexcept;
        double Width() const noexcept;
        double Height() const noexcept;

        void SetX(double value) noexcept;
        void SetY(double value) noexcept;
        void SetZ(double value) noexcept;
        void SetW(double value) noexcept;
        void SetWidth(double value) noexcept;
        void SetHeight(double value) noexcept;
        void Set(double x, double y, double z, double w) noexcept;
        void Set(double scalar) noexcept;
        /**
         * @brief 
         * 
         * @param index 
         * @return double 
         * @exception range_error
         */
        double operator[](const size_t index) const;
        double &operator[](const size_t index);

        void operator+=(const Vector4 &v) noexcept;
        void operator+=(double s) noexcept;

        void AddScaledVector(const Vector4 &v, double scalar) noexcept;

        Vector4 operator+(const Vector4 &v) const noexcept;
        Vector4 operator+(double s) const noexcept;

        Vector4 AddedScaledVector(const Vector4 &v, double scalar) const noexcept;

        void operator-=(const Vector4 &v) noexcept;
        void operator-=(double s) noexcept;

        Vector4 operator-(const Vector4 &v) const noexcept;
        Vector4 operator-(double s) const noexcept;

        void operator*=(double scalar) noexcept;

        Vector4 operator*(double scalar) const noexcept;

        void Apply(const Matrix4 &m) noexcept;

        Vector4 Applied(const Matrix4 &m) const noexcept;
        /**
         * @brief 
         * 
         * @param scalar
         * @exception logical_error 
         */
        void operator/=(double scalar);
        /**
         * @brief 
         * 
         * @param scalar 
         * @return Vector4
         * @exception logical_error 
         */
        Vector4 operator/(double scalar) const;

        void SetAxisAngle(const Quaternion &q) noexcept;
        void SetAxisAngle(const Matrix4 &m) noexcept;

        void Min(const Vector4 &v) noexcept;

        void Max(const Vector4 &v) noexcept;

        void Clamp(const Vector4 &min, const Vector4 &max) noexcept;

        void Clamp(double min, double max) noexcept;

        void Floor() noexcept;

        void Ceil() noexcept;

        void Round() noexcept;

        void RoundToZero() noexcept;

        Vector4 Mined(const Vector4 &v) const noexcept;

        Vector4 Maxed(const Vector4 &v) const noexcept;

        Vector4 Clamped(const Vector4 &min, const Vector4 &max) const noexcept;

        Vector4 Clamped(double min, double max) const noexcept;

        Vector4 Floored() const noexcept;

        Vector4 Ceiled() const noexcept;

        Vector4 Rounded() const noexcept;

        Vector4 RoundedToZero() const noexcept;

        void Negate() noexcept;

        Vector4 operator-(void) const noexcept;

        double Dot(const Vector4 &v) const noexcept;

        double LengthSq() const noexcept;

        double Length() const noexcept;

        double MamhattanLength() const noexcept;

        void Normalize() noexcept;

        Vector4 Normalized() const noexcept;

        void SetLength(double l) noexcept;

        void Lerp(const Vector4 &v, double alpha) noexcept;

        Vector4 Lerped(const Vector4 &v, double alpha) const noexcept;

        bool Equals(const Vector4 &v, uint32_t ulp = 4u) const noexcept;
        bool operator==(const Vector4 &v) const noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Vector4 &v);

    private:
        /**
         * @brief x
         * x维度数值
         */
        double mX;
        /**
         * @brief y
         * y维度数值
         */
        double mY;
        /**
         * @brief z
         * z维度数值
         */
        double mZ;
        /**
         * @brief w
         * w维度数值
         */
        double mW;
    };
} // namespace Three::Math
#include "Vector4.inl"
#endif
