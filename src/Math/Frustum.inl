#include <exception>

#include "Frustum.h"
#include "Plane.h"
#include "Matrix4.h"
#include "Sphere.h"
#include "Box3.h"

using namespace std;

namespace Three
{
    inline Frustum::Frustum() noexcept
    {
    }

    inline Frustum::Frustum(const Plane &p0, const Plane &p1,
                            const Plane &p2, const Plane &p3,
                            const Plane &p4, const Plane &p5) noexcept
    {
        mPlanes[0] = p0;
        mPlanes[1] = p1;
        mPlanes[2] = p2;
        mPlanes[3] = p3;
        mPlanes[4] = p4;
        mPlanes[5] = p5;
    }

    inline void Frustum::Set(const Plane &p0, const Plane &p1,
                             const Plane &p2, const Plane &p3,
                             const Plane &p4, const Plane &p5) noexcept
    {
        mPlanes[0] = p0;
        mPlanes[1] = p1;
        mPlanes[2] = p2;
        mPlanes[3] = p3;
        mPlanes[4] = p4;
        mPlanes[5] = p5;
    }

    inline const Plane &Frustum::operator[](const size_t index) const
    {
        if (index > 5)
        {
            throw range_error("frustum const operator[] index 超出索引");
        }
        else
        {
            return mPlanes[index];
        }
    }

    inline Plane &Frustum::operator[](const size_t index)
    {
        if (index > 5)
        {
            throw range_error("frustum operator[] index 超出索引");
        }
        else
        {
            return mPlanes[index];
        }
    }

    inline void Frustum::SetFromProjectionMatrix(const Matrix4 &m)
    {
        mPlanes[0].Set(m[3] - m[0], m[7] - m[4], m[11] - m[8], m[15] - m[12]);
        mPlanes[0].Normalize();
        mPlanes[1].Set(m[3] + m[0], m[7] + m[4], m[11] + m[8], m[15] + m[12]);
        mPlanes[1].Normalize();
        mPlanes[2].Set(m[3] + m[1], m[7] + m[5], m[11] + m[9], m[15] + m[13]);
        mPlanes[2].Normalize();
        mPlanes[3].Set(m[3] - m[1], m[7] - m[5], m[11] - m[9], m[15] - m[13]);
        mPlanes[3].Normalize();
        mPlanes[4].Set(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]);
        mPlanes[4].Normalize();
        mPlanes[5].Set(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]);
        mPlanes[5].Normalize();
    }

    inline bool Frustum::IntersectsObject(const Object3D &object) const
    {
        // todo
    }

    inline bool Frustum::IntersectsSprite(const Sprite &sprite) const
    {
        // todo
    }

    inline bool Frustum::IntersectsSphere(const Sphere &sphere) const
    {
        const auto &_center = sphere.Center();
        const auto _negRadius = - sphere.Radius();
        for (const auto &_p : mPlanes)
        {
            if (_p.DistanceTo(_center) < _negRadius)
            {
                return false;
            }
        }
        return true;
    }

    inline bool Frustum::IntersectsBox(const Box3 &box) const
    {
        for (const auto &_p : mPlanes)
        {
            const auto &_pn = _p.Normal();
            const Vector3 _vec(_pn.X() > 0. ? box.Max().X() : box.Min().X(),
                               _pn.Y() > 0. ? box.Max().Y() : box.Min().Y(),
                               _pn.Z() > 0. ? box.Max().Z() : box.Min().Z());
            if (_p.DistanceTo(_vec) < 0.)
            {
                return false;
            }
        }
        return true;
    }

    inline bool Frustum::ContainsPoint(const Vector3 &point) const
    {
        for (const auto &_p : mPlanes)
        {
            if (_p.DistanceTo(point) < 0.)
            {
                return false;
            }
        }
        return true;
    }

    inline std::ostream &operator<<(std::ostream &os, const Frustum &frustum)
    {
        os << "{type:'Frustum',"
           << "planes:["
           << frustum[0] << ","
           << frustum[1] << ","
           << frustum[2] << ","
           << frustum[3] << ","
           << frustum[4] << ","
           << frustum[5] << "]}";
        return os;
    }

} // namespace Three
