#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Encodings_fragment = R"(
gl_FragColor = linearToOutputTexel( gl_FragColor );
)";
}
