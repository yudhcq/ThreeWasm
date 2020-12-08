#pragma once
#include <string>
namespace Three
{
    const std::string Specularmap_pars_fragment = R"(
#ifdef USE_SPECULARMAP

	uniform sampler2D specularMap;

#endif
)";
}
