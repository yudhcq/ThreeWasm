#pragma once
#include <string>

namespace Three::Shader 
{
    const std::string Alphamap_fragment = R"(
#ifdef USE_ALPHAMAP
    diffuseColor.a *= texture2D(alphaMap, vUv).g;
#endif
)";
}

