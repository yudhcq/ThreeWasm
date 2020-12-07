#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Map_particle_pars_fragment = R"(
#if defined( USE_MAP ) || defined( USE_ALPHAMAP )

	uniform mat3 uvTransform;

#endif

#ifdef USE_MAP

	uniform sampler2D map;

#endif

#ifdef USE_ALPHAMAP

	uniform sampler2D alphaMap;

#endif
)";
}
