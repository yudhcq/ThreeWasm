#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Alphamap_pars_fragment = R"(
#ifdef USE_ALPHAMAP
    uniform sampler2D alphaMap;
#endif
)";
}
