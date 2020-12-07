#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Equirect_vert = R"(
varying vec3 vWorldDirection;

#include <common>

void main() {

	vWorldDirection = transformDirection( position, modelMatrix );

	#include <begin_vertex>
	#include <project_vertex>

}
)";
}
