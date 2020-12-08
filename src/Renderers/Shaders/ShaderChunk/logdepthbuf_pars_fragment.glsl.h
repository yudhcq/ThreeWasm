#pragma once
#include <string>
namespace Three
{
    const std::string Logdepthbuf_pars_fragment = R"(
#if defined( USE_LOGDEPTHBUF ) && defined( USE_LOGDEPTHBUF_EXT )

	uniform float logDepthBufFC;
	varying float vFragDepth;
	varying float vIsPerspective;

#endif
)";
}
