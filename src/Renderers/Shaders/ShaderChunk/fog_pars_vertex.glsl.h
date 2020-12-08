#pragma once
#include <string>
namespace Three
{
    const std::string Fog_pars_vertex = R"(
#ifdef USE_FOG

	varying float fogDepth;

#endif
)";
}
