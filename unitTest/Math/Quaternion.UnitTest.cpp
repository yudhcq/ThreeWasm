#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Quaternion.h"

namespace ThreeUnitTest
{
    using namespace Three;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace std;

    TEST_CLASS(QuaternionUnitTest)
    {
        TEST_METHOD(Instancing)
        {
            Quaternion _q;
            Assert::IsTrue(_q.X() == 0.);
            Assert::IsTrue(_q.Y() == 0.);
            Assert::IsTrue(_q.Z() == 0.);
            Assert::IsTrue(_q.W() == 1.);

            Quaternion _q1(x, y, z, w);
            Assert::IsTrue(_q1.X() == x);
            Assert::IsTrue(_q1.Y() == y);
            Assert::IsTrue(_q1.Z() == z);
            Assert::IsTrue(_q1.W() == w);
        }
        TEST_METHOD(Slerp)
        {
            Quaternion _a
            (
                0.6753410084407496,
                0.4087830051091744,
                0.32856700410659473,
                0.5185120064806223
            );
            Quaternion _b
            (
                0.6602792107657797,
                0.43647413932562285,
                0.35119011210236006,
                0.5001871596632682
            );
            Quaternion _c = _a.Slerped(_b, 0.);
            Assert::IsTrue(_a == _c);
            _c = _a.Slerped(_b, 1.);
            Assert::IsTrue(_b == _c);
            _c = _a.Slerped(_b, 0.5);
            Assert::IsTrue(_c.Dot(_a) - _c.Dot(_b) < eps);
            Assert::IsTrue(_c.Length() - 1. < eps);
            _c = _a.Slerped(_b, 0.25);
            Assert::IsTrue(_c.Dot(_a) > _c.Dot(_b));
            Assert::IsTrue(_c.Length() - 1. < eps);
            _c = _a.Slerped(_b, 0.75);
            Assert::IsTrue(_c.Dot(_a) < _c.Dot(_b));
            Assert::IsTrue(_c.Length() - 1. < eps);
            _a.Set(1., 0., 0., 0.);
            _b.Set(0., 0., 1., 0.);
            _c = _a.Slerped(_b, 0.5);
            Assert::IsTrue(_c == Quaternion(M_SQRT1_2, 0., M_SQRT1_2, 0.));
            Assert::IsTrue(_c.Length() - 1. < eps);
            _a.Set(0., M_SQRT1_2, 0., M_SQRT1_2);
            _b.Set(0., -M_SQRT1_2, 0., M_SQRT1_2);
            _c = _a.Slerped(_b, 0.5);
            Assert::IsTrue(_c == Quaternion(0., 0., 0., 1.));
            Assert::IsTrue(_c.Length() - 1. < eps);
        }
        TEST_METHOD(SetFromEuler)
        {
            vector<Vector3> _angles;
            _angles.push_back(Vector3(1., 0., 0.));
            _angles.push_back(Vector3(0., 1., 0.));
            _angles.push_back(Vector3(0., 0., 1.));
            vector<EulerOrder> _orders;
            _orders.push_back(EulerOrder::XYZ);
            _orders.push_back(EulerOrder::YXZ);
            _orders.push_back(EulerOrder::ZXY);
            _orders.push_back(EulerOrder::ZYX);
            _orders.push_back(EulerOrder::YZX);
            _orders.push_back(EulerOrder::XZY);

            Euler _euler;
            Quaternion _q;
            for (const auto& _order : _orders)
            {
                for (const auto& _angle : _angles)
                {
                    _q.SetFromEuler(Euler(_angle.X(), _angle.Y(), _angle.Z(), _order));
                    _euler.SetFromQuaternion(_q, _order);
                    Assert::IsTrue(_angle.DistanceTo(Vector3(_euler.X(), _euler.Y(), _euler.Z())) < 0.01);
                }
            }
        }
        TEST_METHOD(SetFromAxisAngle)
        {
            Quaternion _zero;
            Quaternion _a;
            _a.SetFromAxisAngle(Vector3(1., 0., 0.), 0.);
            Assert::IsTrue(_zero == _a);
            _a.SetFromAxisAngle(Vector3(0., 1., 0.), 0.);
            Assert::IsTrue(_zero == _a);
            _a.SetFromAxisAngle(Vector3(0., 0., 1.), 0.);
            Assert::IsTrue(_zero == _a);

            Quaternion _q1;
            _q1.SetFromAxisAngle(Vector3(1., 0., 0.), M_PI);
            Quaternion _q2;
            _q2.SetFromAxisAngle(Vector3(1., 0., 0.), -M_PI);

            _q1 *= _q2;
            Assert::IsTrue(_q1 == _a);
        }
        TEST_METHOD(SetFromRotationMatrix)
        {
            vector<EulerOrder> _orders;
            Euler _euler(0.1, -0.3, 0.25);
            _orders.push_back(EulerOrder::XYZ);
            _orders.push_back(EulerOrder::YXZ);
            _orders.push_back(EulerOrder::ZXY);
            _orders.push_back(EulerOrder::ZYX);
            _orders.push_back(EulerOrder::YZX);
            _orders.push_back(EulerOrder::XZY);

            for (const auto& _order : _orders)
            {
                Quaternion _q, _q2;
                Matrix4 _m;
                Euler _e(_euler);
                _e.SetOrder(_order);
                _q.SetFromEuler(_e);
                _m.MakeRotationFromEuler(_e);
                _q2.SetFromRotationMatrix(_m);
                Assert::IsTrue(Quaternion
                (
                    _q2.X() - _q.X(),
                    _q2.Y() - _q.Y(),
                    _q2.Z() - _q.Z(),
                    _q2.W() - _q.W()
                ).Length() < 0.05);
            }
        }
        TEST_METHOD(SetFromUnitVectors)
        {
            Quaternion _a, _excpted(0., 0., sqrt(2.) / 2., sqrt(2.) / 2.);
            _a.SetFromUnitVectors(Vector3(1., 0., 0.), Vector3(0., 1., 0.));

            Assert::IsTrue(_a == _excpted);
        }
        TEST_METHOD(AngleTo)
        {
            Quaternion _a;
            Quaternion _b;
            Quaternion _c;
            _b.SetFromEuler(Euler(0., M_PI, 0.));
            _c.SetFromEuler(Euler(0., M_PI * 2., 0.));

            Assert::IsTrue(MathUtil::AlmosetEquals(_a.AngleTo(_a), 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.AngleTo(_b), M_PI));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.AngleTo(_c), 0.));
        }
        TEST_METHOD(RotateTowards)
        {
            Quaternion _a, _b, _c;
            _b.SetFromEuler(Euler(0., M_PI, 0.));

            _a.RotateTowards(_b, 0.);
            _a.RotateTowards(_b, M_PI * 2.);
            Assert::IsTrue(_a == _b);
            
            _a.Set(0, 0, 0, 1);
            _a.RotateTowards(_b, M_PI_2);
            Assert::IsTrue(_a.AngleTo(_c) == M_PI_2);
        }
        TEST_METHOD(Identity)
        {
            Quaternion _a(x, y, z, w);
            _a.Identity();
            Assert::IsTrue(_a.X() == 0.);
            Assert::IsTrue(_a.Y() == 0.);
            Assert::IsTrue(_a.Z() == 0.);
            Assert::IsTrue(_a.W() == 1.);
        }
        TEST_METHOD(Conjugate)
        {
            Quaternion _a(x, y, z, w);
            Quaternion _b = _a.Conjugated();

            Assert::IsTrue(_a.X() == -_b.X());
            Assert::IsTrue(_a.Y() == -_b.Y());
            Assert::IsTrue(_a.Z() == -_b.Z());
            Assert::IsTrue(_a.W() == _b.W());
        }
        TEST_METHOD(Dot)
        {
            Quaternion _a, _b;
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.Dot(_b), 1.));
            _a.Set(1, 2, 3, 1);
            _b.Set(3, 2, 1, 1);
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.Dot(_b), 11.));
        }
        TEST_METHOD(Length_Normalize)
        {
            Quaternion _a(x, y, z, w);
            Assert::IsTrue(_a.Length() != 1.);
            Assert::IsTrue(_a.LengthSq() != 1.);
            _a.Normalize();
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.Length(), 1.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.LengthSq(), 1.));
            _a.Set(0, 0, 0, 0);
            Assert::IsTrue(_a.Length() == 0);
            Assert::IsTrue(_a.LengthSq() == 0);
            _a.Normalize();
            Assert::IsTrue(_a.Length() == 1);
            Assert::IsTrue(_a.LengthSq() == 1);
        }
        TEST_METHOD(multiply)
        {
            Euler _es[] = 
            {
                Euler(1., 0., 0.),
                Euler(0., 1., 0.),
                Euler(0., 0., 1.)
            };

            Quaternion _q1, _q2, _q3;
            _q1.SetFromEuler(_es[0]);
            _q2.SetFromEuler(_es[1]);
            _q3.SetFromEuler(_es[2]);

            Matrix4 _m1, _m2, _m3;
            _m1.MakeRotationFromEuler(_es[0]);
            _m2.MakeRotationFromEuler(_es[1]);
            _m3.MakeRotationFromEuler(_es[2]);

            Matrix4 _m = _m1 * _m2 * _m3;
            Quaternion _q;
            _q.SetFromRotationMatrix(_m);
            Assert::IsTrue(_q1 * _q2 * _q3 == _q);
        }
        TEST_METHOD(Premultiply)
        {
            Quaternion _a(x, y, z, w), _b(2. * x, -y, -2. * z, w), _excepted(42., -32., -2., 58.);
            Assert::IsTrue(_a.Premultiplied(_b) == _excepted);
        }
        TEST_METHOD(Equals)
        {
            Quaternion _a(x, y, z, w);
            Quaternion _b(x - FLT_EPSILON, y + FLT_EPSILON, z - FLT_EPSILON, w + FLT_EPSILON);
            Assert::IsTrue(_a == _b);
            _b.Set(x - 2.* FLT_EPSILON, y + FLT_EPSILON, z - FLT_EPSILON, w + FLT_EPSILON);
            Assert::IsFalse(_a == _b);
        }
        TEST_METHOD(ToJson)
        {
            stringstream _ss;
            Quaternion _q;
            _ss << _q;
            Assert::IsTrue(_ss.str() == "{type:'Quaternion',x:0,y:0,z:0,w:1}");
        }
    };
}