#pragma once
#include <string>
namespace Three
{
    const std::string Logdepthbuf_pars_vertex = R"(
#ifdef USE_LOGDEPTHBUF

	#ifdef USE_LOGDEPTHBUF_EXT

		varying float vFragDepth;
		varying float vIsPerspective;

	#else

		uniform float logDepthBufFC;

	#endif

#endif
)";
}
