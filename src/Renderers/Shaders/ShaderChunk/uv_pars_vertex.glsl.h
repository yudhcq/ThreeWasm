#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Uv_pars_vertex = R"(
#ifdef USE_UV

	#ifdef UVS_VERTEX_ONLY

		vec2 vUv;

	#else

		varying vec2 vUv;

	#endif

	uniform mat3 uvTransform;

#endif
)";
}
