#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Uv2_vertex = R"(
#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )

	vUv2 = ( uv2Transform * vec3( uv2, 1 ) ).xy;

#endif
)";
}
