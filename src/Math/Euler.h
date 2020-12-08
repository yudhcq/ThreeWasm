/**
 * @file Euler.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 欧拉角类头文件
 * @version 0.0.1
 * @date 2020-04-18
 * 
 */
#pragma once
#include <stdint.h>
#include <ostream>

/**
 * @brief Three
 * 数学类命名空间
 */
namespace Three
{
    /**
     * @brief EulerOrder
     * 欧拉角的旋转顺序
     */
    enum class EulerOrder : uint8_t
    {
        NONE,
        XYZ,
        YZX,
        ZXY,
        XZY,
        YXZ,
        ZYX,
        // preper
        XYX,
        YZY,
        ZXZ,
        XZX,
        YXY,
        ZYZ
    };
    class Matrix4;
    class Quaternion;
    class Vector3;
    /**
     * @brief Euler
     * 欧拉角，其mX,mY,mZ分别对应绕X轴，Y轴和Z轴的旋转角
     */
    class Euler
    {
    public:
        Euler() noexcept;
        Euler(double x,
              double y,
              double z,
              const EulerOrder order = EulerOrder::XYZ) noexcept;

        double X() const noexcept;

        double Y() const noexcept;

        double Z() const noexcept;

        EulerOrder Order() const noexcept;

        void SetX(double x) noexcept;

        void SetY(double y) noexcept;

        void SetZ(double z) noexcept;

        void SetOrder(const EulerOrder order) noexcept;

        void SetFromVector3(const Vector3& vec, EulerOrder order = EulerOrder::NONE) noexcept;

        void Set(double x, double y, double z,
                 const EulerOrder order = EulerOrder::NONE) noexcept;

        void SetFromRotationMatrix(const Matrix4 &matrix,
                 const EulerOrder order = EulerOrder::NONE);

        void SetFromQuaternion(const Quaternion &q,
                 const EulerOrder order = EulerOrder::NONE);

        void ReOrder(const EulerOrder order);

        bool Equals(const Euler& euler, uint32_t ulp = 4) const noexcept;

        bool operator==(const Euler& euler) const noexcept;

        Vector3 ToVector3() const;

        friend std::ostream &operator<<(std::ostream &os, const Euler &e);

    private:
        std::string GetOrderString() const noexcept;
    private:
        /**
         * @brief x
         * 绕x轴旋转角
         */
        double mX;
        /**
         * @brief y
         * 绕y轴旋转角
         */
        double mY;
        /**
         * @brief z
         * 绕z轴旋转角
         */
        double mZ;
        /**
         * @brief order
         * 旋转顺序
         */
        EulerOrder mOrder;
    };

} // namespace Three

#include "Euler.inl"