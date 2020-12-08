#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Triangle.h"

namespace ThreeUnitTest
{
    using namespace Three;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace std;
    TEST_CLASS(TriangleUnitTest)
    {
        TEST_METHOD(Instancing)
        {
            Triangle _a;
            Triangle _b(one3, one3, two3);
            Assert::IsTrue(_a.A() == zero3);
            Assert::IsTrue(_a.B() == zero3);
            Assert::IsTrue(_a.C() == zero3);
            Assert::IsTrue(_b.A() == one3);
            Assert::IsTrue(_b.B() == one3);
            Assert::IsTrue(_b.C() == two3);
        }
        TEST_METHOD(Set)
        {
            Triangle _a;
            _a.Set(-one3, one3, two3);
            Assert::IsTrue(_a.A().Equals(-one3));
            Assert::IsTrue(_a.B().Equals(one3));
            Assert::IsTrue(_a.C().Equals(two3));
        }
        TEST_METHOD(SetFromPointsAndIndices)
        {
            Vector3 _data[] = {
                one3,
                -one3,
                two3
            };

            vector<Vector3> _points(3);
            memcpy(_points.data(), _data, 3 * sizeof(Vector3));

            Triangle _a;
            _a.SetFromPointAndIndices(_points, 1 , 0, 2);
            Assert::IsTrue(_a.A().Equals(-one3));
            Assert::IsTrue(_a.B().Equals(one3));
            Assert::IsTrue(_a.C().Equals(two3));
        }
        TEST_METHOD(GetArea)
        {
            Triangle _a;
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.GetArea(), 0));
            _a.Set(zero3, Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.GetArea(), 0.5));
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 2));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.GetArea(), 2));
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(3, 0, 0));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.GetArea(), 0));
        }
        TEST_METHOD(GetMidpoint)
        {
            Triangle _a;
            Assert::IsTrue(_a.GetMidpoint() == Vector3());
            _a.Set(zero3, Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(_a.GetMidpoint() == Vector3(1. / 3., 1. / 3., 0.));
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 2));
            Assert::IsTrue(_a.GetMidpoint() == Vector3(2. / 3., 0., 2. / 3.));
        }
        TEST_METHOD(GetNormal)
        {
            Triangle _a;
            Assert::IsTrue(_a.GetMidpoint() == Vector3());
            _a.Set(zero3, Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(_a.GetNormal() == Vector3(0., 0., 1.));
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 2));
            Assert::IsTrue(_a.GetNormal() == Vector3(0., 1., 0.));
        }
        TEST_METHOD(GetPlane)
        {
            Triangle _a;
            Plane _p = _a.GetPlane();
            Assert::IsTrue(_p.DistanceTo(_a.A()) == 0.);
            Assert::IsTrue(_p.DistanceTo(_a.B()) == 0.);
            Assert::IsTrue(_p.DistanceTo(_a.C()) == 0.);
            _a.Set(zero3, Vector3(1, 0, 0), Vector3(0, 1, 0));
            _p = _a.GetPlane();
            Assert::IsTrue(MathUtil::AlmosetEquals(_p.DistanceTo(_a.A()), 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_p.DistanceTo(_a.B()), 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_p.DistanceTo(_a.C()), 0.));
            Assert::IsTrue(_p.Normal() == _a.GetNormal());
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 2));
            _p = _a.GetPlane();
            Assert::IsTrue(MathUtil::AlmosetEquals(_p.DistanceTo(_a.A()), 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_p.DistanceTo(_a.B()), 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_p.DistanceTo(_a.C()), 0.));
            Assert::IsTrue(_p.Normal() == _a.GetNormal());
        }
        TEST_METHOD(GetBarycoord)
        {
            Triangle _a;
            Assert::IsTrue(_a.GetBarycoord(_a.A()) == Vector3(-2, -1, -1));
            Assert::IsTrue(_a.GetBarycoord(_a.B()) == Vector3(-2, -1, -1));
            Assert::IsTrue(_a.GetBarycoord(_a.C()) == Vector3(-2, -1, -1));
            _a.Set(zero3, Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(_a.GetBarycoord(_a.A()) == Vector3(1, 0, 0));
            Assert::IsTrue(_a.GetBarycoord(_a.B()) == Vector3(0, 1, 0));
            Assert::IsTrue(_a.GetBarycoord(_a.C()) == Vector3(0, 0, 1));
            Assert::IsTrue(_a.GetBarycoord(_a.GetMidpoint()) == Vector3(1. / 3., 1. / 3., 1. / 3.));
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 2));
            Assert::IsTrue(_a.GetBarycoord(_a.A()) == Vector3(1, 0, 0));
            Assert::IsTrue(_a.GetBarycoord(_a.B()) == Vector3(0, 1, 0));
            Assert::IsTrue(_a.GetBarycoord(_a.C()) == Vector3(0, 0, 1));
            Assert::IsTrue(_a.GetBarycoord(_a.GetMidpoint()) == Vector3(1. / 3., 1. / 3., 1. / 3.));
        }
        TEST_METHOD(ContainsPoint)
        {
            Triangle _a;
            Assert::IsTrue(!_a.ContainPoint(_a.A()));
            Assert::IsTrue(!_a.ContainPoint(_a.B()));
            Assert::IsTrue(!_a.ContainPoint(_a.C()));
            _a.Set(zero3, Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(_a.ContainPoint(_a.A()));
            Assert::IsTrue(_a.ContainPoint(_a.B()));
            Assert::IsTrue(_a.ContainPoint(_a.C()));
            Assert::IsTrue(_a.ContainPoint(_a.GetMidpoint()));
            Assert::IsTrue(!_a.ContainPoint(Vector3(-1, -1, -1)));
            _a.Set(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 2));
            Assert::IsTrue(_a.ContainPoint(_a.A()));
            Assert::IsTrue(_a.ContainPoint(_a.B()));
            Assert::IsTrue(_a.ContainPoint(_a.C()));
            Assert::IsTrue(_a.ContainPoint(_a.GetMidpoint()));
            Assert::IsTrue(!_a.ContainPoint(Vector3(-1, -1, -1)));
        }
        TEST_METHOD(IntersectsBox)
        {
            Box3 _a(one3, two3);
            auto _b = Triangle(Vector3(1.5, 1.5, 2.5), Vector3(2.5, 1.5, 1.5), Vector3(1.5, 2.5, 1.5));
            auto _c = Triangle(Vector3(1.5, 1.5, 3.5), Vector3(3.5, 1.5, 1.5), Vector3(1.5, 1.5, 1.5));
            auto _d = Triangle(Vector3(1.5, 1.75, 3), Vector3(3, 1.75, 1.5), Vector3(1.5, 2.5, 1.5));
            auto _e = Triangle(Vector3(1.5, 1.8, 3), Vector3(3, 1.8, 1.5), Vector3(1.5, 2.5, 1.5));
            auto _f = Triangle(Vector3(1.5, 2.5, 3), Vector3(3, 2.5, 1.5), Vector3(1.5, 2.5, 1.5));

            Assert::IsTrue(_b.Intersects(_a));
            Assert::IsTrue(_c.Intersects(_a));
            Assert::IsTrue(_d.Intersects(_a));
            Assert::IsTrue(!_e.Intersects(_a));
            Assert::IsTrue(!_f.Intersects(_a));
        }
        TEST_METHOD(ClosestPointToPoint)
        {
            Triangle _a(Vector3(-1, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(_a.ClosesPointToPoint(Vector3(0, 0.5, 0)) == Vector3(0, 0.5, 0));
            Assert::IsTrue(_a.ClosesPointToPoint(_a.A()) == _a.A());
            Assert::IsTrue(_a.ClosesPointToPoint(_a.B()) == _a.B());
            Assert::IsTrue(_a.ClosesPointToPoint(_a.C()) == _a.C());
            Assert::IsTrue(_a.ClosesPointToPoint(zero3) == zero3);
            Assert::IsTrue(_a.ClosesPointToPoint(Vector3(-2, 0, 0)) == Vector3(-1, 0, 0));
            Assert::IsTrue(_a.ClosesPointToPoint(Vector3(2, 0, 0)) == Vector3(1, 0, 0));
            Assert::IsTrue(_a.ClosesPointToPoint(Vector3(0, 2, 0)) == Vector3(0, 1, 0));
            Assert::IsTrue(_a.ClosesPointToPoint(Vector3(0, -2, 0)) == Vector3(0, 0, 0));
        }
        TEST_METHOD(IsFrontFacing)
        {
            Triangle _a;
            Assert::IsTrue(!_a.IsFrontFacing(Vector3()));
            _a.Set(Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0));
            Assert::IsTrue(_a.IsFrontFacing(Vector3(0, 0, -1)));
            _a.Set(Vector3(0, 0, 0), Vector3(0, 1, 0), Vector3(1, 10, 0));
            Assert::IsTrue(!_a.IsFrontFacing(Vector3(0, 0, -1)));
        }
        TEST_METHOD(ToJson)
        {
            stringstream _ss;
            _ss << Triangle();
            Assert::IsTrue(_ss.str() == "{type:'Triangle',a:{type:'Vector3',x:0,y:0,z:0},b:{type:'Vector3',x:0,y:0,z:0},c:{type:'Vector3',x:0,y:0,z:0}}");
        }
    };
}