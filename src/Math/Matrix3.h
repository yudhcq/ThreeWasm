/**
 * @file Matrix3.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 三维矩阵头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */
#pragma once
#ifndef _ThreeMath_Matrix3_HeadFile
#define _ThreeMath_Matrix3_HeadFile
#include <vector>
#include <ostream>

namespace Three::Math
{
    class Vector3;
    class Matrix4;
    /**
     * @brief Matrix3
     * 三维矩阵
     */
    class Matrix3
    {
    public:
        Matrix3() noexcept;
        Matrix3(double n11,
                double n12,
                double n13,
                double n21,
                double n22,
                double n23,
                double n31,
                double n32,
                double n33) noexcept;

        void Set(double n11,
                 double n12,
                 double n13,
                 double n21,
                 double n22,
                 double n23,
                 double n31,
                 double n32,
                 double n33) noexcept;

        void ExtracBasis(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const noexcept;

        void SetFromMatrix4(const Matrix4 &m) noexcept;

        void Identity() noexcept;

        void operator*=(double s) noexcept;
        void operator*=(const Matrix3 &m) noexcept;

        Matrix3 operator*(double s) const noexcept;
        Matrix3 operator*(const Matrix3 &m) const noexcept;

        double Determinant() const;

        Matrix3 GetInverse() const;

        void Transpose() noexcept;

        void GetNormalMatrix(const Matrix4 &m4);

        void SetUvTransform(double tx,
                            double ty,
                            double sx,
                            double sy,
                            double rotation,
                            double cx,
                            double cy);

        void Scale(double sx, double sy) noexcept;

        void Rotate(double theta);

        void Translate(double tx, double ty) noexcept;

        Matrix3 Scaled(double sx, double sy) const noexcept;
        Matrix3 Rotated(double theta) const noexcept;
        Matrix3 Translated(double tx, double ty) const noexcept;

        bool Equals(const Matrix3 &m, uint32_t ulp = 4u) const noexcept;
        bool operator==(const Matrix3 &m) const noexcept;

        void Premultiply(const Matrix3 &m) noexcept;

        Matrix3 Premultiplyed(const Matrix3 &m) const noexcept;

        const double *Elements() const noexcept;

        bool IsIdentity() const noexcept;

        double &operator[](const size_t index);
        double operator[](const size_t index) const;

        friend std::ostream &operator<<(std::ostream &os, const Matrix3 &m);

    private:
        /**
         * @brief elements
         * 三维矩阵数据
         */
        double mElements[9];
    };
} // namespace Three::Math

#include "Matrix3.inl"          
#endif