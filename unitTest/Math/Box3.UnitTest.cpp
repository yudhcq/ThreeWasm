#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Box3.h"
#include "../../src/Math/Matrix4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three;

namespace ThreeUnitTest
{
	TEST_CLASS(Box3UnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Box3 _box;
			Assert::IsTrue(_box.Max() == negInf3 && _box.Min() == posInf3, L"Instancing");

			_box = Box3(zero3, zero3);
			Assert::IsTrue(_box.Max() == zero3 && _box.Min() == zero3, L"Instancing");

			_box = Box3(zero3, one3);
			Assert::IsTrue(_box.Max() == one3 && _box.Min() == zero3, L"Instancing");
		}
		TEST_METHOD(Set)
		{
			Box3 _box;
			_box.Set(zero3, one3);
			Assert::IsTrue(_box.Max() == one3 && _box.Min() == zero3, L"Set");
		}
		TEST_METHOD(SetMax)
		{
			Box3 _box;
			_box.SetMax(one3);
			Assert::IsTrue(_box.Max() == one3 && _box.Min() == posInf3, L"SetMax");
		}
		TEST_METHOD(SetMin)
		{
			Box3 _box;
			_box.SetMin(one3);
			Assert::IsTrue(_box.Max()  == negInf3 && _box.Min() == one3, L"SetMin");
		}
		TEST_METHOD(SetFromPoints)
		{
			Box3 _box;
			_box.SetFromPoints(vector<Vector3>({ zero3, one3, two3 }));
			Assert::IsTrue(_box.Max() == two3, L"SetFromPoints");
			Assert::IsTrue(_box.Min() == zero3, L"SetFromPoints");
			_box.SetFromPoints(vector<Vector3>({ one3 }));
			Assert::IsTrue(_box.Max() == one3, L"SetFromPoints");
			Assert::IsTrue(_box.Min() == one3, L"SetFromPoints");
			_box.SetFromPoints(vector<Vector3>());
			Assert::IsTrue(_box.IsEmpty(), L"SetFromPoints");
		}
		TEST_METHOD(SetFromCenterAndSize)
		{
			Box3 _box(zero3, one3);
			Box3 _box1(_box);

			_box.SetFromCenterAndSize(_box.GetCenter(), _box.GetSize());

			Assert::IsTrue(_box == _box1, L"on change");
			_box.SetFromCenterAndSize(one3, one3);
			Assert::IsTrue(_box.GetCenter() == one3, L"change center");
			Assert::IsTrue(_box.GetSize() == _box1.GetSize(), L"just change center, so size is not change");
			Assert::IsTrue(!(_box == _box1), L"center is not equals");
			
			_box.SetFromCenterAndSize(zero3, two3);
			Assert::IsTrue(_box.GetCenter() == zero3, L"center no change");
			Assert::IsTrue(_box.GetSize() == two3, L"size");
		}
		TEST_METHOD(Empty)
		{
			Box3 _box;
			Assert::IsTrue(_box.IsEmpty(), L"Empty");
			_box.SetFromCenterAndSize(one3, one3);
			Assert::IsTrue(!_box.IsEmpty(), L"Empty");
			_box.MakeEmpty();
			Assert::IsTrue(_box.IsEmpty(), L"Empty");
		}
		TEST_METHOD(GetCenterGetSize)
		{
			Box3 _box(one3, two3);
			Assert::IsTrue(_box.GetCenter() == (one3 + two3) / 2., L"GetCenter");
			Assert::IsTrue(_box.GetSize() == two3 - one3, L"GetSize");
			_box.Set(zero3, two3);
			Assert::IsTrue(_box.GetCenter() == one3, L"GetCenter");
			Assert::IsTrue(_box.GetSize() == two3, L"GetSize");
		}
		TEST_METHOD(ExpandByPoint)
		{
			Box3 _box(zero3, zero3);
			_box.ExpandByPoint(zero3);
			Assert::IsTrue(_box.GetSize() == zero3, L"ExpandByPoint");
			_box.ExpandByPoint(one3);
			Assert::IsTrue(_box.GetSize() == one3, L"ExpandByPoint");
			_box.ExpandByPoint(-one3);
			Assert::IsTrue(_box.GetSize() == two3, L"ExpandByPoint");
			Assert::IsTrue(_box.GetCenter() == zero3, L"ExpandByPoint");
		}
		TEST_METHOD(ExpandByVector)
		{
			Box3 _box(zero3, zero3);
			_box.ExpandByVector(zero3);
			Assert::IsTrue(_box.GetSize() == zero3, L"ExpandByVector");
			_box.ExpandByVector(one3);
			Assert::IsTrue(_box.GetSize() == two3, L"ExpandByVector");
			Assert::IsTrue(_box.GetCenter() == zero3, L"ExpandByVector");
		}
		TEST_METHOD(ExpandByScalar)
		{
			Box3 _box(zero3, zero3);
			_box.ExpandByScalar(0.);
			Assert::IsTrue(_box.GetSize() == zero3, L"ExpandByScalar");
			_box.ExpandByScalar(1.);
			Assert::IsTrue(_box.GetSize() == two3, L"ExpandByScalar");
			Assert::IsTrue(_box.GetCenter() == zero3, L"ExpandByScalar");
		}
		TEST_METHOD(ContainsPoint)
		{
			Box3 _box(zero3, zero3);
			Assert::IsTrue(_box.ContainsPoint(zero3), L"ContainsPoint");
			Assert::IsTrue(!_box.ContainsPoint(one3), L"ContainsPoint");
			_box.ExpandByScalar(1.);
			Assert::IsTrue(_box.ContainsPoint(zero3), L"ContainsPoint");
			Assert::IsTrue(_box.ContainsPoint(one3), L"ContainsPoint");
			Assert::IsTrue(!_box.ContainsPoint(two3), L"ContainsPoint");
		}
		TEST_METHOD(ContainsBox)
		{
			Box3 _box(zero3, zero3);
			Box3 _box1(zero3, one3);
			Box3 _box2(-one3, one3);

			Assert::IsTrue(_box.ContainsBox(_box), L"ContainsBox");
			Assert::IsTrue(!_box.ContainsBox(_box1), L"ContainsBox");
			Assert::IsTrue(!_box.ContainsBox(_box2), L"ContainsBox");
			Assert::IsTrue(_box1.ContainsBox(_box), L"ContainsBox");
			Assert::IsTrue(_box2.ContainsBox(_box), L"ContainsBox");
			Assert::IsTrue(!_box1.ContainsBox(_box2), L"ContainsBox");
		}
		TEST_METHOD(GetParameter)
		{
			Box3 _box(zero3, one3);
			Box3 _box1(-one3, one3);

			Assert::IsTrue(_box.GetParamter(zero3) == zero3, L"GetParameter");
			Assert::IsTrue(_box.GetParamter(one3) == one3, L"GetParameter");
			Assert::IsTrue(_box1.GetParamter(-one3) == zero3, L"GetParameter");
			Assert::IsTrue(_box1.GetParamter(zero3) == one3 / 2., L"GetParameter");
			Assert::IsTrue(_box1.GetParamter(one3) == one3, L"GetParameter");
		}
		TEST_METHOD(IntersectsBox)
		{
			Box3 _a(zero3, zero3);
			Box3 _b(zero3, one3);
			Box3 _c(-one3, one3);

			Assert::IsTrue(_a.IntersectsBox(_b), L"IntersectsBox");
			Assert::IsTrue(_a.IntersectsBox(_c), L"IntersectsBox");
			Assert::IsTrue(_a.IntersectsBox(_b), L"IntersectsBox");
			Assert::IsTrue(_c.IntersectsBox(_b), L"IntersectsBox");
			Assert::IsTrue(_c.IntersectsBox(_a), L"IntersectsBox");
			Assert::IsTrue(_b.IntersectsBox(_c), L"IntersectsBox");

			_b.Translate(Vector3(2.));
			Assert::IsTrue(!_a.IntersectsBox(_b));
			Assert::IsTrue(!_b.IntersectsBox(_a));
			Assert::IsTrue(!_b.IntersectsBox(_c));
		}
		TEST_METHOD(IntersectsSphere)
		{
			Box3 _box(zero3, one3);
			Sphere _sphere(zero3, 1.);
			Assert::IsTrue(_box.IntersectsSphere(_sphere), L"IntersetcsSphere");
			_sphere.Translate(Vector3(2.));
			Assert::IsTrue(!_box.IntersectsSphere(_sphere), L"IntersetcsSphere");
		}
		TEST_METHOD(IntersectsPlane)
		{
			const auto _a = Box3(zero3, one3);
			const auto _b = Plane(Vector3(0, 1, 0), 1);
			const auto _c = Plane(Vector3(0, 1, 0), 1.25);
			const auto _d = Plane(Vector3(0, -1, 0), 1.25);
			const auto _e = Plane(Vector3(0, 1, 0), 0.25);
			const auto _f = Plane(Vector3(0, 1, 0), -0.25);
			const auto _g = Plane(Vector3(0, 1, 0), -0.75);
			const auto _h = Plane(Vector3(0, 1, 0), -1);
			const auto _i = Plane(Vector3(1. / sqrt(3.), 1. / sqrt(3.), 1. / sqrt(3.)), -1.732);
			const auto _j = Plane(Vector3(1. / sqrt(3.), 1. / sqrt(3.), 1. / sqrt(3.)), -1.733);
					   
			Assert::IsTrue(!_a.IntersectsPlane(_b), L"Passed!");
			Assert::IsTrue(!_a.IntersectsPlane(_c), L"Passed!");
			Assert::IsTrue(!_a.IntersectsPlane(_d), L"Passed!");
			Assert::IsTrue(!_a.IntersectsPlane(_e), L"Passed!");
			Assert::IsTrue(_a.IntersectsPlane(_f), L"Passed!");
			Assert::IsTrue(_a.IntersectsPlane(_g), L"Passed!");
			Assert::IsTrue(_a.IntersectsPlane(_h), L"Passed!");
			Assert::IsTrue(_a.IntersectsPlane(_i), L"Passed!");
			Assert::IsTrue(!_a.IntersectsPlane(_j), L"Passed!");
		}
		TEST_METHOD(IntersectsTriangle)
		{
			const auto _a = Box3(one3, two3);
			const auto _b = Triangle(Vector3(1.5, 1.5, 2.5), Vector3(2.5, 1.5, 1.5), Vector3(1.5, 2.5, 1.5));
			const auto _c = Triangle(Vector3(1.5, 1.5, 3.5), Vector3(3.5, 1.5, 1.5), Vector3(1.5, 1.5, 1.5));
			const auto _d = Triangle(Vector3(1.5, 1.75, 3), Vector3(3, 1.75, 1.5), Vector3(1.5, 2.5, 1.5));
			const auto _e = Triangle(Vector3(1.5, 1.8, 3), Vector3(3, 1.8, 1.5), Vector3(1.5, 2.5, 1.5));
			const auto _f = Triangle(Vector3(1.5, 2.5, 3), Vector3(3, 2.5, 1.5), Vector3(1.5, 2.5, 1.5));

			Assert::IsTrue(_a.IntersectsTriangle(_b), L"Passed!");
			Assert::IsTrue(_a.IntersectsTriangle(_c), L"Passed!");
			Assert::IsTrue(_a.IntersectsTriangle(_d), L"Passed!");
			Assert::IsTrue(!_a.IntersectsTriangle(_e), L"Passed!");
			Assert::IsTrue(!_a.IntersectsTriangle(_f), L"Passed!");
		}
		TEST_METHOD(ClampPoint)
		{
			Box3 _a(zero3, zero3);
			Box3 _b(-one3, one3);

			Assert::IsTrue(_a.ClampPoint(zero3) == zero3, L"ClampPoint");
			Assert::IsTrue(_a.ClampPoint(one3) == zero3, L"ClampPoint");
			Assert::IsTrue(_a.ClampPoint(-one3) == zero3, L"ClampPoint");
			Assert::IsTrue(_b.ClampPoint(two3) == one3, L"ClampPoint");
			Assert::IsTrue(_b.ClampPoint(one3) == one3, L"ClampPoint");
			Assert::IsTrue(_b.ClampPoint(zero3) == zero3, L"ClampPoint");
			Assert::IsTrue(_b.ClampPoint(-one3) == -one3, L"ClampPoint");
			Assert::IsTrue(_b.ClampPoint(-two3) == -one3, L"ClampPoint");
		}
		TEST_METHOD(DistanceToPoint)
		{
			Box3 _a(zero3, zero3);
			Box3 _b(-one3, one3);

			AssetAlmosetEqules(_a.DistanceToPoint(Vector3()), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_a.DistanceToPoint(Vector3(1.)), sqrt(3.), L"DistanceToPoint");
			AssetAlmosetEqules(_a.DistanceToPoint(Vector3(-1.)), sqrt(3.), L"DistanceToPoint");

			AssetAlmosetEqules(_b.DistanceToPoint(Vector3(2.)), sqrt(3.), L"DistanceToPoint");
			AssetAlmosetEqules(_b.DistanceToPoint(Vector3(1.)), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_b.DistanceToPoint(Vector3(0.)), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_b.DistanceToPoint(Vector3(-1.)), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_b.DistanceToPoint(Vector3(-2.)), sqrt(3.), L"DistanceToPoint");
		}
		TEST_METHOD(GetBoundingSphere)
		{
			Box3 _a(zero3, zero3);
			Box3 _b(zero3, one3);
			Box3 _c(-one3, one3);

			Assert::IsTrue(_a.GetBoundingSphere() == Sphere(zero3, 0.), L"GetBoundingSphere");
			Assert::IsTrue(_b.GetBoundingSphere() == Sphere(one3 / 2, sqrt(3.) / 2.), L"GetBoundingSphere");
			Assert::IsTrue(_c.GetBoundingSphere() == Sphere(zero3, sqrt(12.) / 2.), L"GetBoundingSphere");
		}
		TEST_METHOD(Intersect)
		{
			Box3 _a(zero3, zero3);
			Box3 _b(zero3, one3);
			Box3 _c(-one3, one3);

			Assert::IsTrue((_a & _b) == _a, L"Intersected");
			Assert::IsTrue((_b & _a) == _a, L"Intersected");
			Assert::IsTrue((_a & _c) == _a, L"Intersected");
			Assert::IsTrue((_c & _a) == _a, L"Intersected");
			Assert::IsTrue((_b & _c) == _b, L"Intersected");
			Assert::IsTrue((_c & _b) == _b, L"Intersected");

			_c &= _b;
			Assert::IsTrue(_c == _b, L"Intersect");
			_b &= _a;
			Assert::IsTrue(_b == _a, L"Intersect");
		}
		TEST_METHOD(Union)
		{
			Box3 _a(zero3, zero3);
			Box3 _b(zero3, one3);
			Box3 _c(-one3, one3);

			Assert::IsTrue((_a | _b) == _b, L"Unioned");
			Assert::IsTrue((_b | _a) == _b, L"Unioned");
			Assert::IsTrue((_a | _c) == _c, L"Unioned");
			Assert::IsTrue((_c | _a) == _c, L"Unioned");
			Assert::IsTrue((_b | _c) == _c, L"Unioned");
			Assert::IsTrue((_c | _b) == _c, L"Unioned");

			_a |= _b;
			Assert::IsTrue(_b == _a, L"Intersect");
			_b |= _c;
			Assert::IsTrue(_b == _c, L"Intersect");
		}
		TEST_METHOD(Apply)
		{
			const auto _a = Box3(zero3, zero3);
			const auto _b = Box3(zero3, one3);
			const auto _c = Box3(-one3, one3);
			const auto _d = Box3(-one3, zero3);

			Matrix4 _m;
			_m.MakeTranslation(1., - 2., 1.);
			Vector3 _t(1., - 2., 1.);

			Assert::IsTrue(_a * _m == _a.Translated(_t), L"ApplyMatrix");
			Assert::IsTrue(_b * _m == _b.Translated(_t), L"ApplyMatrix");
			Assert::IsTrue(_c * _m == _c.Translated(_t), L"ApplyMatrix");
			Assert::IsTrue(_d * _m == _d.Translated(_t), L"ApplyMatrix");
		}
		TEST_METHOD(Translate)
		{
			auto _a = Box3(zero3, zero3);
			auto _b = Box3(zero3, one3);
			auto _c = Box3(-one3, one3);
			auto _d = Box3(-one3, zero3);
			
			Assert::IsTrue(_a.Translated(one3) == Box3(one3, one3), L"Translated");
			Assert::IsTrue(_a.Translated(one3).Translated(-one3) == _a, L"Translated");
			Assert::IsTrue(_d.Translated(one3) == _b, L"Translated");
			Assert::IsTrue(_b.Translated(-one3) == _d, L"Translated");

			_a.Translate(one3);
			Assert::IsTrue(_a == Box3(one3, one3), L"Translate");
			_a.Translate(-one3);
			Assert::IsTrue(_a == Box3(zero3, zero3), L"Translate");
			_d.Translate(one3);
			Assert::IsTrue(_d == _b, L"Translate");
		}
		TEST_METHOD(Equals)
		{
			Box3 _box;

			Assert::IsTrue(_box == Box3(), L"==");
			_box.Set(zero3, zero3);
			Assert::IsTrue(_box == Box3(zero3 - FLT_EPSILON, zero3 + FLT_EPSILON), L"==");
		}
		TEST_METHOD(ToJson)
		{
			Box3 _box(Vector3(1., 2., 3.), Vector3(4., 5., 6.));
			stringstream _ss;
			_ss << _box;

			Assert::IsTrue(_ss.str() == "{type:'Box3',min:{type:'Vector3',x:1,y:2,z:3},max:{type:'Vector3',x:4,y:5,z:6}}", L"ToJson");
		}
	};
}