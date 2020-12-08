#include <CppUnitTest.h>
#include <sstream>

#include "../TestConstants.h"
#include "../../src/Math/Spherical.h"

namespace ThreeUnitTest
{
    using namespace Three;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace std;
    TEST_CLASS(SphericalUnitTest)
    {
        TEST_METHOD(Instancing)
        {
            Spherical _s;

            Assert::IsTrue(_s.Radius() == 1.);
            Assert::IsTrue(_s.Phi() == 0.);
            Assert::IsTrue(_s.Theta() == 0.);

            Spherical _s1(10, cos(-0.5), sqrt(M_PI) * cos(-0.5));

            Assert::IsTrue(MathUtil::AlmosetEquals(_s1.Radius(), 10));
            Assert::IsTrue(MathUtil::AlmosetEquals(_s1.Phi(), cos(-0.5)));
            Assert::IsTrue(MathUtil::AlmosetEquals(_s1.Theta(), sqrt(M_PI) * cos(-0.5)));
        }
        TEST_METHOD(Set)
        {
            Spherical _s;
            _s.Set(10, cos(-0.5), sqrt(M_PI) * cos(-0.5));
            Assert::IsTrue(MathUtil::AlmosetEquals(_s.Radius(), 10));
            Assert::IsTrue(MathUtil::AlmosetEquals(_s.Phi(), cos(-0.5)));
            Assert::IsTrue(MathUtil::AlmosetEquals(_s.Theta(), sqrt(M_PI) * cos(-0.5)));
        }
        TEST_METHOD(MakeSafe)
        {
            const double EPS = 0.000001;
            Spherical _s(1, 0, 0);
            _s.MakeSafe();
            Assert::IsTrue(MathUtil::AlmosetEquals(_s.Phi(), EPS));
            _s.SetPhi(M_PI);
            _s.MakeSafe();
            Assert::IsTrue(MathUtil::AlmosetEquals(_s.Phi(), M_PI - EPS));
            _s.SetPhi(1.5);
            _s.MakeSafe();
            Assert::IsTrue(MathUtil::AlmosetEquals(_s.Phi(), 1.5));
        }
        TEST_METHOD(SetFromVector3)
        {
            auto _a = Spherical(1, 1, 1);
            auto _b = Vector3(0, 0, 0);
            auto _c = Vector3(M_PI, 1, -M_PI);
            auto _expected = Spherical(4.554032147688322, 1.3494066171539107, 2.356194490192345);
            _a.SetFromVector3(_b);
            Assert::IsTrue(_a == Spherical(0, 0, 0));

            _a.SetFromVector3(_c);
            Assert::IsTrue(_a == _expected);
        }
        TEST_METHOD(Equals)
        {
            Assert::IsTrue(Spherical() == Spherical(1. + DBL_EPSILON, DBL_EPSILON, DBL_EPSILON));
            Assert::IsFalse(Spherical() == Spherical(1. + DBL_EPSILON + FLT_EPSILON, DBL_EPSILON, DBL_EPSILON));
        }
        TEST_METHOD(ToJson)
        {
            stringstream _ss;
            _ss << Spherical();
            Assert::IsTrue(_ss.str() == "{type:'Spherical',radius:1,phi:0,theta:0}");
        }
    };
}