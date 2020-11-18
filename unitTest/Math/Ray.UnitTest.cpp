#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Ray.h"

namespace ThreeUnitTest
{
    using namespace Three::Math;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace std;
    TEST_CLASS(RayUnitTest)
    {
        TEST_METHOD(Instancing)
        {
            Ray _a, _b(two3, one3);
            Assert::IsTrue(_a.Origin() == zero3);
            Assert::IsTrue(_a.Direction() == Vector3(0, 0, 1));
            Assert::IsTrue(_b.Origin() == two3);
            Assert::IsTrue(_a.Direction() == one3);
        }
        TEST_METHOD(Set)
        {
            Ray _a;
            _a.Set(one3, one3);
            Assert::IsTrue(_a.Origin() == one3);
            Assert::IsTrue(_a.Direction() == one3);
        }
        TEST_METHOD(Recast)
        {
            Ray _a(one3, Vector3(0, 0, 1));
            Assert::IsTrue(_a.Recasted(0) == _a);
            Assert::IsTrue(_a.Recasted(-1.) == Ray(Vector3(1., 1., 0.), Vector3(0., 0., 1.)));
            Assert::IsTrue(_a.Recasted(1) == Ray(Vector3(1., 1., 2.), Vector3(0., 0., 1.)));
        }
        TEST_METHOD(Equals)
        {
            Ray _a(zero3, one3);
            Ray _b(zero3 + Vector3(FLT_EPSILON), one3 - Vector3(FLT_EPSILON));
            Ray _c(zero3 + Vector3(2. * FLT_EPSILON), one3);
            Assert::IsTrue(_a == _b);
            Assert::IsFalse(_a == _c);
        }
        TEST_METHOD(At)
        {
            Ray _a(one3, Vector3::UINT_Z);
            Assert::IsTrue(_a.At(0) == one3);
            Assert::IsTrue(_a.At(-1) == Vector3(1, 1, 0));
            Assert::IsTrue(_a.At(1) == Vector3(1, 1, 2));
        }
        TEST_METHOD(lookAt)
        {
            Ray _a(two3, one3);
            auto _excepted = (one3 - two3).Normalized();
            _a.LookAt(_excepted);
            Assert::IsTrue(_a.Direction() == _excepted);
        }
        TEST_METHOD(ClosestPointToPoint)
        {
            Ray _a(one3, Vector3(0, 0, 1));
            Assert::IsTrue(_a.ClosestPointToPoint(zero3) == one3);
            Assert::IsTrue(_a.ClosestPointToPoint(Vector3(0, 0, 50)) == Vector3(1, 1, 50));
            Assert::IsTrue(_a.ClosestPointToPoint(one3) == one3);
        }
        TEST_METHOD(DistanceToPoint)
        {
            Ray _a(one3, Vector3::UINT_Z);
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceSqTo(zero3), 3.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceSqTo(Vector3(0, 0, 50)), 2));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceSqTo(one3), 0.));
        }
        TEST_METHOD(DistanceSqToSegment)
        {
            Ray _a(one3, Vector3(0, 0, 1));
            auto _ptOnLine = make_shared<Vector3>();
            auto _ptOnSegment = make_shared<Vector3>();
            Vector3 _v0(3, 5, 50), _v1(50, 50, 50);
            double _distSqr = _a.DistanceSqTo(_v0, _v1, _ptOnLine, _ptOnSegment);
            Assert::IsTrue(*_ptOnSegment == _v0);
            Assert::IsTrue(*_ptOnLine == Vector3(1, 1, 50));
            Assert::IsTrue(MathUtil::AlmosetEquals(_distSqr, 50.));

            _v0.Set(-50, -50, -50);
            _v1.Set(-3, -5, -4);

            _distSqr = _a.DistanceSqTo(_v0, _v1, _ptOnLine, _ptOnSegment);
            Assert::IsTrue(*_ptOnSegment == _v1);
            Assert::IsTrue(*_ptOnLine == one3);
            Assert::IsTrue(MathUtil::AlmosetEquals(_distSqr, 77.));

            _v0.Set(-50, -50, -50);
            _v1.Set(50, 50, 50);
            _distSqr = _a.DistanceSqTo(_v0, _v1, _ptOnLine, _ptOnSegment);
            Assert::IsTrue(*_ptOnSegment == one3);
            Assert::IsTrue(*_ptOnLine == one3);
            Assert::IsTrue(MathUtil::AlmosetEquals(_distSqr, 0.));
        }
        TEST_METHOD(IntersectSphere)
        {
            const double _eps = 0.0001;
            Ray _a0(zero3, Vector3(0, 0, -1));
            Ray _a1(one3, Vector3(-1, 0, 0));
            Sphere _b(Vector3(0, 0, 3), 2);
            Assert::IsTrue(_a0.Intersect(_b) == nullptr);
            _b.Set(Vector3(3, 0, -1), 2);
            Assert::IsTrue(_a0.Intersect(_b) == nullptr);
            _b.Set(Vector3(1, -2, 1), 2);
            Assert::IsTrue(_a1.Intersect(_b) == nullptr);
            _b.Set(Vector3(0, 0, -2), 1);
            Assert::IsTrue(_a0.Intersect(_b)->DistanceTo(Vector3(0, 0, -1)) < _eps);
            _b.Set(Vector3(-1, 1, 1), 1);
            Assert::IsTrue(_a1.Intersect(_b)->DistanceTo(Vector3(0, 1, 1)) < _eps);
            _b.Set(Vector3(2, 0, -1), 2);
            Assert::IsTrue(_a0.Intersect(_b)->DistanceTo(Vector3(0, 0, -1)) < _eps);
            _b.Set(Vector3(2.01, 0, -1), 2);
            Assert::IsTrue(_a0.Intersect(_b) == nullptr);
            _b.Set(zero3, 1);
            Assert::IsTrue(_a0.Intersect(_b)->DistanceTo(Vector3(0, 0, -1)) < _eps);
            _b.Set(Vector3(0, 0, 1), 4);
            Assert::IsTrue(_a0.Intersect(_b)->DistanceTo(Vector3(0, 0, -3)) < _eps);
            _b.Set(Vector3(0, 0, -1), 4);
            Assert::IsTrue(_a0.Intersect(_b)->DistanceTo(Vector3(0, 0, -5)) < _eps);
        }
    };
}