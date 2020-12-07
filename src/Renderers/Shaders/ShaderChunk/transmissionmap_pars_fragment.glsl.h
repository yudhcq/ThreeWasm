#pragma once
#include <string>

namespace Three::Shader
{
	const std::string Transmissionmap_pars_fragment = R"(
#ifdef USE_TRANSMISSIONMAP

	uniform sampler2D transmissionMap;

#endif
)";
}