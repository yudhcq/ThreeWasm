#include <algorithm>
#include <regex>

#include "Color.h"
#include "MathUtil.h"

using namespace std;

namespace Three::Math
{
    map<string, int> Color::ColorKeyWorlds = {
        {"aliceblue", 0xF0F8FF},
        {"antiquewhite", 0xFAEBD7},
        {"aqua", 0x00FFFF},
        {"aquamarine", 0x7FFFD4},
        {"azure", 0xF0FFFF},
        {"beige", 0xF5F5DC},
        {"bisque", 0xFFE4C4},
        {"black", 0x000000},
        {"blanchedalmond", 0xFFEBCD},
        {"blue", 0x0000FF},
        {"blueviolet", 0x8A2BE2},
        {"brown", 0xA52A2A},
        {"burlywood", 0xDEB887},
        {"cadetblue", 0x5F9EA0},
        {"chartreuse", 0x7FFF00},
        {"chocolate", 0xD2691E},
        {"coral", 0xFF7F50},
        {"cornflowerblue", 0x6495ED},
        {"cornsilk", 0xFFF8DC},
        {"crimson", 0xDC143C},
        {"cyan", 0x00FFFF},
        {"darkblue", 0x00008B},
        {"darkcyan", 0x008B8B},
        {"darkgoldenrod", 0xB8860B},
        {"darkgray", 0xA9A9A9},
        {"darkgreen", 0x006400},
        {"darkgrey", 0xA9A9A9},
        {"darkkhaki", 0xBDB76B},
        {"darkmagenta", 0x8B008B},
        {"darkolivegreen", 0x556B2F},
        {"darkorange", 0xFF8C00},
        {"darkorchid", 0x9932CC},
        {"darkred", 0x8B0000},
        {"darksalmon", 0xE9967A},
        {"darkseagreen", 0x8FBC8F},
        {"darkslateblue", 0x483D8B},
        {"darkslategray", 0x2F4F4F},
        {"darkslategrey", 0x2F4F4F},
        {"darkturquoise", 0x00CED1},
        {"darkviolet", 0x9400D3},
        {"deeppink", 0xFF1493},
        {"deepskyblue", 0x00BFFF},
        {"dimgray", 0x696969},
        {"dimgrey", 0x696969},
        {"dodgerblue", 0x1E90FF},
        {"firebrick", 0xB22222},
        {"floralwhite", 0xFFFAF0},
        {"forestgreen", 0x228B22},
        {"fuchsia", 0xFF00FF},
        {"gainsboro", 0xDCDCDC},
        {"ghostwhite", 0xF8F8FF},
        {"gold", 0xFFD700},
        {"goldenrod", 0xDAA520},
        {"gray", 0x808080},
        {"green", 0x008000},
        {"greenyellow", 0xADFF2F},
        {"grey", 0x808080},
        {"honeydew", 0xF0FFF0},
        {"hotpink", 0xFF69B4},
        {"indianred", 0xCD5C5C},
        {"indigo", 0x4B0082},
        {"ivory", 0xFFFFF0},
        {"khaki", 0xF0E68C},
        {"lavender", 0xE6E6FA},
        {"lavenderblush", 0xFFF0F5},
        {"lawngreen", 0x7CFC00},
        {"lemonchiffon", 0xFFFACD},
        {"lightblue", 0xADD8E6},
        {"lightcoral", 0xF08080},
        {"lightcyan", 0xE0FFFF},
        {"lightgoldenrodyellow", 0xFAFAD2},
        {"lightgray", 0xD3D3D3},
        {"lightgreen", 0x90EE90},
        {"lightgrey", 0xD3D3D3},
        {"lightpink", 0xFFB6C1},
        {"lightsalmon", 0xFFA07A},
        {"lightseagreen", 0x20B2AA},
        {"lightskyblue", 0x87CEFA},
        {"lightslategray", 0x778899},
        {"lightslategrey", 0x778899},
        {"lightsteelblue", 0xB0C4DE},
        {"lightyellow", 0xFFFFE0},
        {"lime", 0x00FF00},
        {"limegreen", 0x32CD32},
        {"linen", 0xFAF0E6},
        {"magenta", 0xFF00FF},
        {"maroon", 0x800000},
        {"mediumaquamarine", 0x66CDAA},
        {"mediumblue", 0x0000CD},
        {"mediumorchid", 0xBA55D3},
        {"mediumpurple", 0x9370DB},
        {"mediumseagreen", 0x3CB371},
        {"mediumslateblue", 0x7B68EE},
        {"mediumspringgreen", 0x00FA9A},
        {"mediumturquoise", 0x48D1CC},
        {"mediumvioletred", 0xC71585},
        {"midnightblue", 0x191970},
        {"mintcream", 0xF5FFFA},
        {"mistyrose", 0xFFE4E1},
        {"moccasin", 0xFFE4B5},
        {"navajowhite", 0xFFDEAD},
        {"navy", 0x000080},
        {"oldlace", 0xFDF5E6},
        {"olive", 0x808000},
        {"olivedrab", 0x6B8E23},
        {"orange", 0xFFA500},
        {"orangered", 0xFF4500},
        {"orchid", 0xDA70D6},
        {"palegoldenrod", 0xEEE8AA},
        {"palegreen", 0x98FB98},
        {"paleturquoise", 0xAFEEEE},
        {"palevioletred", 0xDB7093},
        {"papayawhip", 0xFFEFD5},
        {"peachpuff", 0xFFDAB9},
        {"peru", 0xCD853F},
        {"pink", 0xFFC0CB},
        {"plum", 0xDDA0DD},
        {"powderblue", 0xB0E0E6},
        {"purple", 0x800080},
        {"rebeccapurple", 0x663399},
        {"red", 0xFF0000},
        {"rosybrown", 0xBC8F8F},
        {"royalblue", 0x4169E1},
        {"saddlebrown", 0x8B4513},
        {"salmon", 0xFA8072},
        {"sandybrown", 0xF4A460},
        {"seagreen", 0x2E8B57},
        {"seashell", 0xFFF5EE},
        {"sienna", 0xA0522D},
        {"silver", 0xC0C0C0},
        {"skyblue", 0x87CEEB},
        {"slateblue", 0x6A5ACD},
        {"slategray", 0x708090},
        {"slategrey", 0x708090},
        {"snow", 0xFFFAFA},
        {"springgreen", 0x00FF7F},
        {"steelblue", 0x4682B4},
        {"tan", 0xD2B48C},
        {"teal", 0x008080},
        {"thistle", 0xD8BFD8},
        {"tomato", 0xFF6347},
        {"turquoise", 0x40E0D0},
        {"violet", 0xEE82EE},
        {"wheat", 0xF5DEB3},
        {"white", 0xFFFFFF},
        {"whitesmoke", 0xF5F5F5},
        {"yellow", 0xFFFF00},
        {"yellowgreen", 0x9ACD32}};

