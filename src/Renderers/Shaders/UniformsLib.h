#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace Three
{
    class Uniform;

    class UniformsLib
    {
    public:
        UniformsLib() noexcept;

        bool AddUniform(const std::string& uniformName, const Uniform& uniform);

        bool AddUniform(const std::string& uniformName, const void* const value, size_t memorySize);

        bool RemoveUniform(const std::string& uniformName);

        bool HasUniform(const std::string& uniformName) noexcept;

        bool empty() const noexcept;

        size_t GetUniformsCount() const noexcept;

        void MergeUniformsLibs(size_t count, ...);

    public:
        static const UniformsLib& GetCommonUniformsLib();
        static const UniformsLib& GetSpecularmapUniformsLib();
        static const UniformsLib& GetEnvmapUniformsLib();
        static const UniformsLib& GetAomapUniformsLib();
        static const UniformsLib& GetLightmapUniformsLib();
        static const UniformsLib& GetEmissivemapUniformsLib();
        static const UniformsLib& GetBumpmapUniformsLib();
        static const UniformsLib& GetNormalmapUniformsLib();
        static const UniformsLib& GetDisplacementmapUniformsLib();
        static const UniformsLib& GetRoughnessmapUniformsLib();
        static const UniformsLib& GetMetalnessmapUniformsLib();
        static const UniformsLib& GetGradientmapUniformsLib();
        static const UniformsLib& GetFogUniformsLib();
        static const UniformsLib& GetLightsUniformsLib();
        static const UniformsLib& GetPointsUniformsLib();
        static const UniformsLib& GetSpriteUniformsLib();
    
    private:
        static UniformsLib common;
        static UniformsLib specularmap;
        static UniformsLib envmap;
        static UniformsLib aomap;
        static UniformsLib lightmap;
        static UniformsLib emissivemap;
        static UniformsLib bumpmap;
        static UniformsLib normalmap;
        static UniformsLib displacementmap;
        static UniformsLib roughnessmap;
        static UniformsLib metalnessmap;
        static UniformsLib gradientmap;
        static UniformsLib fog;
        static UniformsLib lights;
        static UniformsLib points;
        static UniformsLib sprite;
    private:
        std::unordered_map<std::string, Uniform>
            mUniforms;
    };
}

#include "UniformsLib.inl"
