#pragma once
#include <string>

namespace Three::Shader
{
	const std::string Transmissionmap_fragment = R"(
#ifdef USE_TRANSMISSIONMAP

	totalTransmission *= texture2D( transmissionMap, vUv ).r;

#endif
)";
}