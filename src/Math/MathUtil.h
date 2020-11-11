/**
 * @file MathUtil.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 工具数学方法头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */
#pragma once
#include <string>

/**
 * @brief Three::Math
 * 数学类命名空间
 */
namespace Three::Math
{
    enum class EulerOrder : uint8_t;
    class Quaternion;
    /**
     * @brief MathUtil
     * 数学工具类，只包含静态常量和静态成员函数
     */
    class MathUtil
    {
    public:
        static double Clamp(double value, double min, double max);

        static double EuclideanModulo(double n, double m);

        static double MapLinear(double x,
                                      double a1,
                                      double a2,
                                      double b1,
                                      double b2);

        static double Smoothstep(double x, double min, double max);

        static double Smootherstep(double x, double min, double max);

        static int RandInt(int low, int high);

        static double RandFloat(double low, double high);

        static double RandFloatSpread(double range);

        static double DegToRad(double degress) noexcept;

        static double RadToDeg(double radians) noexcept;

        static double Lerp(double x, double y, double t) noexcept;

        static bool IsPowerOfTwo(const uint64_t value) noexcept;

        static double FloorPowerOfTwo(double value) noexcept;

        static double CeilPowerOfTwo(double value) noexcept;

        static void SetQuaternionFromProperEuler(Quaternion &q,
                                                       double a,
                                                       double b,
                                                       double c,
                                                       const EulerOrder order) noexcept;

        static std::string ToString16(int intVal) noexcept;
        /**
         * @brief 判断两个double类型的数值是否模糊相等
         * 
         * @param rhs 左值
         * @param lhs 右值
         * @param ulp 最小精度位，默认为4
         * 详见https://en.wikipedia.org/wiki/Unit_in_the_last_place
         * @return double 
         */
        static double AlmosetEquals(double rhs, double lhs, uint32_t ulp = 4u) noexcept;

        static bool IsNan(double value) noexcept;

    public:
        static const double DEG2RAD;
        static const double RAD2DEG;
        static const double EPSILION;
    };
} // namespace Three::Math

#include "MathUtil.inl"