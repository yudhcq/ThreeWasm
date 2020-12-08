#pragma once
#include <string>
namespace Three
{
    const std::string Specularmap_fragment = R"(
float specularStrength;

#ifdef USE_SPECULARMAP

	vec4 texelSpecular = texture2D( specularMap, vUv );
	specularStrength = texelSpecular.r;

#else

	specularStrength = 1.0;

#endif
)";
}
