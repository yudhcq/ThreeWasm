#include <CppUnitTest.h>
#include <iostream>
#include <sstream>

#include "../TestConstants.h"
#include "../../src//Math/Vector3.h"
#include "../../src/Math//Vector4.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three::Math;

namespace ThreeUnitTest
{
	TEST_CLASS(Vector3UintTest)
	{
		TEST_METHOD(Instancing)
		{
			Vector3 _v;
			Assert::IsTrue(_v == Vector3(0.), L"Instancing默认构造函数");
			Vector3 _v1(1.);
			Assert::IsTrue(_v1 == Vector3(1., 1., 1.), L"Instancing scalar构造函数");
			Vector3 _v2(1., 2., 3.);
			AssetAlmosetEqules(_v2.X(), 1., L"Instancing x");
			AssetAlmosetEqules(_v2.Y(), 2., L"Instancing y");
			AssetAlmosetEqules(_v2.Z(), 3., L"Instancing z");
		}
		TEST_METHOD(SetGet)
		{
			Vector3 _v;
			_v.SetX(1.);
			AssetAlmosetEqules(1., _v.X(), L"SetX GetX");
			_v.SetY(2.);
			AssetAlmosetEqules(2., _v.Y(), L"SetY GetY");
			_v.SetZ(3.);
			AssetAlmosetEqules(3., _v.Z(), L"SetZ GetZ");
			_v.Set(0.);
			Assert::IsTrue(_v == Vector3(0.), L"Set scalar");
			_v.Set(1.0, 2.0, 3.0);
			Assert::IsTrue(_v == Vector3(1., 2., 3.), L"Set");
		}
		TEST_METHOD(SetGetComponent)
		{
			Vector3 _v;
			_v[0] = 1.;
			AssetAlmosetEqules(1, _v.X(), L"SetComponent 0");
			AssetAlmosetEqules(_v[0], _v.X(), L"SetComponent 0");
			_v[1] = 2.;
			AssetAlmosetEqules(2., _v.Y(), L"SetComponent 1");
			AssetAlmosetEqules(_v[1], _v.Y(), L"SetComponent 1");
			_v[2] = 3.;
			AssetAlmosetEqules(3., _v.Z(), L"SetComponent 2");
			AssetAlmosetEqules(_v[2], _v.Z(), L"SetComponent 2");
			try
			{
				double _value = _v[3];
			}
			catch (const std::exception& e)
			{
				Assert::IsTrue(e.what() == "Vector3 operator[] 下标超出索引", L"SetComponent 3");
			}
		}
		TEST_METHOD(Equals)
		{
			Vector3 _v;
			Assert::IsTrue(_v.Equals(Vector3(0.)), L"Equles");
			Assert::IsFalse(_v.Equals(Vector3(0., 0., 2.)), L"Equles");
			_v.Set(1., 2., 3.);
			Assert::IsTrue(_v == Vector3(1. + MathUtil::EPSILION, 
				2. + MathUtil::EPSILION, 
				3. + MathUtil::EPSILION));
		}
		TEST_METHOD(Add)
		{
			Vector3 _v(x, y, z);
			Vector3 _v1(-x, -y, -z);
			_v += _v1;
			Assert::IsTrue(_v == Vector3(), L"+=");
			_v = _v1 + x;
			Assert::IsTrue(_v == Vector3(0., x - y, x - z), L"+ scalar");
			_v = _v1 + _v1;
			Assert::IsTrue(_v == Vector3(2. * -x, 2. * -y, 2. * -z), L"+");
		}
		TEST_METHOD(Sub)
		{
			Vector3 _v(x, y, z);
			Vector3 _v1(x, y, z);
			_v -= _v1;
			Assert::IsTrue(_v == Vector3(), L"-=");
			_v = _v1 - Vector3(x);
			Assert::IsTrue(_v == Vector3(0., y - x, z - x), L"-");
			_v = _v1 - y;
			Assert::IsTrue(_v == Vector3(x - y, 0., z - y), L"- scalar");
		}
		TEST_METHOD(Multipy)
		{
			Vector3 _v(x, y, z);
			Vector3 _v1(y, x, z);
			_v *= _v1;
			Assert::IsTrue(_v == Vector3(x * y, x * y, z * z), L"*=");
			_v = _v1 * _v1;
			Assert::IsTrue(_v == Vector3(y * y, x * x, z * z), L"*");
			_v = _v1 * x;
			Assert::IsTrue(_v == Vector3(x * y, x * x, z * x), L"*scalar");
		}
		TEST_METHOD(Divide)
		{
			Vector3 _v(x, y, z);
			Vector3 _v1(x, y, z);
			_v /= _v1;
			Assert::IsTrue(_v == Vector3(1.), L"/=");
			_v = _v / _v1;
			Assert::IsTrue(_v == Vector3(1. / x, 1. / y, 1. / z), L"/");
			_v = _v1 / x;
			Assert::IsTrue(_v == Vector3(1., y / x, z / x), L"/ scalar");
		}
		TEST_METHOD(ApplyEuler)
		{
			Vector3 _v(x, y, z);
			Euler _e(90., -45., 0.);
			Vector3 _expected(-2.352970120501014, -4.7441750936226645, 0.9779234597246458);
			_v.Apply(_e);
			Assert::IsTrue(_v == _expected, L"Apply Euler");
			_v.Set(x, y, z);
			Assert::IsTrue(_v.Applied(_e) == _expected, L"Applied Euler");
		}
		TEST_METHOD(ApplyAxisAngle)
		{
			Vector3 _v(x, y ,z);
			const Vector3 _axis(0., 1., 0.);
			const double _angle = M_PI_4;
			const Vector3 _expected(3. * sqrt(2.), 3., sqrt(2.));
			_v.Apply(_axis, _angle);
			Assert::IsTrue(_v == _expected, L"Apply Axis Angle");
			_v.Set(x, y, z);
			Assert::IsTrue(_v.Applied(_axis, _angle) == _expected, L"Applied Axis Angle");
		}
		TEST_METHOD(ApplyMatrix3)
		{
			Vector3 _v(x, y, z);
			Matrix3 _m(2., 3., 5., 7., 11., 13., 17., 19., 23.);
			_v.Apply(_m);
			Assert::IsTrue(_v == Vector3(33., 99., 183), L"Apply Matrix3");
			_v.Set(x, y, z);
			Assert::IsTrue(_v.Applied(_m) == Vector3(33., 99., 183), L"Applied Matrix3");
		}
		TEST_METHOD(ApplyMatrix4)
		{
			Vector3 _v(x, y, z);
			Vector4 _v4(x, y, z, 1.);
			Matrix4 _m;
			
			_m.MakeRotationX(M_PI);
			_v4.Apply(_m);
			Assert::IsTrue(_v.Applied(_m) == Vector3(_v4[0] / _v4[3], _v4[1] / _v4[3], _v4[2] / _v4[3]), L"ApplyMatrix4");
			_v.Apply(_m);
			Assert::IsTrue(_v == Vector3(_v4[0] / _v4[3], _v4[1] / _v4[3], _v4[2] / _v4[3]), L"AppliedMatrix4");
			
			_m.MakeTranslation(3., 2., 1.);
			_v4.Apply(_m);
			Assert::IsTrue(_v.Applied(_m) == Vector3(_v4[0] / _v4[3], _v4[1] / _v4[3], _v4[2] / _v4[3]), L"ApplyMatrix4");
			_v.Apply(_m);
			Assert::IsTrue(_v == Vector3(_v4[0] / _v4[3], _v4[1] / _v4[3], _v4[2] / _v4[3]), L"ApplyMatrix4");
			
			_m.Set(1., 0., 0., 0.,
				   0., 1., 0., 0.,
				   0., 0., 1., 0.,
				   0., 0., 1., 0.);
			_v4.Apply(_m);
			Assert::IsTrue(_v.Applied(_m) == Vector3(_v4[0] / _v4[3], _v4[1] / _v4[3], _v4[2] / _v4[3]), L"ApplyMatrix4");
			_v.Apply(_m);
			Assert::IsTrue(_v == Vector3(_v4[0] / _v4[3], _v4[1] / _v4[3], _v4[2] / _v4[3]), L"ApplyMatrix4");
		}
		TEST_METHOD(ApplyQuaternion)
		{
			Vector3 _v(x, y, z);
			Assert::IsTrue(_v.Applied(Quaternion()) == Vector3(x, y, z), L"AppliedQuaternion");
			_v.Apply(Quaternion());
			Assert::IsTrue(_v == Vector3(x, y, z), L"ApplyQuaternion");
			Assert::IsTrue(_v.Applied(Quaternion(x, y, z, w)) == Vector3(108., 162., 216.), L"AppliedQuaternion");
			_v.Apply(Quaternion(x, y, z, w));
			Assert::IsTrue(_v == Vector3(108., 162., 216.), L"ApplyQuaternion");
		}
		TEST_METHOD(Project)
		{
			cout << "project todo" << endl;
		}
		TEST_METHOD(Unproject)
		{
			cout << "unproject todo" << endl;
		}
		TEST_METHOD(MinMax)
		{
			Vector3 _v(x, y, z);
			Vector3 _v1(-2., 4., -5.);
			Assert::IsTrue(_v.Mined(_v1) == Vector3(-2., y, -5.), L"Mined");
			_v.Min(_v1);
			Assert::IsTrue(_v == Vector3(-2., y, -5.), L"Min");

			_v.Set(x, y, z);
			Assert::IsTrue(_v.Maxed(_v1) == Vector3(x, 4., z), L"Maxed");
			_v.Max(_v1);
			Assert::IsTrue(_v == Vector3(x, 4., z), L"Maxed");
		}
		TEST_METHOD(Clamp)
		{
			Vector3 _v(x, y, z);
			const Vector3 _min(0., 3., 1.), _max(2., 5., 2.);
			const double _minVal = x + 0.5, _maxVal = z - 0.5;

			Assert::IsTrue(_v.Clamped(_min, _max) == Vector3(x, 3., 2.), L"Clamped Vector3");
			_v.Clamp(_min, _max);
			Assert::IsTrue(_v == Vector3(x, 3., 2.), L"Clamp Vector3");

			_v.Set(x, y, z);
			Assert::IsTrue(_v.Clamped(_minVal, _maxVal) == Vector3(x + 0.5, y, z - 0.5), L"Clamped Scalar");
			_v.Clamp(_minVal, _maxVal);
			Assert::IsTrue(_v.Clamped(_minVal, _maxVal) == Vector3(x + 0.5, y, z - 0.5), L"Clamp Scalar");
		}
		TEST_METHOD(ClampLength)
		{
			Vector3 _v(x, y, z);
			const double _vLen = _v.Length();
			Vector3 _v1 = _v.ClampedLength(1., 10.);
			AssetAlmosetEqules(_v1.Length(), _vLen, L"ClampedLengh");
			_v1 = _v.ClampedLength(6., 10.);
			AssetAlmosetEqules(_v1.Length(), 6., L"ClampedLengh");
			_v1 = _v.ClampedLength(1., 2.);
			AssetAlmosetEqules(_v1.Length(), 2., L"ClampedLengh");
			_v.ClampLength(1, 10);
			AssetAlmosetEqules(_v.Length(), _vLen, L"ClampLength");
			_v.ClampLength(6., 10.);
			AssetAlmosetEqules(_v.Length(), 6., L"ClampLength");
			_v.Set(x, y, z);
			_v.ClampLength(1., 2.);
			AssetAlmosetEqules(_v.Length(), 2., L"ClampLength");
		}
		TEST_METHOD(Floor)
		{
			Vector3 _v(-5.765, 8.654, 9.362);
			_v.Floor();
			AssetAlmosetEqules(_v.X(), -6., L"Floor");
			AssetAlmosetEqules(_v.Y(), 8., L"Floor");
			AssetAlmosetEqules(_v.Z(), 9., L"Floor");

			_v.Set(-5.765, 8.654, 9.362);
			Vector3 _v1 = _v.Floored();
			AssetAlmosetEqules(_v1.X(), -6., L"Floored");
			AssetAlmosetEqules(_v1.Y(), 8., L"Floored");
			AssetAlmosetEqules(_v1.Z(), 9., L"Floored");
		}
		TEST_METHOD(Ceil)
		{
			Vector3 _v(-5.765, 8.654, 9.362);
			_v.Ceil();
			AssetAlmosetEqules(_v.X(), -5., L"Ceil");
			AssetAlmosetEqules(_v.Y(), 9., L"Ceil");
			AssetAlmosetEqules(_v.Z(), 10., L"Ceil");

			_v.Set(-5.765, 8.654, 9.362);
			Vector3 _v1 = _v.Ceiled();
			AssetAlmosetEqules(_v1.X(), -5., L"Ceiled");
			AssetAlmosetEqules(_v1.Y(), 9., L"Ceilder");
			AssetAlmosetEqules(_v1.Z(), 10., L"Ceilder");
		}
		TEST_METHOD(Round)
		{
			Vector3 _v(-5.5 - FLT_EPSILON, 5.5 + FLT_EPSILON, 9.5);
			_v.Round();
			AssetAlmosetEqules(_v.X(), -6., L"Round");
			AssetAlmosetEqules(_v.Y(), 6., L"Round");
			AssetAlmosetEqules(_v.Z(), 10., L"Round");

			_v.Set(-5.5 + FLT_EPSILON, 5.5 - FLT_EPSILON, 9.5);
			_v.Round();
			AssetAlmosetEqules(_v.X(), -5., L"Round");
			AssetAlmosetEqules(_v.Y(), 5., L"Round");
			AssetAlmosetEqules(_v.Z(), 10., L"Round");

			_v.Set(-5.50 - FLT_EPSILON, 5.5 + FLT_EPSILON, 9.5);
			Vector3 _v1 = _v.Rounded();
			AssetAlmosetEqules(_v1.X(), -6., L"Rounded");
			AssetAlmosetEqules(_v1.Y(), 6., L"Rounded");

			_v.Set(-5.50 + FLT_EPSILON, 5.5 - FLT_EPSILON, 9.5);
			_v1 = _v.Rounded();
			AssetAlmosetEqules(_v1.X(), -5., L"Rounded");
			AssetAlmosetEqules(_v1.Y(), 5., L"Rounded");
		}
		TEST_METHOD(RoundToZero)
		{
			Vector3 _v(-6.782, 8.782, 9.5);
			_v.RoundToZero();
			AssetAlmosetEqules(_v.X(), -6., L"RoundToZero");
			AssetAlmosetEqules(_v.Y(), 8., L"RoundToZero");
			AssetAlmosetEqules(_v.Z(), 9., L"RoundToZero");

			_v.Set(-6.782, 8.782, 9.5);
			Vector3 _v1 = _v.RoundedToZero();
			AssetAlmosetEqules(_v1.X(), -6., L"RoundedToZero");
			AssetAlmosetEqules(_v1.Y(), 8., L"RoundedToZero");
			AssetAlmosetEqules(_v1.Z(), 9., L"RoundedToZero");
		}

		TEST_METHOD(Negate)
		{
			Vector3 _v(x, y, z);
			_v.Negate();
			Assert::IsTrue(_v == Vector3(-x, -y, -z), L"Negate");
			Assert::IsTrue(-_v == Vector3(x, y, z), L"-");
		}
		TEST_METHOD(Dot)
		{
			Vector3 _v(x, y, z), _v1(-x, -y, -z), _v2;
			AssetAlmosetEqules(_v.Dot(_v1), (-x * x + -y * y + -z * z), L"Dot");
			AssetAlmosetEqules(_v.Dot(_v2), 0, L"Dot Zero3");
		}
		TEST_METHOD(LengthSq)
		{
			Vector3 _v(x, y, z);
			AssetAlmosetEqules(_v.LengthSq(), x * x + y * y + z * z, L"LengthSq");
		}
		TEST_METHOD(Length)
		{
			Vector3 _v(x, y, z);
			AssetAlmosetEqules(_v.Length(), sqrt(x * x + y * y + z * z), L"Length");
		}
		TEST_METHOD(ManhattanLength)
		{
			Vector3 _v(x, 0., 0.);
			Vector3 _v1(0, -y, 0.);
			Vector3 _v2(0, 0., z);
			Vector3 _v3;

			AssetAlmosetEqules(_v.Manhattanlength(), x, L"ManhattanLength");
			AssetAlmosetEqules(_v1.Manhattanlength(), y, L"ManhattanLength");
			AssetAlmosetEqules(_v2.Manhattanlength(), z, L"ManhattanLength");
			AssetAlmosetEqules(_v3.Manhattanlength(), 0, L"ManhattanLength");

			_v.Set(x, y, z);
			AssetAlmosetEqules(_v.Manhattanlength(), x + y + z, L"ManhattanLength");
		}
		TEST_METHOD(Normalize)
		{
			Vector3 _v(x, 0., 0.);
			Vector3 _v1(0, -y, 0.);
			Vector3 _v2(0, 0., z);

			AssetAlmosetEqules(_v.Normalized().Length(), 1., L"Normalized");
			_v.Normalize();
			AssetAlmosetEqules(_v.Length(), 1., L"Normaliz");
			AssetAlmosetEqules(_v.X(), 1., L"Normaliz");

			AssetAlmosetEqules(_v1.Normalized().Length(), 1., L"Normalized");
			_v1.Normalize();
			AssetAlmosetEqules(_v1.Length(), 1., L"Normaliz");
			AssetAlmosetEqules(_v1.Y(), -1., L"Normaliz");

			AssetAlmosetEqules(_v2.Normalized().Length(), 1., L"Normalized");
			_v2.Normalize();
			AssetAlmosetEqules(_v2.Length(), 1., L"Normaliz");
			AssetAlmosetEqules(_v2.Z(), 1., L"Normaliz");
		}
		TEST_METHOD(SetLength)
		{
			Vector3 _v(x, 0., 0.);
			AssetAlmosetEqules(_v.Length(), x, L"SetLength");
			_v.SetLength(y);
			AssetAlmosetEqules(_v.Length(), y, L"SetLength");

			_v.Set(0.);
			_v.SetLength(y);
			AssetAlmosetEqules(_v.Length(), 0., L"SetLength");
		}
		TEST_METHOD(Lerp)
		{
			Vector3 _v(1.0, 0., -1.);
			Vector3 _v1(x, y, z);
			_v.Lerp(_v1, 0.85);
			AssetAlmosetEqules(_v.X(), 1.0 + (x - 1.0) * 0.85, L"Lerp");
			AssetAlmosetEqules(_v.Y(), y * 0.85, L"Lerp");
			AssetAlmosetEqules(_v.Z(), -1. + (z + 1.) * 0.85, L"Lerp");

			_v.Set(1., 0., -1.);
			Vector3 _v2 = _v.Lerped(_v1, 0.85);
			AssetAlmosetEqules(_v2.X(), 1.0 + (x - 1.0) * 0.85, L"Lerped");
			AssetAlmosetEqules(_v2.Y(), y * 0.85, L"Lerped");
			AssetAlmosetEqules(_v2.Z(), -1. + (z + 1.) * 0.85, L"Lerp");
		}
		TEST_METHOD(Cross)
		{
			Vector3 _v(x, y, z);
			const Vector3 _v1(2 * x, -y, z / 2.);
			const Vector3 _v2(18., 12., -18.);

			Assert::IsTrue(_v.Crossed(_v1) == _v2, L"Crossed");
			_v.Cross(_v1);
			Assert::IsTrue(_v == _v2, L"Crossed");
		}
		TEST_METHOD(ProjectOnVector)
		{
			Vector3 _v(1., 0., 0.);
			Vector3 _normal(10., 0., 0.);
			Assert::IsTrue(_v.Projected(_normal) == Vector3(1., 0., 0.), L"ProjectedOnVector");
			_v.Set(0., 1., 0.);
			Assert::IsTrue(_v.Projected(_normal) == Vector3(0., 0., 0.), L"ProjectedOnVector");
			_v.Set(0., 0., -1.);
			Assert::IsTrue(_v.Projected(_normal) == Vector3(0., 0., 0.), L"ProjectedOnVector");
			_v.Set(-1., 0., 0.);
			Assert::IsTrue(_v.Projected(_normal) == Vector3(-1., 0., 0.), L"ProjectedOnVector");
		}
		TEST_METHOD(ProjectOnPlane)
		{
			Vector3 _v(1., 0., 0.);
			Plane _p(Vector3(1., 0., 0.), 0.);
			Assert::IsTrue(_v.Projected(_p) == Vector3(0., 0., 0.), L"ProjectedOnPlane");
			_v.Set(0., 1., 0.);
			Assert::IsTrue(_v.Projected(_p) == Vector3(0., 1., 0.), L"ProjectedOnPlane");
			_v.Set(0., 0., -1.);
			Assert::IsTrue(_v.Projected(_p) == Vector3(0., 0., -1.), L"ProjectedOnPlane");
			_v.Set(-1., 0., 0.);
			Assert::IsTrue(_v.Projected(_p) == Vector3(0., 0., 0.), L"ProjectedOnPlane");
		}
		TEST_METHOD(Reflect)
		{
			Plane _p(Vector3(0., 1., 0.), 0.);
			Vector3 _v(0., -1., 0.);
			Assert::IsTrue(_v.Reflected(_p) == Vector3(0., 1., 0.), L"Reflected");
			_v.Set(1., -1., 0.);
			Assert::IsTrue(_v.Reflected(_p) == Vector3(1., 1., 0.), L"Reflected");
			_v.Set(1., -1., 0.);
			_p.SetNormal(Vector3(0., -1., 0.));
			Assert::IsTrue(_v.Reflected(_p) == Vector3(1., 1., 0.), L"Reflected");
		}
		TEST_METHOD(AngleTo)
		{
			Vector3 _v(0, -0.18851655680720186, 0.9820700116639124);
			Vector3 _v1(0, 0.18851655680720186, -0.9820700116639124);
			AssetAlmosetEqules(_v.AngleTo(_v), 0., L"AngleTo");
			AssetAlmosetEqules(_v.AngleTo(_v1), M_PI, L"AngleTo");

			Vector3 _x(1., 0., 0.);
			Vector3 _y(0., 1., 0.);
			Vector3 _z(0., 0., 1.);
			AssetAlmosetEqules(_x.AngleTo(_y), M_PI_2, L"AngleTo");
			AssetAlmosetEqules(_x.AngleTo(_z), M_PI_2, L"AngleTo");
			AssetAlmosetEqules(_z.AngleTo(_x), M_PI_2, L"AngleTo");

			AssetAlmosetEqules(_x.AngleTo(Vector3(1., 1., 0.)), M_PI_4, L"AngleTo");
		}
		TEST_METHOD(DistanceTo)
		{
			Vector3 _v(1., 0., 0.);
			Vector3 _v1(0., 1., 0.);

			AssetAlmosetEqules(_v1.DistanceTo(_v), sqrt(2.), L"DistanceTo");
		}
		TEST_METHOD(DistanceToSquared)
		{
			Vector3 _v(1., 0., 0.);
			Vector3 _v1(0., 1., 0.);

			AssetAlmosetEqules(_v1.DistanceToSquared(_v), 2., L"DistanceToSquared");
		}
		TEST_METHOD(ManhattanDistanceTo)
		{
			Vector3 _v(1., 0., 0.);
			Vector3 _v1(0., 1., 1.);

			AssetAlmosetEqules(_v1.ManhattanDistanceTo(_v), 3., L"ManhattanDistanceTo");
		}
		TEST_METHOD(SetFromSpherical)
		{
			Vector3 _v;
			const double _phi = acos(-0.5);
			const double _theta = sqrt(M_PI) * _phi;
			Spherical _sph(10., _phi, _theta);
			Vector3 _expected(-4.677914006701843, -5., -7.288149322420796);
			_v.SetFromSpherical(_sph);
			Assert::IsTrue(_v == _expected, L"SetFromSpherical");
		}
		TEST_METHOD(SetFromCylindrical)
		{
			Vector3 _v;
			Cylindrical _cy(10., M_PI / 8., 20.);
			_v.SetFromCylindrical(_cy);
			Assert::IsTrue(_v == Vector3(3.826834323650898, 20, 9.238795325112868), L"SetFromCylindrical");
		}
		TEST_METHOD(SetFromMatrixPosition)
		{
			Vector3 _v;
			Matrix4 _m(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53);
			_v.SetFromMatrixPosition(_m);
			Assert::IsTrue(_v == Vector3(7., 19., 37), L"SetFromMatrixPosition");
		}
		TEST_METHOD(SetFromMatrixScale)
		{
			Vector3 _v;
			Matrix4 _m(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53);
			_v.SetFromMatrixScale(_m);
			Assert::IsTrue(_v == Vector3(25.573423705088842, 31.921779399024736, 35.70714214271425), L"SetFromMatrixScale");
		}
		TEST_METHOD(SetFromMatrixColumn)
		{
			Vector3 _v;
			Matrix4 _m(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53);
			_v.SetFromMatrixColumn(_m, 0);
			Assert::IsTrue(_v == Vector3(2., 11., 23), L"SetFromMatrixColumn index 0");
			_v.SetFromMatrixColumn(_m, 2);
			Assert::IsTrue(_v == Vector3(5., 17., 31), L"SetFromMatrixColumn index 2");
		}
		TEST_METHOD(ToJson)
		{
			Vector3 _v(2.,3.,4.);
			stringstream _ss;
			_ss << _v;
			Assert::IsTrue(_ss.str() == "{type:'Vector3',x:2,y:3,z:4}", L"ToJson");
		}
	};
}