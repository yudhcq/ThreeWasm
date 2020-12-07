#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Uv_pars_fragment = R"(
#if ( defined( USE_UV ) && ! defined( UVS_VERTEX_ONLY ) )

	varying vec2 vUv;

#endif
)";
}
