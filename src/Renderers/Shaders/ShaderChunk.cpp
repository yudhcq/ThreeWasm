#include "ShaderChunk.h"
#include "ShaderChunk/alphamap_fragment.glsl.h"
#include "ShaderChunk/alphamap_pars_fragment.glsl.h"
#include "ShaderChunk/alphatest_fragment.glsl.h"
#include "ShaderChunk/aomap_fragment.glsl.h"
#include "ShaderChunk/aomap_pars_fragment.glsl.h"
#include "ShaderChunk/beginnormal_vertex.glsl.h"
#include "ShaderChunk/begin_vertex.glsl.h"
#include "ShaderChunk/clearcoat_normal_fragment_begin.glsl.h"
#include "ShaderChunk/clearcoat_normal_fragment_maps.glsl.h"
#include "ShaderChunk/clearcoat_pars_fragment.glsl.h"
#include "ShaderChunk/clipping_planes_fragment.glsl.h"
#include "ShaderChunk/clipping_planes_pars_fragment.glsl.h"
#include "ShaderChunk/clipping_planes_pars_vertex.glsl.h"
#include "ShaderChunk/clipping_planes_vertex.glsl.h"
#include "ShaderChunk/map_fragment.glsl.h"
#include "ShaderChunk/map_pars_fragment.glsl.h"
#include "ShaderChunk/map_particle_fragment.glsl.h"
#include "ShaderChunk/map_particle_pars_fragment.glsl.h"
#include "ShaderChunk/metalnessmap_fragment.glsl.h"
#include "ShaderChunk/metalnessmap_pars_fragment.glsl.h"
#include "ShaderChunk/normalmap_pars_fragment.glsl.h"
#include "ShaderChunk/normal_fragment_begin.glsl.h"
#include "ShaderChunk/normal_fragment_maps.glsl.h"
#include "ShaderChunk/packing.glsl.h"
#include "ShaderChunk/premultiplied_alpha_fragment.glsl.h"
#include "ShaderChunk/project_vertex.glsl.h"
#include "ShaderChunk/roughnessmap_fragment.glsl.h"
#include "ShaderChunk/roughnessmap_pars_fragment.glsl.h"
#include "ShaderChunk/shadowmap_pars_fragment.glsl.h"
#include "ShaderChunk/shadowmap_pars_vertex.glsl.h"
#include "ShaderChunk/shadowmap_vertex.glsl.h"
#include "ShaderChunk/shadowmask_pars_fragment.glsl.h"
#include "ShaderChunk/skinbase_vertex.glsl.h"
#include "ShaderChunk/skinning_pars_vertex.glsl.h"
#include "ShaderChunk/skinning_vertex.glsl.h"
#include "ShaderChunk/skinnormal_vertex.glsl.h"
#include "ShaderChunk/specularmap_fragment.glsl.h"
#include "ShaderChunk/specularmap_pars_fragment.glsl.h"
#include "ShaderChunk/tonemapping_fragment.glsl.h"
#include "ShaderChunk/tonemapping_pars_fragment.glsl.h"
#include "ShaderChunk/transmissionmap_fragment.glsl.h"
#include "ShaderChunk/transmissionmap_pars_fragment.glsl.h"
#include "ShaderChunk/uv2_pars_fragment.glsl.h"
#include "ShaderChunk/uv2_pars_vertex.glsl.h"
#include "ShaderChunk/uv2_vertex.glsl.h"
#include "ShaderChunk/uv_pars_fragment.glsl.h"
#include "ShaderChunk/uv_pars_vertex.glsl.h"
#include "ShaderChunk/uv_vertex.glsl.h"
#include "ShaderChunk/worldpos_vertex.glsl.h"
#include "ShaderChunk/bsdfs.glsl.h"
#include "ShaderChunk/bumpmap_pars_fragment.glsl.h"
#include "ShaderChunk/color_fragment.glsl.h"
#include "ShaderChunk/color_pars_fragment.glsl.h"
#include "ShaderChunk/color_pars_vertex.glsl.h"
#include "ShaderChunk/color_vertex.glsl.h"
#include "ShaderChunk/common.glsl.h"
#include "ShaderChunk/cube_uv_reflection_fragment.glsl.h"
#include "ShaderChunk/defaultnormal_vertex.glsl.h"
#include "ShaderChunk/default_fragment.glsl.h"
#include "ShaderChunk/default_vertex.glsl.h"
#include "ShaderChunk/displacementmap_pars_vertex.glsl.h"
#include "ShaderChunk/displacementmap_vertex.glsl.h"
#include "ShaderChunk/emissivemap_fragment.glsl.h"
#include "ShaderChunk/emissivemap_pars_fragment.glsl.h"
#include "ShaderChunk/encodings_fragment.glsl.h"
#include "ShaderChunk/encodings_pars_fragment.glsl.h"
#include "ShaderChunk/envmap_common_pars_fragment.glsl.h"
#include "ShaderChunk/envmap_fragment.glsl.h"
#include "ShaderChunk/envmap_pars_fragment.glsl.h"
#include "ShaderChunk/envmap_pars_vertex.glsl.h"
#include "ShaderChunk/envmap_physical_pars_fragment.glsl.h"
#include "ShaderChunk/envmap_vertex.glsl.h"
#include "ShaderChunk/fog_fragment.glsl.h"
#include "ShaderChunk/fog_pars_fragment.glsl.h"
#include "ShaderChunk/fog_pars_vertex.glsl.h"
#include "ShaderChunk/fog_vertex.glsl.h"
#include "ShaderChunk/gradientmap_pars_fragment.glsl.h"
#include "ShaderChunk/lightmap_fragment.glsl.h"
#include "ShaderChunk/lightmap_pars_fragment.glsl.h"
#include "ShaderChunk/lights_fragment_begin.glsl.h"
#include "ShaderChunk/lights_fragment_end.glsl.h"
#include "ShaderChunk/lights_fragment_maps.glsl.h"
#include "ShaderChunk/lights_lambert_vertex.glsl.h"
#include "ShaderChunk/lights_pars_begin.glsl.h"
#include "ShaderChunk/lights_phong_fragment.glsl.h"
#include "ShaderChunk/lights_phong_pars_fragment.glsl.h"
#include "ShaderChunk/lights_physical_fragment.glsl.h"
#include "ShaderChunk/lights_physical_pars_fragment.glsl.h"
#include "ShaderChunk/lights_toon_fragment.glsl.h"
#include "ShaderChunk/lights_toon_pars_fragment.glsl.h"
#include "ShaderChunk/logdepthbuf_fragment.glsl.h"
#include "ShaderChunk/logdepthbuf_pars_fragment.glsl.h"
#include "ShaderChunk/logdepthbuf_pars_vertex.glsl.h"
#include "ShaderChunk/logdepthbuf_vertex.glsl.h"
#include "ShaderChunk/morphnormal_vertex.glsl.h"
#include "ShaderChunk/morphtarget_pars_vertex.glsl.h"
#include "ShaderChunk/morphtarget_vertex.glsl.h"
#include "ShaderChunk/dithering_fragment.glsl.h"
#include "ShaderChunk/dithering_pars_fragment.glsl.h"

