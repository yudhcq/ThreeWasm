#pragma once
#include <string>

namespace Three::Shader
{
	const std::string Clearcoat_normal_fragment_begin = R"(
#ifdef CLEARCOAT

	vec3 clearcoatNormal = geometryNormal;

#endif
)";
}

