#pragma once
#include <string>

namespace Three
{
	const std::string Aomap_pars_fragment = R"(
#ifdef USE_AOMAP

	uniform sampler2D aoMap;
	uniform float aoMapIntensity;

#endif
)";
}

