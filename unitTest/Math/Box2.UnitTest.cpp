#include <CppUnitTest.h>
#include <sstream>

#include "../../src/Math/Box2.h"
#include "../TestConstants.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Three;

namespace ThreeUnitTest
{
	TEST_CLASS(Box2UnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Box2 _box2;
			Assert::IsTrue(_box2.Max() == negInf2, L"Instancing");
			Assert::IsTrue(_box2.Min() == posInf2, L"Instancing");

			Box2 _box21(zero2, zero2);
			Assert::IsTrue(_box21.Max() == zero2, L"Instancing");
			Assert::IsTrue(_box21.Min() == zero2, L"Instancing");

			Box2 _box22(zero2, one2);
			Assert::IsTrue(_box22.Max() == one2, L"Instancing");
			Assert::IsTrue(_box22.Min() == zero2, L"Instancing");
		}
		TEST_METHOD(Set)
		{
			Box2 _box;
			_box.Set(zero2, one2);
			Assert::IsTrue(_box.Max() == one2, L"Set");
			Assert::IsTrue(_box.Min() == zero2, L"Set");
		}
		TEST_METHOD(SetMax)
		{
			Box2 _box;
			_box.SetMax(one2);
			Assert::IsTrue(_box.Max() == one2, L"SetMax");
			Assert::IsTrue(_box.Min() == posInf2, L"SetMax");
		}
		TEST_METHOD(SetMin)
		{
			Box2 _box;
			_box.SetMin(one2);
			Assert::IsTrue(_box.Max() == negInf2, L"SetMax");
			Assert::IsTrue(_box.Min() == one2, L"SetMax");
		}
		TEST_METHOD(SetFromPoints)
		{
			Box2 _box;
			vector<Vector2> _points;
			_points.emplace_back(zero2);
			_points.emplace_back(one2);
			_points.emplace_back(two2);
			_box.SetFromPoints(_points);
			Assert::IsTrue(_box.Max() == two2, L"SetFromPoints");
			Assert::IsTrue(_box.Min() == zero2, L"SetFromPoints");

			_points.clear();
			_box.MakeEmpty();
			_points.emplace_back(one2);
			_box.SetFromPoints(_points);
			Assert::IsTrue(_box.Max() == one2, L"SetFromPoints");
			Assert::IsTrue(_box.Min() == one2, L"SetFromPoints");

			_points.clear();
			_box.MakeEmpty();
			_box.SetFromPoints(_points);
			Assert::IsTrue(_box.IsEmpty(), L"SetFromPoints");
		}
		TEST_METHOD(SetFromCenterAndSize)
		{
			Box2 _box;
			_box.SetFromCenterAndSize(zero2, two2);
			Assert::IsTrue(_box.Max() == one2, L"SetFromCenterAndSize");
			Assert::IsTrue(_box.Min() == negOne2, L"SetFromCenterAndSize");

			_box.SetFromCenterAndSize(one2, two2);
			Assert::IsTrue(_box.Max() == two2, L"SetFromCenterAndSize");
			Assert::IsTrue(_box.Min() == zero2, L"SetFromCenterAndSize");

			_box.SetFromCenterAndSize(zero2, zero2);
			Assert::IsTrue(_box.Max() == zero2, L"SetFromCenterAndSize");
			Assert::IsTrue(_box.Min() == zero2, L"SetFromCenterAndSize");
		}
		TEST_METHOD(Empty)
		{
			Box2 _box;
			Assert::IsTrue(_box.IsEmpty(), L"Empty");
			_box.Set(one2, two2);
			Assert::IsTrue(!_box.IsEmpty(), L"Empty");
			_box.MakeEmpty();
			Assert::IsTrue(_box.IsEmpty(), L"Empty");
		}
		TEST_METHOD(GetCenter)
		{
			Box2 _box(zero2, zero2);
			Assert::IsTrue(_box.GetCenter() == zero2, L"GetCenter");

			_box.Set(zero2, one2);
			Assert::IsTrue(_box.GetCenter() == one2 / 2., L"GetCenter");
		}
		TEST_METHOD(GetSize)
		{
			Box2 _box(zero2, zero2);
			Assert::IsTrue(_box.GetSize() == zero2, L"GetSize");

			_box.Set(zero2, one2);
			Assert::IsTrue(_box.GetSize() == one2, L"GetSize");

			_box.MakeEmpty();
			Assert::IsTrue(_box.GetSize() == zero2, L"GetSize");
		}
		TEST_METHOD(ExpandByPoint)
		{
			Box2 _box(zero2, zero2);
			_box.ExpandByPoint(zero2);
			Assert::IsTrue(_box.GetSize() == zero2, L"ExpandByPoint");
			_box.ExpandByPoint(one2);
			Assert::IsTrue(_box.GetSize() == one2, L"ExpandByPoint");
			_box.ExpandByPoint(negOne2);
			Assert::IsTrue(_box.GetSize() == two2, L"ExpandByPoint");
			Assert::IsTrue(_box.GetCenter() == zero2, L"ExpandByPoint");
		}
		TEST_METHOD(ExpandByVector)
		{
			Box2 _box(zero2, zero2);
			_box.ExpandByVector(zero2);
			Assert::IsTrue(_box.GetSize() == zero2, L"ExpandByVector");

			_box.ExpandByVector(one2);
			Assert::IsTrue(_box.GetSize() == two2, L"ExpandByVector");
			Assert::IsTrue(_box.GetCenter() == zero2, L"ExpandByVector");
		}
		TEST_METHOD(ExpandByScalar)
		{
			Box2 _box(zero2, zero2);
			_box.ExpandByScalar(0.);
			Assert::IsTrue(_box.GetSize() == zero2, L"ExpandByScalar");

			_box.ExpandByScalar(1.);
			Assert::IsTrue(_box.GetSize() == two2, L"ExpandByScalar");
			Assert::IsTrue(_box.GetCenter() == zero2, L"ExpandByScalar");
		}
		TEST_METHOD(ContainsPoint)
		{
			Box2 _box(zero2, zero2);
			Assert::IsTrue(_box.ContainsPoint(zero2), L"ContainsPoint");
			Assert::IsTrue(!_box.ContainsPoint(one2), L"ContainsPoint");

			_box.ExpandByScalar(1.);
			Assert::IsTrue(_box.ContainsPoint(zero2), L"ContainsPoint");
			Assert::IsTrue(_box.ContainsPoint(one2), L"ContainsPoint");
			Assert::IsTrue(_box.ContainsPoint(-one2), L"ContainsPoint");
			Assert::IsTrue(!_box.ContainsPoint(two2), L"ContainsPoint");
		}
		TEST_METHOD(ContainsBox)
		{
			Box2 _box(zero2, zero2);
			Box2 _box1(zero2, one2);
			Box2 _box2(-one2, one2);

			Assert::IsTrue(_box.ContainsBox(_box), L"ContainsBox");
			Assert::IsTrue(!_box.ContainsBox(_box1), L"ContainsBox");
			Assert::IsTrue(!_box.ContainsBox(_box2), L"ContainsBox");

			Assert::IsTrue(_box1.ContainsBox(_box), L"ContainsBox");
			Assert::IsTrue(_box2.ContainsBox(_box), L"ContainsBox");
			Assert::IsTrue(!_box1.ContainsBox(_box2), L"ContainsBox");
		}
		TEST_METHOD(GetParameter)
		{
			Box2 _box(zero2, one2);
			Box2 _box1(-one2, one2);

			Assert::IsTrue(_box.GetParameter(zero2) == zero2, L"GetParameter");
			Assert::IsTrue(_box.GetParameter(one2) == one2, L"GetParameter");

			Assert::IsTrue(_box1.GetParameter(-one2) == zero2, L"GetParameter");
			Assert::IsTrue(_box1.GetParameter(zero2) == one2 / 2., L"GetParameter");
			Assert::IsTrue(_box1.GetParameter(one2) == one2, L"GetParameter");
		}
		TEST_METHOD(IntersetcsBox)
		{
			Box2 _box(zero2, zero2);
			Box2 _box1(zero2, one2);
			Box2 _box2(-one2, one2);

			Assert::IsTrue(_box.IntersectsBox(_box), L"IntersetcsBox");
			Assert::IsTrue(_box.IntersectsBox(_box1), L"IntersetcsBox");
			Assert::IsTrue(_box.IntersectsBox(_box2), L"IntersetcsBox");

			Assert::IsTrue(_box1.IntersectsBox(_box), L"IntersetcsBox");
			Assert::IsTrue(_box1.IntersectsBox(_box2), L"IntersetcsBox");
			Assert::IsTrue(_box2.IntersectsBox(_box), L"IntersetcsBox");

			_box1.Translate(two2);
			Assert::IsTrue(!_box.IntersectsBox(_box1), L"IntersetcsBox");
			Assert::IsTrue(!_box1.IntersectsBox(_box), L"IntersetcsBox");
			Assert::IsTrue(!_box1.IntersectsBox(_box2), L"IntersetcsBox");
		}
		TEST_METHOD(ClampPoint)
		{
			Box2 _box(zero2, zero2);
			Box2 _box1(-one2, one2);

			Assert::IsTrue(_box.ClampPoint(zero2) == zero2, L"ClampPoint");
			Assert::IsTrue(_box.ClampPoint(one2) == zero2, L"ClampPoint");
			Assert::IsTrue(_box.ClampPoint(-one2) == zero2, L"ClampPoint");

			Assert::IsTrue(_box1.ClampPoint(two2) == one2, L"ClampPoint");
			Assert::IsTrue(_box1.ClampPoint(one2) == one2, L"ClampPoint");
			Assert::IsTrue(_box1.ClampPoint(zero2) == zero2, L"ClampPoint");
			Assert::IsTrue(_box1.ClampPoint(-one2) == -one2, L"ClampPoint");
			Assert::IsTrue(_box1.ClampPoint(-two2) == -one2, L"ClampPoint");
		}
		TEST_METHOD(DistanceToPoint)
		{
			Box2 _box(zero2, zero2);
			Box2 _box1(-one2, one2);

			AssetAlmosetEqules(_box.DistanceToPoint(zero2), 0, L"DistanceToPoint");
			AssetAlmosetEqules(_box.DistanceToPoint(one2), sqrt(2.), L"DistanceToPoint");
			AssetAlmosetEqules(_box.DistanceToPoint(-one2), sqrt(2.), L"DistanceToPoint");

			AssetAlmosetEqules(_box1.DistanceToPoint(two2), sqrt(2.), L"DistanceToPoint");
			AssetAlmosetEqules(_box1.DistanceToPoint(one2), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_box1.DistanceToPoint(zero2), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_box1.DistanceToPoint(-one2), 0., L"DistanceToPoint");
			AssetAlmosetEqules(_box1.DistanceToPoint(-two2), sqrt(2.), L"DistanceToPoint");
		}
		TEST_METHOD(Intersect)
		{
			Box2 _box(zero2, zero2);
			Box2 _box1(zero2, one2);
			Box2 _box2(-one2, one2);

			Assert::IsTrue((_box & _box) == _box, L"Intersected");
			Assert::IsTrue((_box & _box1) == _box, L"Intersected");
			Assert::IsTrue((_box1 & _box1) == _box1, L"Intersected");
			Assert::IsTrue((_box & _box2) == _box, L"Intersected");
			Assert::IsTrue((_box1 & _box2) == _box1, L"Intersected");
			Assert::IsTrue((_box2 & _box2) == _box2, L"Intersected");
			_box &= _box1;
			Assert::IsTrue(_box == Box2(zero2, zero2), L"Intersect");
			_box1 &= _box2;
			Assert::IsTrue(_box1 == Box2(zero2, one2), L"Intersect");
		}

