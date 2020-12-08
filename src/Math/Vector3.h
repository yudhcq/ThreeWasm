/**
 * @file Vector3.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 三维向量或点类头文件
 * @version 0.0.1
 * @date 2020-04-25
 * 
 */
#pragma once
#include <ostream>
#include <vector>

namespace Three
{
	class Camera;
	class Euler;
	class Matrix3;
	class Matrix4;
	class Quaternion;
	class Plane;
	class Spherical;
	class Cylindrical;
	/**
	 * @brief Vector3
	 * 三维向量或点类
	 */
	class Vector3
	{
	public:
		Vector3() noexcept;
		explicit Vector3(double scalar) noexcept;
		Vector3(double x, double y, double z) noexcept;

		double X() const noexcept;
		double Y() const noexcept;
		double Z() const noexcept;

		void SetX(double value) noexcept;
		void SetY(double value) noexcept;
		void SetZ(double value) noexcept;
		void Set(double x, double y, double z) noexcept;
		void Set(double scalar) noexcept;
		/**
		 * @brief 
		 * 
		 * @param index 
		 * @return const double 
		 * @exception range_error
		 */
		double operator[](const size_t index) const;
        double& operator[](const size_t index);

		void operator+=(const Vector3 &v) noexcept;
		void operator+=(double s) noexcept;
		void AddScaledVector(const Vector3 &v, double s) noexcept;

		Vector3 operator+(const Vector3 &v) const noexcept;
		Vector3 operator+(double s) const noexcept;
		Vector3 AddedScaledVector(const Vector3 &v, double s);

		void operator-=(const Vector3 &v) noexcept;
		void operator-=(double s) noexcept;

		Vector3 operator-(const Vector3 &v) const noexcept;
		Vector3 operator-(double s) const noexcept;

		void operator*=(const Vector3 &v) noexcept;
		void operator*=(double s) noexcept;

		Vector3 operator*(const Vector3 &v) const noexcept;
		Vector3 operator*(double s) const noexcept;

		void Apply(const Euler &e) noexcept;
		void Apply(const Vector3 &axis, double angle) noexcept;
		void Apply(const Matrix3 &m) noexcept;
		void ApplyNormalMatrix(const Matrix3 &m) noexcept;
		/**
	 * @brief 
	 * 
	 * @param m
	 * @exception logical_error 矩阵数据异常 
	 */
		void Apply(const Matrix4 &m);
		void Apply(const Quaternion &q) noexcept;

		Vector3 Applied(const Euler &e) const noexcept;
		Vector3 Applied(const Vector3 &axis, double angle) const noexcept;
		Vector3 Applied(const Matrix3 &m) const noexcept;
		Vector3 AppliedNormalMatrix(const Matrix3 &m) const noexcept;
		Vector3 Applied(const Matrix4 &m) const noexcept;
		Vector3 Applied(const Quaternion &q) const noexcept;

		void Unproject(const Camera &camera) noexcept;

		Vector3 Unprojected(const Camera &camera) const noexcept;

		void TransformDirection(const Matrix4 &m) noexcept;

		Vector3 TransformedDirection(const Matrix4 &m) const noexcept;
		/**
	 * @brief 
	 * 
	 * @param v
	 * @exception logical_error 
	 */
		void operator/=(const Vector3 &v);
		/**
	 * @brief 
	 * 
	 * @param v
	 * @exception logical_error 
	 */
		void operator/=(double s);
		/**
	 * @brief 
	 * 
	 * @param v
	 * @exception logical_error 
	 */
		Vector3 operator/(const Vector3 &v) const;
		/**
	 * @brief 
	 * 
	 * @param v
	 * @exception logical_error 
	 */
		Vector3 operator/(double s) const;

		void Min(const Vector3 &v) noexcept;

		void Max(const Vector3 &v) noexcept;

		Vector3 Mined(const Vector3 &v) const noexcept;

		Vector3 Maxed(const Vector3 &v) const noexcept;

		void Clamp(const Vector3 &min, const Vector3 &max) noexcept;
		void Clamp(double min, double max) noexcept;
		void ClampLength(double min, double max) noexcept;

		Vector3 Clamped(const Vector3 &min, const Vector3 &max) const noexcept;
		Vector3 Clamped(double min, double max) const noexcept;
		Vector3 ClampedLength(double min, double max) const noexcept;

		void Floor() noexcept;

		void Round() noexcept;

		void Ceil() noexcept;

		void RoundToZero() noexcept;

		Vector3 Floored() const noexcept;

		Vector3 Rounded() const noexcept;

		Vector3 Ceiled() const noexcept;

		Vector3 RoundedToZero() const noexcept;

		void Negate() noexcept;

		Vector3 Negated() const noexcept;

		Vector3 operator-(void) const noexcept;

		double Dot(const Vector3 &v) const noexcept;

		double LengthSq() const noexcept;

		double Length() const noexcept;

		double Manhattanlength() const noexcept;

		double ManhattanDistanceTo(const Vector3 &v) const noexcept;

		void Normalize() noexcept;

		Vector3 Normalized() const noexcept;

		void SetLength(double l) noexcept;

		void Lerp(const Vector3 &v, double alpha) noexcept;

		Vector3 Lerped(const Vector3 &v, double dalpha) const noexcept;

		void Cross(const Vector3 &a) noexcept;

		Vector3 Crossed(const Vector3 &a) const noexcept;

		void Project(const Vector3 &v) noexcept;
		void Project(const Plane &plane) noexcept;
		void Project(const Camera &camera) noexcept;

		Vector3 Projected(const Vector3 &v) const noexcept;
		Vector3 Projected(const Plane &plane) const noexcept;
		Vector3 Projected(const Camera &camera) const noexcept;

		void Reflect(const Plane &plane) noexcept;

		const Vector3 Reflected(const Plane &plane) const noexcept;

		double AngleTo(const Vector3 &v) const noexcept;

		double DistanceTo(const Vector3 &v) const noexcept;

		double DistanceToSquared(const Vector3 &v) const noexcept;

		void SetFromSpherical(const Spherical &s) noexcept;
		void SetFromSpherical(double radius, double phi, double theta) noexcept;

		void SetFromCylindrical(const Cylindrical &c) noexcept;
		void SetFromCylindrical(double radius, double theta, double y) noexcept;

		void SetFromMatrixPosition(const Matrix4 &m) noexcept;

		void SetFromMatrixScale(const Matrix4 &m) noexcept;

		void SetFromMatrixColumn(const Matrix4 &m, const size_t index);

		void SetFromMatrix3Column(const Matrix3 &m, const size_t index);

		bool Equals(const Vector3 &v, uint32_t ulp = 4u) const noexcept;
		bool operator==(const Vector3 &v) const noexcept;

		friend std::ostream &operator<<(std::ostream &os, const Vector3 &v);

	private:
		/**
		 * @brief x
		 * x轴上值
		 */
		double mX;
		/**
		 * @brief y
		 * y轴上值
		 */
		double mY;
		/**
		 * @brief z
		 * z轴上值
		 * 
		 */
		double mZ;

	public:
		const static Vector3 UINT_X;
		const static Vector3 UINT_Y;
		const static Vector3 UINT_Z;
	};
} // namespace Three

#include "Vector3.inl"
