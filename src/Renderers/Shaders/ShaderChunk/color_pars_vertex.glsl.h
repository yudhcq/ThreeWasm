#pragma once
#include <string>

namespace Three
{
    const std::string color_pars_vertex = R"(
#if defined( USE_COLOR ) || defined( USE_INSTANCING_COLOR )

	varying vec3 vColor;

#endif
)";
}