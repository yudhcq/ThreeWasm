/**
 * @file Matrix4.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 四位矩阵头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */
#pragma once
#ifndef _ThreeMath_Matrix4_HeadFile
#define _ThreeMath_Matrix4_HeadFile
#include <vector>
#include <ostream>

/**
 * @brief Three::Math
 * 数学类命名空间
 */
namespace Three::Math
{
    class Vector3;
    class Matrix3;
    class Euler;
    class Quaternion;
    /**
     * @brief Matrix4
     * 三维矩阵
     */
    class Matrix4
    {
    public:
        Matrix4() noexcept;
        Matrix4(double n11,
                double n12,
                double n13,
                double n14,
                double n21,
                double n22,
                double n23,
                double n24,
                double n31,
                double n32,
                double n33,
                double n34,
                double n41,
                double n42,
                double n43,
                double n44) noexcept;

        void Set(double n11,
                 double n12,
                 double n13,
                 double n14,
                 double n21,
                 double n22,
                 double n23,
                 double n24,
                 double n31,
                 double n32,
                 double n33,
                 double n34,
                 double n41,
                 double n42,
                 double n43,
                 double n44) noexcept;

        void Identity() noexcept;

        bool IsIndentity() const noexcept;

        void CopyPosition(const Matrix4 &m) noexcept;

        void ExtractBasis(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const noexcept;

        void MakeBasis(const Vector3 &xAsis, Vector3 &yAxis, Vector3 &zAxis) noexcept;

        void ExtractRotation(const Matrix4 &m) noexcept;

        void MakeRotationFromEuler(const Euler &euler) noexcept;

        void MakeRotationFromQuaternion(const Quaternion &q) noexcept;

        void LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up) noexcept;

        void operator*=(const Matrix4 &m) noexcept;
        void operator*=(double scalar) noexcept;

        void Premultiply(const Matrix4 &m) noexcept;

        Matrix4 operator*(const Matrix4 &m) const noexcept;

        Matrix4 Premultiplied(const Matrix4 &m) const noexcept;

        Matrix4 operator*(double s) const noexcept;

        double Determinant() const noexcept;

        void Transpose() noexcept;

        void SetPosition(double x, double y, double z) noexcept;
        void SetPosition(const Vector3 &v) noexcept;

        void GetInverse(const Matrix4 &m) noexcept;

        void Scale(const Vector3 &s) noexcept;

        Matrix4 Scaled(const Vector3 &s) const noexcept;

        double GetMaxScaleOnAxis() const noexcept;

        void MakeTranslation(double x, double y, double z) noexcept;

        void MakeRotationX(double theta) noexcept;

        void MakeRotationY(double theta) noexcept;

        void MakeRotationZ(double theta) noexcept;

        void MakeRotationAxis(const Vector3 &axis, double angle) noexcept;

        void MakeScale(double x, double y, double z) noexcept;
        void MakeScale(const Vector3 &s) noexcept;

        void MakeShear(double x, double y, double z) noexcept;
        void MakeShear(const Vector3 &s) noexcept;

        void Compose(const Vector3 &p, const Quaternion &q, const Vector3 &s) noexcept;

        void Decompose(Vector3 &p, Quaternion &q, Vector3 &s) const noexcept;

        void MakePerspective(double left,
                             double right,
                             double top,
                             double bottom,
                             double near,
                             double far) noexcept;

        void MakeOrthographic(double left,
                              double right,
                              double top,
                              double bottom,
                              double near,
                              double far) noexcept;

        bool Equals(const Matrix4 &m, uint32_t ulp = 4u) const noexcept;
        bool operator==(const Matrix4 &m) const noexcept;

        const double *Elements() const noexcept;

        double &operator[](const size_t index);
        double operator[](const size_t index) const;

        friend std::ostream &operator<<(std::ostream &os, const Matrix4 &m);

    private:
        /**
         * @brief elements
         * 四维矩阵数据
         */
        double mElements[16];
    };
} // namespace Three::Math

#include "Matrix4.inl"
#endif