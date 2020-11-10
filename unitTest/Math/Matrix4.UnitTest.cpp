#include <CppUnitTest.h>
#include <sstream>

#include "../../src/Math/Matrix4.h"
#include "../TestConstants.h"

namespace ThreeUnitTest
{
	using namespace Three::Math;
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	TEST_CLASS(Matrix4UnitTest)
	{
		TEST_METHOD(Instancing)
		{
			Matrix4 _m;
			Assert::IsTrue(_m[0] == 1.);
			Assert::IsTrue(_m[1] == 0.);
			Assert::IsTrue(_m[2] == 0.);
			Assert::IsTrue(_m[3] == 0.);
			Assert::IsTrue(_m[4] == 0.);
			Assert::IsTrue(_m[5] == 1.);
			Assert::IsTrue(_m[6] == 0.);
			Assert::IsTrue(_m[7] == 0.);
			Assert::IsTrue(_m[8] == 0.);
			Assert::IsTrue(_m[9] == 0.);
			Assert::IsTrue(_m[10] == 1.);
			Assert::IsTrue(_m[11] == 0.);
			Assert::IsTrue(_m[12] == 0.);
			Assert::IsTrue(_m[13] == 0.);
			Assert::IsTrue(_m[14] == 0.);
			Assert::IsTrue(_m[15] == 1.);
			Matrix4 _m1(0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15);
			Assert::IsTrue(_m1[0] == 0.);
			Assert::IsTrue(_m1[1] == 4.);
			Assert::IsTrue(_m1[2] == 8.);
			Assert::IsTrue(_m1[3] == 12.);
			Assert::IsTrue(_m1[4] == 1.);
			Assert::IsTrue(_m1[5] == 5.);
			Assert::IsTrue(_m1[6] == 9.);
			Assert::IsTrue(_m1[7] == 13.);
			Assert::IsTrue(_m1[8] == 2.);
			Assert::IsTrue(_m1[9] == 6.);
			Assert::IsTrue(_m1[10] == 10.);
			Assert::IsTrue(_m1[11] == 14.);
			Assert::IsTrue(_m1[12] == 3.);
			Assert::IsTrue(_m1[13] == 7.);
			Assert::IsTrue(_m1[14] == 11.);
			Assert::IsTrue(_m1[15] == 15.);
		}				   	 
		TEST_METHOD(SetGet)
		{
			Matrix4 _m;
			Assert::IsTrue(MathUtil::AlmosetEquals(_m.Determinant(), 1.));
			_m.Set(0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15);
			Assert::IsTrue(_m[0] == 0.);
			Assert::IsTrue(_m[1] == 4.);
			Assert::IsTrue(_m[2] == 8.);
			Assert::IsTrue(_m[3] == 12.);
			Assert::IsTrue(_m[4] == 1.);
			Assert::IsTrue(_m[5] == 5.);
			Assert::IsTrue(_m[6] == 9.);
			Assert::IsTrue(_m[7] == 13.);
			Assert::IsTrue(_m[8] == 2.);
			Assert::IsTrue(_m[9] == 6.);
			Assert::IsTrue(_m[10] == 10.);
			Assert::IsTrue(_m[11] == 14.);
			Assert::IsTrue(_m[12] == 3.);
			Assert::IsTrue(_m[13] == 7.);
			Assert::IsTrue(_m[14] == 11.);
			Assert::IsTrue(_m[15] == 15.);
		}
		TEST_METHOD(Identity_IsIndentity)
		{
			Matrix4 _b;
			_b.Set(0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15);
			const Matrix4 _a;
			Assert::IsTrue(!(_a == _b));
			_b.Identity();
			Assert::IsTrue(_a.IsIndentity());
			Assert::IsTrue(_b.IsIndentity());
			Assert::IsTrue(_a == _b);
		}
		TEST_METHOD(CopyPosition)
		{
			Matrix4 _a, _b;
			_a.Set(1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16.);
			_b.Set(1., 2., 3., 0., 5., 6., 7., 0., 9., 10., 11., 0., 13., 14., 15., 16.);

			Assert::IsTrue(!(_a == _b));
			_b.CopyPosition(_a);
			Assert::IsTrue(_a == _b);
		}
		TEST_METHOD(MakeBasis_ExtractBasis)
		{
			Vector3 _identityBasis[3] = { Vector3(1., 0., 0.), Vector3(0., 1., 0.), Vector3(0., 0., 1.) };
			Matrix4 _a;
			_a.MakeBasis(_identityBasis[0], _identityBasis[1], _identityBasis[2]);
			Assert::IsTrue(_a == Matrix4());

			Vector3 _testBasis[3] = { Vector3(0., 1., 0.), Vector3(-1., 0., 0.), Vector3(0., 0., 1.) };
			
			for (int i = 0; i < 3; ++i)
			{
				Matrix4 _b;
				_b.MakeBasis(_testBasis[0], _testBasis[1], _testBasis[2]);
				Vector3 _outBasis[3];
				_b.ExtractBasis(_outBasis[0], _outBasis[1], _outBasis[2]);
				for (int j = 0; j < 3; ++j)
				{
					Assert::IsTrue(_outBasis[j] == _testBasis[j]);
				}
				for (int j = 0; j < 3; ++j)
				{
					_outBasis[j] = _identityBasis[j];
					_outBasis[j].Apply(_b);
				}
				for (int j = 0; j < 3; ++j)
				{
					Assert::IsTrue(_outBasis[j] == _testBasis[j]);
				}
			}
		}
		TEST_METHOD(MakeRotationFromEuler_ExtractRotation)
		{
			Euler _testEulers[5] = {
				Euler(0.,0.,0., EulerOrder::XYZ), 
				Euler(1., 0., 0., EulerOrder::XYZ), 
				Euler(0., 1., 0., EulerOrder::ZYX), 
				Euler(0., 0., 0.5, EulerOrder::YZX),
				Euler(0., 0., -0.5, EulerOrder::YZX)
			};

			for (const auto &_euler : _testEulers)
			{
				Matrix4 _m;
				_m.MakeRotationFromEuler(_euler);
				Euler _euler2;
				_euler2.SetFromRotationMatrix(_m, _euler.Order());
				Matrix4 _m2;
				_m2.MakeRotationFromEuler(_euler2);
				Assert::IsTrue(_m == _m2);
				Assert::IsTrue(_euler == _euler2);

				Matrix4 _m3;
				_m3.ExtractRotation(_m2);
				Euler _euler3;
				_euler3.SetFromRotationMatrix(_m3);
				Assert::IsTrue(_m == _m3);
				Assert::IsTrue(_euler == _euler3);
			}
		}
		TEST_METHOD(LookAt)
		{
			Matrix4 _a, _expected;
			Vector3 _eye, _target(0., 1., -1.), _up(0., 1., 0.);
			_a.LookAt(_eye, _target, _up);
			Euler _rotation;
			_rotation.SetFromRotationMatrix(_a);
			Assert::IsTrue(MathUtil::AlmosetEquals(_rotation.X() * (180. / M_PI), 45.));
			
			_eye = _target;
			_a.LookAt(_eye, _target, _up);
			Assert::IsTrue(_a == _expected);

			_eye.Set(0., 1., 0.);
			_target.Set(0.);
			_a.LookAt(_eye, _target, _up);
			_expected.Set(1., 0., 0., 0., 0., 0.0001, 1., 0., 0., -1., 0.0001, 0., 0., 0., 0., 1.);
			Assert::IsTrue(_a == _expected);
		}
		TEST_METHOD(Multiply)
		{
			Matrix4 _lhs(2., 3., 5., 7., 11., 13., 17., 19., 23., 29., 31., 37., 41., 43., 47., 53.);
			Matrix4 _rhs(59., 61., 67., 71., 73., 79., 83., 89., 97., 101., 103., 107., 109., 113., 127., 131.);
			_lhs *= _rhs;
			AssetAlmosetEqules(_lhs[0], 1585.);
			AssetAlmosetEqules(_lhs[1], 5318.);
			AssetAlmosetEqules(_lhs[2], 10514.);
			AssetAlmosetEqules(_lhs[3], 15894.);
			AssetAlmosetEqules(_lhs[4], 1655.);
			AssetAlmosetEqules(_lhs[5], 5562.);
			AssetAlmosetEqules(_lhs[6], 11006.);
			AssetAlmosetEqules(_lhs[7], 16634.);
			AssetAlmosetEqules(_lhs[8], 1787.);
			AssetAlmosetEqules(_lhs[9], 5980.);
			AssetAlmosetEqules(_lhs[10], 11840.);
			AssetAlmosetEqules(_lhs[11], 17888.);
			AssetAlmosetEqules(_lhs[12], 1861.);
			AssetAlmosetEqules(_lhs[13], 6246.);
			AssetAlmosetEqules(_lhs[14], 12378.);
			AssetAlmosetEqules(_lhs[15], 18710.);
			Matrix4 _lhs1(_lhs);
			_lhs = _lhs * _rhs;
			AssetAlmosetEqules(_lhs[0], 1585.);
			AssetAlmosetEqules(_lhs[1], 5318.);
			AssetAlmosetEqules(_lhs[2], 10514.);
			AssetAlmosetEqules(_lhs[3], 15894.);
			AssetAlmosetEqules(_lhs[4], 1655.);
			AssetAlmosetEqules(_lhs[5], 5562.);
			AssetAlmosetEqules(_lhs[6], 11006.);
			AssetAlmosetEqules(_lhs[7], 16634.);
			AssetAlmosetEqules(_lhs[8], 1787.);
			AssetAlmosetEqules(_lhs[9], 5980.);
			AssetAlmosetEqules(_lhs[10], 11840.);
			AssetAlmosetEqules(_lhs[11], 17888.);
			AssetAlmosetEqules(_lhs[12], 1861.);
			AssetAlmosetEqules(_lhs[13], 6246.);
			AssetAlmosetEqules(_lhs[14], 12378.);
			AssetAlmosetEqules(_lhs[15], 18710.);
		}
		TEST_METHOD(MultiplyScalar)
		{
			Matrix4 _b(0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.);

			Assert::IsTrue(_b[0] == 0.);
			Assert::IsTrue(_b[1] == 4.);
			Assert::IsTrue(_b[2] == 8.);
			Assert::IsTrue(_b[3] == 12.);
			Assert::IsTrue(_b[4] == 1.);
			Assert::IsTrue(_b[5] == 5.);
			Assert::IsTrue(_b[6] == 9.);
			Assert::IsTrue(_b[7] == 13.);
			Assert::IsTrue(_b[8] == 2.);
			Assert::IsTrue(_b[9] == 6.);
			Assert::IsTrue(_b[10] == 10.);
			Assert::IsTrue(_b[11] == 14.);
			Assert::IsTrue(_b[12] == 3.);
			Assert::IsTrue(_b[13] == 7.);
			Assert::IsTrue(_b[14] == 11.);
			Assert::IsTrue(_b[15] == 15.);

			_b *= 2.;
			Assert::IsTrue(_b[0] == 0. * 2.);
			Assert::IsTrue(_b[1] == 4. * 2.);
			Assert::IsTrue(_b[2] == 8. * 2.);
			Assert::IsTrue(_b[3] == 12. * 2.);
			Assert::IsTrue(_b[4] == 1. * 2.);
			Assert::IsTrue(_b[5] == 5. * 2.);
			Assert::IsTrue(_b[6] == 9. * 2.);
			Assert::IsTrue(_b[7] == 13. * 2.);
			Assert::IsTrue(_b[8] == 2. * 2.);
			Assert::IsTrue(_b[9] == 6. * 2.);
			Assert::IsTrue(_b[10] == 10. * 2.);
			Assert::IsTrue(_b[11] == 14. * 2.);
			Assert::IsTrue(_b[12] == 3. * 2.);
			Assert::IsTrue(_b[13] == 7. * 2.);
			Assert::IsTrue(_b[14] == 11. * 2.);
			Assert::IsTrue(_b[15] == 15. * 2.);
		}
		TEST_METHOD(Determinant)
		{
			Matrix4 _a;
			Assert::IsTrue(_a.Determinant() == 1.);

			_a[0] = 2.;
			Assert::IsTrue(_a.Determinant() == 2.);

			_a[0] = 0;
			Assert::IsTrue(_a.Determinant() == 0.);

			_a.Set(2., 3., 4., 5., -1., -21., -3., -4., 6., 7., 8., 10., -8., -9., -10., -12.);
			Assert::IsTrue(_a.Determinant() == 76.);
		}
		TEST_METHOD(Transpose)
		{
			Matrix4 _a;
			Matrix4 _b = _a.Transposed();
			Assert::IsTrue(_a == _b);

			_b.Set(0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.);
			Matrix4 _c = _b.Transposed();
			Assert::IsTrue(!(_b == _c));
			_c.Transpose();
			Assert::IsTrue(_b == _c);
		}
		TEST_METHOD(SetPosition)
		{
			Matrix4 _a(0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.);
			Vector3 _b(-1., -2., -3.);
			Matrix4 _c(0., 1., 2., -1., 4., 5., 6., -2., 8., 9., 10., -3., 12., 13., 14., 15.);

			_a.SetPosition(_b);
			Assert::IsTrue(_a == _c);
		}
		TEST_METHOD(GetInverse)
		{
			Matrix4 _zero(0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);
			Matrix4 _identity;
			Matrix4 _a;
			Matrix4 _b(0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);
			_a = _b.GetInverse();
			Assert::IsTrue(_a == _zero);

			Matrix4 _testMatrices[11];
			_testMatrices[0].MakeRotationX(0.3);
			_testMatrices[1].MakeRotationX(-0.3);
			_testMatrices[2].MakeRotationY(0.3);
			_testMatrices[3].MakeRotationY(-0.3);
			_testMatrices[4].MakeRotationZ(0.3);
			_testMatrices[5].MakeRotationZ(-0.3);
			_testMatrices[6].MakeScale(1., 2., 3.);
			_testMatrices[7].MakeScale(1. / 8., 1. / 2., 1. / 3.);
			_testMatrices[8].MakePerspective(-1., 1., 1., -1., 1., 1000.);
			_testMatrices[9].MakePerspective(-16.,16., 9., -9., 0.1, 10000.);
			_testMatrices[10].MakeTranslation(1., 2., 3.);
		}
		TEST_METHOD(Scale)
		{}
		TEST_METHOD(GetMaxScaleOnAxis)
		{}
		TEST_METHOD(MakeTranslation)
		{}
		TEST_METHOD(MakeRotationX)
		{}
		TEST_METHOD(MakeRotationY)
		{}
		TEST_METHOD(MakeRotationZ)
		{}
		TEST_METHOD(MakeRotationAxis)
		{}
		TEST_METHOD(MakeScale)
		{}
		TEST_METHOD(MakeShear)
		{}
		TEST_METHOD(Compose_Decompose)
		{}
		TEST_METHOD(MakePerspective)
		{}
		TEST_METHOD(MakeOrthograph)
		{}
		TEST_METHOD(Equals)
		{}
		TEST_METHOD(ToJson)
		{}
	}; 

}