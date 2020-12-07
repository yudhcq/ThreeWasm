#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Color_pars_fragment = R"(
#ifdef USE_COLOR

	varying vec3 vColor;

#endif
)";
}