    inline Color::Color() noexcept : mRed(1.),
                                     mGreen(1.),
                                     mBlue(1.)
    {
    }

    inline Color::Color(double scalar) noexcept : mRed(scalar),
                                                  mGreen(scalar),
                                                  mBlue(scalar)
    {
    }

    inline Color::Color(int colorHex) noexcept
    {
        mRed = double(colorHex >> 16 & 0xff) / 255.;
        mGreen = double(colorHex >> 8 & 0xff) / 255.;
        mBlue = double(colorHex & 0xff) / 255.;
    }

    inline Color::Color(const std::string &style)
    {
        SetStyle(style);
    }

    inline Color::Color(double red,
                        double green,
                        double blue) noexcept : mRed(red),
                                                mGreen(green),
                                                mBlue(blue)
    {
    }

    inline Color::Color(const HSL &hsl) noexcept
    {
        SetHSL(hsl.h, hsl.s, hsl.l);
    }

    inline double Color::HueToRgb(double p, double q, double t) noexcept
    {
        const double _t = t > 1. ? t - 1. : t < 0. ? t + 1. : t;
        if (_t < 1. / 6.)
        {
            return p + (q - p) * 6. * _t;
        }
        else if (_t < 1. / 2.)
        {
            return q;
        }
        else if (_t < 2 / 3)
        {
            return p + (q - p) * 6. * (2. / 3. - _t);
        }
        else
        {
            return p;
        }
    }

    inline double Color::SRGBToLinear(double c) noexcept
    {
        return c < 0.04045 ? c * 0.0773993808 : pow(c * 0.9478672986 + 0.0521327014, 2.4);
    }

