/**
 * @file Vector2.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 二维向量或点类头文件
 * @version 0.0.1
 * @date 2020-04-25
 * 
 */
#pragma once
#include <ostream>
#include <vector>

namespace Three
{
	class BufferAttribute;
} // namespace Three

namespace Three
{
	class Matrix3;
	/**
	 * @brief Vetcor2
	 * 二维向量或点类
	 */
	class Vector2
	{
	public:
		/**
		 * @brief Vector2 默认构造函数
		 * x和y值都为0.
		 */
		Vector2() noexcept;
		/**
		 * @brief Vector2 构造函数
		 * 通.x = .y = scalar
		 * @param scalar 
		 */
		explicit Vector2(double scalar) noexcept;
		/**
		 * @brief Vector2 构造函数
		 * 
		 * @param x 
		 * @param y 
		 */
		Vector2(double x, double y) noexcept;
		/**
		 * @brief 设置x值
		 * 
		 * @param value
		 */
		void SetX(double value) noexcept;
		/**
		 * @brief 设置y值
		 * 
		 * @param value
		 */
		void SetY(double value) noexcept;
		/**
		 * @brief 同时设置x值和y值
		 * 
		 * @param x 
		 * @param y 
		 */
		void Set(double x, double y) noexcept;
		/**
		 * @brief 通过一个常量同时设置x值和y值
		 * 
		 * @param scalar 
		 */
		void Set(double scalar) noexcept;
		/**
		 * @brief 获取x值
		 * 
		 * @return double 
		 */
		double X() const noexcept;
		/**
		 * @brief 获取y值
		 * 
		 * @return double 
		 */
		double Y() const noexcept;
		/**
		 * @brief 获取宽度值，实际为x值
		 * 
		 * @return double 
		 */
		double Width() const noexcept;
		/**
		 * @brief 获取高度值，实际为y值
		 * 
		 * @return double 
		 */
		double Height() const noexcept;
		/**
		 * @brief 设置宽度值，实际为x值
		 * 
		 * @param width 
		 */
		void SetWidth(double width) noexcept;
		/**
		 * @brief 设置高度值，实际为y值
		 * 
		 * @param height 
		 */
		void SetHeight(double height) noexcept;
		/**
		 * @brief 通过下标获取二维向量值，常量只能做右值，非常量下可做左值
		 * index < 2
		 * @param index 
		 * @return double 
		 * @exception range_error 下标值超出索引
		 */
		double operator[](const size_t index) const;
		double &operator[](const size_t index);
		/**
		 * @brief 向量相加，值赋值给该向量
		 * 
		 * @param v 
		 */
		void operator+=(const Vector2 &v) noexcept;
		/**
		 * @brief 向量加上一个标量，值赋值给该向量
		 * .x += scalar, .y += scalar
		 * @param s 
		 */
		void operator+=(double s) noexcept;
		/**
		 * @brief 向量相交，返回相加结果
		 * 
		 * @param v 
		 * @return Vector2 
		 */
		Vector2 operator+(const Vector2 &v) const noexcept;
		/**
		 * @brief 向量加上另一个向量乘以一个标量的结果
		 * += v * s
		 * @param v 
		 * @param s 
		 */
		void AddScaledVector(const Vector2 &v, double s) noexcept;
		/**
		 * @brief 该向量加上另一个向量乘以一个标量的结果
		 * this + v * s
		 * @param v 
		 * @param s 
		 * @return Vector2 
		 */
		Vector2 AddedScaleVector(const Vector2 &v, double s) const noexcept;
		/**
		 * @brief 减去一个向量，并赋值给该向量
		 * -= v
		 * @param v 
		 */
		void operator-=(const Vector2 &v) noexcept;
		/**
		 * @brief 减去一个标量，并赋值给该向量
		 * .x -= s, -y -= s
		 * @param s 
		 */
		void operator-=(double s) noexcept;
		/**
		 * @brief 减去向量
		 * this - v
		 * @param v 
		 * @return Vector2 
		 */
		Vector2 operator-(const Vector2 &v) const noexcept;
		/**
		 * @brief 减去标量
		 * .x - s, .y - s
		 * @param s 
		 * @return Vector2 
		 */
		Vector2 operator-(double s) const noexcept;
		/**
		 * @brief 向量相乘，结果赋值给该向量
		 * .x *= v.x, .y *= v.y
		 * @param v 
		 */
		void operator*=(const Vector2 &v) noexcept;
		/**
		 * @brief 向量乘以标量，结果赋值给该向量
		 * .x *= s, .y *= s
		 * @param s 
		 */
		void operator*=(double s) noexcept;

