#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Cylindrical.h"

using namespace std;
using namespace Three::Math;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ThreeUnitTest
{
	TEST_CLASS(CylindicalUnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Cylindrical _c;
			AssetAlmosetEqules(_c.Radius(), 1.0, L"Default values, radius");
			AssetAlmosetEqules(_c.Theta(), 0., L"Default values, theta");
			AssetAlmosetEqules(_c.Y(), 0., L"Default values, y");

			_c = Cylindrical(10., M_PI, 5.);

			AssetAlmosetEqules(_c.Radius(), 10.0, L"Custom values, radius");
			AssetAlmosetEqules(_c.Theta(), M_PI, L"Custom values, theta");
			AssetAlmosetEqules(_c.Y(), 5., L"Custom values, y");
		}
		TEST_METHOD(Set)
		{
			Cylindrical _c;
			_c.Set(10, M_PI, 5.);

			AssetAlmosetEqules(_c.Radius(), 10.0, L"Set values, radius");
			AssetAlmosetEqules(_c.Theta(), M_PI, L"Set values, theta");
			AssetAlmosetEqules(_c.Y(), 5., L"Set values, y");

			_c.SetRadius(20.);
			AssetAlmosetEqules(_c.Radius(), 20.0, L"Set radius");

			_c.SetTheta(M_PI_2);
			AssetAlmosetEqules(_c.Theta(), M_PI_2, L"Set theta");

			_c.SetY(10.);
			AssetAlmosetEqules(_c.Y(), 10., L"Set y");
		}
		TEST_METHOD(SetFromVector3)
		{
			Cylindrical _c;
			_c.SetFromVector3(Vector3(0.));

			AssetAlmosetEqules(_c.Radius(), 0., L"Zero-length vector: check radius");
			AssetAlmosetEqules(_c.Theta(), 0., L"Zero-length vector: check theta");
			AssetAlmosetEqules(_c.Y(), 0., L"Zero-length vector: check y");

			_c.SetFromVector3(Vector3(3., -1., -3.));

			AssetAlmosetEqules(_c.Radius(), sqrt(18.), L"Normal vector: check radius");
			AssetAlmosetEqules(_c.Theta(), atan2(3., -3.), L"Normal vector: check theta");
			AssetAlmosetEqules(_c.Y(), -1, L"Normal vector: check y");
		}

		TEST_METHOD(ToJson)
		{
			Cylindrical _c(10., 3.14, 1.);
			stringstream _ss;
			_ss << _c;

			Assert::IsTrue(_ss.str() == "{type:'Cylindrical',radius:10,theta:3.14,y:1}", L"");
		}
	};
}