#ifndef INCLUDED_VISHV_COMPONENTS_MESH_COMPONENET_H
#define INCLUDED_VISHV_COMPONENTS_MESH_COMPONENET_H

#include "Component.h"

namespace Vishv::Components
{
	class TransformComponent;
	class ColliderComponent;

	class MeshComponent : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Render() override;
		void SimpleDraw() override;
		void DebugUI() override;

		int GetShape() { return mShape; }
		const Vishv::Graphics::ModelBase<Vishv::Graphics::MeshPX>& GetModel() { return mModel; }

		Math::Vector3 Getlengths() { return { mLength1, mLength2, mLength3 }; }

		void Set(int shape, float l1, float l2, float l3, std::filesystem::path& diffPath, std::filesystem::path& normPath, std::filesystem::path& specPath);

	private:
		void ImportUI();
		void InitMesh();

		TransformComponent* mTransformComponent;
		int mShape = -1;
		Vishv::Graphics::ModelBase<Vishv::Graphics::MeshPX> mModel;
		Vishv::Graphics::Color mColor;
		float mLength1, mLength2, mLength3;

		std::filesystem::path mDiffusePath;
		std::filesystem::path mNormalPath;
		std::filesystem::path mSpecularPath;

		Vishv::Graphics::Camera* mCamera;

		bool mIsFinal = false;
		bool shouldRender = false;
	};
}

#endif // !INCLUDED_VISHV_COMPONENTS_MESH_COMPONENET_H


