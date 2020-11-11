#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Plane.h"

namespace ThreeUnitTest
{
    using namespace Three::Math;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;

    TEST_CLASS(PlaneUintTest)
    {
        TEST_METHOD(Instancing)
        {
            const Plane _a;
            Assert::IsTrue(_a.Normal() == Vector3(1., 0., 0.));
            Assert::IsTrue(_a.Constant() == 0.);

            const Plane _b(one3, 0);
            Assert::IsTrue(_b.Normal() == one3);
            Assert::IsTrue(_b.Constant() == 0.);

            const Plane _c(one3, 1);
            Assert::IsTrue(_c.Normal() == one3);
            Assert::IsTrue(_c.Constant() == 1.);
        }

        TEST_METHOD(Set)
        {
            Plane _a;
            Assert::IsTrue(_a.Normal() == Vector3(1., 0., 0.));
            Assert::IsTrue(_a.Constant() == 0.);

            _a.SetNormal(Vector3(x, y, z));
            _a.SetConstant(w);
            Assert::IsTrue(_a.Normal() == Vector3(x, y, z));
            Assert::IsTrue(_a.Constant() == w);

            Plane _b;
            _b.Set(Vector3(x, y, z), w);
            Assert::IsTrue(_b.Normal() == Vector3(x, y, z));
            Assert::IsTrue(_b.Constant() == w);

            Plane _c;
            _c.Set(x, y, z, w);
            Assert::IsTrue(_c.Normal() == Vector3(x, y, z));
            Assert::IsTrue(_c.Constant() == w);
        }

        TEST_METHOD(SetComponents)
        {
            Plane _a;
            _a[0] = x;
            _a[1] = y;
            _a[2] = z;
            _a[3] = w;

            Assert::IsTrue(x == _a[0]);
            Assert::IsTrue(y == _a[1]);
            Assert::IsTrue(z == _a[2]);
            Assert::IsTrue(w == _a[3]);

            const Plane _b(Vector3(x, y, z), w);

            Assert::IsTrue(x == _b[0]);
            Assert::IsTrue(y == _b[1]);
            Assert::IsTrue(z == _b[2]);
            Assert::IsTrue(w == _b[3]);

            Assert::ExpectException<range_error>([]()
            {
                Plane _a;
                const auto _a_4 = _a[4];
            });
        }

        TEST_METHOD(SetFromNormalAndCoplanarPoint)
        {
            Plane _a;
            _a.SetFromNormalAndCopanarPoint(one3.Normalized(), zero3);
            Assert::IsTrue(_a.Normal() == one3.Normalized());
            Assert::IsTrue(_a.Constant() == 0.);
        }

        TEST_METHOD(SetFromCoplanarPoints)
        {
            Plane _a;
            _a.SetFromCoplanarPoints
            (
                Vector3(2., 0.5, 0.25),
                Vector3(2., -0.5, 1.25),
                Vector3(2., -3.5, 2.2)
            );
            Assert::IsTrue(_a.Normal() == Vector3(1., 0., 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.Constant(), -2.));
        }

        TEST_METHOD(Normalize)
        {
            Plane _a(Vector3(2., 0., 0.), 2.);
            Plane _b = _a.Normalized();

            Assert::IsTrue(_b.Normal() == Vector3(1., 0., 0.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_b.Constant(), 1.));
        }

        TEST_METHOD(Negate_DistanceToPoint)
        {
            Plane _a(Vector3(2, 0., 0.), -2.);
            _a.Normalize();
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(Vector3(4., 0., 0.)), 3.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(Vector3(1., 0., 0.)), 0.));
            Plane _b = _a.Negated();
            Assert::IsTrue(MathUtil::AlmosetEquals(_b.DistanceTo(Vector3(4., 0., 0.)), -3.));
            Assert::IsTrue(MathUtil::AlmosetEquals(_b.DistanceTo(Vector3(1., 0., 0.)), 0.));
        }

        TEST_METHOD(DistanceToSphere)
        {
            Plane _a(Vector3(1., 0., 0.), 0.);
            Sphere _b(Vector3(2., 0., 0.), 1.);
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(_b), 1.));
            _a.Set(Vector3(1., 0., 0.), 2.);
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(_b), 3.));
            _a.Set(Vector3(1., 0., 0.), -2.);
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(_b), -1.));
        }

        TEST_METHOD(ProjectPoint)
        {
            Plane _a(Vector3::UINT_X, 0.);
            Assert::IsTrue(_a.ProjectPoint(Vector3(10., 0., 0.)) == zero3);
            Assert::IsTrue(_a.ProjectPoint(Vector3(-10., 0., 0.)) == zero3);
            _a.Set(Vector3::UINT_Y, -1.);
            Assert::IsTrue(_a.ProjectPoint(Vector3()) == Vector3::UINT_Y);
            Assert::IsTrue(_a.ProjectPoint(Vector3(0., 1., 0.)) == Vector3::UINT_Y);
        }
        TEST_METHOD(IntersectLine)
        {
            Plane _a(Vector3::UINT_X, 0.);
            Line3 _l1(Vector3(-10., 0., 0.), Vector3(10., 0, 0.));
            Vector3 _target;
            Assert::IsTrue(_a.IntersectLine(_l1, _target));
            Assert::IsTrue(_target == Vector3());
            _a.SetConstant(-3.);
            Assert::IsTrue(_a.IntersectLine(_l1, _target));
            Assert::IsTrue(_target == Vector3(3., 0., 0.));
        }
        TEST_METHOD(IntersectsBox)
        {
            Box3 _a(zero3, one3);
            Plane _b(Vector3::UINT_Y, 1.);
            Plane _c(Vector3::UINT_Y, 1.25);
            Plane _d(Vector3::UINT_Y.Negated(), 1.25);
            Plane _e(Vector3::UINT_Y, 0.25);
            Plane _f(Vector3::UINT_Y, -0.25);
            Plane _g(Vector3::UINT_Y, -0.75);
            Plane _h(Vector3::UINT_Y, -1.);
            Plane _i(one3.Normalized(), -1.732);
            Plane _j(one3.Normalized(), -1.733);

            Assert::IsTrue(!_b.IntersectsBox(_a));
            Assert::IsTrue(!_c.IntersectsBox(_a));
            Assert::IsTrue(!_d.IntersectsBox(_a));
            Assert::IsTrue(!_e.IntersectsBox(_a));
            Assert::IsTrue(_f.IntersectsBox(_a));
            Assert::IsTrue(_g.IntersectsBox(_a));
            Assert::IsTrue(_h.IntersectsBox(_a));
            Assert::IsTrue(_i.IntersectsBox(_a));
            Assert::IsTrue(!_j.IntersectsBox(_a));
        }
        TEST_METHOD(IntersectsSphere)
        {
            Sphere _a(zero3, 1.);
            Plane _b(Vector3::UINT_Y, 1.);
            Plane _c(Vector3::UINT_Y, 1.25);
            Plane _d(Vector3::UINT_Y.Negated(), 1.25);

            Assert::IsTrue(_b.IntersectsSphere(_a));
            Assert::IsTrue(!_c.IntersectsSphere(_a));
            Assert::IsTrue(!_d.IntersectsSphere(_a));
        }
        TEST_METHOD(CoplanarPoint)
        {
            Plane _a(Vector3::UINT_X, 0.);
            auto _point = _a.CoplanarPoint();
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(_point), 0.));
            _a.Set(Vector3::UINT_Y, -1.);
            _point = _a.CoplanarPoint();
            Assert::IsTrue(MathUtil::AlmosetEquals(_a.DistanceTo(_point), 0.));
        }
        TEST_METHOD(ApplyMatrix4_Translate)
        {
            Plane _a(Vector3::UINT_X, 0.);
            Matrix4 _m;
            _m.MakeRotationZ(M_PI_2);
            Matrix3 _normalM;
            _normalM.GetNormalMatrix(_m);
            Assert::IsTrue(_a.AppliedMatrix4(_m, _normalM) == Plane(Vector3::UINT_Y, 0.));
            _a.Set(Vector3::UINT_Y, -1.);
            Assert::IsTrue(_a.AppliedMatrix4(_m, _normalM) == Plane(Vector3::UINT_X.Negated(), -1.));
            _m.MakeTranslation(1., 1., 1.);
            _normalM.GetNormalMatrix(_m);
            Assert::IsTrue(_a.AppliedMatrix4(_m, _normalM) == _a.Translated(Vector3(1., 1., 1.)));
        }
        TEST_METHOD(Equals)
        {
            Plane _a(Vector3::UINT_X, 0.);
            Plane _b(Vector3::UINT_X, 1.);
            Plane _c(Vector3::UINT_Y, 0.);

            Assert::IsFalse(_a == _b);
            Assert::IsFalse(_a == _c);

            _a = _b;
            Assert::IsTrue(_a == _b);
        }
        TEST_METHOD(ToJson)
        {
            Plane _a(Vector3::UINT_X, 1.);
            std::stringstream _ss;
            _ss << _a;

            Assert::IsTrue(_ss.str() == "{type:'Plane',normal:{type:'Vector3',x:1,y:0,z:0},constant:1}");
        }
    };
}