#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Sphere.h"

namespace ThreeUnitTest
{
    using namespace Three::Math;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace std;
    TEST_CLASS(SphereUnitTest)
    {
        TEST_METHOD(Instancing)
        {
            Sphere _a;
            Assert::IsTrue(_a.Center() == zero3);
            Assert::IsTrue(_a.Radius() == 0);

            Sphere _b(one3, 1.);
            Assert::IsTrue(_b.Center() == one3);
            Assert::IsTrue(_b.Radius() == 1);
        }
        TEST_METHOD(Set)
        {
            Sphere _a;
            _a.Set(one3, 1);
            Assert::IsTrue(_a.Center() == one3);
            Assert::IsTrue(_a.Radius() == 1);

            _a.SetCenter(zero3);
            _a.SetRadius(0.);
            Assert::IsTrue(_a.Center() == zero3);
            Assert::IsTrue(_a.Radius() == 0);
        }
        TEST_METHOD(SetFromPoints)
        {
            Sphere _a;
            Vector3 _data[] =
            {
                Vector3(1, 1, 0),
                Vector3(1, 1, 0),
                Vector3(1, 1, 0),
                Vector3(1, 1, 0),
                Vector3(1, 1, 0),
                Vector3(0.8660253882408142, 0.5, 0),
                Vector3(-0, 0.5, 0.8660253882408142), Vector3(1.8660253882408142, 0.5, 0),
                Vector3(0, 0.5, -0.8660253882408142), Vector3(0.8660253882408142, 0.5, -0),
                Vector3(0.8660253882408142, -0.5, 0), Vector3(-0, -0.5, 0.8660253882408142),
                Vector3(1.8660253882408142, -0.5, 0), Vector3(0, -0.5, -0.8660253882408142),
                Vector3(0.8660253882408142, -0.5, -0), Vector3(-0, -1, 0),
                Vector3(-0, -1, 0), Vector3(0, -1, 0),
                Vector3(0, -1, -0), Vector3(-0, -1, -0)
            };
            vector<Vector3> _points(20);
            memcpy(_points.data(), _data, 20 * sizeof(_data[0]));
            _a.SetFromPoints(_points);

            Assert::IsTrue(_a.Center() == Vector3(0.9330126941204071, 0, 0));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.Radius(), 1.3676668773461689));

            _a.SetFromPoints(_points, Vector3(1.));
            Assert::IsTrue(_a.Center() == Vector3(1.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.Radius(), 2.5946195770400102));
        }
        TEST_METHOD(Empty) 
        {
            Sphere _a;
            Assert::IsTrue(_a.Empty());
            _a.SetRadius(1.);
            Assert::IsTrue(!_a.Empty());
        }
        TEST_METHOD(ContainsPoint)
        {
            Sphere _a(zero3, 1.);
            Assert::IsTrue(_a.ContainsPoint(zero3));
            Assert::IsTrue(!_a.ContainsPoint(one3));
        }
        TEST_METHOD(DistanceToPoint)
        {
            Sphere _a(one3, 1);
            Assert::IsTrue(_a.DistanceTo(zero3) - 0.732 < 0.001);
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(one3), -1.));
        }
        TEST_METHOD(IntersectsSphere)
        {
            Sphere _a(one3, 1.);
            Sphere _b(zero3, 1);
            Sphere _c(zero3, 0.25);

            Assert::IsTrue(_a.Intersects(_b));
            Assert::IsFalse(_a.Intersects(_c));
        }
        TEST_METHOD(IntersectsBox)
        {
            Sphere _a;
            Sphere _b(Vector3(-5.), 0.);
            Box3 _box(zero3, one3);

            Assert::IsTrue(_a.Intersects(_box));
            Assert::IsFalse(_b.Intersects(_box));
        }
        TEST_METHOD(IntersectsPlane)
        {
            auto _a = Sphere(zero3, 1);
            auto _b = Plane(Vector3(0, 1, 0), 1);
            auto _c = Plane(Vector3(0, 1, 0), 1.25);
            auto _d = Plane(Vector3(0, -1, 0), 1.25);

            Assert::IsTrue(_a.Intersects(_b));
            Assert::IsTrue(!_a.Intersects(_c));
            Assert::IsTrue(!_a.Intersects(_d));
        }
        TEST_METHOD(ClampPoint)
        {
            Sphere _a(one3, 1.);
            Assert::IsTrue(_a.ClampPoint(Vector3(1, 1, 3)) == Vector3(1, 1, 2));
            Assert::IsTrue(_a.ClampPoint(Vector3(1, 1, -3)) == Vector3(1, 1, 0));
        }
        TEST_METHOD(GetBoundingBox)
        {
            Sphere _a(one3, 1.);
            Assert::IsTrue(_a.GetBoundingBox() == Box3(zero3, two3));
            _a.Set(zero3, 0.);
            Assert::IsTrue(_a.GetBoundingBox() == Box3(zero3, zero3));
        }
        TEST_METHOD(Translate)
        {
            Sphere _a(one3, 1.);
            Assert::IsTrue (_a.Translated(-one3).Center() == zero3);
        }
        TEST_METHOD(Equals)
        {
            Assert::IsTrue(Sphere() == Sphere(Vector3(DBL_EPSILON), DBL_EPSILON));
            Assert::IsFalse(Sphere() == Sphere(Vector3(FLT_EPSILON + DBL_EPSILON), DBL_EPSILON));
        }
        TEST_METHOD(ToJson)
        {
            stringstream _ss;
            Sphere _s;
            _ss << _s;
            Assert::IsTrue(_ss.str() == "{type:'Sphere',center:{type:'Vector3',x:0,y:0,z:0},radius:0}");
        }
    };
}