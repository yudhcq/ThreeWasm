#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Uv2_pars_fragment = R"(
#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )

	varying vec2 vUv2;

#endif
)";
}