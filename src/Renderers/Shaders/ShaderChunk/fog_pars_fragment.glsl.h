#pragma once
#include <string>

namespace Three
{
    const std::string Fog_pars_fragment = R"(
#ifdef USE_FOG

	uniform vec3 fogColor;
	varying float fogDepth;

	#ifdef FOG_EXP2

		uniform float fogDensity;

	#else

		uniform float fogNear;
		uniform float fogFar;

	#endif

#endif
)";
}
