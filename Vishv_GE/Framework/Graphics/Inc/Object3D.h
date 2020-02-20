#ifndef INCLUDED_VISHV_GRAPHICS_OBJECT3D_H
#define INCLUDED_VISHV_GRAPHICS_OBJECT3D_H

#include "RiggedModel.h"
#include "MeshBuffer.h"
#include "EffectsManager.h"

namespace Vishv::Graphics
{
	class Camera;

	enum class MeshShape
	{
		Cylinder,
		Sphere,
		Cube,
	};

	class Object3D
	{
	public:
		Object3D() = default;
		Object3D(Math::Transform& transformation)
			:transform(transformation)
		{
		}

		void Set(MeshShape shape);
		void Set(std::filesystem::path modelPath);

		void Update(size_t animationIndex = 0, bool isPlaying = false, bool pause = false);
		void Render(const Camera& camera, EffectType type, bool SceneRender = true);
		void Render(const Camera& camera, Math::Transform& otherTransform, EffectType type = EffectType::Skinning, bool SceneRender = true);

		void UpdateBlend(size_t currentAnimationID, size_t finalAnimationID, float ratio);

		Vishv::Math::Transform transform;
		RiggedModel mModel;
		std::vector<Vishv::Math::Matrix4> boneTransforms;
		std::vector<Vishv::Math::Matrix4> tPoseToParents;
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_OBJECT3D_H


