
#include "Line3.h"

using namespace std;

namespace Three
{
    inline Line3::Line3() noexcept
    {
    }

    inline Line3::Line3(const Vector3 &start,
                        const Vector3 &end) noexcept : mStart(start),
                                                       mEnd(end)
    {
    }

    inline const Vector3 &Line3::Start() const noexcept
    {
        return mStart;
    }

    inline const Vector3 &Line3::End() const noexcept
    {
        return mEnd;
    }

    inline void Line3::SetStart(const Vector3 &start) noexcept
    {
        mStart = start;
    }

    inline void Line3::SetEnd(const Vector3 &end) noexcept
    {
        mEnd = end;
    }

    inline void Line3::Set(const Vector3 &start, const Vector3 &end) noexcept
    {
        mStart = start;
        mEnd = end;
    }

    inline Vector3 Line3::GetCenter() const noexcept
    {
        return (mStart + mEnd) / 2.;
    }

    inline Vector3 Line3::Delta() const noexcept
    {
        return mEnd - mStart;
    }

    inline double Line3::DistanceSq() const noexcept
    {
        return mEnd.DistanceToSquared(mStart);
    }

    inline double Line3::Distance() const noexcept
    {
        return mEnd.DistanceTo(mStart);
    }

    inline Vector3 Line3::At(double t) const noexcept
    {
        return mStart.Lerped(mEnd, t);
    }

    inline double Line3::ClosestPointToPointParameter(const Vector3 &point,
                                                            bool clampToLine) const noexcept
    {
        const Vector3 _startP(point - mStart);
        const Vector3 _startE(mEnd - mStart);
        double _t = _startE.Dot(_startP) / _startE.Dot(_startE);
        if (clampToLine)
        {
            return MathUtil::Clamp(_t, 0., 1.);
        }
        else
        {
            return _t;
        }
    }

    inline Vector3 Line3::ClosePointToPoint(const Vector3 &point,
                                                  bool clampToLine) const noexcept
    {
        return At(ClosestPointToPointParameter(point, clampToLine));
    }

    inline void Line3::operator*=(const Matrix4 &m)
    {
        mStart.Apply(m);
        mEnd.Apply(m);
    }

    inline Line3 Line3::operator*(const Matrix4 &m) const
    {
        return Line3(mStart.Applied(m), mEnd.Applied(m));
    }

    inline bool Line3::Equals(const Line3 &line, uint32_t ulp) const
    {
        return mStart.Equals(line.mStart) && mEnd.Equals(mEnd);
    }

    inline bool Line3::operator==(const Line3 &line) const
    {
        return Equals(line);
    }

    inline std::ostream &operator<<(std::ostream &os, const Line3 &line)
    {
        os << "{type:'Line3',"
           << "start:" << line.Start() << ","
           << "end:" << line.End() << "}";
        return os;
    }

} // namespace Three
