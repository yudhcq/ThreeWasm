#pragma once
#include <string>
namespace Three
{
    const std::string Displacementmap_vertex = R"(
#ifdef USE_DISPLACEMENTMAP

	transformed += normalize( objectNormal ) * ( texture2D( displacementMap, vUv ).x * displacementScale + displacementBias );

#endif
)";
}
