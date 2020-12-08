#pragma once
#include <string>
namespace Three
{
    const std::string Encodings_fragment = R"(
gl_FragColor = linearToOutputTexel( gl_FragColor );
)";
}