#include "ShaderLib/background_frag.glsl.h"
#include "ShaderLib/background_vert.glsl.h"
#include "ShaderLib/cube_frag.glsl.h"
#include "ShaderLib/cube_vert.glsl.h"
#include "ShaderLib/depth_frag.glsl.h"
#include "ShaderLib/depth_vert.glsl.h"
#include "ShaderLib/distanceRGBA_frag.glsl.h"
#include "ShaderLib/distanceRGBA_vert.glsl.h"
#include "ShaderLib/equirect_frag.glsl.h"
#include "ShaderLib/equirect_vert.glsl.h"
#include "ShaderLib/linedashed_frag.glsl.h"
#include "ShaderLib/linedashed_vert.glsl.h"
#include "ShaderLib/meshbasic_frag.glsl.h"
#include "ShaderLib/meshbasic_vert.glsl.h"
#include "ShaderLib/meshlambert_frag.glsl.h"
#include "ShaderLib/meshlambert_vert.glsl.h"
#include "ShaderLib/meshmatcap_frag.glsl.h"
#include "ShaderLib/meshmatcap_vert.glsl.h"
#include "ShaderLib/meshphong_frag.glsl.h"
#include "ShaderLib/meshphong_vert.glsl.h"
#include "ShaderLib/meshphysical_frag.glsl.h"
#include "ShaderLib/meshphysical_vert.glsl.h"
#include "ShaderLib/meshtoon_frag.glsl.h"
#include "ShaderLib/meshtoon_vert.glsl.h"
#include "ShaderLib/normal_frag.glsl.h"
#include "ShaderLib/normal_vert.glsl.h"
#include "ShaderLib/points_frag.glsl.h"
#include "ShaderLib/points_vert.glsl.h"
#include "ShaderLib/sprite_frag.glsl.h"
#include "ShaderLib/sprite_vert.glsl.h"
#include "ShaderLib/shadow_frag.glsl.h"
#include "ShaderLib/shadow_vert.glsl.h"
#include "ShaderLib/vsm_frag.glsl.h"
#include "ShaderLib/vsm_vert.glsl.h"

