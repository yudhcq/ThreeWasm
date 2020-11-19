#include "Ray.h"
#include "Plane.h"

using namespace std;

namespace Three::Math
{
    inline Ray::Ray() noexcept
    {
    }

    inline Ray::Ray(const Vector3 &origin, const Vector3 &direction) noexcept : mOrigin(origin),
                                                                                mDirection(direction)
    {
    }

    inline const Vector3 &Ray::Origin() const noexcept
    {
        return mOrigin;
    }

    inline const Vector3 &Ray::Direction() const noexcept
    {
        return mDirection;
    }

    inline void Ray::SetOrigin(const Vector3 &o) noexcept
    {
        mOrigin = o;
    }

    inline void Ray::SetDirection(const Vector3 &d) noexcept
    {
        mDirection = d;
    }

    inline void Ray::Set(const Vector3 &o, const Vector3 &d) noexcept
    {
        mOrigin = o;
        mDirection = d;
    }

    inline Vector3 Ray::At(double t) const noexcept
    {
        return mOrigin + mDirection * t;
    }

    inline void Ray::LookAt(const Vector3 &v) noexcept
    {
        mDirection = v - mOrigin;
        mDirection.Normalize();
    }

    inline void Ray::Recast(double t) noexcept
    {
        mOrigin = At(t);
    }

    inline Ray Ray::Recasted(double t) const noexcept
    {
        Ray _r(*this);
        _r.Recast(t);
        return _r;
    }

    inline Vector3 Ray::ClosestPointToPoint(const Vector3 &point) const
    {
        Vector3 _v(point - mOrigin);
        double _directionDistance = _v.Dot(mDirection);
        if (_directionDistance < 0.)
        {
            return mOrigin;
        }
        return At(_directionDistance);
    }

    inline double Ray::DistanceTo(const Vector3 &point) const
    {
        return sqrt(DistanceSqTo(point));
    }

    inline double Ray::DistanceSqTo(const Vector3 &point) const
    {
        return point.DistanceToSquared(ClosestPointToPoint(point));
    }

    inline double Ray::DistanceSqTo(const Vector3 &v0,
                                          const Vector3 &v1,
                                          shared_ptr<Vector3> optionalPointOnRaySPtr,
                                          shared_ptr<Vector3> optionalPointOnSegmentSPtr) const
    {
        const Vector3 _segCenter = (v0 + v1) * 0.5;
        const Vector3 _segDir = (v1 - v0).Normalized();
        const Vector3 _diff = mOrigin - _segCenter;

        const double _segExtent = v0.DistanceTo(v1) * 0.5;
        const double _a01 = -mDirection.Dot(_segDir);
        const double _b0 = _diff.Dot(mDirection);
        const double _b1 = -_diff.Dot(_segDir);
        const double _c = _diff.LengthSq();
        const double _det = abs(1. - _a01 * _a01);
        double _s0 = 0., _s1 = 0., _sqrDist = 0., _extDet = 0.;

        if (_det > 0.)
        {

            // The ray and segment are not parallel.

            _s0 = _a01 * _b1 - _b0;
            _s1 = _a01 * _b0 - _b1;
            _extDet = _segExtent * _det;

            if (_s0 >= 0.)
            {

                if (_s1 >= -_extDet)
                {

                    if (_s1 <= _extDet)
                    {

                        // region 0
                        // Minimum at interior points of ray and segment.

                        double _invDet = 1. / _det;
                        _s0 *= _invDet;
                        _s1 *= _invDet;
                        _sqrDist = _s0 * (_s0 + _a01 * _s1 + 2. * _b0) +
                                   _s1 * (_a01 * _s0 + _s1 + 2. * _b1) + _c;
                    }
                    else
                    {

                        // region 1

                        _s1 = _segExtent;
                        _s0 = max(0., -(_a01 * _s1 + _b0));
                        _sqrDist = -_s0 * _s0 + _s1 * (_s1 + 2. * _b1) + _c;
                    }
                }
                else
                {

                    // region 5

                    _s1 = -_segExtent;
                    _s0 = max(0., -(_a01 * _s1 + _b0));
                    _sqrDist = -_s0 * _s0 + _s1 * (_s1 + 2 * _b1) + _c;
                }
            }
            else
            {

                if (_s1 <= -_extDet)
                {

                    // region 4

                    _s0 = max(0., -(-_a01 * _segExtent + _b0));
                    _s1 = (_s0 > 0.) ? -_segExtent : min(max(-_segExtent, -_b1), _segExtent);
                    _sqrDist = -_s0 * _s0 + _s1 * (_s1 + 2. * _b1) + _c;
                }
                else if (_s1 <= _extDet)
                {

                    // region 3

                    _s0 = 0.;
                    _s1 = min(max(-_segExtent, -_b1), _segExtent);
                    _sqrDist = _s1 * (_s1 + 2. * _b1) + _c;
                }
                else
                {

                    // region 2

                    _s0 = max(0., -(_a01 * _segExtent + _b0));
                    _s1 = (_s0 > 0.) ? _segExtent : min(max(-_segExtent, -_b1), _segExtent);
                    _sqrDist = -_s0 * _s0 + _s1 * (_s1 + 2. * _b1) + _c;
                }
            }
        }
        else
        {

            // Ray and segment are parallel.

            _s1 = (_a01 > 0.) ? -_segExtent : _segExtent;
            _s0 = max(0., -(_a01 * _s1 + _b0));
            _sqrDist = -_s0 * _s0 + _s1 * (_s1 + 2. * _b1) + _c;
        }
        if (nullptr != optionalPointOnRaySPtr)
        {
            *optionalPointOnRaySPtr = At(_s0);
        }
        if (nullptr != optionalPointOnSegmentSPtr)
        {
            *optionalPointOnSegmentSPtr = At(_s1);
        }

        return _sqrDist;
    }

