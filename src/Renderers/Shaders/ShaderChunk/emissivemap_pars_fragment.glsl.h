#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Emissivemap_pars_fragment = R"(
#ifdef USE_EMISSIVEMAP

	uniform sampler2D emissiveMap;

#endif
)";
}