namespace Three
{
    std::string ShaderChunk::alphamap_fragment = Alphamap_fragment;
    std::string ShaderChunk::alphamap_pars_fragment = Alphamap_pars_fragment;
    std::string ShaderChunk::alphatest_fragment = Alphatest_fragment;
    std::string ShaderChunk::aomap_fragment = Aomap_fragment;
    std::string ShaderChunk::aomap_pars_fragment = Aomap_pars_fragment;
    std::string ShaderChunk::begin_vertex = Begin_vertex;
    std::string ShaderChunk::beginnormal_vertex = Beginnormal_vertex;
    std::string ShaderChunk::bsdfs = Bsdfs;
    std::string ShaderChunk::bumpmap_pars_fragment = Bumpmap_pars_fragment;
    std::string ShaderChunk::clipping_planes_fragment = Clipping_planes_fragment;
    std::string ShaderChunk::clipping_planes_pars_fragment = Clipping_planes_pars_fragment;
    std::string ShaderChunk::clipping_planes_pars_vertex = Clipping_planes_pars_vertex;
    std::string ShaderChunk::clipping_planes_vertex = Clipping_planes_vertex;
    std::string ShaderChunk::color_fragment = Color_fragment;
    std::string ShaderChunk::color_pars_fragment = Color_pars_fragment;
    std::string ShaderChunk::color_pars_vertex = color_pars_vertex;
    std::string ShaderChunk::color_vertex = Color_vertex;
    std::string ShaderChunk::common = Commom;
    std::string ShaderChunk::cube_uv_reflection_fragment = Cube_uv_reflection_fragment;
    std::string ShaderChunk::defaultnormal_vertex = Defaultnormal_vertex;
    std::string ShaderChunk::displacementmap_pars_vertex = Displacementmap_pars_vertex;
    std::string ShaderChunk::displacementmap_vertex = Displacementmap_vertex;
    std::string ShaderChunk::emissivemap_fragment = Emissivemap_fragment;
    std::string ShaderChunk::emissivemap_pars_fragment = Emissivemap_pars_fragment;
    std::string ShaderChunk::encodings_fragment = Encodings_fragment;
    std::string ShaderChunk::encodings_pars_fragment = Encodings_pars_fragment;
    std::string ShaderChunk::envmap_fragment = Envmap_fragment;
    std::string ShaderChunk::envmap_common_pars_fragment = Envmap_common_pars_fragment;
    std::string ShaderChunk::envmap_pars_fragment = Envmap_pars_fragment;
    std::string ShaderChunk::envmap_pars_vertex = Envmap_pars_vertex;
    std::string ShaderChunk::envmap_physical_pars_fragment = Envmap_physical_pars_fragment;
    std::string ShaderChunk::envmap_vertex = Envmap_vertex;
    std::string ShaderChunk::fog_vertex = Fog_vertex;
    std::string ShaderChunk::fog_pars_vertex = Fog_pars_vertex;
    std::string ShaderChunk::fog_fragment = Fog_fragment;
    std::string ShaderChunk::fog_pars_fragment = Fog_pars_fragment;
    std::string ShaderChunk::gradientmap_pars_fragment = Gradientmap_pars_fragment;
    std::string ShaderChunk::lightmap_fragment = Lightmap_fragment;
    std::string ShaderChunk::lightmap_pars_fragment = Lightmap_pars_fragment;
    std::string ShaderChunk::lights_lambert_vertex = Lights_lambert_vertex;
    std::string ShaderChunk::lights_pars_begin = Lights_pars_begin;
    std::string ShaderChunk::lights_toon_fragment = Lights_toon_fragment;
    std::string ShaderChunk::lights_toon_pars_fragment = Lights_toon_pars_fragment;
    std::string ShaderChunk::lights_phong_fragment = Lights_phong_fragment;
    std::string ShaderChunk::lights_phong_pars_fragment = Lights_phong_pars_fragment;
    std::string ShaderChunk::lights_physical_fragment = Lights_physical_fragment;
    std::string ShaderChunk::lights_physical_pars_fragment = Lights_physical_pars_fragment;
    std::string ShaderChunk::lights_fragment_begin = Lights_fragment_begin;
    std::string ShaderChunk::lights_fragment_maps = Lights_fragment_maps;
    std::string ShaderChunk::lights_fragment_end = Lights_fragment_end;
    std::string ShaderChunk::logdepthbuf_fragment = Logdepthbuf_fragment;
    std::string ShaderChunk::logdepthbuf_pars_fragment = Logdepthbuf_pars_fragment;
    std::string ShaderChunk::logdepthbuf_pars_vertex = Logdepthbuf_pars_vertex;
    std::string ShaderChunk::logdepthbuf_vertex = Logdepthbuf_vertex;
    std::string ShaderChunk::map_fragment = Map_fragment;
    std::string ShaderChunk::map_pars_fragment = Map_pars_fragment;
    std::string ShaderChunk::map_particle_fragment = Map_particle_fragment;
    std::string ShaderChunk::map_particle_pars_fragment = Map_particle_pars_fragment;
    std::string ShaderChunk::metalnessmap_fragment = Metalnessmap_fragment;
    std::string ShaderChunk::metalnessmap_pars_fragment = Metalnessmap_pars_fragment;
    std::string ShaderChunk::morphnormal_vertex = Morphnormal_vertex;
    std::string ShaderChunk::morphtarget_pars_vertex = Morphtarget_pars_vertex;
    std::string ShaderChunk::morphtarget_vertex = Morphtarget_vertex;
    std::string ShaderChunk::normal_fragment_begin = Normal_fragment_begin;
    std::string ShaderChunk::normal_fragment_maps = Normal_fragment_maps;
    std::string ShaderChunk::normalmap_pars_fragment = Normalmap_pars_fragment;
    std::string ShaderChunk::clearcoat_normal_fragment_begin = Clearcoat_normal_fragment_begin;
    std::string ShaderChunk::clearcoat_normal_fragment_maps = Clearcoat_normal_fragment_maps;
    std::string ShaderChunk::clearcoat_pars_fragment = clearcoat_pars_fragment;
    std::string ShaderChunk::packing = Packing;
    std::string ShaderChunk::premultiplied_alpha_fragment = Premultiplied_alpha_fragment;
    std::string ShaderChunk::project_vertex = Project_vertex;
    std::string ShaderChunk::dithering_fragment = Dithering_fragment;
    std::string ShaderChunk::dithering_pars_fragment = Dithering_pars_fragment;
    std::string ShaderChunk::roughnessmap_fragment = Roughnessmap_fragment;
    std::string ShaderChunk::roughnessmap_pars_fragment = Roughnessmap_pars_fragment;
    std::string ShaderChunk::shadowmap_pars_fragment =  Shadowmap_pars_fragment;
    std::string ShaderChunk::shadowmap_pars_vertex = Shadowmap_pars_vertex;
    std::string ShaderChunk::shadowmap_vertex = Shadowmap_vertex;
    std::string ShaderChunk::shadowmask_pars_fragment = Shadowmask_pars_fragment;
    std::string ShaderChunk::skinbase_vertex = Skinbase_vertex;
    std::string ShaderChunk::skinning_pars_vertex = Skinning_pars_vertex;
    std::string ShaderChunk::skinning_vertex = Skinning_vertex;
    std::string ShaderChunk::skinnormal_vertex = Skinnormal_vertex;
    std::string ShaderChunk::specularmap_fragment = Specularmap_fragment;
    std::string ShaderChunk::specularmap_pars_fragment = Specularmap_pars_fragment;
    std::string ShaderChunk::tonemapping_fragment = Tonemapping_fragment;
    std::string ShaderChunk::tonemapping_pars_fragment = Tonemapping_pars_fragment;
    std::string ShaderChunk::transmissionmap_fragment = Transmissionmap_fragment;
    std::string ShaderChunk::transmissionmap_pars_fragment = Transmissionmap_pars_fragment;
    std::string ShaderChunk::uv_pars_fragment = Uv_pars_fragment;
    std::string ShaderChunk::uv_pars_vertex = Uv_pars_vertex;
    std::string ShaderChunk::uv_vertex = Uv_vertex;
    std::string ShaderChunk::uv2_pars_fragment = Uv2_pars_fragment;
    std::string ShaderChunk::uv2_pars_vertex = Uv2_pars_vertex;
    std::string ShaderChunk::uv2_vertex = Uv2_vertex;
    std::string ShaderChunk::worldpos_vertex = Worldpos_vertex;

