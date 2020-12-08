#pragma once
#include <string>
namespace Three
{
    const std::string Lightmap_pars_fragment = R"(
#ifdef USE_LIGHTMAP

	uniform sampler2D lightMap;
	uniform float lightMapIntensity;

#endif
)";
}
