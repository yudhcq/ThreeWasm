#include "UniformsLib.h"
#include "../../Math/Color.h"
#include "../../Textures/Texture.h"
#include "../../Math/Matrix3.h"

#include <memory>
#include <cstdarg>

namespace Three::Shader
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
            common.AddUniform("diffuse", &Math::Color(0xee), sizeof(Math::Color));
            const float _opacity = 1.0;
            common.AddUniform("opacity", &_opacity, 4);
            common.AddUniform("map", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            common.AddUniform("uvTransform", &Math::Matrix3(), sizeof(Math::Matrix3));
            common.AddUniform("uv2Transform", &Math::Matrix3(), sizeof(Math::Matrix3));
            common.AddUniform("alphaMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
        }
        
        return common;
    }

    const UniformsLib& UniformsLib::GetSpecularmapUniformsLib()
    {
        if (specularmap.empty())
        {
            specularmap.AddUniform("specularMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
        }
        return specularmap;
    }

    const UniformsLib& UniformsLib::GetEnvmapUniformsLib()
    {
        if (envmap.empty())
        {
            envmap.AddUniform("envMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            const float _flipEnvMap = -1.;
            const float _reflectivity = 1.;
            const float _refractionRatio = 0.98;
            const float _maxMipLevel = 0.;
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
            aomap.AddUniform("aoMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            const float _aoMapIntensity = -1.;
            aomap.AddUniform("aoMapIntensity", &_aoMapIntensity, 4);
        }
        return aomap;
    }

    const UniformsLib& UniformsLib::GetLightmapUniformsLib()
    {
        if (lightmap.empty())
        {
            lightmap.AddUniform("lightMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            const float _lightMapIntensity = -1.;
            lightmap.AddUniform("lightMapIntensity", &_lightMapIntensity, 4);
        }
        return lightmap;
    }

    const UniformsLib& UniformsLib::GetEmissivemapUniformsLib()
    {
        if (emissivemap.empty())
        {
            emissivemap.AddUniform("emissiveMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
        }
        return emissivemap;
    }

    const UniformsLib& UniformsLib::GetBumpmapUniformsLib()
    {
        if (bumpmap.empty())
        {
            bumpmap.AddUniform("bumpMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            const float _bumpScale = 1.;
            lightmap.AddUniform("bumpScale", &_bumpScale, 4);
        }
        return bumpmap;
    }

    const UniformsLib& UniformsLib::GetNormalmapUniformsLib()
    {
        if (normalmap.empty())
        {
            normalmap.AddUniform("normalMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            normalmap.AddUniform("normalScale", &Math::Vector2(1.), sizeof(Math::Vector2));
        }
        return normalmap;
    }

    const UniformsLib& UniformsLib::GetDisplacementmapUniformsLib()
    {
        if (displacementmap.empty())
        {
            displacementmap.AddUniform("displacementMap", &std::make_shared<Textures::Texture>(nullptr), sizeof(std::shared_ptr<Textures::Texture>));
            const float _displacementScale = 1.;
            const float _displacementBias = 0.;
            displacementmap.AddUniform("displacementScale", &_displacementScale, 4);
            displacementmap.AddUniform("displacementBias", &_displacementBias, 4);
        }
        return displacementmap;
    }

    const UniformsLib& UniformsLib::GetRoughnessmapUniformsLib()
    {}

    const UniformsLib& UniformsLib::GetMetalnessmapUniformsLib()
    {}

    const UniformsLib& UniformsLib::GetGradientmapUniformsLib()
    {}

    const UniformsLib& UniformsLib::GetFogUniformsLib()
    {}

    const UniformsLib& UniformsLib::GetLightsUniformsLib()
    {}

    const UniformsLib& UniformsLib::GetPointsUniformsLib()
    {}

    const UniformsLib& UniformsLib::GetSpriteUniformsLib()
    {}

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