    inline shared_ptr<const Vector3> Ray::Intersect(const Sphere &sphere) const
    {
        const Vector3 _vec(sphere.Center() - mOrigin);
        const double _tca = _vec.Dot(mDirection);
        const double _d2 = _vec.Dot(_vec) - _tca * _tca;
        const double _radius2 = sphere.Radius() * sphere.Radius();

        if (_d2 > _radius2)
            return nullptr;

        const double _thc = sqrt(_radius2 - _d2);

        // t0 = first intersect point - entrance on front of sphere
        const double _t0 = _tca - _thc;

        // t1 = second intersect point - exit point on back of sphere
        const double _t1 = _tca + _thc;

        // test to see if both t0 and t1 are behind the ray - if so, return null
        if (_t0 < 0. && _t1 < 0.)
            return nullptr;

        // test to see if t0 is behind the ray:
        // if it is, the ray is inside the sphere, so return the second exit point scaled by t1,
        // in order to always return an intersect point that is in front of the ray.
        if (_t0 < 0.)
            return make_shared<Vector3>(At(_t1));

        // else t0 is in front of the ray, so return the first collision point scaled by t0
        return make_shared<Vector3>(At(_t0));
    }

    inline bool Ray::Intersects(const Sphere &sphere) const
    {
        return DistanceSqTo(sphere.Center()) <= sphere.Radius() * sphere.Radius();
    }

    inline double Ray::DistanceTo(const Plane &plane) const
    {
        const double _denomonator = plane.Normal().Dot(mDirection);
        if (_denomonator == 0.)
        {
            if (plane.DistanceTo(mOrigin) == 0.)
            {
                return 0.;
            }

            return -1;
        }

        return -(mOrigin.Dot(plane.Normal()) + plane.Constant()) / _denomonator;
    }

    inline shared_ptr<const Vector3> Ray::Intersect(const Plane &plane) const
    {
        const double _t = DistanceTo(plane);
        if (_t < 0.)
        {
            return nullptr;
        }
        else
        {
            return make_shared<Vector3>(At(_t));
        }
    }

    inline bool Ray::Intersects(const Plane &plane) const
    {
        // check if the ray lies on the plane first

        const double _distToPoint = plane.DistanceTo(mOrigin);

        if (_distToPoint == 0.)
        {
            return true;
        }

        const double _denominator = plane.Normal().Dot(mDirection);

        if (_denominator * _distToPoint < 0.)
        {
            return true;
        }

        // ray origin is behind the plane (and is pointing behind it)

        return false;
    }

