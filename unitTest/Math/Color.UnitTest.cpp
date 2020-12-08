#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Color.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three;

namespace ThreeUnitTest
{
	TEST_CLASS(ColorUnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Color _color;
			AssetAlmosetEqules(_color.Red(), 1., L"Instancing");
			AssetAlmosetEqules(_color.Green(), 1., L"Instancing");
			AssetAlmosetEqules(_color.Blue(), 1., L"Instancing");
			
			_color = Color(1.0);
			AssetAlmosetEqules(_color.Red(), 1., L"Instancing");
			AssetAlmosetEqules(_color.Green(), 1., L"Instancing");
			AssetAlmosetEqules(_color.Blue(), 1., L"Instancing");

			_color = Color("aqua");
			AssetAlmosetEqules(_color.Red(), 0., L"Instancing");
			AssetAlmosetEqules(_color.Green(), 1., L"Instancing");
			AssetAlmosetEqules(_color.Blue(), 1., L"Instancing");

			_color = Color(0xff00ff);
			AssetAlmosetEqules(_color.Red(), 1., L"Instancing");
			AssetAlmosetEqules(_color.Green(), 0., L"Instancing");
			AssetAlmosetEqules(_color.Blue(), 1., L"Instancing");
		}
		TEST_METHOD(SetGet)
		{
			Color _c;
			Assert::IsTrue(_c == Color(1.), L"SetGet");
			AssetAlmosetEqules(_c.Red(), 1., L"GetRed");
			_c.SetScalar(0.);
			Assert::IsTrue(_c == Color(0.), L"SetGet");
			AssetAlmosetEqules(_c.Green(), 0., L"GetGreen");
			_c.SetRGB(0., 0.5, 1.);
			Assert::IsTrue(_c == Color(0., 0.5, 1.), L"SetRGB");
			AssetAlmosetEqules(_c.Blue(), 1., L"GetBlue");
			_c.SetColorKeyWorld("aqua");
			Assert::IsTrue(_c == Color("aqua"), L"SetKeyWorld");
			AssetAlmosetEqules(_c.Red(), 0., L"GetGreen");
			AssetAlmosetEqules(_c.Green(), 1., L"GetGreen");
			AssetAlmosetEqules(_c.Blue(), 1., L"GetGreen");
			_c.SetHex(0xffff00);
			Assert::IsTrue(_c == Color(0xffff00), L"SetHex");
			Assert::IsTrue(_c.GetHex() == 0xffff00, L"GetHex");
			_c.SetHSL(0.75, 1.0, 0.25);
			const auto _hsl = _c.GetHSL();
			AssetAlmosetEqules(_hsl.h, 0.75, L"SetGetHSL");
			AssetAlmosetEqules(_hsl.s, 1.0, L"SetGetHSL");
			AssetAlmosetEqules(_hsl.l, 0.25, L"SetGetHSL");
		}
		TEST_METHOD(SetStyle)
		{
			Color _a;
			Color _b(8. / 255., 25./ 255., 178. / 255.);
			_a.SetStyle("rgba(8,25,178)");
			Assert::IsTrue(_a == _b, L"SetStyle");
			
			_a.SetStyle("rgba(8, 25, 178, 200)");
			Assert::IsTrue(_a == _b, L"SetStyle");

			_a.SetStyle("hsl(270,50%,75%)");
			auto _hsl = _a.GetHSL();
			AssetAlmosetEqules(_hsl.h, 0.75, L"SetStyle");
			AssetAlmosetEqules(_hsl.s, 0.5, L"SetStyle");
			AssetAlmosetEqules(_hsl.l, 0.75, L"SetStyle");

			_a.SetStyle("hsl(270,50%,75%, 0.5)");
			_hsl = _a.GetHSL();
			AssetAlmosetEqules(_hsl.h, 0.75, L"SetStyle");
			AssetAlmosetEqules(_hsl.s, 0.5, L"SetStyle");
			AssetAlmosetEqules(_hsl.l, 0.75, L"SetStyle");

			_a.SetStyle("#f8a");
			Assert::IsTrue(_a == Color(static_cast<double>(0xff) / 255., 
				static_cast<double>(0x88) / 255., static_cast<double>(0xaa)/ 255.), L"SetStyle");

			_a.SetStyle("#f8abc1");
			Assert::IsTrue(_a == Color(static_cast<double>(0xf8) / 255.,
				static_cast<double>(0xab) / 255., static_cast<double>(0xc1) / 255.), L"SetStyle");

			_a.SetStyle("aliceblue");
			Assert::IsTrue(_a == Color(static_cast<double>(0xf0) / 255.,
				static_cast<double>(0xf8) / 255., static_cast<double>(0xff) / 255.), L"SetStyle");
		}
		TEST_METHOD(CopyGamaTolinear)
		{
			Color _color;
			_color.CopyGamaToLinear(Color(0.3, 0.5, 0.9));
			Assert::IsTrue(_color == Color(0.09, 0.25, 0.81), L"CopyGamaTolinear");
		}
		TEST_METHOD(CopyLinearToGamma)
		{
			Color _color;
			_color.CopyLinearToGamma(Color(0.09, 0.25, 0.81));
			Assert::IsTrue(_color == Color(0.3, 0.5, 0.9), L"CopyLinearToGamma");
		}
		TEST_METHOD(ConvertGammaToLinear)
		{
			Color _color(0.3, 0.5, 0.9);
			_color.ConvertGammaToLinear();
			Assert::IsTrue(_color == Color(0.09, 0.25, 0.81), L"ConvertGammaToLinear");
		}
		TEST_METHOD(ConvertLinearToGamma)
		{
			Color _color(0.09, 0.25, 0.81);
			_color.ConvertLinearToGamma();
			Assert::IsTrue(_color == Color(0.3, 0.5, 0.9), L"ConvertGammaToLinear");
		}
		TEST_METHOD(GetHex)
		{
			Color _c("red");
			Assert::IsTrue(_c.GetHex() == 0xff0000, L"GetHex");
		}
		TEST_METHOD(GetHexString)
		{
			Color _c("tomato");
			Assert::IsTrue(_c.GetHexString() == "ff6347", L"GetHexString");
			_c.SetHex(0x32);
			Assert::IsTrue(_c.GetHexString() == "000032", L"GetHexString");
		}
		TEST_METHOD(GetStyle)
		{
			Color _c("plum");
			Assert::IsTrue(_c.GetStyle() == "rgb(221,160,221)", L"GetStyle");
		}
		TEST_METHOD(OffsetHSL)
		{
			Color _c("hsl(120,50%,50%)");
			_c.OffsetHSL(0.1, 0.1, 0.1);

			Assert::IsTrue(_c == Color(0.36, 0.84, 0.648), L"OffsetHSL");
		}
		TEST_METHOD(Add)
		{
			Color _c(0xff);
			Color _c1(0xff0000);

			Assert::IsTrue(_c + _c1 == Color(0xff00ff), L"Added");
			_c += _c1;
			Assert::IsTrue(_c == Color(0xff00ff), L"Add");
		}
		TEST_METHOD(AddScalar)
		{
			Color _c(0.1, 0.0, 0.0);
			Assert::IsTrue(_c + 0.5 == Color(0.6, 0.5, 0.5), L"AddScalar");
			_c += 0.5;
			Assert::IsTrue(_c == Color(0.6, 0.5, 0.5), L"AddScalar");
		}
		TEST_METHOD(Sub)
		{
			Color _c(0xff);
				
			Assert::IsTrue(_c - Color(0xff0000) == Color(0xff), L"Sub");
			_c -= Color(0xff0000);
			Assert::IsTrue(_c == Color(0xff), L"Sub");

			Assert::IsTrue(_c - Color(0xaa) == Color(0x55), L"Sub");
			_c -= Color(0xaa);
			Assert::IsTrue(_c == Color(0x55), L"Sub");
		}
		TEST_METHOD(SubScalar)
		{
			Color _c(0.6, 0.5, 0.5);

			Assert::IsTrue(_c - 0.5 == Color(0.1, 0., 0.), L"SubScalar");
			_c -= 0.5;
			Assert::IsTrue(_c == Color(0.1, 0., 0.), L"SubScalar");
		}
		TEST_METHOD(Multiply)
		{
			Color _c(1., 0., 0.5);

			Assert::IsTrue(_c * Color(0.5, 1., 0.5) == Color(0.5, 0, 0.25), L"Multiply");
			_c *= Color(0.5, 1., 0.5);
			Assert::IsTrue(_c == Color(0.5, 0, 0.25), L"Multiply");
		}
		TEST_METHOD(MutiplyScalar)
		{
			Color _c(0.25, 0., 0.5);
			
			Assert::IsTrue(_c * 2. == Color(0.5, 0., 1.0), L"MultiplyScalar");
			_c *= 2.0;
			Assert::IsTrue(_c == Color(0.5, 0., 1.0), L"MultiplyScalar");
		}
		TEST_METHOD(Lerp)
		{
			Color _c(0.);
			
			Assert::IsTrue(_c.Lerped(Color(), 0.2) == Color(0.2), L"Lerped");
			_c.Lerp(Color(), 0.2);
			Assert::IsTrue(_c == Color(0.2), L"Lerp");
		}
		TEST_METHOD(Equls)
		{
			Color _c;
			Assert::IsTrue(_c.Equals(Color(1.0 - FLT_EPSILON)), L"Equls");
			Assert::IsTrue(_c.Equals(Color(1.0 + FLT_EPSILON)), L"Equls");
		}
		TEST_METHOD(ToJson)
		{
			Color _c(0.2, 0.3, 0.4);

			stringstream _ss;
			_ss << _c;

			Assert::IsTrue(_ss.str() == "{type:'Color',red:0.2,green:0.3,blue:0.4}", L"ToJson");
		}
	};
}