    inline double Color::LinearToSRGB(double c) noexcept
    {
        return c < 0.0031308 ? c * 12.92 : 1.055 * pow(c, 0.41666) - 0.055;
    }

    inline double Color::Red() const noexcept
    {
        return mRed;
    }

    inline double Color::Green() const noexcept
    {
        return mGreen;
    }

    inline double Color::Blue() const noexcept
    {
        return mBlue;
    }

    inline void Color::SetRed(double red) noexcept
    {
        mRed = red;
    }

    inline void Color::SetGreen(double green) noexcept
    {
        mGreen = green;
    }

    inline void Color::SetBlue(double blue) noexcept
    {
        mBlue = blue;
    }

    inline void Color::SetHex(int colorHex)
    {
        mRed = double(colorHex >> 16 & 0xff) / 255.;
        mGreen = double(colorHex >> 8 & 0xff) / 255.;
        mBlue = double(colorHex & 0xff) / 255.;
    }

    inline void Color::SetColorKeyWorld(const std::string &colorKeyworld)
    {
        if (ColorKeyWorlds.count(colorKeyworld))
        {
            SetHex(ColorKeyWorlds[colorKeyworld]);
        }
    }

    inline void Color::SetScalar(double scalar) noexcept
    {
        SetRGB(scalar, scalar, scalar);
    }

    inline void Color::SetRGB(double r, double g, double b) noexcept
    {
        mRed = r;
        mGreen = g;
        mBlue = b;
    }

    inline void Color::SetHSL(double h, double s, double l)
    {
        const double _h = MathUtil::EuclideanModulo(h, 1.);
        const double _s = MathUtil::Clamp(s, 0., 1.);
        const double _l = MathUtil::Clamp(l, 0., 1.);

        if (_s == 0.)
        {
            SetRGB(_l, _l, _l);
        }
        else
        {
            const double _p = _l <= 0.5 ? _l * (1. + _s) : _l + _s - (_l * _s);
            const double _q = (2. * _l) - _p;
            SetRGB(HueToRgb(_q, _p, _h + 1. / 3.),
                   HueToRgb(_q, _p, _h),
                   HueToRgb(_q, _p, _h - 1. / 3.));
        }
    }

    inline void Color::SetStyle(const std::string &style)
    {
         smatch _matchResults;
         if (regex_match(style, _matchResults, regex(R"(^((?:rgb|hsl)a?)[(]\s*(.*)\s*[)])")))
         {
             const string &_name = _matchResults[1].str();
             const string &_colorStr = _matchResults[2].str();
             smatch _colorMatchResults;

             if (_name == "rgb" || _name == "rgba")
             {
                 if (regex_match(_colorStr, _colorMatchResults,
                     regex(R"(^(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*(,\s*([0-9]*\.?[0-9]+)\s*)?$)")))
                 {
                     // rgb(255,0,0) rgba(255,0,0,0.5)
                     mRed = min(255., stod(_colorMatchResults[1].str())) / 255.;
                     mGreen = min(255., stod(_colorMatchResults[2].str())) / 255.;
                     mBlue = min(255., stod(_colorMatchResults[3].str())) / 255.;
                 } else if (regex_match(_colorStr, _colorMatchResults,
                     regex(R"(^(\d+)%\s*,\s*(\d+)%\s*,\s*(\d+)%\s*(,\s*([0-9]*\.?[0-9]+)\s*)?$)")))
                 {
                     // rgb(100%,0%,0%) rgba(100%,0%,0%,0.5)
                     mRed = min(100., stod(_colorMatchResults[1].str())) / 100.;
                     mGreen = min(100., stod(_colorMatchResults[2].str())) / 100.;
                     mBlue = min(100., stod(_colorMatchResults[3].str())) / 100.;
                 }
             }
             else if (_name == "hsl" || _name == "hsla")
             {
                 if (regex_match(_colorStr, _colorMatchResults,
                     regex(R"(^(\d+)\s*,\s*(\d+)%\s*,\s*(\d+)%\s*(,\s*([0-9]*\.?[0-9]+)\s*)?$)")))
                 {
                     // hsl(120,50%,50%) hsla(120,50%,50%,0.5)
                     const auto _h = stod(_colorMatchResults[1].str()) / 360.;
                     const auto _s= stod(_colorMatchResults[2].str()) / 100.;
                     const auto _l = stod(_colorMatchResults[3].str()) / 100.;

                     SetHSL(_h, _s, _l);
                 }
             }
         }
         else if (regex_match(style, _matchResults, regex(R"(^\#([A-Fa-f0-9]+)$)")))
         {
             const auto _hex = _matchResults[1].str();
             const auto _size = _hex.size();
             if (_size == 3)
             {
                 // #ff0
                 string _hexStr("");
                 for (const auto& _hc : _hex)
                 {
                     _hexStr += _hc;
                     _hexStr += _hc;
                 }
                 const auto _hexInt = stoi(_hexStr, 0, 16);
                 mRed = static_cast<double>(_hexInt >> 16) / 255.;
                 mGreen = static_cast<double>((_hexInt >> 8) & 0xff) / 255.;
                 mBlue = static_cast<double>(_hexInt & 0xff) / 255.;
             }
             else if (_size == 6)
             {
                 // # ffff00
                 const auto _hexInt = stoi(_hex, 0, 16);
                 mRed = static_cast<double>(_hexInt >> 16) / 255.;
                 mGreen = static_cast<double>((_hexInt >> 8) & 0xff) / 255.;
                 mBlue = static_cast<double>(_hexInt & 0xff) / 255.;
             }
         }
         else if (!style.empty())
         {
            // key world
             SetColorKeyWorld(style);
         }
    }

