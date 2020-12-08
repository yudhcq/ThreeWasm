/**
 * @file Box2.h
 * @author yudonghai (yudhcq@163.com)
 * @brief 二维盒头文件
 * @version 0.0.1
 * @date 2020-04-18
 * 
 */
#pragma once
#include <vector>
#include <ostream>

#include "Vector2.h"

/**
 * @brief Three
 * 数学类的命名空间
 */
namespace Three
{
	/**
	 * @brief 二维盒
	 * 采用一个min二维向量和一个max二维向量的表示方法
	 */
	class Box2
	{
	public:
		/**
		 * @brief Box2 默认构造函数
		 * 将构造出一个空的二维盒子
		 */
		Box2() noexcept;
		/**
		 * @brief Box2 构造函数
		 * 通过极大值点和极小值点构造一个二维盒子
		 * @param min 极大值点
		 * @param max 极小值点
		 */
		Box2(const Vector2 &min, const Vector2 &max) noexcept;
		/**
		 * @brief 获取极大值点的常引用
		 * 
		 * @return const Vector2&
		 */
		const Vector2 &Max() const noexcept;
		/**
		 * @brief 获取极小值点的常引用
		 * 
		 * @return const Vector2& 
		 */
		const Vector2 &Min() const noexcept;
		/**
		 * @brief 设置极大值点
		 * 
		 * @param max 
		 */
		void SetMax(const Vector2 &max) noexcept;
		/**
		 * @brief 设置极小值点
		 * 
		 * @param min 
		 */
		void SetMin(const Vector2 &min) noexcept;
		/**
		 * @brief 同时设置极大值点和极小值点
		 * 
		 * @param min 
		 * @param max 
		 */
		void Set(const Vector2 &min, const Vector2 &max) noexcept;
		/**
		 * @brief 通过中线点和盒子尺寸设置二维盒子
		 * 
		 * @param center 中心点坐标值
		 * @param size 盒子尺寸
		 */
		void SetFromCenterAndSize(const Vector2 &center, const Vector2 &size) noexcept;
		/**
		 * @brief 通过一组二维点坐标值设置二维盒子
		 * 
		 * @param points 
		 */
		void SetFromPoints(const std::vector<Vector2> &points) noexcept;
		/**
		 * @brief 将二维盒子置空
		 * 
		 */
		void MakeEmpty() noexcept;
		/**
		 * @brief 判断二维盒子是否为空
		 * 
		 * @return true 表示空 
		 * @return false 表示不为空
		 */
		bool IsEmpty() const noexcept;
		/**
		 * @brief 获取二维盒子的中心点
		 * 
		 * @return Vector2 中心点坐标值
		 */
		Vector2 GetCenter() const noexcept;
		/**
		 * @brief 获取二维盒子的尺寸
		 * 
		 * @return Vector2 二维盒子尺寸
		 */
		Vector2 GetSize() const noexcept;
		/**
		 * @brief 通过二位点扩充二维盒子
		 * 
		 * @param point 二维点坐标值
		 */
		void ExpandByPoint(const Vector2 &point) noexcept;
		/**
		 * @brief 通过二维向量扩充二维盒子，盒子的极大值点和极小值点都将会被扩充
		 * 
		 * @param point 
		 */
		void ExpandByVector(const Vector2 &point) noexcept;
		/**
		 * @brief 通过标量来扩充二维盒子
		 * 
		 * @param scalar 标量值
		 */
		void ExpandByScalar(double scalar) noexcept;
		/**
		 * @brief 判断二维盒子与二维点的包含关系
		 * 
		 * @param point 需判断二维点坐标值
		 * @return true 包含
		 * @return false 不包含
		 */
		bool ContainsPoint(const Vector2 &point) const noexcept;
		/**
		 * @brief 判断二维盒子与二维盒子的包含关系
		 * 
		 * @param box 需判断二维盒子
		 * @return true 该盒子包含需判断盒子
		 * @return false 该盒子不包含需判断盒子
		 */
		bool ContainsBox(const Box2 &box) const noexcept;
		/**
		 * @brief 获取二维点在二维盒子范围内比例值
		 * 
		 * @param point 需用于获取比例的点
		 * @return Vector2 
		 * @exception logical_error 当二维盒子尺寸的x或者y为0的时候将会抛出该异常
		 */
		Vector2 GetParameter(const Vector2 &point) const;
		/**
		 * @brief 判断两个二维盒子是否相交
		 * 
		 * @param box 需判断二维盒子
		 * @return true 相交
		 * @return false 不相交 
		 */
		bool IntersectsBox(const Box2 &box) const noexcept;
		/**
		 * @brief 将二维点的坐标值限制在二维盒子的最小值点和最大值点范围内
		 * 
		 * @param point 需限制的二维点坐标值
		 * @return Vector2 返回限制之后的二维点坐标值
		 */
		Vector2 ClampPoint(const Vector2 &point) const noexcept;
		/**
		 * @brief 二维点到二维盒子的距离，如果二维点在二维盒子内部，则距离为0
		 * 
		 * @param point 需求取距离的二维坐标值
		 * @return double 距离值
		 */
		double DistanceToPoint(const Vector2 &point) const noexcept;
		/**
		 * @brief 该二维盒子与其他二维盒子做交集的结果赋值给该盒子
		 * 
		 * @param box 需用于求取交集的二维盒子
		 */
		void operator&=(const Box2 &box) noexcept;
		/**
		 * @brief 该二维盒子与其他二维盒子做并集的结果赋值给该盒子
		 * 
		 * @param box 需用于求取并集的二维盒子
		 */
		void operator|=(const Box2 &box) noexcept;

