#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Displacementmap_pars_vertex = R"(
#ifdef USE_DISPLACEMENTMAP

	uniform sampler2D displacementMap;
	uniform float displacementScale;
	uniform float displacementBias;

#endif
)";
}
