#pragma once
#include <string>

namespace Three
{
	const std::string Beginnormal_vertex = R"(
vec3 objectNormal = vec3( normal );

#ifdef USE_TANGENT

	vec3 objectTangent = vec3( tangent.xyz );

#endif
)";
}

