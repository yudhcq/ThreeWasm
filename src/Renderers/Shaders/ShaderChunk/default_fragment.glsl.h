#pragma once
#include <string>
namespace Three
{
    const std::string Default_fragment = R"(
void main() {
	gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );
}
)";
}
