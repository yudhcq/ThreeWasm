#include <CppUnitTest.h>

#include "../TestConstants.h"
#include "../../src/Math/Line3.h"
#include "../../src/Math/Vector4.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three::Math;

namespace ThreeUnitTest
{
	TEST_CLASS(Line3UnitTest)
	{
		TEST_METHOD(Instancing)
		{
			const Line3 _a;
			Assert::IsTrue(_a.Start() == zero3, L"Instancing");
			Assert::IsTrue(_a.End() == zero3, L"Instancing");

			const Line3 _b(one3, two3);
			Assert::IsTrue(_b.Start() == one3, L"Instancing");
			Assert::IsTrue(_b.End() == two3, L"Instancing");
		}
		TEST_METHOD(SetGet)
		{
			Line3 _a;
			_a.Set(one3, two3);
			Assert::IsTrue(_a.Start() == one3, L"Instancing");
			Assert::IsTrue(_a.End() == two3, L"Instancing");

			_a.SetStart(two3);
			Assert::IsTrue(_a.Start() == two3, L"Instancing");

			_a.SetEnd(one3);
			Assert::IsTrue(_a.End() == one3, L"Instancing");
		}
		TEST_METHOD(Equals)
		{
			Assert::IsTrue(Line3(one3, two3) == Line3(one3 + FLT_EPSILON, two3 - FLT_EPSILON), L"Equals");
			Assert::IsTrue(!(Line3(one3, two3) == Line3(one3 + FLT_EPSILON * 2., two3 - FLT_EPSILON * 2.)), L"Equals");
		}
		TEST_METHOD(GetCenter)
		{
			const Line3 _a(one3, two3);
			Assert::IsTrue(_a.GetCenter() == (two3 + one3) / 2., L"GetCenter");
		}
		TEST_METHOD(Delta)
		{
			const Line3 _a(one3, two3);
			Assert::IsTrue(_a.Delta() == one3, L"Delta");
		}
		TEST_METHOD(Distance)
		{
			const Line3 _a;
			const Line3 _b(zero3, one3);
			const Line3 _c(-one3, one3);
			const Line3 _d(two3 * -2., -two3);

			AssetAlmosetEqules(_a.Distance(), 0., L"Distance");
			AssetAlmosetEqules(_b.Distance(), sqrt(3.), L"Distance");
			AssetAlmosetEqules(_c.Distance(), sqrt(12.), L"Distance");
			AssetAlmosetEqules(_d.Distance(), sqrt(12.), L"Distance");
		}
		TEST_METHOD(At)
		{
			Line3 _a(one3, Vector3(1., 1., 2.));

			Assert::IsTrue(_a.At(-1.) == Vector3(1., 1., 0.), L"At");
			Assert::IsTrue(_a.At(0.) == one3, L"At");
			Assert::IsTrue(_a.At(1.) == Vector3(1., 1., 2.), L"At");
			Assert::IsTrue(_a.At(2.) == Vector3(1., 1., 3.), L"At");
		}
		TEST_METHOD(ClosestPointToPoint_ClosestPointToPointParameter)
		{
			Line3 _a(one3, Vector3(1., 1., 2.));

			AssetAlmosetEqules(_a.ClosestPointToPointParameter(zero3, true), 0., L"ClosestPointToPoint_ClosestPointToPointParameter");
			AssetAlmosetEqules(_a.ClosestPointToPointParameter(zero3, false), -1., L"ClosestPointToPoint_ClosestPointToPointParameter");
			AssetAlmosetEqules(_a.ClosestPointToPointParameter(Vector3(1., 1., 5.), true), 1., L"ClosestPointToPoint_ClosestPointToPointParameter");
			AssetAlmosetEqules(_a.ClosestPointToPointParameter(one3, true), 0., L"ClosestPointToPoint_ClosestPointToPointParameter");
		}
		TEST_METHOD(ApplyMatrix4)
		{
			Line3 _a(zero3, two3);
			Vector4 _b(2., 2., 2., 1.);
			Matrix4 _m;
			_m.MakeTranslation(x, y, z);
			Vector3 _v(x, y, z);

			Assert::IsTrue(_a * _m == Line3(_v, _v + 2.), L"ApplyMatrix4");
			
			_m.MakeRotationX(M_PI);

			Assert::IsTrue(_a * _m == Line3(zero3, Vector3(_b.X() / _b.W(), _b.Y() / _b.W(), _b.Z() / _b.W())));

			_m.SetPosition(_v);
			Assert::IsTrue(_a * _m == Line3(_v, Vector3(_b.X() / _b.W(), _b.Y() / _b.W(), _b.Z() / _b.W())));
		}
		TEST_METHOD(ToJson)
		{
			Line3 _a(one3, one3);

			stringstream _ss;
			_ss << _a;

			Assert::IsTrue(_ss.str() == "{type:'Line3',start:{type:'Vector3',x:1,y:1,z:1},end:{type:'Vector3',x:1,y:1,z:1}}");
		}
	};
}