#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Tonemapping_fragment = R"(
#if defined( TONE_MAPPING )

	gl_FragColor.rgb = toneMapping( gl_FragColor.rgb );

#endif
)";
}
