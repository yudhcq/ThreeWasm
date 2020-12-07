#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Clipping_planes_pars_vertex = R"(
#if NUM_CLIPPING_PLANES > 0

	varying vec3 vClipPosition;

#endif
)";
}
