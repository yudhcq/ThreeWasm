#include <CppUnitTest.h>
#include <string>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Vector2.h"
#include "../../src/Math/MathUtil.h"
#include "../../src//Math/Matrix3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three;
using namespace std;

namespace ThreeUnitTest
{
	TEST_CLASS(Vector2UnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Vector2 _a;
			Assert::IsTrue(_a.X() == 0., L"默认构造函数");
			Assert::IsTrue(_a.Y() == 0., L"默认构造函数");

			Vector2 _b(x, y);
			Assert::IsTrue(_b.X() == x, L"(x, y)构造函数");
			Assert::IsTrue(_b.Y() == y, L"(x, y)构造函数");

			Vector2 _c(x);
			Assert::IsTrue(_c.X() == x, L"(scalar)构造函数");
			Assert::IsTrue(_c.Y() == x, L"(scalar)构造函数");

			Vector2 _d(103., 201.);
			_a = _d;
			Assert::AreEqual(_a.X(), _d.X(), L"等号赋值");
			Assert::AreEqual(_a.Y(), _d.Y(), L"等号赋值");

			Vector2 _e(_d);
			Assert::AreEqual(_e.X(), _d.X(), L"复制构造函数");
			Assert::AreEqual(_e.Y(), _d.Y(), L"复制构造函数");
		}
		TEST_METHOD(SetAndGet)
		{
			Vector2 _a;
			_a.SetX(100.);
			Assert::AreEqual(_a.X(), 100., L"SetX");
			Assert::AreEqual(_a.Width(), 100., L"SetX");
			_a.SetY(200.);
			Assert::AreEqual(_a.Y(), 200., L"SetY");
			Assert::AreEqual(_a.Height(), 200., L"SetY");
			_a.Set(100.);
			Assert::AreEqual(_a.X(), 100., L"Set(scalar)");
			Assert::AreEqual(_a.Y(), 100., L"Set(scalar)");
			_a.Set(100., 200.);
			Assert::AreEqual(_a.X(), 100., L"Set(x,y)");
			Assert::AreEqual(_a.Y(), 200., L"Set(x,y)");
			_a.SetWidth(100.);
			Assert::AreEqual(_a.X(), 100., L"SetWidth");
			_a.SetHeight(200.);
			Assert::AreEqual(_a.Y(), 200., L"SetHeight");
		}
		TEST_METHOD(SetGetComponent)
		{
			Vector2 _v;
			_v[0] = x;
			_v[1] = y;

			Assert::IsTrue(_v[0] == x, L"SetGetComponent 0");
			Assert::IsTrue(_v[1] == y, L"SetGetComponent 1");
		}
		TEST_METHOD(Add)
		{
			Vector2 _a(x, y);
			Vector2 _b(-x, -y);
			_a += _b;
			AssetAlmosetEqules(_a.X(), 0., L"+=");
			AssetAlmosetEqules(_a.Y(), 0., L"+=");

			_a.Set(x, y);
			_a += _a;
			AssetAlmosetEqules(_a.X(), x * 2., L"+= 加上自己");
			AssetAlmosetEqules(_a.Y(), y * 2., L"+= 加上自己");

			_a = _b + _b;
			AssetAlmosetEqules(_a.X(), 2. * -x, L"+");
			AssetAlmosetEqules(_a.Y(), 2. * -y, L"+");

			_b += x;
			AssetAlmosetEqules(_b.X(), 0., L"+= scalar");
			AssetAlmosetEqules(_b.Y(), x - y, L"+= scalar");

			_a = _b + x;
			AssetAlmosetEqules(_a.X(), _b.X() + x, L"+ scalar");
			AssetAlmosetEqules(_a.Y(), _b.Y() + x, L"+ scalar");

			_a = x + _b;
			AssetAlmosetEqules(_a.X(), _b.X() + x, L"scalar +");
			AssetAlmosetEqules(_a.Y(), _b.Y() + x, L"scalar +");
		}
		TEST_METHOD(Sub)
		{
			Vector2 _a(x, y);
			Vector2 _b(x, y);
			_a -= _b;
			AssetAlmosetEqules(_a.X(), 0., L"-=");
			AssetAlmosetEqules(_a.Y(), 0., L"-=");

			_a.Set(x, y);
			_a -= _a;
			AssetAlmosetEqules(_a.X(), 0., L"-= 减去自己");
			AssetAlmosetEqules(_a.Y(), 0., L"-= 减去自己");

			_a.Set(3.278, 4.876);
			_b = _a;
			_a -= x;
			AssetAlmosetEqules(_a.X(), _b.X() - x, L"-= scalar");
			AssetAlmosetEqules(_a.Y(), _b.Y() - x, L"-= scalar");

			Vector2 _c(0.987, 2.876);
			_a = _b - _c;
			AssetAlmosetEqules(_a.X(), _b.X() - _c.X(), L"-");
			AssetAlmosetEqules(_a.Y(), _b.Y() - _c.Y(), L"-");

			_a = _b - x;
			AssetAlmosetEqules(_a.X(), _b.X() - x, L"- scalar");
			AssetAlmosetEqules(_a.Y(), _b.Y() - x, L"- scalar");
		}
		TEST_METHOD(Multiply)
		{
			Vector2 _a(x, y);
			Vector2 _b(88., 22.);
			_a *= _b;
			AssetAlmosetEqules(_a.X(), x * _b.X(), L"*=");
			AssetAlmosetEqules(_a.Y(), y * _b.Y(), L"*=");

			_b = _a;
			_a *= x;
			AssetAlmosetEqules(_a.X(), x * _b.X(), L"*= scalar");
			AssetAlmosetEqules(_a.Y(), x * _b.Y(), L"*= scalar");

			Vector2 _c(20., 101.58);
			_a = _b * _c;
			AssetAlmosetEqules(_a.X(), _b.X() * _c.X(), L"*");
			AssetAlmosetEqules(_a.Y(), _b.Y() * _c.Y(), L"*");

			_a = _c * _b;
			AssetAlmosetEqules(_a.X(), _b.X() * _c.X(), L"*");
			AssetAlmosetEqules(_a.Y(), _b.Y() * _c.Y(), L"*");

			_a = _b * x;
			AssetAlmosetEqules(_a.X(), _b.X() * x, L"* scalar");
			AssetAlmosetEqules(_a.Y(), _b.Y() * x, L"* scalar");

			_a = x * _b;
			AssetAlmosetEqules(_a.X(), _b.X() * x, L"scalar *");
			AssetAlmosetEqules(_a.Y(), _b.Y() * x, L"scalar *");
		}
		TEST_METHOD(Divide)
		{
			Vector2 _a(x, y);
			Vector2 _b(0.328, 0.254);
			_a /= _b;
			AssetAlmosetEqules(_a.X(), x / _b.X(), L"/=");
			AssetAlmosetEqules(_a.Y(), y / _b.Y(), L"/=");

			// /= vector2
			{
				const string _divideVecZeroErrorStr = "Vector2 operator/=(Vector2) 除0操作";

				try
				{
					_a /= zero2;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _divideVecZeroErrorStr.c_str(), L"/= zero2");
				}

				try
				{
					Vector2 _b(x, 0.);
					_a /= _b;
				}
				
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _divideVecZeroErrorStr.c_str(), L"/= 被除向量中x分量为0");
				}

				try
				{
					Vector2 _b(0., y);
					_a /= _b;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _divideVecZeroErrorStr.c_str(), L"/= 被除向量中y分量为0");
				}
			}

			// /= scalar
			{
				_b = _a;
				_a /= x;
				AssetAlmosetEqules(_a.X(), _b.X() / x, L"/=scalar");
				AssetAlmosetEqules(_a.Y(), _b.Y() / x, L"/=scalar");

				const string _devideScalarZeroErrorStr = "Vector2 operator/=(double) 除0操作";
				try
				{
					_a /= 0.;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _devideScalarZeroErrorStr.c_str(), L"/= 0.");
				}
			}

			Vector2 _c(0.287, 7.652);
			// / vector2
			{
				_b.Set(0.328, 0.254);

				_a = _b / _c;
				AssetAlmosetEqules(_a.X(), _b.X() / _c.X(), L"/");

				const string _dividedVecZeroErrorStr = "Vector2 operator/(Vector2) 除0操作";
				try
				{
					_a = _b / zero2;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _dividedVecZeroErrorStr.c_str(), L"/ zero2");
				}

				try
				{
					_c.Set(0., y);
					_a = _b / _c;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _dividedVecZeroErrorStr.c_str(), L"/ 向量中的x分量为0");
				}

				try
				{
					_c.Set(x, 0.);
					_a = _b / _c;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _dividedVecZeroErrorStr.c_str(), L"/ 向量中的y分量为0");
				}
			}

			// / scalar
			{
				_b.Set(7.327, 6.987);
				_a = _b / x;
				AssetAlmosetEqules(_a.X(), _b.X() / x, L"/ scalar");

				const string _devidedScalarZeroErrorStr = "Vector2 operator/=(double) 除0操作";
				try
				{
					_a = _b / 0.;
				}
				catch (const exception & e)
				{
					Assert::AreEqual(e.what(), _devidedScalarZeroErrorStr.c_str(), "/ 0.");
				}
			}
		}
		TEST_METHOD(Apply)
		{
			Vector2 _a(x, y);
			const Matrix3 _m(2., 3., 5., 7., 11., 13., 17., 19., 23.);
			_a.Apply(_m);

			AssetAlmosetEqules(_a.X(), 18., L"Apply(Matrix3)");
			AssetAlmosetEqules(_a.Y(), 60., L"Apply(Matrix3)");

			const Vector2 _b(x, y);
			_a = _b.Applied(_m);
			AssetAlmosetEqules(_a.X(), 18., L"Applied(Matrix3)");
			AssetAlmosetEqules(_a.Y(), 60., L"Applied(Matrix3)");
		}
		TEST_METHOD(MinMax)
		{
			Vector2 _a(x, y);
			Vector2 _b(x - 1., y + 1.);
			_a.Min(_b);
			AssetAlmosetEqules(_a.X(), x - 1., L"Min");
			AssetAlmosetEqules(_a.Y(), y, L"Min");

			_a.Set(x, y);
			_a.Max(_b);
			AssetAlmosetEqules(_a.X(), x, L"Max");
			AssetAlmosetEqules(_a.Y(), y + 1, L"Max");

			_a.Set(x, y);
			Vector2 _c = _a.Mined(_b);
			AssetAlmosetEqules(_c.X(), _b.X(), L"Mined");
			AssetAlmosetEqules(_c.Y(), _a.Y(), L"Mined");

			_c = _a.Maxed(_b);
			AssetAlmosetEqules(_c.X(), _a.X(), L"Maxed");
			AssetAlmosetEqules(_c.Y(), _b.Y(), L"Maxed");
		}
		TEST_METHOD(Clamp)
		{
			// clamp vector2
			{
				const Vector2 _min(-100., -200);
				const Vector2 _max(100., 200.);
				Vector2 _a(10., 20.);
				Vector2 _c;

				_a.Clamp(_min, _max);
				AssetAlmosetEqules(_a.X(), 10., L"Clamp in");
				AssetAlmosetEqules(_a.Y(), 20., L"Clamp in");

				_a.Set(-150, -250.);
				_a.Clamp(_min, _max);
				AssetAlmosetEqules(_a.X(), -100., L"Clamp less");
				AssetAlmosetEqules(_a.Y(), -200., L"Clamp less");

				_a.Set(101., 201.);
				_a.Clamp(_min, _max);
				AssetAlmosetEqules(_a.X(), 100., L"Clamp large");
				AssetAlmosetEqules(_a.Y(), 200., L"Clamp large");

				_a.Set(10., 20.);
				_c = _a.Clamped(_min, _max);
				AssetAlmosetEqules(_c.X(), 10., L"Clamped in");
				AssetAlmosetEqules(_c.Y(), 20., L"Clamped in");

				_a.Set(-150, -250.);
				_c = _a.Clamped(_min, _max);
				AssetAlmosetEqules(_c.X(), -100., L"Clamped lesser");
				AssetAlmosetEqules(_c.Y(), -200., L"Clamped lesser");

				_a.Set(101., 201.);
				_c = _a.Clamped(_min, _max);
				AssetAlmosetEqules(_c.X(), 100., L"Clamped greater");
				AssetAlmosetEqules(_c.Y(), 200., L"Clamped greater");
			}

			// clamp scalar
			{
				const double _min = -100., _max = 200.;
				Vector2 _a(10., 20);
				Vector2 _c;

				_a.Clamp(_min, _max);
				AssetAlmosetEqules(_a.X(), 10., L"Clamp scalar in");
				AssetAlmosetEqules(_a.Y(), 20., L"Clamp scalar in");

				_a.Set(-101., -250.);
				_a.Clamp(_min, _max);
				AssetAlmosetEqules(_a.X(), -100., L"Clamp scalar lesser");
				AssetAlmosetEqules(_a.Y(), -100., L"Clamp scalar lesser");

				_a.Set(201., 260.);
				_a.Clamp(_min, _max);
				AssetAlmosetEqules(_a.X(), 200., L"Clamp scalar greater");
				AssetAlmosetEqules(_a.Y(), 200., L"Clamp scalar greater");

				_a.Set(10., 20.);
				_c = _a.Clamped(_min, _max);
				AssetAlmosetEqules(_c.X(), 10., L"Clamped scalar in");
				AssetAlmosetEqules(_c.Y(), 20., L"Clamped scalar in");

				_a.Set(-150, -250.);
				_c = _a.Clamped(_min, _max);
				AssetAlmosetEqules(_c.X(), -100., L"Clamped scalar lesser");
				AssetAlmosetEqules(_c.Y(), -100., L"Clamped scalar lesser");

				_a.Set(230., 201.);
				_c = _a.Clamped(_min, _max);
				AssetAlmosetEqules(_c.X(), 200., L"Clamped scalar greater");
				AssetAlmosetEqules(_c.Y(), 200., L"Clamped scalar greater");
			}

			// clamp length
			{
				const double _minLen = 3., _maxLen = 20;
				Vector2 _v(4, 8);
				Vector2 _v1;
				double _preLen = _v.Length();

				_v.ClampLength(_minLen, _maxLen);
				AssetAlmosetEqules(_v.Length(), _preLen, L"ClampLength in");

				_v.Set(-2., -1.);
				_preLen = _v.Length();
				_v.ClampLength(_minLen, _maxLen);
				Assert::IsTrue(_preLen < _v.Length(), L"ClampLength lesser");
				AssetAlmosetEqules(_v.Length(), _minLen, L"ClampLength lesser");

				_v.Set(20., 30.);
				_preLen = _v.Length();
				_v.ClampLength(_minLen, _maxLen);
				Assert::IsTrue(_preLen > _v.Length(), L"ClampLength greater");
				AssetAlmosetEqules(_v.Length(), _maxLen, L"ClampLenght greater");

				_v.Set(4., 8.);
				_v1 = _v.ClampedLength(_minLen, _maxLen);
				AssetAlmosetEqules(_v1.Length(), _v.Length(), L"ClampedLength in");

				_v.Set(-2., -1.);
				_v1 = _v.ClampedLength(_minLen, _maxLen);
				AssetAlmosetEqules(_v1.Length(), _minLen, L"ClampedLength lesser");

				_v.Set(20., 30.);
				_v1 = _v.ClampedLength(_minLen, _maxLen);
				AssetAlmosetEqules(_v1.Length(), _maxLen, L"ClampedLength greater");
			}
		}
		TEST_METHOD(Floor)
		{
			Vector2 _v(-5.765, 8.654);
			_v.Floor();
			AssetAlmosetEqules(_v.X(), -6., L"Floor");
			AssetAlmosetEqules(_v.Y(), 8., L"Floor");

			_v.Set(-5.765, 8.654);
			Vector2 _v1 = _v.Floored();
			AssetAlmosetEqules(_v1.X(), -6., L"Floored");
			AssetAlmosetEqules(_v1.Y(), 8., L"Floored");
		}
		TEST_METHOD(Ceil)
		{
			Vector2 _v(-5.765, 8.654);
			_v.Ceil();
			AssetAlmosetEqules(_v.X(), -5., L"Ceil");
			AssetAlmosetEqules(_v.Y(), 9., L"Ceil");

			_v.Set(-5.765, 8.654);
			Vector2 _v1 = _v.Ceiled();
			AssetAlmosetEqules(_v1.X(), -5., L"Ceiled");
			AssetAlmosetEqules(_v1.Y(), 9., L"Ceilder");
		}
		TEST_METHOD(Round)
		{
			Vector2 _v(-5.5 - FLT_EPSILON, 5.5 + FLT_EPSILON);
			_v.Round();
			AssetAlmosetEqules(_v.X(), -6., L"Round");
			AssetAlmosetEqules(_v.Y(), 6., L"Round");

			_v.Set(-5.5 + FLT_EPSILON, 5.5 - FLT_EPSILON);
			_v.Round();
			AssetAlmosetEqules(_v.X(), -5., L"Round");
			AssetAlmosetEqules(_v.Y(), 5., L"Round");

			_v.Set(-5.50 - FLT_EPSILON, 5.5 + FLT_EPSILON);
			Vector2 _v1 = _v.Rounded();
			AssetAlmosetEqules(_v1.X(), -6., L"Rounded");
			AssetAlmosetEqules(_v1.Y(), 6., L"Rounded");

			_v.Set(-5.50 + FLT_EPSILON, 5.5 - FLT_EPSILON);
			_v1 = _v.Rounded();
			AssetAlmosetEqules(_v1.X(), -5., L"Rounded");
			AssetAlmosetEqules(_v1.Y(), 5., L"Rounded");
		}
		TEST_METHOD(RoundToZero)
		{
			Vector2 _v(-6.782, 8.782);
			_v.RoundToZero();
			AssetAlmosetEqules(_v.X(), -6., L"RoundToZero");
			AssetAlmosetEqules(_v.Y(), 8., L"RoundToZero");

			_v.Set(-6.782, 8.782);
			Vector2 _v1 = _v.RoundedToZero();
			AssetAlmosetEqules(_v1.X(), -6., L"RoundedToZero");
			AssetAlmosetEqules(_v1.Y(), 8., L"RoundedToZero");
		}
		TEST_METHOD(Negate)
		{
			Vector2 _v(9.2, 10.8);
			_v.Negate();
			AssetAlmosetEqules(_v.X(), -9.2, L"Negate");
			AssetAlmosetEqules(_v.Y(), -10.8, L"Negate");

			_v.Set(9.2, 10.8);
			Vector2 _v1 = -_v;
			AssetAlmosetEqules(_v1.X(), -9.2, L"Negated");
			AssetAlmosetEqules(_v1.Y(), -10.8, L"Negated");
		}
		TEST_METHOD(Dot)
		{
			Vector2 _v(3.234, 4.908);
			Vector2 _v1(-8.987, 2.324);

			double _d = _v.Dot(_v1);
			AssetAlmosetEqules(_d, _v1.X() * _v.X() + _v1.Y() * _v.Y(), L"Dot");
			_d = _v1.Dot(_v);
			AssetAlmosetEqules(_d, _v1.X() * _v.X() + _v1.Y() * _v.Y(), L"Dot");
		}
		TEST_METHOD(Cross)
		{
			Vector2 _v(4.0329, 5.09823);
			Vector2 _v1(-8.898, 4.321);
			double _cross = _v.Cross(_v1);
			AssetAlmosetEqules(_cross, 4.0329 * 4.321 + 8.898 * 5.09823, L"Cross");
			_cross = _v1.Cross(_v);
			AssetAlmosetEqules(_cross, -4.0329 * 4.321 - 8.898 * 5.09823, L"Cross");
		}
		TEST_METHOD(LengthSq)
		{
			Vector2 _v(x, y);
			AssetAlmosetEqules(_v.LengthSq(), x * x + y * y, L"LengthSq");
		}
		TEST_METHOD(Length)
		{
			Vector2 _v(x, y);
			AssetAlmosetEqules(_v.Length(), sqrt(x * x + y * y), L"Length");
		}
		TEST_METHOD(ManhattanLength)
		{
			Vector2 _v(-x, y);
			AssetAlmosetEqules(_v.ManhattanLength(), x + y, L"ManhattanLength");
		}
		TEST_METHOD(Normalize)
		{
			Vector2 _v;
			_v.Normalize();
			Assert::IsTrue(_v.Equals(Vector2()), L"Normalize Zero Vector2");

			_v.Set(x, y);
			_v.Normalize();
			AssetAlmosetEqules(_v.Length(), 1., L"Normalize Length == 1.");
			Assert::IsTrue(_v.Equals(Vector2(x / sqrt(x * x + y * y), y / sqrt(x * x + y * y))), L"Normalize");

			_v.Set(0., 0.);
			Vector2 _v1 = _v.Normalized();
			Assert::IsTrue(_v1.Equals(Vector2()), L"Normalizeed Zero Vector2");

			_v.Set(x, y);
			_v1 = _v.Normalized();
			AssetAlmosetEqules(_v1.Length(), 1., L"Normalized Length == 1.");
			Assert::IsTrue(_v1.Equals(Vector2(x / sqrt(x * x + y * y), y / sqrt(x * x + y * y))), L"Normalized");
		}
		TEST_METHOD(Angle)
		{
			Vector2 _v(1., 0.);
			AssetAlmosetEqules(_v.Angle(), 0., L"Angle 0");

			_v.Set(sqrt(0.5), sqrt(0.5));
			AssetAlmosetEqules(_v.Angle(), M_PI_4, L"Angle pi / 4");

			_v.Set(0., 1.);
			AssetAlmosetEqules(_v.Angle(), M_PI_2, L"Angle pi / 2");

			_v.Set(-1., 0.);
			AssetAlmosetEqules(_v.Angle(), M_PI, L"Angle pi");

			_v.Set(0., -1.);
			AssetAlmosetEqules(_v.Angle(), M_PI * 3. / 2., L"Angle pi * 3 / 2");
		}
		TEST_METHOD(DistanceTo)
		{
			Vector2 _v(1., 1.);
			Vector2 _v1(2., 2.);
			AssetAlmosetEqules(_v.DistanceTo(_v1), sqrt(2.), L"DistanceTo");
		}
		TEST_METHOD(DistanceToSquared)
		{
			Vector2 _v(1., 1.);
			Vector2 _v1(2., 2.);
			AssetAlmosetEqules(_v.DistanceToSquared(_v1), 2., L"DistanceToSquared");
		}
		TEST_METHOD(ManhattanDistanceTo)
		{
			Vector2 _v(10., 20.);
			Vector2 _v1(-30., 40.);
			AssetAlmosetEqules(_v.ManhattanDistanceTo(_v1), 60., L"ManhattanDistanceTo");
		}
		TEST_METHOD(SetLength)
		{
			Vector2 _v(1., 0.);
			AssetAlmosetEqules(_v.Length(), 1., L"SetLength");
			_v.SetLength(y);
			AssetAlmosetEqules(_v.Length(), y, L"SetLength");
			_v.Set(0., 0.);
			AssetAlmosetEqules(_v.Length(), 0., L"SetLength");
			_v.SetLength(y);
			AssetAlmosetEqules(_v.Length(), 0., L"SetLength");
			_v.Set(nanDouble);
			Assert::IsTrue(MathUtil::IsNan(_v.Length()), L"SetLength NaN");
		}
		TEST_METHOD(Lerp)
		{
			Vector2 _v(1.0, 0.);
			Vector2 _v1(x, y);
			_v.Lerp(_v1, 0.85);
			AssetAlmosetEqules(_v.X(), 1.0 + (x - 1.0) * 0.85, L"Lerp");
			AssetAlmosetEqules(_v.Y(), y * 0.85, L"Lerp");

			_v.Set(1., 0.);
			Vector2 _v2 = _v.Lerped(_v1, 0.85);
			AssetAlmosetEqules(_v2.X(), 1.0 + (x - 1.0) * 0.85, L"Lerped");
			AssetAlmosetEqules(_v2.Y(), y * 0.85, L"Lerped");
		}
		TEST_METHOD(Equals)
		{
			Vector2 _v;
			Assert::IsTrue(_v.Equals(Vector2()), L"Equals");
			Assert::IsTrue(_v == Vector2(), L"Equals");
			Assert::IsFalse(_v == Vector2(1.), L"Equals");
			_v.Set(0.3, 0.2);
			Assert::IsTrue(_v == Vector2(0.3 + MathUtil::EPSILION, 0.2 + MathUtil::EPSILION), L"Equals");
		}
		TEST_METHOD(RotateRound)
		{
			Vector2 _c(-1., 0.);
			Vector2 _v(1., 0.);
			_v.RotateAround(_c, M_PI_2);
			Assert::IsTrue(_v == Vector2(-1, 2.), L"RotateRound");

			Vector2 _v2 = _v.RotatedAround(_c, M_PI_2);
			Assert::IsTrue(_v2 == Vector2(-3., 0.), L"RotatedRound");
		}
		TEST_METHOD(ToJson)
		{
			Vector2 _v(1., 0.);
			stringstream _ss;
			_ss << _v;
			string json = _ss.str();
			Assert::IsTrue(json == "{type:'Vector2',x:1,y:0}", L"operotor<<");
		}
	};
}