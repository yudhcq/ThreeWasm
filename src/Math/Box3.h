/**
 * @file Box3.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 三位盒子类头文件
 * @version 0.0.1
 * @date 2020-04-18
 * 
 */

#pragma once
#include <vector>
#include <ostream>

#include "Vector3.h"

namespace Three
{
	class BufferAttrobute;
	class Object3D;
} // namespace Three

/**
 * @brief Three
 * 数学类命名空间
 */
namespace Three
{
	class Sphere;
	class Plane;
	class Triangle;
	class Matrix4;

	/**
	 * @brief Box3
	 * 三维盒子
	 */
	class Box3
	{
	public:
		/**
		 * @brief Box3 默认构造函数
		 * 将构造出一个空的三维盒子
		 */
		Box3() noexcept;
		/**
		 * @brief Box3 构造函数
		 * 通过三维极大值点和三维极小值点构造三维盒子
		 * @param min 极小值点坐标值
		 * @param max 极大值点坐标值
		 */
		Box3(const Vector3 &min, const Vector3 &max) noexcept;
		/**
		 * @brief 同时设置三维盒子的极大值点和极小值点
		 * 
		 * @param min 极小值点坐标值
		 * @param max 极大值点坐标值
		 */
		void Set(const Vector3 &min, const Vector3 &max) noexcept;
		/**
		 * @brief 获取极小值点坐标值常量引用
		 * 
		 * @return const Vector3& 
		 */
		const Vector3 &Min() const noexcept;
		/**
		 * @brief 获取极大值点常量引用
		 * 
		 * @return const Vector3& 
		 */
		const Vector3 &Max() const noexcept;
		/**
		 * @brief 设置极大值点坐标值
		 * 
		 * @param max 
		 */
		void SetMax(const Vector3 &max) noexcept;
		/**
		 * @brief 设置极小值点坐标值
		 * 
		 * @param min 
		 */
		void SetMin(const Vector3 &min) noexcept;
		/**
		 * @brief 通过一组点设置三维盒子
		 * 
		 * @param points 
		 */
		void SetFromPoints(const std::vector<Vector3> &points) noexcept;
		/**
		 * @brief 通过中心点和尺寸设置三维盒子
		 * 
		 * @param center 
		 * @param size 
		 */
		void SetFromCenterAndSize(const Vector3 &center, const Vector3 &size) noexcept;
		/**
		 * @brief 将三维盒子置空
		 * 此时三维盒子的极大值点的xyz都为-DBL_MAX，极小值点的xyz都为DBL_MAX
		 */
		void MakeEmpty() noexcept;
		/**
		 * @brief 判断该三维盒子是否为空
		 * 三维盒子为空表示其极小值点的xyz坐标值存在大于极大值点的xyz坐标值
		 * @return true 表示为空
		 * @return false 表示不为空
		 */
		bool IsEmpty() const noexcept;
		/**
		 * @brief 获取三维盒子的中心点坐标
		 * 
		 * @return Vector3 
		 */
		Vector3 GetCenter() const noexcept;
		/**
		 * @brief 获取三维盒子的尺寸值
		 * 
		 * @return Vector3 
		 */
		Vector3 GetSize() const noexcept;
		/**
		 * @brief 通过一个三位点扩充三维盒子
		 * 
		 * @param point 
		 */
		void ExpandByPoint(const Vector3 &point) noexcept;
		/**
		 * @brief 通过一个三维向量扩充盒子
		 * 盒子的极大值点和极小值点都会发生向量值大小的扩充
		 * @param vector 
		 */
		void ExpandByVector(const Vector3 &vector) noexcept;
		/**
		 * @brief 通过一个标量扩充三维盒子
		 * 
		 * @param scalar 
		 */
		void ExpandByScalar(double scalar) noexcept;
		/**
		 * @brief 三维盒子和点之间的包含关系
		 * 
		 * @param point 
		 * @return true 包含
		 * @return false 不包含
		 */
		bool ContainsPoint(const Vector3 &point) const noexcept;
		/**
		 * @brief 三维盒子和三维盒子之间的包含关系
		 * 
		 * @param box 
		 * @return true 该盒子包含传入盒子
		 * @return false 该盒子不包含传入盒子
		 */
		bool ContainsBox(const Box3 &box) const noexcept;
		/**
		 * @brief 获取二维点在二维盒子范围内比例值
		 * 
		 * @param point 需用于获取比例的点
		 * @return Vector3 返回传入点的三个维度的比例值
		 * @exception logical_error 当三维盒子尺寸的x或者y为0的时候将会抛出该异常
		 */
		Vector3 GetParamter(const Vector3 &point) const;
		/**
		 * @brief 和三维盒子碰撞
		 * 
		 * @param box 
		 * @return true 碰撞
		 * @return false 未碰撞
		 */
		bool IntersectsBox(const Box3 &box) const noexcept;
		/**
		 * @brief 和三维球碰撞
		 * 球中心点到盒子的距离小于球的半径
		 * @param sphere 
		 * @return true 发生碰撞
		 * @return false 未碰撞
		 */
		bool IntersectsSphere(const Sphere &sphere) const noexcept;
		/**
		 * @brief 和平面碰撞
		 * 
		 * @param plane 
		 * @return true 发生碰撞
		 * @return false 未发生碰撞
		 */
		bool IntersectsPlane(const Plane &plane) const;
		/**
		 * @brief 和三角形发生碰撞
		 * 
		 * @param triangle 
		 * @return true 发生碰撞
		 * @return false 未发生碰撞
		 */
		bool IntersectsTriangle(const Triangle &triangle) const;
		/**
		 * @brief 将三维点的坐标值限制在三维盒子的最小值点和最大值点范围内
		 * 
		 * @param point 
		 * @return Vector2 返回限制之后的三维点坐标值
		 */
		Vector3 ClampPoint(const Vector3 &point) const noexcept;
		/**
		 * @brief 点到盒子的距离，如果点在盒子内部则距离为0
		 * 
		 * @param point 
		 * @return double 返回距离
		 */
		double DistanceToPoint(const Vector3 &point) const noexcept;
		/**
		 * @brief 获取盒子的包围球
		 * 
		 * @return Sphere 
		 */
		Sphere GetBoundingSphere() const noexcept;
		/**
		 * @brief 求取交集，并将结果赋值给该盒子
		 * 
		 * @param box 
		 */
		void operator&=(const Box3 &box) noexcept;
		/**
		 * @brief 求取并集，并将结果赋值给该盒子
		 * 
		 * @param box 
		 */
		void operator|=(const Box3 &box) noexcept;
		/**
		 * @brief 两盒子求取交集
		 * 
		 * @param box 
		 * @return Box3 返回结果
		 */
		Box3 operator&(const Box3 &box) const noexcept;
		/**
		 * @brief 两盒子求取并集
		 * 
		 * @param box 
		 * @return Box3 返回盒子
		 */
		Box3 operator|(const Box3 &box) const noexcept;
		/**
		 * @brief 乘上四维矩阵，并将结果复制给该盒子
		 * 
		 * @param matrix 
		 */
		void operator*=(const Matrix4 &matrix) noexcept;
		/**
		 * @brief 乘上四维矩阵，返回结果
		 * 
		 * @param matrix 
		 * @return Box3 
		 */
		Box3 operator*(const Matrix4 &matrix) const noexcept;
		/**
		 * @brief 平移盒子
		 * 
		 * @param offset 
		 */
		void Translate(const Vector3 &offset) noexcept;

		Box3 Translated(const Vector3 &offset) const noexcept;
		/**
		 * @brief 判断盒子是否相等
		 * 
		 * @param box 
		 * @param ulp unit in the last place
		 * @return true 相等
		 * @return false 不等
		 */
		bool Equals(const Box3 &box, const uint8_t ulp = 4u) const noexcept;
		/**
		 * @brief 判断盒子是否相等
		 * 使用的是Equals方法，Unit in the last place，默认为4
		 * @param box 
		 * @return true 相等
		 * @return false 不等
		 */
		bool operator==(const Box3 &box) const noexcept;
		/**
		 * @brief 将box3输出为json类型的字符串
		 * 
		 * @param os 输出流
		 * @param box 需输出盒子
		 * @return std::ostream& 
		 */
		friend std::ostream &operator<<(std::ostream &os, const Box3 &box);

	private:
		/**
		 * @brief min
		 * 包围盒的最小点
		 */
		Vector3 mMin;
		/**
		 * @brief max
		 * 包围盒的最大点
		 */
		Vector3 mMax;
	};
} // namespace Three

#include "Box3.inl"