    inline void Color::CopyGamaToLinear(const Color &color, double gammaFactor)
    {
        SetRGB(pow(color.mRed, gammaFactor),
               pow(color.mGreen, gammaFactor),
               pow(color.mBlue, gammaFactor));
    }

    inline void Color::CopyLinearToGamma(const Color &color, double gammaFactor)
    {
        double _safeInverse = gammaFactor > 0. ? 1. / gammaFactor : 1.;
        SetRGB(pow(color.mRed, _safeInverse),
               pow(color.mGreen, _safeInverse),
               pow(color.mBlue, _safeInverse));
    }

    inline void Color::ConvertGammaToLinear(double gammaFactor)
    {
        CopyGamaToLinear(*this, gammaFactor);
    }

    inline void Color::ConvertLinearToGamma(double gammaFactor)
    {
        CopyLinearToGamma(*this, gammaFactor);
    }

    inline void Color::CopySRGBToLinear(const Color &color)
    {
        SetRGB(SRGBToLinear(color.mRed),
               SRGBToLinear(color.mGreen),
               SRGBToLinear(color.mBlue));
    }

    inline void Color::CopyLinearToSRGB(const Color &color)
    {
        SetRGB(LinearToSRGB(color.mRed),
               LinearToSRGB(color.mGreen),
               LinearToSRGB(color.mBlue));
    }

    inline void Color::ConvertSRGBToLinear()
    {
        CopySRGBToLinear(*this);
    }

    inline void Color::ConvertLinearToSRGB()
    {
        CopyLinearToGamma(*this);
    }

    inline int Color::GetHex() const noexcept
    {
        return int(mRed * 255.) << 16 ^ int(mGreen * 255.) << 8 ^ int(mBlue * 255.);
    }

    inline std::string Color::GetHexString() const noexcept
    {
        const auto _hexStr = MathUtil::ToString16(GetHex());
        return ("000000" + _hexStr).substr(_hexStr.length(), 6);
    }

    inline Color::HSL Color::GetHSL() const noexcept
    {
        const double _max = max(mRed, max(mGreen, mBlue));
        const double _min = min(mRed, min(mGreen, mBlue));
        const double _l = (_max + _min) / 2.;
        if (_min == _max)
        {
            return {0.,
                    0.,
                    _l};
        }
        else
        {
            const double _delta = _max - _min;
            return {(_max == mRed ? (mGreen - mBlue) / _delta + (mGreen < mBlue ? 6. : 0.) : (_max == mGreen ? (mBlue - mRed) / _delta + 2. : (mRed - mGreen) / _delta + 4.)) / 6.,
                    _l <= 0.5 ? _delta / (_max + _min) : _delta / (2. - _max - _min),
                    _l};
        }
    }

    inline void Color::OffsetHSL(double h, double s, double l) noexcept
    {
        const auto _hsl = GetHSL();
        SetHSL(_hsl.h + h, _hsl.s + s, _hsl.l + l);
    }
    

