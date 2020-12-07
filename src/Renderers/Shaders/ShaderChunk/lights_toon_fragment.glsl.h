#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Lights_toon_fragment = R"(
ToonMaterial material;
material.diffuseColor = diffuseColor.rgb;
)";
}
