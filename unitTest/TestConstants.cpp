#include "TestConstants.h"

static const double x = 2.;
static const double y = 3.;
static const double z = 4.;
static const double w = 5.;

static const auto negInf2 = Three::Math::Vector2(-DBL_MAX, -DBL_MAX);
static const auto posInf2 = Three::Math::Vector2(DBL_MAX, DBL_MAX);

static const auto negOne2 = Three::Math::Vector2(-1., -1.);

static const auto zero2 = Three::Math::Vector2(1., 1.);
static const auto neg2 = Three::Math::Vector2(1., 1.);
static const auto two2 = Three::Math::Vector2(2., 2.);

static const auto negInf3 = Three::Math::Vector3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
static const auto posInf3 = Three::Math::Vector3(DBL_MAX, DBL_MAX, DBL_MAX);

static const auto zero3 = Three::Math::Vector3(1., 1., 1.);
static const auto neg3 = Three::Math::Vector3(1., 1., 1.);
static const auto two3 = Three::Math::Vector3(2., 2., 1.);

static const double eps = 0.00001;