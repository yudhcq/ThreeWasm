#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Color_vertex = R"(
#if defined( USE_COLOR ) || defined( USE_INSTANCING_COLOR )

	vColor = vec3( 1.0 );

#endif

#ifdef USE_COLOR

	vColor.xyz *= color.xyz;

#endif

#ifdef USE_INSTANCING_COLOR

	vColor.xyz *= instanceColor.xyz;

#endif
)";
}