		/**
		 * @brief 该二维盒子与其他二维盒子做交集
		 * 
		 * @param box 需用于求取交集的二维盒子
		 * @return Box2 交集结果
		 */
		Box2 operator&(const Box2 &box) const noexcept;

		/**
		 * @brief 该二维盒子与其他二维盒子做并集
		 * 
		 * @param box 需用于求取并集的二维盒子
		 * @return Box2 并集结果
		 */
		Box2 operator|(const Box2 &box) const noexcept;
		/**
		 * @brief 将该二维盒子平移offset
		 * 
		 * @param offset 用于平移的二维向量值
		 */
		void Translate(const Vector2 &offset) noexcept;

		Box2 Translated(const Vector2 &offset) const noexcept;
		/**
		 * @brief 判断二维盒子是否相等
		 * 对于二维盒子是否相等的一个模糊判断，precision用于设置判断精度，其值越大判断越准确
		 * @param box 需判断二维盒子
		 * @param ulp Unit in the last place，默认为4
		 * 详见https://en.wikipedia.org/wiki/Unit_in_the_last_place
		 * @return true 表示相等
		 * @return false 表示不等
		 */
		bool Equals(const Box2 &box, uint32_t ulp = 4u) const noexcept;
		/**
		 * @brief 判断两个二维盒子是否相等
		 * 使用的是Equals方法，Unit in the last place，默认为4
		 * @param box 需用于判断的二维盒子
		 * @return true 表示相等
		 * @return false 表示不等
		 */
		bool operator==(const Box2 &box) const noexcept;
		/**
		 * @brief 用于输出JSON格式字符串的二维盒子
		 * 
		 * @param os 输出流
		 * @param box 需输出盒子
		 * @return std::ostream& 返回输出流
		 */
		friend std::ostream &operator<<(std::ostream &os, const Box2 &box);

	private:
		/**
		 * @brief min
		 * 包围盒的最小点
		 */
		Vector2 mMin;
		/**
		 * @brief max
		 * 包围盒的最大点
		 */
		Vector2 mMax;
	};
} // namespace Three

#include "Box2.inl"