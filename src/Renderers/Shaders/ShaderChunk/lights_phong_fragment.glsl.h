#pragma once
#include <string>
namespace Three::Shader
{
    const std::string Lights_phong_fragment = R"(
BlinnPhongMaterial material;
material.diffuseColor = diffuseColor.rgb;
material.specularColor = specular;
material.specularShininess = shininess;
material.specularStrength = specularStrength;
)";
}
