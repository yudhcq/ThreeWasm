#include <CppUnitTest.h>
#include <sstream>
#include <vector>

#include "../TestConstants.h"
#include "../../src/Math/Matrix3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Three;
using namespace std;

namespace ThreeUnitTest
{
	Matrix4 ToMatrix4(const Matrix3 &matrix)
	{
		Matrix4 _res;
		_res[0] = matrix[0];
		_res[1] = matrix[1];
		_res[2] = matrix[2];
		_res[4] = matrix[3];
		_res[5] = matrix[4];
		_res[6] = matrix[5];
		_res[8] = matrix[6];
		_res[9] = matrix[7];
		_res[10] = matrix[8];
		return _res;
	}

	TEST_CLASS(Matrix3UnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Matrix3 _a;
			Assert::IsTrue(_a[0] == 1.);
			Assert::IsTrue(_a[1] == 0.);
			Assert::IsTrue(_a[2] == 0.);
			Assert::IsTrue(_a[3] == 0.);
			Assert::IsTrue(_a[4] == 1.);
			Assert::IsTrue(_a[5] == 0.);
			Assert::IsTrue(_a[6] == 0.);
			Assert::IsTrue(_a[7] == 0.);
			Assert::IsTrue(_a[8] == 1.);

			Matrix3 _b(0., 1., 2., 3., 4., 5., 6., 7., 8.);

			Assert::IsTrue(_b[0] == 0.);
			Assert::IsTrue(_b[1] == 3.);
			Assert::IsTrue(_b[2] == 6.);
			Assert::IsTrue(_b[3] == 1.);
			Assert::IsTrue(_b[4] == 4.);
			Assert::IsTrue(_b[5] == 7.);
			Assert::IsTrue(_b[6] == 2.);
			Assert::IsTrue(_b[7] == 5.);
			Assert::IsTrue(_b[8] == 8.);
		}
		TEST_METHOD(SetGet)
		{
			Matrix3 _a;
			Assert::IsTrue(_a[0] == 1.);
			Assert::IsTrue(_a[1] == 0.);
			Assert::IsTrue(_a[2] == 0.);
			Assert::IsTrue(_a[3] == 0.);
			Assert::IsTrue(_a[4] == 1.);
			Assert::IsTrue(_a[5] == 0.);
			Assert::IsTrue(_a[6] == 0.);
			Assert::IsTrue(_a[7] == 0.);
			Assert::IsTrue(_a[8] == 1.);

			_a.Set(0., 1., 2., 3., 4., 5., 6., 7., 8.);

			Assert::IsTrue(_a[0] == 0.);
			Assert::IsTrue(_a[1] == 3.);
			Assert::IsTrue(_a[2] == 6.);
			Assert::IsTrue(_a[3] == 1.);
			Assert::IsTrue(_a[4] == 4.);
			Assert::IsTrue(_a[5] == 7.);
			Assert::IsTrue(_a[6] == 2.);
			Assert::IsTrue(_a[7] == 5.);
			Assert::IsTrue(_a[8] == 8.);
		}
		TEST_METHOD(Identity)
		{
			Matrix3 _a;
			_a.Set(0., 1., 2., 3., 4., 5., 6., 7., 8.);
			Assert::IsTrue(!_a.IsIdentity());
			_a.Identity();
			Assert::IsTrue(_a.IsIdentity());
		}
		TEST_METHOD(SetFromMatrix4)
		{
			Matrix4 _a(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
			Matrix3 _b;
			Matrix3 _c(0, 1, 2, 4, 5, 6, 8, 9, 10);
			_b.SetFromMatrix4(_a);
			Assert::IsTrue(_b == _c);
		}
		TEST_METHOD(Multiply_PreMultiply)
		{
			Matrix3 _a(2, 3, 5, 7, 11, 13, 17, 19, 23);
			Matrix3 _b(29, 31, 37, 41, 43, 47, 53, 59, 61);

			Matrix3 _exp;
			_exp[0] = 446.;
			_exp[1] = 1343.;
			_exp[2] = 2491.;
			_exp[3] = 486.;
			_exp[4] = 1457.;
			_exp[5] = 2701.;
			_exp[6] = 520.;
			_exp[7] = 1569.;
			_exp[8] = 2925.;

			Assert::IsTrue(_a * _b == _exp);

			_exp[0] = 904.;
			_exp[1] = 1182.;
			_exp[2] = 1556.;
			_exp[3] = 1131.;
			_exp[4] = 1489.;
			_exp[5] = 1967.;
			_exp[6] = 1399.;
			_exp[7] = 1845.;
			_exp[8] = 2435.;

			Assert::IsTrue(_a.Premultiplyed(_b) == _exp);
		}
		TEST_METHOD(MultiplyScalar)
		{
			Matrix3 _a(0, 1, 2, 3, 4, 5, 6, 7, 8);
			
			Assert::IsTrue(_a * 2 == Matrix3(0., 2., 4., 6., 8., 10., 12., 14., 16));
		}
		TEST_METHOD(Determinant)
		{
			Matrix3 _a;
			Assert::IsTrue(_a.Determinant() == 1.);

			_a[0] = 2.;
			Assert::IsTrue(_a.Determinant() == 2.);

			_a[0] = 0.;
			Assert::IsTrue(_a.Determinant() == 0.);

			_a.Set(2, 3, 4, 5, 13, 7, 8, 9, 11);
			Assert::IsTrue(_a.Determinant() == -73);
		}
		TEST_METHOD(GetInverse)
		{
			Matrix3 _zero(0., 0., 0., 0., 0., 0., 0., 0., 0.);
			Matrix3 _a(_zero);
			Matrix3 _b;
			_b = _a.GetInverse();
			Assert::IsTrue(_zero == _b);

			vector<Matrix4> _mv;
			Matrix4 _m4;
			_m4.MakeRotationX(0.3);
			_mv.emplace_back(_m4);
			_m4.MakeRotationX(-0.3);
			_mv.emplace_back(_m4);
			_m4.MakeRotationY(0.3);
			_mv.emplace_back(_m4);
			_m4.MakeRotationY(-0.3);
			_mv.emplace_back(_m4);
			_m4.MakeRotationZ(0.3);
			_mv.emplace_back(_m4);
			_m4.MakeRotationZ(-0.3);
			_mv.emplace_back(_m4);
			_m4.MakeScale(1., 2., 3.);
			_mv.emplace_back(_m4);
			_m4.MakeScale(1. / 8., 1. / 2., 1. / 3.);

			for (const auto& _m : _mv)
			{
				_a.SetFromMatrix4(_m);
				_b = _a.GetInverse();
				const Matrix4 _m4 = ToMatrix4(_b);

				AssetAlmosetEqules(_a.Determinant() * _b.Determinant(), 1., L"");
				AssetAlmosetEqules(_m.Determinant() * _m4.Determinant(), 1., L"");

				Assert::IsTrue((_m * _m4).IsIndentity());
			}
		}
		TEST_METHOD(Transpose)
		{
			Matrix3 _a;
			Matrix3 _b(_a);
			_b.Transpose();
			Assert::IsTrue(_a == _b);
			_b.Set(0, 1, 2, 3, 4, 5, 6, 7, 8);
			Matrix3 _c(_b);
			_c.Transpose();
			Assert::IsTrue(!(_b == _c));
			_c.Transpose();
			Assert::IsTrue(_b == _c);
		}
		TEST_METHOD(GetNormalMatrix)
		{
			Matrix3 _a;

			_a.GetNormalMatrix(Matrix4 (2., 3., 5., 7.,
				11., 13., 17., 19.,
				23., 29., 31., 37.,
				41., 43., 47., 57.));
			Assert::IsTrue(_a == Matrix3(-1.2857142857142856, 0.7142857142857143, 0.2857142857142857,
				0.7428571428571429, -0.7571428571428571, 0.15714285714285714,
				-0.19999999999999998, 0.3, -0.09999999999999999));
		}
		TEST_METHOD(SetUvTransform)
		{
			Matrix3 _a(0.1767766952966369, 0.17677669529663687, 0.32322330470336313,
					  -0.17677669529663687, 0.1767766952966369, 0.5,
					  0., 0., 1.);
			Matrix3 _b;
			const double _centerX = 0.5;
			const double _centerY = 0.5;
			const double _offsetX = 0.;
			const double _offsetY = 0.;
			const double _repeatX = 0.25;
			const double _repeatY = 0.25;
			const double _rotation = 0.7753981633974483;

			_a.SetUvTransform(_offsetX,
				_offsetY,
				_repeatX,
				_repeatY,
				_rotation,
				_centerX,
				_centerY);

			_b.Identity();
			_b.Translate(-_centerX, -_centerY);
			_b.Rotate(_rotation);
			_b.Scale(_repeatX, _repeatY);
			_b.Translate(_centerX, _centerY);
			_b.Translate(_offsetX, _offsetY);

			Assert::IsTrue(_a == Matrix3(0.1785355940258599, 0.17500011904519763, 0.32323214346447127,
										-0.17500011904519763, 0.1785355940258599, 0.4982322625096689,
										0., 0., 1.));
			Assert::IsTrue(_b == Matrix3(0.1785355940258599, 0.17500011904519763, 0.32323214346447127,
										-0.17500011904519763, 0.1785355940258599, 0.4982322625096689,
										0., 0., 1.));
		}
		TEST_METHOD(Scale)
		{
			Matrix3 _a(1., 2., 3., 4., 5., 6., 7., 8., 9.);

			Assert::IsTrue(_a.Scaled(0.25, 0.25) == Matrix3(0.25, 0.5, 0.75,
				1, 1.25, 1.5,
				7., 8., 9.));
		}
		TEST_METHOD(Rotate)
		{
			Matrix3 _a(1., 2., 3., 4., 5., 6., 7., 8., 9.);

			Assert::IsTrue(_a.Rotated(M_PI_4) == Matrix3(3.5355339059327373, 4.949747468305833, 6.363961030678928,
				2.121320343559643, 2.121320343559643, 2.1213203435596433,
				7., 8., 9.));
		}
		TEST_METHOD(Translate)
		{
			Matrix3 _a(1., 2., 3., 4., 5., 6., 7., 8., 9.);

			Assert::IsTrue(_a.Translated(3., 7.) == Matrix3(22, 26, 30, 53, 61, 69, 7, 8, 9));
		}
		TEST_METHOD(Equals)
		{
			Assert::IsTrue(Matrix3(1., 2., 3., 4., 5., 6., 7., 8., 9.) == 
			Matrix3(1. + FLT_EPSILON, 2. + FLT_EPSILON, 3. + FLT_EPSILON, 
				4. + FLT_EPSILON, 5. - FLT_EPSILON, 6. - FLT_EPSILON,
				7. - FLT_EPSILON, 8. - FLT_EPSILON, 9. - FLT_EPSILON));

			Assert::IsTrue(!(Matrix3(1., 2., 3., 4., 5., 6., 7., 8., 9.) ==
				Matrix3(1. + FLT_EPSILON + DBL_EPSILON, 2. + FLT_EPSILON + DBL_EPSILON, 3. + FLT_EPSILON + DBL_EPSILON,
					4. + FLT_EPSILON + DBL_EPSILON, 5. - FLT_EPSILON - DBL_EPSILON, 6. - FLT_EPSILON - DBL_EPSILON,
					7. - FLT_EPSILON - DBL_EPSILON, 8. - FLT_EPSILON - DBL_EPSILON, 9. - FLT_EPSILON - DBL_EPSILON)));
		}
		TEST_METHOD(ToJson)
		{
			Matrix3 _m;

			stringstream _ss;

			_ss << _m;

			Assert::IsTrue( _ss.str() == "{type:'Matrix3',elements:[1,0,0,0,1,0,0,0,1]}");
		}
	};
}