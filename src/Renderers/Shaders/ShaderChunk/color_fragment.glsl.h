#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Color_fragment = R"(
#ifdef USE_COLOR

	diffuseColor.rgb *= vColor;

#endif
)";
}
