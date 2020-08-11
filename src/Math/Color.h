/**
 * @file Color.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 颜色类头文件
 * @version 0.0.1
 * @date 2020-04-18
 * 
 */

#pragma once
#ifndef _ThreeMath_Color_HeadFile
#define _ThreeMath_Color_HeadFile
#include <string>
#include <stdint.h>
#include <ostream>
#include <vector>
#include <map>

/**
 * @brief Three::Math
 * 数学类命名空间
 */
namespace Three::Math
{
    /**
     * @brief Color
     * 其包含rgb通道，采用0.~1.0的表示方式
     */
    class Color
    {
    public:
        /**
         * @brief HSL
         * 颜色的h,s,l表示方式
         */
        struct HSL
        {
            double h;
            double s;
            double l;
        };

        Color() noexcept;
        explicit Color(double scalar) noexcept;
        explicit Color(int colorHex) noexcept;
        explicit Color(const std::string &style);
        Color(double red, double green, double blue) noexcept;
        Color(const HSL &hsl) noexcept;

        static double HueToRgb(double p, double q, double t) noexcept;
        static double SRGBToLinear(double c) noexcept;
        static double LinearToSRGB(double c) noexcept;

        double Red() const noexcept;

        double Green() const noexcept;

        double Blue() const noexcept;

        void SetRed(double red) noexcept;

        void SetGreen(double green) noexcept;

        void SetBlue(double blue) noexcept;

        void SetHex(int colorHex);
        void SetColorKeyWorld(const std::string &colorKeyworld);

        void SetScalar(double scalar) noexcept;

        void SetRGB(double r, double g, double b) noexcept;

        void SetHSL(double h, double s, double l);

        void SetStyle(const std::string &style);

        void CopyGamaToLinear(const Color &color, double gammaFactor = 2.0);

        void CopyLinearToGamma(const Color &color, double gammaFactor = 2.0);

        void ConvertGammaToLinear(double gammaFactor = 2.0);

        void ConvertLinearToGamma(double gammaFactor = 2.0);

        void CopySRGBToLinear(const Color &color);

        void CopyLinearToSRGB(const Color &color);

        void ConvertSRGBToLinear();

        void ConvertLinearToSRGB();

        int GetHex() const noexcept;

        std::string GetHexString() const noexcept;

        HSL GetHSL() const noexcept;

        void OffsetHSL(double h, double s, double l) noexcept;

        std::string GetStyle() const noexcept;

        void operator+=(const Color &color) noexcept;
        void operator+=(double scalar) noexcept;

        Color operator+(const Color &color) const noexcept;
        Color operator+(double scalar) const noexcept;

        void operator-=(const Color &color) noexcept;
        void operator-=(double scalar) noexcept;

        Color operator-(const Color &color) const noexcept;
        Color operator-(double scalar) const noexcept;

        void operator*=(const Color &color) noexcept;
        void operator*=(double scalar) noexcept;

        Color operator*(const Color &color) const noexcept;
        Color operator*(double scalar) const noexcept;

        void Lerp(const Color &color, double alpha) noexcept;
        Color Lerped(const Color &color, double alpha) const noexcept;

        void LerpHSL(const Color &color, double alpha) noexcept;
        Color LerpHSL(const Color &color, double alpha) const noexcept;

        bool Equals(const Color &c, uint32_t ulp = 4u) const noexcept;

        bool operator==(const Color &c) const noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Color &color);

    private:
        /**
         * @brief red
         * 红色通道值，取值为0.0-1.0
         */
        double mRed;
        /**
         * @brief green
         * 绿色通道值，取值为0.0-1.0
         */
        double mGreen;
        /**
         * @brief blue
         * 蓝色通道之，取值为0.0-1.0
         */
        double mBlue;

    public:
        static std::map<std::string, int> ColorKeyWorlds;
    };
} // namespace Three::Math

#include "Color.inl"
#endif