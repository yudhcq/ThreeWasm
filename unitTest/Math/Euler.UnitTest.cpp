#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Euler.h"
#include "../../src/Math/Quaternion.h"
#include "../../src/Math/Matrix4.h"

using namespace std;
using namespace Three::Math;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ThreeUnitTest
{
	const Euler ZeroEuler(0., 0., 0., EulerOrder::XYZ);
	const Euler EulerAxyz(1., 0., 0., EulerOrder::XYZ);
	const Euler EulerAzyx(0., 1., 0., EulerOrder::ZYX);

	TEST_CLASS(EulerUnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Euler _e;
			Assert::IsTrue(_e == ZeroEuler, L"Instancing");
			Assert::IsTrue(!(_e == EulerAxyz), L"Instancing");
			Assert::IsTrue(!(_e == EulerAzyx), L"Instancing");

			Euler _e1(2., 3., 4., EulerOrder::YXZ);
			AssetAlmosetEqules(_e1.X(), 2., L"Instancing");
			AssetAlmosetEqules(_e1.Y(), 3., L"Instancing");
			AssetAlmosetEqules(_e1.Z(), 4., L"Instancing");
			Assert::IsTrue(_e1.Order() == EulerOrder::YXZ, L"Instancing");
		}
		TEST_METHOD(SetGet)
		{
			Euler _e;
			_e.SetX(10.);
			Assert::IsTrue(_e.X() == 10., L"SetGet");
			_e.SetY(20.);
			Assert::IsTrue(_e.Y() == 20., L"SetGet");
			_e.SetZ(30.);
			Assert::IsTrue(_e.Z() == 30., L"SetGet");
			_e.SetOrder(EulerOrder::YZX);
			Assert::IsTrue(_e.Order() == EulerOrder::YZX, L"SetGet");
			_e.Set(1.,2.,3.,EulerOrder::XYZ);
			Assert::IsTrue(_e == Euler(1., 2., 3., EulerOrder::XYZ));
		}
		TEST_METHOD(SetFromMatrix4)
		{
			Euler _es[3] = { ZeroEuler, EulerAxyz, EulerAzyx };
			for (const auto& _e : _es)
			{
				Matrix4 _m, _m1;
				_m.MakeRotationFromEuler(_e);
				Euler _e1;
				_e1.SetFromMatrix4(_m, _e.Order());
				_m1.MakeRotationFromEuler(_e1);

				Assert::IsTrue(_m == _m1, L"SetFromMatrix");
			}
		}
		TEST_METHOD(SetFromQuaternion)
		{
			Euler _es[3] = { ZeroEuler, EulerAxyz, EulerAzyx };
			for (const auto& _e : _es)
			{
				Quaternion _q, _q1;
				_q.SetFromEuler(_e);
				Euler _e1;
				_e1.SetFromQuaternion(_q, _e.Order());
				_q1.SetFromEuler(_e1);

				Assert::IsTrue(_q == _q1, L"SetFromQuaternion");
			}
		}
		TEST_METHOD(SetFromVector3)
		{
			Euler _a(0., 1., 0., EulerOrder::YXZ);
			Euler _b;
			_b.SetFromVector3(Vector3(0., 1., 0.), EulerOrder::YXZ);
			Assert::IsTrue(_a == _b, L"SetFromVector3");
		}
		TEST_METHOD(ReOrder)
		{
			Euler _es[3] = { ZeroEuler, EulerAxyz, EulerAzyx };
			for (auto& _e : _es)
			{
				Quaternion _q, _q1, _q2;
				_q.SetFromEuler(_e);
				_e.ReOrder(EulerOrder::YZX);
				_q1.SetFromEuler(_e);
				Assert::IsTrue(_q == _q1, L"ReOrder");
				_e.ReOrder(EulerOrder::ZXY);
				_q2.SetFromEuler(_e);
				Assert::IsTrue(_q == _q2, L"ReOrder");
			}
		}
		TEST_METHOD(Equals)
		{
			Assert::IsTrue(Euler(x, y, z) == Euler(x + FLT_EPSILON, y + FLT_EPSILON, z + FLT_EPSILON));
			Assert::IsTrue(Euler(x, y, z) == Euler(x - FLT_EPSILON, y - FLT_EPSILON, z - FLT_EPSILON));
			Assert::IsTrue(!(Euler(x, y, z) == Euler(x + FLT_EPSILON * 2., y + FLT_EPSILON * 2., z + FLT_EPSILON * 2.)));
			Assert::IsTrue(!(Euler(x, y, z) == Euler(x - FLT_EPSILON * 2., y - FLT_EPSILON * 2., z - FLT_EPSILON * 2.)));
		}
		TEST_METHOD(ToJson)
		{
			Euler _e(2., 3., 4., EulerOrder::XYZ);

			stringstream _ss;
			_ss << _e;

			Assert::IsTrue(_ss.str() == "{type:'Euler',x:2,y:3,z:4,order:'XYZ'}", L"ToJson");
		}
	};
}