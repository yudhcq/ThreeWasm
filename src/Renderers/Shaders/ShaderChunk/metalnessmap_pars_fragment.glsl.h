#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Metalnessmap_pars_fragment = R"(
#ifdef USE_METALNESSMAP

	uniform sampler2D metalnessMap;

#endif
)";
}
