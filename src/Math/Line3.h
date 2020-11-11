
/**
 * @file Line3.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 三维线段类头文件
 * @version 0.0.1
 * @date 2020-04-19
 * 
 */

#pragma once
#include <ostream>

#include "Vector3.h"

/**
 * @brief Three::Math
 * 数学库命名空间
 */
namespace Three::Math
{
    class Matrix4;
    /**
     * @brief Line3
     * 三维线段
     */
    class Line3
    {
    public:
        Line3() noexcept;
        Line3(const Vector3 &start, const Vector3 &end) noexcept;

        const Vector3 &Start() const noexcept;

        const Vector3 &End() const noexcept;

        void SetStart(const Vector3 &start) noexcept;

        void SetEnd(const Vector3 &end) noexcept;

        void Set(const Vector3 &start, const Vector3 &end) noexcept;

        Vector3 GetCenter() const noexcept;

        Vector3 Delta() const noexcept;

        double DistanceSq() const noexcept;

        double Distance() const noexcept;

        Vector3 At(double t) const noexcept;

        double ClosestPointToPointParameter(const Vector3 &point,
                                                  bool clampToLine = false) const noexcept;

        Vector3 ClosePointToPoint(const Vector3 &point,
                                        bool clampToLine = false) const noexcept;

        void operator*=(const Matrix4 &m);

        Line3 operator*(const Matrix4 &m) const;

        bool Equals(const Line3 &line, uint32_t ulp = 4u) const;
        bool operator==(const Line3 &line) const;

        friend std::ostream &operator<<(std::ostream &os, const Line3 &line);

    private:
        /**
         * @brief start
         * 起始点
         */
        Vector3 mStart;
        /**
         * @brief end
         * 终止点
         */
        Vector3 mEnd;
    };
} // namespace Three::Math

#include "Line3.inl"