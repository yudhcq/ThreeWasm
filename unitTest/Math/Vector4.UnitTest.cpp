#include <CppUnitTest.h>

#include "../TestConstants.h"
#include "../../src/Math/Vector4.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three::Math;
using namespace std;

namespace ThreeUnitTest
{
	TEST_CLASS(Vector4UnitTest)
	{
		TEST_METHOD(Equales)
		{
			Vector4 _v;
			Assert::IsTrue(_v == Vector4(), L"Equales");
			_v.Set(1., 2., 3., 4.);
			Assert::IsTrue(_v == Vector4(1., 2., 3., 4.), L"Equales");
			Assert::IsTrue(_v == Vector4(1. + FLT_EPSILON, 2. + FLT_EPSILON, 
				3. - FLT_EPSILON, 4. - FLT_EPSILON), L"Equales");
		}
		TEST_METHOD(Intsancing)
		{
			Vector4 _v;
			AssetAlmosetEqules(_v.X(), 0., L"Intsancing x");
			AssetAlmosetEqules(_v.Y(), 0., L"Intsancing y");
			AssetAlmosetEqules(_v.Z(), 0., L"Intsancing z");
			AssetAlmosetEqules(_v.W(), 1., L"Intsancing w");
			
			Vector4 _v1(x, y, z, w);
			AssetAlmosetEqules(_v1.X(), x, L"Intsancing x");
			AssetAlmosetEqules(_v1.Y(), y, L"Intsancing y");
			AssetAlmosetEqules(_v1.Z(), z, L"Intsancing z");
			AssetAlmosetEqules(_v1.W(), w, L"Intsancing w");

			Vector4 _v2(x);
			AssetAlmosetEqules(_v2.X(), x, L"Intsancing x");
			AssetAlmosetEqules(_v2.Y(), x, L"Intsancing y");
			AssetAlmosetEqules(_v2.Z(), x, L"Intsancing z");
			AssetAlmosetEqules(_v2.W(), x, L"Intsancing w");
		}
		TEST_METHOD(SetGet)
		{
			Vector4 _v;
			AssetAlmosetEqules(_v.X(), 0., L"Get x");
			AssetAlmosetEqules(_v.Y(), 0., L"Get Y");
			AssetAlmosetEqules(_v.Z(), 0., L"Get Z");
			AssetAlmosetEqules(_v.W(), 1., L"Get W");

			_v.Set(x, y, z, w);
			AssetAlmosetEqules(_v.X(), x, L"Set x");
			AssetAlmosetEqules(_v.Y(), y, L"Set Y");
			AssetAlmosetEqules(_v.Z(), z, L"Set Z");
			AssetAlmosetEqules(_v.W(), w, L"Set W");

			_v.Set(0.);
			AssetAlmosetEqules(_v.X(), 0., L"SetScalar x");
			AssetAlmosetEqules(_v.Y(), 0., L"SetScalar Y");
			AssetAlmosetEqules(_v.Z(), 0., L"SetScalar Z");
			AssetAlmosetEqules(_v.W(), 0., L"SetScalar W");

			_v.SetX(x);
			_v.SetY(y);
			_v.SetZ(z);
			_v.SetW(w);
			AssetAlmosetEqules(_v.X(), x, L"Set x");
			AssetAlmosetEqules(_v.Y(), y, L"Set Y");
			AssetAlmosetEqules(_v.Z(), z, L"Set Z");
			AssetAlmosetEqules(_v.W(), w, L"Set W");

			_v.SetWidth(100.);
			_v.SetHeight(200.);

			AssetAlmosetEqules(_v.Width(), _v.Z(), L"Width");
			AssetAlmosetEqules(_v.Width(), 100., L"Width");
			AssetAlmosetEqules(_v.Height(), _v.W(), L"Height");
			AssetAlmosetEqules(_v.Height(), 200., L"Height");
		}
		TEST_METHOD(SetGetComponent)
		{
			Vector4 _v(1., 2., 3., 4.);
			AssetAlmosetEqules(_v[0], 1., L"GetComponent 0");
			AssetAlmosetEqules(_v[1], 2., L"GetComponent 0");
			AssetAlmosetEqules(_v[2], 3., L"GetComponent 0");
			AssetAlmosetEqules(_v[3], 4., L"GetComponent 0");

			_v[0] += 1.;
			_v[1] += 1.;
			_v[2] += 1.;
			_v[3] += 1.;

			AssetAlmosetEqules(_v[0], 2., L"GetComponent 0");
			AssetAlmosetEqules(_v[1], 3., L"GetComponent 0");
			AssetAlmosetEqules(_v[2], 4., L"GetComponent 0");
			AssetAlmosetEqules(_v[3], 5., L"GetComponent 0");

			Assert::ExpectException<range_error>([]() 
				{
					const Vector4 _v1;
					const auto _v1_4 = _v1[4];
				}, L"const GetComponent 4");

			Assert::ExpectException<range_error>([_v]()
				{
					const auto _v_4 = _v[4];
				}, L"GetComponent 4");
		}
		TEST_METHOD(Add)
		{
			Vector4 _v(2.);
			Assert::IsTrue(_v + 3. == Vector4(5.), L"Add scalar");
			Assert::IsTrue(_v + Vector4(x, y, z, w) == Vector4(2.+ x, 2. + y, 2. + z, 2. + w), L"Add vector");
		}
		TEST_METHOD(Sub)
		{
			Vector4 _v(2.);
			Assert::IsTrue(_v - 2. == Vector4(0.), L"Add scalar");
			Assert::IsTrue(_v - Vector4(x, y, z, w) == Vector4(2. - x, 2. - y, 2. - z, 2. - w), L"Sub vector");
		}
		TEST_METHOD(Mul)
		{
			Vector4 _v(3.);
			Assert::IsTrue(_v * 3. == Vector4(9.), L"Mul scalar");
		}
		TEST_METHOD(Divide)
		{
			Vector4 _v(x, y, z, w);
			Assert::IsTrue(_v / 3. == Vector4(x / 3., y / 3., z / 3., w / 3.), L"Divide scalar");
		}
		TEST_METHOD(Apply)
		{
			Vector4 _v(x, y, z, w);
			Matrix4 _m;
			_m.MakeRotationX(M_PI);
			Assert::IsTrue(_v.Applied(_m) == Vector4(2., -3., -4., 5.), L"Apply Matrix");
			_m.MakeTranslation(5., 7., 11);
			Assert::IsTrue(_v.Applied(_m) == Vector4(27., 38., 59., 5.), L"Apply Matrix");
			_m.Set(1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 1., 0.);
			Assert::IsTrue(_v.Applied(_m) == Vector4(2., 3., 4., 4.), L"Apply Matrix");
			_m.Set(2., 3., 5., 7., 11., 13., 17., 19., 23., 29., 31., 37., 41., 43., 47., 53.);
			Assert::IsTrue(_v.Applied(_m) == Vector4(68., 224., 442., 664.), L"Apply Matrix");
		}
		TEST_METHOD(ClampScalar)
		{
			Vector4 _v(-0.1, 0.01, 0.5, 1.5);
			Assert::IsTrue(_v.Clamped(0.1, 1.0) == Vector4(0.1, 0.1, 0.5, 1.0), L"ClampScalar");
		}
		TEST_METHOD(Negate)
		{
			Vector4 _v(x, y, z, w);
			_v.Negate();
			Assert::IsTrue(_v == Vector4(-x, -y, -z, -w), L"Negate");
			Assert::IsTrue(-_v == Vector4(x, y, z, w), L"Negate");
		}
		TEST_METHOD(Dot)
		{
			Vector4 _v(x, y, z, w);
			Vector4 _v1(-_v);
			Vector4 _v2(0.);
			AssetAlmosetEqules(_v.Dot(_v1), -x * x - y * y - z * z - w * w, L"Dot");
			AssetAlmosetEqules(_v.Dot(_v2), 0., L"Dot");
		}
		TEST_METHOD(ManhattanLength)
		{
			Vector4 _v(x, 0, 0, 0);
			Vector4 _v1(0, -y, 0, 0);
			Vector4 _v2(0, 0, z, 0);
			Vector4 _v3(0, 0, 0, w);
			Vector4 _v4(0, 0, 0, 0);
			AssetAlmosetEqules(_v.MamhattanLength(), x, L"ManhattanLength");
			AssetAlmosetEqules(_v1.MamhattanLength(), y, L"ManhattanLength");
			AssetAlmosetEqules(_v2.MamhattanLength(), z, L"ManhattanLength");
			AssetAlmosetEqules(_v3.MamhattanLength(), w, L"ManhattanLength");
			AssetAlmosetEqules(_v4.MamhattanLength(), 0., L"ManhattanLength");
		}
		TEST_METHOD(Normalize)
		{
			Vector4 _v(x, 0, 0, 0);
			Vector4 _v1(0, -y, 0, 0);
			Vector4 _v2(0, 0, z, 0);
			Vector4 _v3(0, 0, 0, -w);
			
			Assert::IsTrue(_v.Normalized() == Vector4(1., 0., 0., 0.), L"Normalize");
			Assert::IsTrue(_v1.Normalized() == Vector4(0., -1., 0., 0.), L"Normalize");
			Assert::IsTrue(_v2.Normalized() == Vector4(0., 0., 1., 0.), L"Normalize");
			Assert::IsTrue(_v3.Normalized() == Vector4(0.,0., 0., -1.), L"Normalize");
		}
		TEST_METHOD(SetLenght)
		{
			Vector4 _v(x, 0., 0., 0.);
			AssetAlmosetEqules(_v.Length(), x, L"SetLength");
			_v.SetLength(y);
			AssetAlmosetEqules(_v.Length(), y, L"SetLength");
			_v.Set(0.);
			AssetAlmosetEqules(_v.Length(), 0, L"SetLength");
			_v.SetLength(y);
			AssetAlmosetEqules(_v.Length(), 0, L"SetLength");
		}
		TEST_METHOD(ToJson)
		{
			Vector4 _v(2., 3., 4., 5.);
			stringstream _ss;
			_ss << _v;
			Assert::IsTrue(_ss.str() == "{type:Vector4,x:2,y:3,z:4,w:5}", L"ToJson");
		}
	};
}