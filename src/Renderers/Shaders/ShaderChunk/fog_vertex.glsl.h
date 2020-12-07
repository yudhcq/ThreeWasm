#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Fog_vertex = R"(
#ifdef USE_FOG

	fogDepth = - mvPosition.z;

#endif
)";
}