		TEST_METHOD(Union)
		{
			Box2 _box(zero2, zero2);
			Box2 _box1(zero2, one2);
			Box2 _box2(-one2, one2);

			Assert::IsTrue((_box | _box) == _box, L"Unioned");
			Assert::IsTrue((_box | _box1) == _box1, L"Unioned");
			Assert::IsTrue((_box | _box2) == _box2, L"Unioned");
			Assert::IsTrue((_box1 | _box2) == _box2, L"Unioned");
			_box |= _box1;
			Assert::IsTrue(_box == _box1, L"Union");
			_box1 |= _box2;
			Assert::IsTrue(_box1 == _box2, L"Union");
		}
		TEST_METHOD(Equals)
		{
			Box2 _box;
			Box2 _box1;

			Assert::IsTrue(_box == _box1, L"Equals");
			Assert::IsTrue(_box1 == _box, L"Equals");
			_box1.ExpandByScalar(FLT_EPSILON);
			Assert::IsTrue(_box == _box1, L"Equals");
			_box1.ExpandByScalar(-2. * FLT_EPSILON);
			Assert::IsTrue(_box == _box1, L"Equals");
		}
		TEST_METHOD(ToJson)
		{
			Box2 _box(Vector2(1., 2.), Vector2(3., 4.));
			stringstream _ss;
			_ss << _box;
			Assert::IsTrue(_ss.str() == "{type:'Box2',min:{type:'Vector2',x:1,y:2},max:{type:'Vector2',x:3,y:4}}", L"ToJson");
		}
	};
}