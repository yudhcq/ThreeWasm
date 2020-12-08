#pragma once
#include <string>
namespace Three
{
    const std::string Map_fragment = R"(
#ifdef USE_MAP

	vec4 texelColor = texture2D( map, vUv );

	texelColor = mapTexelToLinear( texelColor );
	diffuseColor *= texelColor;

#endif
)";
}
