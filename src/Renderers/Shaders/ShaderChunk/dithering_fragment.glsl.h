#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Dithering_fragment = R"(
#ifdef DITHERING

	gl_FragColor.rgb = dithering( gl_FragColor.rgb );

#endif
`;
)";
}