    std::string ShaderChunk::background_frag = Background_frag;
    std::string ShaderChunk::background_vert = Background_vert;
    std::string ShaderChunk::cube_frag = Cube_frag;
    std::string ShaderChunk::cube_vert = Cube_vert;
    std::string ShaderChunk::depth_frag = Depth_frag;
    std::string ShaderChunk::depth_vert = Depth_vert;
    std::string ShaderChunk::distanceRGBA_frag = DistanceRGBA_frag;
    std::string ShaderChunk::distanceRGBA_vert = DistanceRGBA_vert;
    std::string ShaderChunk::equirect_frag = Equirect_frag;
    std::string ShaderChunk::equirect_vert = Equirect_vert;
    std::string ShaderChunk::linedashed_frag = Linedashed_frag;
    std::string ShaderChunk::linedashed_vert = Linedashed_vert;
    std::string ShaderChunk::meshbasic_frag = Meshbasic_frag;
    std::string ShaderChunk::meshbasic_vert = Meshbasic_vert;
    std::string ShaderChunk::meshlambert_frag = Meshlambert_frag;
    std::string ShaderChunk::meshlambert_vert = Meshlambert_vert;
    std::string ShaderChunk::meshmatcap_frag = Meshmatcap_frag;
    std::string ShaderChunk::meshmatcap_vert = Meshmatcap_vert;
    std::string ShaderChunk::meshtoon_frag = Meshtoon_frag;
    std::string ShaderChunk::meshtoon_vert = Meshtoon_vert;
    std::string ShaderChunk::meshphong_frag = Meshphong_frag;
    std::string ShaderChunk::meshphong_vert = Meshbasic_vert;
    std::string ShaderChunk::meshphysical_frag = Meshphysical_frag;
    std::string ShaderChunk::meshphysical_vert = Meshphysical_vert;
    std::string ShaderChunk::normal_frag = Normal_frag;
    std::string ShaderChunk::normal_vert = Normal_vert;
    std::string ShaderChunk::points_frag = Points_frag;
    std::string ShaderChunk::points_vert = Points_vert;
    std::string ShaderChunk::shadow_frag = Shadow_frag;
    std::string ShaderChunk::shadow_vert = Shadow_vert;
    std::string ShaderChunk::sprite_frag = Sprite_frag;
    std::string ShaderChunk::sprite_vert = Sprite_vert;
}