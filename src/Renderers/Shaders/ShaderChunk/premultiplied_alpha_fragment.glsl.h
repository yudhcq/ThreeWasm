#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Premultiplied_alpha_fragment = R"(
#ifdef PREMULTIPLIED_ALPHA

	// Get get normal blending with premultipled, use with CustomBlending, OneFactor, OneMinusSrcAlphaFactor, AddEquation.
	gl_FragColor.rgb *= gl_FragColor.a;

#endif
)";
}
