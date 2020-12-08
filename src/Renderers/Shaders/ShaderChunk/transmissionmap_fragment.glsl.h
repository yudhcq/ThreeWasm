#pragma once
#include <string>

namespace Three
{
	const std::string Transmissionmap_fragment = R"(
#ifdef USE_TRANSMISSIONMAP

	totalTransmission *= texture2D( transmissionMap, vUv ).r;

#endif
)";
}