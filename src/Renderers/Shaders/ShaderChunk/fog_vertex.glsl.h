#pragma once
#include <string>

namespace Three
{
    const std::string Fog_vertex = R"(
#ifdef USE_FOG

	fogDepth = - mvPosition.z;

#endif
)";
}
