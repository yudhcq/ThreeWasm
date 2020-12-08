#pragma once
#include <string>

namespace Three 
{
    const std::string Alphamap_fragment = R"(
#ifdef USE_ALPHAMAP
    diffuseColor.a *= texture2D(alphaMap, vUv).g;
#endif
)";
}

