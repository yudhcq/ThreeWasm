#pragma once
#include <string>

namespace Three::Shader
{
    const std::string Alphatest_fragment = R"(
#ifdef ALPHATEST
    if (diffuseColor.a < ALPHATEST) {
        discard;
    }
#endif
)";
}
