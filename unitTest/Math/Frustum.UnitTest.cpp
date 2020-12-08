#include <CppUnitTest.h>

#include "../TestConstants.h";
#include "../../src/Math/Frustum.h"
#include "../../src/Math/Vector3.h"
#include "../../src/Math/Matrix4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Three;

namespace ThreeUnitTest
{
	const Vector3 unit3(1., 0., 0.);
	TEST_CLASS(FrustumUnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Frustum _a;
			for (size_t _index = 0; _index < 6; ++_index)
			{
				Assert::IsTrue(_a[_index] == Plane(), L"");
			}
			const auto _p0 = Plane(unit3, -1);
			const auto _p1 = Plane(unit3, 1);
			const auto _p2 = Plane(unit3, 2);
			const auto _p3 = Plane(unit3, 3);
			const auto _p4 = Plane(unit3, 4);
			const auto _p5 = Plane(unit3, 5);

			Frustum _b(_p0, _p1, _p2, _p3, _p4, _p5);
			Assert::IsTrue(_b[0] == _p0, L"Instancing");
			Assert::IsTrue(_b[1] == _p1, L"Instancing");
			Assert::IsTrue(_b[2] == _p2, L"Instancing");
			Assert::IsTrue(_b[3] == _p3, L"Instancing");
			Assert::IsTrue(_b[4] == _p4, L"Instancing");
			Assert::IsTrue(_b[5] == _p5, L"Instancing");
		}
		TEST_METHOD(Set)
		{
			const auto _p0 = Plane(unit3, -1);
			const auto _p1 = Plane(unit3, 1);
			const auto _p2 = Plane(unit3, 2);
			const auto _p3 = Plane(unit3, 3);
			const auto _p4 = Plane(unit3, 4);
			const auto _p5 = Plane(unit3, 5);

			Frustum _b(_p0, _p1, _p2, _p3, _p4, _p5);
			Assert::IsTrue(_b[0] == _p0, L"Instancing");
			Assert::IsTrue(_b[1] == _p1, L"Instancing");
			Assert::IsTrue(_b[2] == _p2, L"Instancing");
			Assert::IsTrue(_b[3] == _p3, L"Instancing");
			Assert::IsTrue(_b[4] == _p4, L"Instancing");
			Assert::IsTrue(_b[5] == _p5, L"Instancing");
		}
		TEST_METHOD(SetFromProjectionMatrix_MakeOrthographic_ContainsPoint)
		{
			Matrix4 _m;
			_m.MakeOrthographic(-1., 1., -1., 1., 1., 100.);
			Frustum _a;
			_a.SetFromProjectionMatrix(_m);

			Assert::IsTrue(!_a.ContainsPoint(Vector3()), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(0., 0., -50.)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(0., 0, -1.001)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(-1, -1, -1.001)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(!_a.ContainsPoint(Vector3(-1.1, -1.1, -1.001)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(1., 1., -1.001)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(!_a.ContainsPoint(Vector3(1.1, 1.1, -1.001)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(0.,0.,-100.)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(-1., -1., -100.)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(!_a.ContainsPoint(Vector3(-1.1, -1.1, -100.1)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(_a.ContainsPoint(Vector3(1., 1., -100.)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(!_a.ContainsPoint(Vector3(1.1, 1.1, -100.1)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
			Assert::IsTrue(!_a.ContainsPoint(Vector3(0., 0., -101.)), L"SetFromProjectionMatrix_MakeOrthographic_ContainsPoint");
		}
		TEST_METHOD(SetFromProjectionMatrix_MakePerspective_ContainsPoint)
		{
			Matrix4 _m;
			_m.MakePerspective(-1., 1., 1., -1., 1., 100.);
			Frustum _a;
			_a.SetFromProjectionMatrix(_m);
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(0., 0., 0.), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(0., 0., 0.), 0.9)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(0., 0., 0.), 1.1)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(0., 0., -50.), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(0., 0., -1.001), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(-1, -1, -1.001), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(-1.1, -1.1, -1.001), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(-1.1, -1.1, -1.001), 0.5)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(1., 1., -1.001), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(1.1, 1.1, -1.001), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(1.1, 1.1, -1.001), 0.5)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(0., 0., -99.999), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(-99.999, -99.999, -99.999), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(-100.1, -100.1, -100.1), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(-100.1, -100.1, -100.1), 0.5)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(99.999, 99.999, -99.999), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(100.1, 100.1, -100.1), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(100.1, 100.1, -100.1), 0.2)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(!_a.IntersectsSphere( Sphere( Vector3(0., 0., -101.), 0.)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
			Assert::IsTrue(_a.IntersectsSphere( Sphere( Vector3(0., 0., -101.), 1.1)), L"SetFromProjectionMatrix_MakePerspective_ContainsPoint");
		}
		TEST_METHOD(IntersectsObejct)
		{
		}
		TEST_METHOD(IntersetcsSprite)
		{
		}
		TEST_METHOD(IntersectsBox)
		{
			Matrix4 _m;
			_m.MakePerspective(-1., 1., 1., -1., 1., 100.);
			Frustum _a;
			_a.SetFromProjectionMatrix(_m);
			Box3 _box(zero3, one3);
			Assert::IsTrue(!_a.IntersectsBox(_box), L"IntersectsBox3");
			_box.Translate(Vector3(-1. - 0.0001));
			Assert::IsTrue(_a.IntersectsBox(_box), L"IntersectsBox3");
		}
		TEST_METHOD(ToJson)
		{
			Frustum _f(Plane(Vector3(1., 0., 0.), 1.),
				Plane(Vector3(1., 0., 0.), 1.),
				Plane(Vector3(1., 0., 0.), 1.),
				Plane(Vector3(1., 0., 0.), 1.),
				Plane(Vector3(1., 0., 0.), 1.),
				Plane(Vector3(1., 0., 0.), 1.));

			stringstream _ss;
			_ss << _f;
			Assert::IsTrue(_ss.str() == "{type:'Frustum',planes:[{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1},{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1},{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1},{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1},{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1},{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1}]}", L"ToJson");
		}
	};
}