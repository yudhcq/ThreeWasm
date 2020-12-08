#pragma once
#include <string>
namespace Three
{
    const std::string Uv_vertex = R"(
#ifdef USE_UV

	vUv = ( uvTransform * vec3( uv, 1 ) ).xy;

#endif
)";
}
