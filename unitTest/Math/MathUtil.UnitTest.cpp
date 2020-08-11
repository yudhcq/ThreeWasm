#include <CppUnitTest.h>

#include "../TestConstants.h"
#include "../../src/Math/MathUtil.h"
#define _USE_MATH_DEFINES
#include <float.h>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three::Math;
namespace ThreeUnitTest
{
	TEST_CLASS(MathUtilUintTest)
	{
		TEST_METHOD(AlmostEqule)
		{
			// 小数比较
			const double _x = 1.98 * 13. / 13.;
			// x == 经过数学运算之后的x
			Assert::IsTrue(MathUtil::AlmosetEquals(_x, 1.98));
			// x == x + EPSILION
			Assert::IsTrue(MathUtil::AlmosetEquals(x, x + MathUtil::EPSILION));
			// x == x - EPSILION
			Assert::IsTrue(MathUtil::AlmosetEquals(x, x - MathUtil::EPSILION));
			// x != x + EPSILION + DBL_EPSILON * 2.
			Assert::IsFalse(MathUtil::AlmosetEquals(x, x + MathUtil::EPSILION + DBL_EPSILON * 2.));
			// 大数比较
			// c++中的双精度浮点型数字遵从IEEE的规则:1个符号位，11个指数为、52个数据位，52个二进制数据位，能表示的
			// 有效数值，转换位十进制位1e16
			const double _largeDouble = 1.234e16;
			Assert::IsTrue(MathUtil::AlmosetEquals(_largeDouble, _largeDouble + 8.));
			Assert::IsTrue(MathUtil::AlmosetEquals(_largeDouble, _largeDouble + 9.));
			Assert::IsFalse(MathUtil::AlmosetEquals(_largeDouble, _largeDouble + 10.));
			Assert::IsTrue(MathUtil::AlmosetEquals(_largeDouble, _largeDouble + 10., 5));
			Assert::IsTrue(MathUtil::AlmosetEquals(_largeDouble, _largeDouble + 15., 8));
			Assert::IsFalse(MathUtil::AlmosetEquals(_largeDouble, _largeDouble + 18., 8));
			// nan != nan
			Assert::IsFalse(MathUtil::AlmosetEquals(numeric_limits<double>::quiet_NaN(), 
				numeric_limits<double>::quiet_NaN()));
			// infinity == infinity
			Assert::IsTrue(MathUtil::AlmosetEquals(numeric_limits<double>::infinity(),
				numeric_limits<double>::infinity()));
			// -infinity == -infinity
			Assert::IsTrue(MathUtil::AlmosetEquals(-numeric_limits<double>::infinity(),
				-numeric_limits<double>::infinity()));
			// infinity != -infinity
			Assert::IsFalse(MathUtil::AlmosetEquals(numeric_limits<double>::infinity(),
				-numeric_limits<double>::infinity()));
			// infinity !=  double
			Assert::IsFalse(MathUtil::AlmosetEquals(numeric_limits<double>::infinity(), x));
			// nan != double 
			Assert::IsFalse(MathUtil::AlmosetEquals(numeric_limits<double>::quiet_NaN(), x));
		}
		TEST_METHOD(Clamp)
		{
			AssetAlmosetEqules(MathUtil::Clamp(0.5, 0., 1.), 0.5, L"Clamp");
			AssetAlmosetEqules(MathUtil::Clamp(0., 0., 1.), 0., L"Clamp");
			AssetAlmosetEqules(MathUtil::Clamp(-0.1, 0., 1.), 0., L"Clamp");
			AssetAlmosetEqules(MathUtil::Clamp(1.1, 0., 1.), 1., L"Clamp");
		}
		TEST_METHOD(EuclideanModulo)
		{
			Assert::IsTrue(MathUtil::IsNan(MathUtil::EuclideanModulo(6., 0.)), L"EuclideanModulo");
			AssetAlmosetEqules(MathUtil::EuclideanModulo(6., 1.), 0., L"EuclideanModulo");
			AssetAlmosetEqules(MathUtil::EuclideanModulo(6., 2.), 0., L"EuclideanModulo");
			AssetAlmosetEqules(MathUtil::EuclideanModulo(6., 5.), 1., L"EuclideanModulo");
			AssetAlmosetEqules(MathUtil::EuclideanModulo(6., 6.), 0., L"EuclideanModulo");
			AssetAlmosetEqules(MathUtil::EuclideanModulo(6., 7.), 6., L"EuclideanModulo");
		}
		TEST_METHOD(MapLinear)
		{
			AssetAlmosetEqules(MathUtil::MapLinear(0.5, 0., 1., 0., 10.), 5., L"MapLinear");
			AssetAlmosetEqules(MathUtil::MapLinear(0., 0., 1., 0., 10.), 0., L"MapLinear");
			AssetAlmosetEqules(MathUtil::MapLinear(1., 0., 1., 0., 10.), 10., L"MapLinear");
		}
		TEST_METHOD(Lerp)
		{
			AssetAlmosetEqules(MathUtil::Lerp(1., 2., 0.), 1., L"Lerp");
			AssetAlmosetEqules(MathUtil::Lerp(1., 2., 1.), 2., L"Lerp");
			AssetAlmosetEqules(MathUtil::Lerp(1., 2., 0.4), 1.4, L"Lerp");
		}
		TEST_METHOD(SmoothStep)
		{
			AssetAlmosetEqules(MathUtil::Smootherstep(-1., 0., 2.), 0., L"SmoothStep");
			AssetAlmosetEqules(MathUtil::Smootherstep(0., 0., 2.), 0., L"SmoothStep");
			AssetAlmosetEqules(MathUtil::Smootherstep(0.5, 0., 2.), 0.103515625, L"SmoothStep");
			AssetAlmosetEqules(MathUtil::Smootherstep(1.0, 0., 2.), 0.5, L"SmoothStep");
			AssetAlmosetEqules(MathUtil::Smootherstep(1.5, 0., 2.), 0.896484375, L"SmoothStep");
			AssetAlmosetEqules(MathUtil::Smootherstep(2., 0., 2.), 1., L"SmoothStep");
			AssetAlmosetEqules(MathUtil::Smootherstep(3., 0., 2.), 1., L"SmoothStep");
		}
		TEST_METHOD(RandInt)
		{
			const int _low = 1, _hight = 3;
			const int a = MathUtil::RandInt(_low, _hight);

			Assert::IsTrue(a >= _low && a <= _hight, L"RandInt");
		}
		TEST_METHOD(RandFloat)
		{
			const double _low = 1., _hight = 3.;
			const double a = MathUtil::RandFloat(_low, _hight);

			Assert::IsTrue(a >= _low && a <= _hight, L"RandFloat");
		}
		TEST_METHOD(RandFloatSpread)
		{
			const double _a = MathUtil::RandFloatSpread(3.);
			Assert::IsTrue( _a > -1.5 && _a < 1.5, L"RandFloatSpread");
		}
		TEST_METHOD(DegToRad)
		{
			AssetAlmosetEqules(MathUtil::DegToRad(0.), 0., L"DegToRad 0");
			AssetAlmosetEqules(MathUtil::DegToRad(90.), M_PI_2, L"DegToRad 0");
			AssetAlmosetEqules(MathUtil::DegToRad(180.), M_PI, L"DegToRad 0");
			AssetAlmosetEqules(MathUtil::DegToRad(360.), M_PI * 2., L"DegToRad 0");
		}
		TEST_METHOD(RadToDeg)
		{
			AssetAlmosetEqules(MathUtil::RadToDeg(0.), 0., L"RadToDeg");
			AssetAlmosetEqules(MathUtil::RadToDeg(M_PI_2), 90., L"RadToDeg");
			AssetAlmosetEqules(MathUtil::RadToDeg(M_PI), 180., L"RadToDeg");
			AssetAlmosetEqules(MathUtil::RadToDeg(M_PI * 2), 360., L"RadToDeg");
		}
		TEST_METHOD(IsPowerofTwo)
		{
			Assert::IsTrue(MathUtil::IsPowerOfTwo(0) == false, L"IsPowerOfTwo 0");
			Assert::IsTrue(MathUtil::IsPowerOfTwo(1) == true, L"IsPowerOfTwo 1");
			Assert::IsTrue(MathUtil::IsPowerOfTwo(2) == true, L"IsPowerOfTwo 2");
			Assert::IsTrue(MathUtil::IsPowerOfTwo(3) == false, L"IsPowerOfTwo 3");
			Assert::IsTrue(MathUtil::IsPowerOfTwo(4) == true, L"IsPowerOfTwo 4");
		}
		TEST_METHOD(CeilPowerOfTwo)
		{
			AssetAlmosetEqules(MathUtil::CeilPowerOfTwo(1), 1, L"CeilPowerOfTwo 1");
			AssetAlmosetEqules(MathUtil::CeilPowerOfTwo(3), 4, L"CeilPowerOfTwo 3");
			AssetAlmosetEqules(MathUtil::CeilPowerOfTwo(4), 4, L"CeilPowerOfTwo 4");
		}
		TEST_METHOD(FloorPowerOfTwo)
		{
			AssetAlmosetEqules(MathUtil::FloorPowerOfTwo(1), 1, L"FloorPowerOfTwo 1");
			AssetAlmosetEqules(MathUtil::FloorPowerOfTwo(3), 2, L"FloorPowerOfTwo 3");
			AssetAlmosetEqules(MathUtil::FloorPowerOfTwo(4), 4, L"FloorPowerOfTwo 4");
		}
		TEST_METHOD(IsNan)
		{
			Assert::IsTrue(!MathUtil::IsNan(1), L"IsNan");
			Assert::IsTrue(MathUtil::IsNan(NAN), L"IsNaN");
		}
		TEST_METHOD(ToString16)
		{
			Assert::IsTrue(MathUtil::ToString16(0xff) == "ff", L"ToString16");
			Assert::IsTrue(MathUtil::ToString16(0xff00) == "ff00", L"ToString16");
			Assert::IsTrue(MathUtil::ToString16(0xff0000) == "ff0000", L"ToString16");
		}
	};
}
#undef _USE_MATH_DEFINES