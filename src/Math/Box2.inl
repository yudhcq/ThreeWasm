#include <exception>
#include <float.h>

#include "Box2.h"

using namespace std;

namespace Three
{
	inline Box2::Box2() noexcept : 
		mMin(DBL_MAX, DBL_MAX), 
		mMax(-DBL_MAX, -DBL_MAX)
	{
	}

	inline Box2::Box2(const Vector2 &min,
					  const Vector2 &max) noexcept : mMin(min),
													 mMax(max)
	{
	}

	inline const Vector2 &Box2::Max() const noexcept
	{
		return mMax;
	}

	inline const Vector2 &Box2::Min() const noexcept
	{
		return mMin;
	}

	inline void Box2::SetMax(const Vector2 &max) noexcept
	{
		mMax = max;
	}

	inline void Box2::SetMin(const Vector2 &min) noexcept
	{
		mMin = min;
	}

	inline void Box2::Set(const Vector2 &min, const Vector2 &max) noexcept
	{
		mMax = max;
		mMin = min;
	}

	inline void Box2::SetFromCenterAndSize(const Vector2 &center, const Vector2 &size) noexcept
	{
		const auto &_halfSize = size / 2.0;
		mMax = center + _halfSize;
		mMin = center - _halfSize;
	}

	inline void Box2::SetFromPoints(const std::vector<Vector2> &points) noexcept
	{
		for (const auto &_point : points)
		{
			ExpandByPoint(_point);
		}
	}

	inline void Box2::MakeEmpty() noexcept
	{
		mMax.Set(-DBL_MAX, -DBL_MAX);
		mMin.Set(DBL_MAX, DBL_MAX);
	}

	inline bool Box2::IsEmpty() const noexcept
	{
		return mMax.X() < mMin.X() || mMax.Y() < mMin.Y();
	}

	inline Vector2 Box2::GetCenter() const noexcept
	{
		if (IsEmpty())
		{
			return Vector2();
		}
		else
		{
			return (mMax + mMin) / 2.0;
		}
	}

	inline Vector2 Box2::GetSize() const noexcept
	{
		if (IsEmpty())
		{
			return Vector2();
		}
		else
		{
			return mMax - mMin;
		}
	}

	inline void Box2::ExpandByPoint(const Vector2 &point) noexcept
	{
		mMax.Max(point);
		mMin.Min(point);
	}

	inline void Box2::ExpandByVector(const Vector2 &point) noexcept
	{
		mMax += point;
		mMin -= point;
	}

	inline void Box2::ExpandByScalar(double scalar) noexcept
	{
		mMax += scalar;
		mMin -= scalar;
	}

	inline bool Box2::ContainsPoint(const Vector2 &point) const noexcept
	{
		return !(point.X() < mMin.X() ||
				 point.Y() < mMin.Y() ||
				 point.X() > mMax.X() ||
				 point.Y() > mMax.Y());
	}

	inline bool Box2::ContainsBox(const Box2 &box) const noexcept
	{
		return box.mMin.X() >= mMin.X() &&
			box.mMin.Y() >= mMin.Y() &&
			box.mMax.X() <= mMax.X() &&
			box.mMax.Y() <= mMax.Y();
	}

	inline Vector2 Box2::GetParameter(const Vector2 &point) const
	{
		return (point - mMin) / GetSize();
	}

	inline bool Box2::IntersectsBox(const Box2 &box) const noexcept
	{
		return !(box.mMax.X() < mMin.X() ||
				 box.mMin.X() > mMax.X() ||
				 box.mMax.Y() < mMin.Y() ||
				 box.mMin.Y() > mMax.Y());
	}

	inline Vector2 Box2::ClampPoint(const Vector2 &point) const noexcept
	{
		return point.Clamped(mMin, mMax);
	}

	inline double Box2::DistanceToPoint(const Vector2 &point) const noexcept
	{
		return (point.Clamped(mMin, mMax) - point).Length();
	}

	inline void Box2::operator&=(const Box2 &box) noexcept
	{
		mMax.Min(box.mMax);
		mMin.Max(box.mMin);
	}

	inline void Box2::operator|=(const Box2 &box) noexcept
	{
		mMax.Max(box.mMax);
		mMin.Min(box.mMin);
	}

	inline Box2 Box2::operator&(const Box2 &box) const noexcept
	{
		return Box2(mMin.Maxed(box.mMin), mMax.Mined(box.mMax));
	}

	inline Box2 Box2::operator|(const Box2 &box) const noexcept
	{
		return Box2(mMin.Mined(box.mMin), mMax.Maxed(box.mMax));
	}

	//!
	inline void Box2::Translate(const Vector2 &offset) noexcept
	{
		mMax += offset;
		mMin += offset;
	}

	inline Box2 Box2::Translated(const Vector2& offset) const noexcept
	{
		return Box2(mMin + offset, mMax + offset);
	}

	inline bool Box2::Equals(const Box2 &box, uint32_t ulp) const noexcept
	{
		return mMin.Equals(box.mMin, ulp) && mMax.Equals(box.mMax, ulp);
	}

	inline bool Box2::operator==(const Box2 &box) const noexcept
	{
		return Equals(box);
	}

	inline ostream &operator<<(ostream &os, const Box2 &box)
	{
		os << "{type:"
		   << "'Box2',"
		   << "min:"
		   << box.mMin
		   << ","
		   << "max:"
		   << box.mMax
		   << "}";

		return os;
	}
} // namespace Three
