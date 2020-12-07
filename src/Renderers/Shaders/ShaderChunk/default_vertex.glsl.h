#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Default_vertex = R"(
void main() {
	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
}
)";
}
