#pragma once
#include <string>
namespace Three
{
    const std::string Map_pars_fragment = R"(
#ifdef USE_MAP

	uniform sampler2D map;

#endif
)";
}
