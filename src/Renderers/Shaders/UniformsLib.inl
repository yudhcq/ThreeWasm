#include "UniformsLib.h"
#include "Uniform.h"
#include "../../Math/Color.h"
#include "../../Textures/Texture.h"
#include "../../Math/Matrix3.h"

#include <memory>
#include <cstdarg>

namespace Three
{
    inline UniformsLib::UniformsLib() noexcept
    {};

    inline bool UniformsLib::AddUniform(const std::string& uniformName, const Uniform& uniform)
    {
        if (mUniforms.find(uniformName) == mUniforms.end())
        {
            mUniforms[uniformName] = uniform;
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool UniformsLib::AddUniform(const std::string& uniformName, const void* const value, size_t memorySize)
    {
        if (mUniforms.find(uniformName) == mUniforms.end())
        {
            mUniforms[uniformName] = Uniform(value, memorySize);
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool UniformsLib::RemoveUniform(const std::string& uniformName)
    {
        auto _unformItertor = mUniforms.find(uniformName);
        if (_unformItertor == mUniforms.end())
        {
            return false;
        }
        else
        {
            mUniforms.erase(_unformItertor);
            return true;
        }
    }

    inline bool UniformsLib::HasUniform(const std::string& uniformName) noexcept
    {
        return mUniforms.find(uniformName) == mUniforms.end();
    }

    inline bool UniformsLib::empty() const noexcept
    {
        return mUniforms.empty();
    }

    size_t UniformsLib::GetUniformsCount() const noexcept
    {
        return mUniforms.size();
    }

    UniformsLib UniformsLib::common;
    UniformsLib UniformsLib::specularmap;
    UniformsLib UniformsLib::envmap;
    UniformsLib UniformsLib::aomap;
    UniformsLib UniformsLib::lightmap;
    UniformsLib UniformsLib::emissivemap;
    UniformsLib UniformsLib::bumpmap;
    UniformsLib UniformsLib::normalmap;
    UniformsLib UniformsLib::displacementmap;
    UniformsLib UniformsLib::roughnessmap;
    UniformsLib UniformsLib::metalnessmap;
    UniformsLib UniformsLib::gradientmap;
    UniformsLib UniformsLib::fog;
    UniformsLib UniformsLib::lights;
    UniformsLib UniformsLib::points;
    UniformsLib UniformsLib::sprite;

    const UniformsLib& UniformsLib::GetCommonUniformsLib()
    {
        if (common.empty())
        {
            const Color _c(0xeeeeee);
            common.AddUniform("diffuse", &_c, sizeof(Color));
            const float _opacity = 1.0;
            common.AddUniform("opacity", &_opacity, 4);
            const shared_ptr<Texture> _map = nullptr;
            common.AddUniform("map", &_map, sizeof(std::shared_ptr<Texture>));
            const Matrix3 _uvTransform;
            const Matrix3 _uv2Transform;
            common.AddUniform("uvTransform", &_uvTransform, sizeof(Matrix3));
            common.AddUniform("uv2Transform", &_uv2Transform, sizeof(Matrix3));
            const shared_ptr<Texture> _alphaMap = nullptr;
            common.AddUniform("alphaMap", &_alphaMap, sizeof(std::shared_ptr<Texture>));
        }

        return common;
    }

    const UniformsLib& UniformsLib::GetSpecularmapUniformsLib()
    {
        if (specularmap.empty())
        {
            const shared_ptr<Texture> _specularMap = nullptr;
            specularmap.AddUniform("specularMap", &_specularMap, sizeof(std::shared_ptr<Texture>));
        }
        return specularmap;
    }

    const UniformsLib& UniformsLib::GetEnvmapUniformsLib()
    {
        if (envmap.empty())
        {
            const shared_ptr<Texture> _envMap = nullptr;
            envmap.AddUniform("envMap", &_envMap, sizeof(std::shared_ptr<Texture>));
            const float _flipEnvMap = -1.f;
            const float _reflectivity = 1.f;
            const float _refractionRatio = 0.98f;
            const float _maxMipLevel = 0.f;
            envmap.AddUniform("flipEnvMap", &_flipEnvMap, 4);
            envmap.AddUniform("reflectivity", &_reflectivity, 4);
            envmap.AddUniform("refractionRatio", &_refractionRatio, 4);
            envmap.AddUniform("maxMipLevel", &_maxMipLevel, 4);
        }
        return envmap;
    }

    const UniformsLib& UniformsLib::GetAomapUniformsLib()
    {
        if (aomap.empty())
        {
            const shared_ptr<Texture> _aoMap = nullptr;
            aomap.AddUniform("aoMap", &_aoMap, sizeof(std::shared_ptr<Texture>));
            const float _aoMapIntensity = -1.;
            aomap.AddUniform("aoMapIntensity", &_aoMapIntensity, 4);
        }
        return aomap;
    }

    const UniformsLib& UniformsLib::GetLightmapUniformsLib()
    {
        if (lightmap.empty())
        {
            const shared_ptr<Texture> _lightMap = nullptr;
            lightmap.AddUniform("lightMap", &_lightMap, sizeof(std::shared_ptr<Texture>));
            const float _lightMapIntensity = -1.;
            lightmap.AddUniform("lightMapIntensity", &_lightMapIntensity, 4);
        }
        return lightmap;
    }

    const UniformsLib& UniformsLib::GetEmissivemapUniformsLib()
    {
        if (emissivemap.empty())
        {
            const shared_ptr<Texture> _emissiveMap = nullptr;
            emissivemap.AddUniform("emissiveMap", &_emissiveMap, sizeof(std::shared_ptr<Texture>));
        }
        return emissivemap;
    }

    const UniformsLib& UniformsLib::GetBumpmapUniformsLib()
    {
        if (bumpmap.empty())
        {
            const shared_ptr<Texture> _bumpMap = nullptr;
            bumpmap.AddUniform("bumpMap", &_bumpMap, sizeof(std::shared_ptr<Texture>));
            const float _bumpScale = 1.;
            lightmap.AddUniform("bumpScale", &_bumpScale, 4);
        }
        return bumpmap;
    }

    const UniformsLib& UniformsLib::GetNormalmapUniformsLib()
    {
        if (normalmap.empty())
        {
            const shared_ptr<Texture> _normalMap = nullptr;
            normalmap.AddUniform("normalMap", &_normalMap, sizeof(std::shared_ptr<Texture>));
            const Vector2 _normalScale(1.);
            normalmap.AddUniform("normalScale", &_normalScale, sizeof(Vector2));
        }
        return normalmap;
    }

    const UniformsLib& UniformsLib::GetDisplacementmapUniformsLib()
    {
        if (displacementmap.empty())
        {
            const shared_ptr<Texture> _displacementMap = nullptr;
            displacementmap.AddUniform("displacementMap", &_displacementMap, sizeof(std::shared_ptr<Texture>));
            const float _displacementScale = 1.;
            const float _displacementBias = 0.;
            displacementmap.AddUniform("displacementScale", &_displacementScale, 4);
            displacementmap.AddUniform("displacementBias", &_displacementBias, 4);
        }
        return displacementmap;
    }

    const UniformsLib& UniformsLib::GetRoughnessmapUniformsLib()
    {
        return roughnessmap;
    }

    const UniformsLib& UniformsLib::GetMetalnessmapUniformsLib()
    {
        return metalnessmap;
    }

    const UniformsLib& UniformsLib::GetGradientmapUniformsLib()
    {
        return gradientmap;
    }

    const UniformsLib& UniformsLib::GetFogUniformsLib()
    {
        return fog;
    }

    const UniformsLib& UniformsLib::GetLightsUniformsLib()
    {
        return lights;
    }

    const UniformsLib& UniformsLib::GetPointsUniformsLib()
    {
        return points;
    }

    const UniformsLib& UniformsLib::GetSpriteUniformsLib()
    {
        return sprite;
    }

    void UniformsLib::MergeUniformsLibs(size_t count, ...)
    {
        if (count > 0)
        {
            std::va_list _arg_list;
            va_start(_arg_list, count);

            for (size_t _index = 0; _index < count; ++_index)
            {
                const UniformsLib& _uniformsLib = va_arg(_arg_list, UniformsLib);
                for (const auto& _pair : _uniformsLib.mUniforms)
                {
                    AddUniform(std::get<0>(_pair), std::get<1>(_pair));
                }
            }
        }
    }
}