    inline shared_ptr<const Vector3> Ray::Intersect(const Box3 &box) const
    {
        double _tmin = 0., _tmax = 0., _tymin = 0., _tymax = 0., _tzmin = 0., _tzmax = 0.;

        const double invdirx = 1 / mDirection.X(),
                     invdiry = 1 / mDirection.Y(),
                     invdirz = 1 / mDirection.Z();

        if (invdirx >= 0)
        {

            _tmin = (box.Min().X() - mOrigin.X()) * invdirx;
            _tmax = (box.Max().X() - mOrigin.X()) * invdirx;
        }
        else
        {

            _tmin = (box.Max().X() - mOrigin.X()) * invdirx;
            _tmax = (box.Min().X() - mOrigin.X()) * invdirx;
        }

        if (invdiry >= 0)
        {

            _tymin = (box.Min().Y() - mOrigin.Y()) * invdiry;
            _tymax = (box.Max().Y() - mOrigin.Y()) * invdiry;
        }
        else
        {

            _tymin = (box.Max().Y() - mOrigin.Y()) * invdiry;
            _tymax = (box.Min().Y() - mOrigin.Y()) * invdiry;
        }

        if ((_tmin > _tymax) || (_tymin > _tmax))
            return nullptr;

        // These lines also handle the case where _tmin or _tmax is NaN
        // (result of 0 * Infinity). x !== x returns true if x is NaN

        if (_tymin > _tmin || _tmin != _tmin)
            _tmin = _tymin;

        if (_tymax < _tmax || _tmax != _tmax)
            _tmax = _tymax;

        if (invdirz >= 0)
        {

            _tzmin = (box.Min().Z() - mOrigin.Z()) * invdirz;
            _tzmax = (box.Max().Z() - mOrigin.Z()) * invdirz;
        }
        else
        {

            _tzmin = (box.Max().Z() - mOrigin.Z()) * invdirz;
            _tzmax = (box.Min().Z() - mOrigin.Z()) * invdirz;
        }

        if ((_tmin > _tzmax) || (_tzmin > _tmax))
            return nullptr;

        if (_tzmin > _tmin || _tmin != _tmin)
            _tmin = _tzmin;

        if (_tzmax < _tmax || _tmax != _tmax)
            _tmax = _tzmax;

        //return point closest to the ray (positive side)

        if (_tmax < 0)
            return nullptr;

        return make_shared<Vector3>(At(_tmin >= 0 ? _tmin : _tmax));
    }

    inline bool Ray::Intersects(const Box3 &box) const
    {
        return nullptr == Intersect(box);
    }

    inline shared_ptr<const Vector3> Ray::Intersect(const Vector3 &a,
                                                          const Vector3 &b,
                                                          const Vector3 &c,
                                                          bool backfaceCulling) const
    {
        // Compute the offset origin, edges, and normal.

        // from http://www.geometrictools.com/GTEngine/Include/Mathematics/GteIntrRay3Triangle3.h

        const Vector3 _edge1 = b - a;
        const Vector3 _edge2 = c - a;
        const Vector3 _normal = _edge1.Crossed(_edge2);

        // Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
        // E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
        //   |Dot(D,N)|*b1 = _sign(Dot(D,N))*Dot(D,Cross(Q,E2))
        //   |Dot(D,N)|*b2 = _sign(Dot(D,N))*Dot(D,Cross(E1,Q))
        //   |Dot(D,N)|*t = -_sign(Dot(D,N))*Dot(Q,N)
        double _DdN = mDirection.Dot(_normal);
        double _sign = 0.;

        if (_DdN > 0)
        {

            if (backfaceCulling)
                return nullptr;
            _sign = 1;
        }
        else if (_DdN < 0)
        {

            _sign = -1;
            _DdN = -_DdN;
        }
        else
        {

            return nullptr;
        }

        const Vector3 _diff = mOrigin - a;
        const double _DdQxE2 = _sign * mDirection.Dot(_diff.Crossed(_edge2));

        // b1 < 0, no intersection
        if (_DdQxE2 < 0)
        {

            return nullptr;
        }

        const double _DdE1xQ = _sign * mDirection.Dot(_edge1.Crossed(_diff));

        // b2 < 0, no intersection
        if (_DdE1xQ < 0)
        {

            return nullptr;
        }

        // b1+b2 > 1, no intersection
        if (_DdQxE2 + _DdE1xQ > _DdN)
        {

            return nullptr;
        }

        // Line intersects triangle, check if ray does.
        const double _QdN = -_sign * _diff.Dot(_normal);

        // t < 0, no intersection
        if (_QdN < 0)
        {

            return nullptr;
        }

        // Ray intersects triangle.
        return make_shared<Vector3>(At(_QdN / _DdN));
    }

    inline shared_ptr<const Vector3> Ray::Intersect(const Triangle &triangle,
                                                          bool backfaceCulling) const
    {
        return Intersect(triangle.A(), triangle.B(), triangle.C(), backfaceCulling);
    }

    inline void Ray::operator*=(const Matrix4 &matrix)
    {
        mOrigin.Apply(matrix);
        mDirection.TransformDirection(matrix);
    }

    inline Ray Ray::operator*(const Matrix4 &matrix) const
    {
        Ray _ray(*this);
        _ray *= matrix;
        return _ray;
    }

    inline bool Ray::Equals(const Ray &ray, uint32_t ulp) const
    {
        return mOrigin.Equals(ray.mOrigin, ulp) &&
               mDirection.Equals(ray.mDirection, ulp);
    }

    inline bool Ray::operator==(const Ray &ray) const
    {
        return Equals(ray);
    }

    inline ostream &operator<<(ostream &os, const Ray &ray)
    {
        os << "{type:'Ray',origin:" << ray.Origin()
           << ",direction:" << ray.Direction() << "}";
        return os;
    }

} // namespace Three::Math
