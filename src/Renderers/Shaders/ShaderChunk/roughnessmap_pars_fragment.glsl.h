#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Roughnessmap_pars_fragment = R"(
#ifdef USE_ROUGHNESSMAP

	uniform sampler2D roughnessMap;

#endif
)";
}
