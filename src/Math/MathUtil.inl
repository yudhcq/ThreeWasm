#include <float.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <sstream>

#include "MathUtil.h"
#include "Euler.h"
#include "Vector3.h"

using namespace std;

namespace Three::Math
{

    inline const double MathUtil::DEG2RAD = M_PI / 180.;
    inline const double MathUtil::RAD2DEG = 180. / M_PI;
    inline const double MathUtil::EPSILION = FLT_EPSILON;

    inline double MathUtil::Clamp(double value, double minVal, double maxVal)
    {
        return max(minVal, min(maxVal, value));
    }

    inline double MathUtil::EuclideanModulo(double n, double m)
    {
        return fmod(fmod(n, m) + m, m);
    }

    inline double MathUtil::MapLinear(double x,
                                      double a1,
                                      double a2,
                                      double b1,
                                      double b2)
    {
        return b1 + (x - a1) * (b2 - b1) / (a2 - a1);
    }

    inline double MathUtil::Smoothstep(double x, double minVal, double maxVal)
    {
        if (x <= minVal)
        {
            return 0.;
        }
        else if (x >= maxVal)
        {
            return 1.;
        }
        else
        {
            double _x = (x - minVal) / (maxVal - minVal);
            return _x * _x * (3. - 2. * _x);
        }
    }

    inline double MathUtil::Smootherstep(double x, double minVal, double maxVal)
    {
        if (x <= minVal)
        {
            return 0.;
        }
        else if (x >= maxVal)
        {
            return 1.;
        }
        else
        {
            double _x = (x - minVal) / (maxVal - minVal);
            return _x * _x * _x * (_x * (6. * _x - 15.) + 10.);
        }
    }

    inline int MathUtil::RandInt(int low, int high)
    {
        srand((unsigned int)time(NULL));
        return low + int(double(rand()) / double(RAND_MAX) * double(high - low));
    }

    inline double MathUtil::RandFloat(double low, double high)
    {
        srand((unsigned int)time(NULL));
        return low + double(rand()) / double(RAND_MAX) * (high - low);
    }

    inline double MathUtil::RandFloatSpread(double range)
    {
        srand((unsigned int)time(NULL));
        return range * (0.5 - double(rand()) / double(RAND_MAX));
    }

    inline double MathUtil::DegToRad(double degress) noexcept
    {
        return degress * DEG2RAD;
    }

    inline double MathUtil::RadToDeg(double radians) noexcept
    {
        return radians * RAD2DEG;
    }

    inline double MathUtil::Lerp(double x, double y, double t) noexcept
    {
        return x + (y - x) * t;
    }

    inline bool MathUtil::IsPowerOfTwo(const uint64_t value) noexcept
    {
        return (value & (value - 1)) == 0 && value != 0;
    }

    inline double MathUtil::FloorPowerOfTwo(double value) noexcept
    {
        return pow(2., floor(log2(value)));
    }

    inline double MathUtil::CeilPowerOfTwo(double value) noexcept
    {
        return pow(2., ceil(log2(value)));
    }

    inline void MathUtil::SetQuaternionFromProperEuler(Quaternion &q,
                                                double a,
                                                double b,
                                                double c,
                                                const EulerOrder order) noexcept
    {
        const double _c2 = cos(b / 2.);
        const double _s2 = sin(b / 2.);
        const double _c13 = cos((a + c) / 2.);
        const double _s13 = sin((a + c) / 2.);
        const double _c1_3 = cos((a - c) / 2.);
        const double _s1_3 = sin((a - c) / 2.);
        const double _c3_1 = cos((c - a) / 2.);
        const double _s3_1 = sin((c - a) / 2.);

        switch (order)
        {
        case EulerOrder::XYX:
            q.Set(_c2 * _s13, _s2 * _c1_3, _s2 * _s1_3, _c2 * _c13);
            break;
        case EulerOrder::YZY:
            q.Set(_s2 * _s1_3, _c2 * _s13, _s2 * _c1_3, _c2 * _c13);
            break;
        case EulerOrder::ZXZ:
            q.Set(_s2 * _c1_3, _s2 * _s1_3, _c2 * _s13, _c2 * _c13);
            break;
        case EulerOrder::XZX:
            q.Set(_c2 * _s13, _s2 * _s3_1, _s2 * _c3_1, _c2 * _c13);
            break;
        case EulerOrder::YXY:
            q.Set(_s2 * _c3_1, _c2 * _s13, _s2 * _s3_1, _c2 * _c13);
            break;
        case EulerOrder::ZYZ:
            q.Set(_s2 * _s3_1, _s2 * _c3_1, _c2 * _s13, _c2 * _c13);
            break;
        default:
            break;
        }
    }

    inline std::string MathUtil::ToString16(int intVal) noexcept
    {
        stringstream _ss;
        string _s;
        _ss << hex << intVal;
        _ss >> _s;
        return _s;
    }

    inline double MathUtil::AlmosetEquals(double rhs, double lhs, uint32_t ulp) noexcept
    {
        const uint64_t a = *reinterpret_cast<const uint64_t *>(&lhs);
        const uint64_t b = *reinterpret_cast<const uint64_t *>(&rhs);

        // nan or infinity
        if ((a & 0x7FF0000000000000u) == 0x7FF0000000000000u ||
            (b & 0x7FF0000000000000u) == 0x7FF0000000000000u)
        {
            // lhs or rhs is infinity
            if ((a & 0x7FFFFFFFFFFFFFFFu) == 0x7FF0000000000000u ||
                (b & 0x7FFFFFFFFFFFFFFFu) == 0x7FF0000000000000u)
            {
                return a == b;
            }

            // if lhs or rhs is nan return false
            if ((a & 0x7FF0000000000000) == 0x7FF0000000000000 && (a & 0xfffffffffffff) != 0 ||
                (b & 0x7FF0000000000000) == 0x7FF0000000000000 && (b & 0xfffffffffffff) != 0)
            {
                return false;
            }
        }

        if (abs(lhs - rhs) <= EPSILION)
        {
            return true;
        }

        const uint64_t absAB = a > b ? a - b : b - a;

        return absAB <= ulp;
    }

    inline bool MathUtil::IsNan(double value) noexcept
    {
        return value != value;
    }


} // namespace Three::Math
#undef _USE_MATH_DEFINES