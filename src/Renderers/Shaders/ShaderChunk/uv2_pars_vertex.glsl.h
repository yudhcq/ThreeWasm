#pragma once
#include <string>
namespace Three
{
    const std::string Uv2_pars_vertex = R"(
#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )

	attribute vec2 uv2;
	varying vec2 vUv2;

	uniform mat3 uv2Transform;

#endif
)";
}
