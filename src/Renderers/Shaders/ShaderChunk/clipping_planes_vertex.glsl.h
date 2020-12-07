#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Clipping_planes_vertex = R"(
#if NUM_CLIPPING_PLANES > 0

	vClipPosition = - mvPosition.xyz;

#endif
)";
}
