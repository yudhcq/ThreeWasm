#pragma once
#include <CppUnitTest.h>
#include <limits>

#include "../src/Math/Vector2.h"
#include "../src/Math/Vector3.h"
#include "../src/Math/MathUtil.h"

namespace ThreeUnitTest
{
	static const double x = 2.;
	static const double y = 3.;
	static const double z = 4.;
	static const double w = 5.;

	static const auto negInf2 = Three::Math::Vector2(-DBL_MAX, -DBL_MAX);
	static const auto posInf2 = Three::Math::Vector2(DBL_MAX, DBL_MAX);

	static const auto one2 = Three::Math::Vector2(1., 1.);
	static const auto negOne2 = Three::Math::Vector2(-1., -1.);

	static const auto zero2 = Three::Math::Vector2(0., 0.);
	static const auto neg2 = Three::Math::Vector2(1., 1.);
	static const auto two2 = Three::Math::Vector2(2., 2.);

	static const auto negInf3 = Three::Math::Vector3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	static const auto posInf3 = Three::Math::Vector3(DBL_MAX, DBL_MAX, DBL_MAX);

	static const auto one3 = Three::Math::Vector3(1., 1., 1.);
	static const auto zero3 = Three::Math::Vector3(0., 0., 0.);
	static const auto neg3 = Three::Math::Vector3(1., 1., 1.);
	static const auto two3 = Three::Math::Vector3(2., 2., 2.);

	static const double eps = 0.00001;

	static const double nanDouble = numeric_limits<double>::quiet_NaN();

	static void AssetAlmosetEqules(double l, double r, const wchar_t* message)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(Three::Math::MathUtil::AlmosetEquals(l, r), message);
	}

	static void AssetNotAlmosetEqules(double l, double r, const wchar_t* message)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsFalse(Three::Math::MathUtil::AlmosetEquals(l, r), message);
	}
}