		/**
		 * @brief 向量相乘
		 * .x * v.x, .y * v.y
		 * @param v 
		 * @return Vector2 
		 */
		Vector2 operator*(const Vector2 &v) const noexcept;
		/**
		 * @brief 向量相除，结果赋值该向量
		 * .x /= v.x, .y /= v.y
		 * @param v 
		 * @exception logical_error 除0异常
		 */
		void operator/=(const Vector2 &v);
		/**
		 * @brief 向量除以标量值，结果赋值该向量
		 * .x /= s, .y /= s
		 * @param s 
		 * @exception logical_error 除0异常
		 */
		void operator/=(double s);
		/**
		 * @brief 向量相除
		 * .x / v.x, .y / v.y
		 * @param v 
		 * @return Vector2 
		 * @exception logical_error 除0异常
		 */
		Vector2 operator/(const Vector2 &v) const;
		/**
		 * @brief 向量除以标量
		 * .x / s, .y /s 
		 * @param s 
		 * @return Vector2 
		 * @exception logical_error 除0异常
		 */
		Vector2 operator/(double s) const;
		/**
		 * @brief 通过三维矩阵进行变换，结果赋值给该向量
		 * 
		 * @param m 
		 */
		void Apply(const Matrix3 &m) noexcept;
		/**
		 * @brief 向量通过三维矩阵变换
		 * 
		 * @param m 
		 * @return const Vector2 
		 */
		Vector2 Applied(const Matrix3 &m) const noexcept;
		/**
		 * @brief 求小，返回值赋值给该向量
		 * .x = min(.x, v.x), .y = min(.y, v.y)
		 * @param v 
		 */
		void Min(const Vector2 &v) noexcept;
		/**
		 * @brief 求大，返回赋值给该向量
		 * .x = max(.x, v.x), .y = max(.y, v.y)
		 * @param v 
		 */
		void Max(const Vector2 &v) noexcept;
		/**
		 * @brief 求小
		 * min(.x, v.x), min(.y, v.y)
		 * @param v 
		 * @return Vector2 
		 */
		Vector2 Mined(const Vector2 &v) const noexcept;
		/**
		 * @brief 求大
		 * max(.x, v.x), max(.y, v.y)
		 * @param v 
		 * @return Vector2 
		 */
		Vector2 Maxed(const Vector2 &v) const noexcept;
		/**
		 * @brief 将该向量限定在min和max的范围内
		 * 
		 * @param min 
		 * @param max 
		 */
		void Clamp(const Vector2 &min, const Vector2 &max) noexcept;
		/**
		 * @brief 将该向量限定在min和max的标量范围内
		 * 
		 * @param min 
		 * @param max 
		 */
		void Clamp(double min, double max) noexcept;
		/**
		 * @brief 求取该向量在min和max限定之后的向量值
		 * 
		 * @param min 
		 * @param max 
		 * @return Vector2 
		 */
		Vector2 Clamped(const Vector2 &min, const Vector2 &max) const noexcept;
		/**
		 * @brief 求取该向量在min和max标值值限定之后的向量值
		 * 
		 * @param min 
		 * @param max 
		 * @return Vector2 
		 */
		Vector2 Clamped(double min, double max) const noexcept;
		/**
		 * @brief 向量长度的值限定在min和max范围内
		 * 
		 * @param min 
		 * @param max 
		 */
		void ClampLength(double min, double max) noexcept;
		/**
		 * @brief 求取值限定之后的向量
		 * 
		 * @param min 
		 * @param max 
		 * @return Vector2 
		 */
		Vector2 ClampedLength(double min, double max) noexcept;
		/**
		 * @brief 向量的x和y做floor操作
		 * 
		 */
		void Floor() noexcept;
		/**
		 * @brief 求取该向量的x和y做floor操作之后的向量
		 * 
		 * @return Vector2 
		 */
		Vector2 Floored() const noexcept;
		/**
		 * @brief 向量的x和y做ceil操作
		 * 
		 */
		void Ceil() noexcept;
		/**
		 * @brief 求取该向量的x和y做ceil操作之后的向量
		 * 
		 * @return Vector2 
		 */
		Vector2 Ceiled() const noexcept;
		/**
		 * @brief 向量的x和y做round操作
		 * 
		 */
		void Round() noexcept;
		/**
		 * @brief 求取该向量的x和y做round操作之后的向量
		 * 
		 * @return Vector2 
		 */
		Vector2 Rounded() const noexcept;
		/**
		 * @brief 向量的x和y做roundToZero操作
		 * 
		 */
		void RoundToZero() noexcept;
		/**
		 * @brief 求取该向量的x和y做roundedToZero操作之后的向量
		 * 
		 * @return Vector2 
		 */
		Vector2 RoundedToZero() const noexcept;
		/**
		 * @brief 该向量取反
		 * 
		 */
		void Negate() noexcept;
		/**
		 * @brief 返回该向量取反之后的向量
		 * 
		 * @return Vector2 
		 */
		Vector2 operator-(void) const noexcept;
		/**
		 * @brief 点乘
		 * 
		 * @param v 
		 * @return double 
		 */
		double Dot(const Vector2 &v) const noexcept;
		/**
		 * @brief 叉乘
		 * 
		 * @param v 
		 * @return double 
		 */
		double Cross(const Vector2 &v) const noexcept;
		/**
		 * @brief 求向量的长度
		 * 
		 * @return double 
		 */
		double Length() const noexcept;
		/**
		 * @brief 向量长度的平方
		 * 
		 * @return double 
		 */
		double LengthSq() const noexcept;
		/**
		 * @brief 求取曼哈顿长度
		 * 
		 * @return double 
		 */
		double ManhattanLength() const noexcept;
		/**
		 * @brief 该向量归一化
		 * 
		 */
		void Normalize() noexcept;
		/**
		 * @brief 返回通过该向量归一化的向量
		 * 
		 * @return Vector2 
		 */
		Vector2 Normalized() const noexcept;
		/**
		 * @brief 计算该向量与+x轴之间的夹角
		 * 
		 * @return double 
		 */
		double Angle() const noexcept;
		/**
		 * @brief 两点之间的距离
		 * 
		 * @param v 
		 * @return double 
		 */
		double DistanceTo(const Vector2 &v) const noexcept;
		/**
		 * @brief 两点之间距离平方
		 * 
		 * @param v 
		 * @return double 
		 */
		double DistanceToSquared(const Vector2 &v) const noexcept;
		/**
		 * @brief 求取曼哈顿距离
		 * 
		 * @param v 
		 * @return double 
		 */
		double ManhattanDistanceTo(const Vector2 &v) const noexcept;
		/**
		 * @brief 通过设置长度值修改向量值
		 * 
		 * @param length 
		 */
		void SetLength(double length) noexcept;
		/**
		 * @brief 
		 * 
		 * @param v 
		 * @param alpha 
		 */
		void Lerp(const Vector2 &v, double alpha) noexcept;
		/**
		 * @brief 
		 * 
		 * @param v 
		 * @param alpha 
		 * @return Vector2 
		 */
		Vector2 Lerped(const Vector2 &v, double alpha) const noexcept;
		/**
		 * @brief 
		 * 
		 * @param v 
		 * @param ulp 
		 * @return true 
		 * @return false 
		 */
		bool Equals(const Vector2 &v, uint32_t ulp = 4u) const noexcept;
		/**
		 * @brief 
		 * 
		 * @param v 
		 * @return true 
		 * @return false 
		 */
		bool operator==(const Vector2 &v) const noexcept;
		///**
		// * @brief 
		// * 
		// * @param array 
		// * @param offset 
		// * @exception range_error
		// */
		//void FromArray(const std::vector<double> &array, const size_t offset = 0u);
		///**
		// * @brief 
		// * 
		// * @param array 
		// * @param offset 
		// * @exception range_error
		// */
		//void ToArray(std::vector<double> &array, const size_t offset = 0u);
		///**
		// * @brief 
		// * 
		// * @param attribute 
		// * @param index 
		// */
		//void FromBufferAttribute(const Core::BufferAttribute &attribute, const size_t index) noexcept;
		/**
		 * @brief 
		 * 
		 * @param center 
		 * @param angle 
		 */
		void RotateAround(const Vector2 &center, double angle) noexcept;
		/**
		 * @brief
		 *
		 * @param center
		 * @param angle
		 * @ return Vector2
		 */
		Vector2 RotatedAround(const Vector2& center, double angle) const noexcept;
		/**
		 * @brief 
		 * 
		 * @param os 
		 * @param v 
		 * @return std::ostream& 
		 */
		friend std::ostream &operator<<(std::ostream &os, const Vector2 &v);

	private:
		/**
		 * @brief x
		 * x轴数值
		 */
		double mX;
		/**
		 * @brief y
		 * y轴数值
		 */
		double mY;
	};

	Vector2 operator*(const Vector2& v, double s) noexcept;
	Vector2 operator*(double s, const Vector2& v) noexcept;
	Vector2 operator+(const Vector2& v, double s) noexcept;
	Vector2 operator+(double s, const Vector2& v) noexcept;
} // namespace Three

#include "Vector2.inl"
