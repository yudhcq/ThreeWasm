#pragma once
#include <stdint.h>
#include <memory>
#include <unordered_map>
#include "EventDispatcher.h"
#include "../Math/Box3.h"
#include "../Math/Sphere.h"

#include "Guid.h"

namespace Three
{
    class BufferAttribute;
    class Matrix4;
    class Object3D;
    class Geometry;
    class DirectGeometry;

    class BufferGeometry : public EventDispatcher
    {
    public:
        BufferGeometry();
        const std::shared_ptr<BufferAttribute>& GetIndex() const;
        void SetIndx(const std::shared_ptr<BufferAttribute>& index);
        void SetAttribute(const std::string& name, const std::shared_ptr<BufferAttribute>& attribute);
        const std::shared_ptr<BufferAttribute>& GetAttribute(const std::string& name);
        void DeleteAttribute(const std::string& name);
        void AddGroup(size_t start, size_t count);
        void AddGroup(size_t start, size_t count, size_t materialIndex);
        void ClearGroups();
        void SetDrawRange(size_t start, size_t count);
        void ApplyMatrix4(const Matrix4& m);

        void RotateX(double angle);
        void RotateY(double angle);
        void RotateZ(double angle);
        void Translate(double x, double y, double z);

        void Scale(double x, double y, double z);

        void LookAt(const Vector3& v);

        void Center();

        void SetFromObject(const Object3D& object);

        void SetFromPoints(const std::vector<Vector3>& points);
        void SetFromPoints(const std::vector<Vector2>& points);

        void UpdateFromObject(const Object3D& object);

        void FromGeometry(const Geometry& geometry);

        void FromDirectGeometry(const DirectGeometry& geometry);

        void ComputeBoundingBox();

        void ComputeBoundingSphere();

        void ComputeVertexNormals();

        void Merge(const BufferGeometry& geometry, size_t offset);

        void NormalizeNormals();

        void ToNonIndexed();

        std::string ToJson() const;

    public:
        static size_t MaxIndex;
    private:
        static size_t BufferGeometryId;
    public:
        size_t id;
        Guid uuid;
        std::string name;
        std::shared_ptr<BufferAttribute> index;
        std::unordered_map<std::string, std::shared_ptr<BufferAttribute>> attributes;
        std::unordered_map<std::string, std::shared_ptr<BufferAttribute>> morphAttributes;
        bool morphTargetsRelative;
        struct Group
        {
            size_t start;
            size_t count;
            size_t materialIndex;
        };
        std::vector<Group> groups;
        Box3 boundingBox;
        Sphere boudingSphere;
        struct DrawRange
        {
            size_t start;
            size_t count;
        } drawRange;

        void* userData;
    };
} // namespace Three
