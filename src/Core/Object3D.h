#pragma once
#include <memory>
#include <set>

#include "EventDispatcher.h"
#include "Guid.h"
#include "Layers.h"
#include "../Math/Vector3.h"
#include "../Math/Euler.h"
#include "../Math/Matrix4.h"

namespace Three
{
    class Material;
    class WebGLRenderer;
    class Camera;
    class Geometry;
    class Group;
    class Scene;
    class Raycaster;
    struct Intersection;
    class Object3D : public EventDispatcher
    {
    public:
        typedef std::shared_ptr<Object3D> Object3DSharedPtr;

    public:
        Object3D();
        Object3D(const Object3D& object);
        Object3D& operator=(const Object3D& object);

        void OnBeforeRender
        (
            const WebGLRenderer& renderer,
            const Scene& scene,
            const Camera& camera,
            const Geometry& geometry,
            const Material,
            const Group& group
        );
        void OnAfterRender
        (
            const WebGLRenderer& renderer,
            const Scene& scene,
            const Camera& camera,
            const Geometry& geometry,
            const Material,
            const Group& group
        );
        void ApplyMatrix4(const Matrix4& matrix);
        void ApplyQuaternion(const Quaternion& quaternion);
        void SetRotationFromAxisAngle(const Vector3& axis, double angle);
        void SetRotationFromEuler(const Euler euler);
        void SetRotationFromMatrix(const Matrix4& m);
        void SetRotationFromQuaternion(const Quaternion& q);
        void RotateOnAxis(const Vector3& axis, double angle);
        void RotateOnWorldAxis(const Vector3& axis, double angle);
        void RotateX(double angle);
        void RotateY(double angle);
        void RotateZ(double angle);
        void TranslateOnAxis(const Vector3& axis, double distance);
        void TranslateX(double distance);
        void TranslateY(double distance);
        void TranslateZ(double distance);
        Vector3 LocalToWorld(const Vector3& vector) const;
        Vector3 WorldToLocal(const Vector3& vector) const;
        void LookAt(double x, double y, double z);
        void LookAt(const Vector3& vector);
        void Add(const Object3DSharedPtr& objectPtr);
        void Remove(const Object3DSharedPtr& objectPtr);
        void Attach(const Object3DSharedPtr& objectPtr);
        const Object3DSharedPtr& GetObjectById(size_t id) const;
        const Object3DSharedPtr& GetObjectByName(size_t name) const;
        Vector3 GetWorldPosition() const;
        Vector3 GetWorldScale() const;
        Quaternion GetWorldQuaternion() const;
        virtual Vector3 GetWorldDirection() const;
        void Raycast(const Raycaster& raycaster, std::vector<Intersection>& intersections) const;
        void traverse(const std::function<void(const Object3D*)>& callback);
        void traverseVisible(const std::function<void(const Object3D*)>& callback);
        void traverseAncestors(const std::function<void(const Object3D*)>& callback);
        void UpdateMatrix();
        virtual void UpdateMatrixWorld(bool force = false);
        void UpdateWorldMatrix(bool updateParent, bool updateChildren);
        virtual std::string ToJson() const;
    public:
        static Vector3 DefaultUp;
        static bool DefaultMatrixAutoUpdate;
    private:
        static size_t Object3DId;
    public:
        size_t id;
        Guid UUID;
        std::string name;
        Object3D* parent = nullptr;
        std::set<Object3DSharedPtr> children;
        Vector3 up;

        Vector3 position;
        Vector3 scale;
        Euler euler;
        Quaternion quaternion;
        Matrix4 modelViewMatrix;
        Matrix4 normalMatrix;
        Matrix4 matrix;
        Matrix4 matrixWorld;
        bool matrixAutoUpdate;
        bool matrixWorldNeedsUpdate;
        Layers layers;
        bool visible;
        bool castShadow;
        bool receiveShadow;
        bool frustumCulled;
        size_t renderOrder;
        std::shared_ptr<void*> userData;
        std::shared_ptr<Material> customDepthMaterial;
        std::shared_ptr<Material> customDistanceMaterial;
    };
}