    inline std::string Color::GetStyle() const noexcept
    {
        return "rgb(" + to_string(int(mRed * 255.)) + ',' + to_string(int(mGreen * 255.)) + ',' + to_string(int(mBlue * 255.)) + ')';
    }

    inline void Color::operator+=(const Color &color) noexcept
    {
        mRed += color.mRed;
        mGreen += color.mGreen;
        mBlue += color.mBlue;
    }

    inline void Color::operator+=(double scalar) noexcept
    {
        mRed += scalar;
        mGreen += scalar;
        mBlue += scalar;
    }

    inline Color Color::operator+(const Color &color) const noexcept
    {
        return Color(mRed + color.mRed, mGreen + color.mGreen, mBlue + color.mBlue);
    }

    inline Color Color::operator+(double scalar) const noexcept
    {
        return Color(mRed + scalar, mGreen + scalar, mBlue + scalar);
    }

    inline void Color::operator-=(const Color &color) noexcept
    {
        mRed = max(0., mRed - color.mRed);
        mGreen = max(0., mGreen - color.mGreen);
        mBlue = max(0., mBlue - color.mBlue);
    }

    inline void Color::operator-=(double scalar) noexcept
    {
        mRed = max(0., mRed - scalar);
        mGreen = max(0., mGreen - scalar);
        mBlue = max(0., mBlue - scalar);
    }

    inline Color Color::operator-(const Color &color) const noexcept
    {
        return Color(max(0., mRed - color.mRed),
                     max(0., mGreen - color.mGreen),
                     max(0., mBlue - color.mBlue));
    }

    inline Color Color::operator-(double scalar) const noexcept
    {
        return Color(max(0., mRed - scalar),
                     max(0., mGreen - scalar),
                     max(0., mBlue - scalar));
    }

    inline void Color::operator*=(const Color &color) noexcept
    {
        mRed *= color.mRed;
        mGreen *= color.mGreen;
        mBlue *= color.mBlue;
    }

    inline void Color::operator*=(double scalar) noexcept
    {
        mRed *= scalar;
        mGreen *= scalar;
        mBlue *= scalar;
    }

    inline Color Color::operator*(const Color &color) const noexcept
    {
        return Color(mRed * color.mRed, mGreen * color.mGreen, mBlue * color.mBlue);
    }

    inline Color Color::operator*(double scalar) const noexcept
    {
        return Color(mRed * scalar, mGreen * scalar, mBlue * scalar);
    }

    inline void Color::Lerp(const Color &color, double alpha) noexcept
    {
        mRed += (color.mRed - mRed) * alpha;
        mGreen += (color.mGreen - mGreen) * alpha;
        mBlue += (color.mBlue - mBlue) * alpha;
    }

    inline Color Color::Lerped(const Color &color, double alpha) const noexcept
    {
        return Color(mRed + (color.mRed - mRed) * alpha,
                     mGreen + (color.mGreen - mGreen) * alpha,
                     mBlue + (color.mBlue - mBlue) * alpha);
    }

    inline void Color::LerpHSL(const Color &color, double alpha) noexcept
    {
        const HSL _hslA = GetHSL();
        const HSL _hslB = color.GetHSL();
        SetHSL(MathUtil::Lerp(_hslA.h, _hslB.h, alpha),
               MathUtil::Lerp(_hslA.s, _hslB.s, alpha),
               MathUtil::Lerp(_hslA.l, _hslB.l, alpha));
    }

    inline Color Color::LerpHSL(const Color &color, double alpha) const noexcept
    {
        Color _c(*this);
        _c.Lerp(color, alpha);
        return _c;
    }

    inline bool Color::Equals(const Color &c, uint32_t ulp) const noexcept
    {
        return MathUtil::AlmosetEquals(mRed, c.mRed, ulp) &&
               MathUtil::AlmosetEquals(mGreen, c.mGreen, ulp) &&
               MathUtil::AlmosetEquals(mBlue, c.mBlue, ulp);
    }

    inline bool Color::operator==(const Color &c) const noexcept
    {
        return Equals(c);
    }

    inline std::ostream &operator<<(std::ostream &os, const Color &color)
    {
        os << "{type:'Color',"
           << "red:" << color.mRed
           << ",green:" << color.mGreen
           << ",blue:" << color.mBlue
           << "}";
        return os;
    }
} // namespace Three::Math
