#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Vsm_vert = R"(
void main() {

	gl_Position = vec4( position, 1.0 );

}
)";
}
