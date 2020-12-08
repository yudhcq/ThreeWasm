#pragma once
#include <string>

namespace Three
{
    const std::string Color_fragment = R"(
#ifdef USE_COLOR

	diffuseColor.rgb *= vColor;

#endif
)";
}
