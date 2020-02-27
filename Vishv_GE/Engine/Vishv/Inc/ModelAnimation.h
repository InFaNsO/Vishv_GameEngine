#ifndef INCLUDED_VISHV_COMPONENT_MODELANIMATION_COMPONENT
#define INCLUDED_VISHV_COMPONENT_MODELANIMATION_COMPONENT

#include "Component.h"

namespace Vishv::Components
{
	class TransformComponent;
	//class Camera;	Camera Component

	class ModelAnimation : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update(float deltaTime) override;
		void SimpleDraw() override;
		void DebugUI() override;
		void Render() override;
		void Terminate() override;

		void ChangeAnimation(size_t animID) { mNextAnimationIndex = animID; }
		float GetAnimationDuration(size_t animID) { return mModel->animations->animationClips[animID]->duration; }

		//void Set(Graphics::MeshShape shape);
		void Set(std::filesystem::path modelPath, std::string modelNmae, Vishv::Graphics::AnimationSet& animation);
		void Set(Graphics::RiggedModel& model);

		bool IsNextAnim();

		int CurrentrAnimation() { return (int)mCurrentAnimationIndex; }

	private:
		void UpdateAnimationPlayInformation(Graphics::AnimationPlayInformation & play, float deltaTime);
		void UpdateBlend(size_t currentAnimationID, size_t finalAnimationID, float ratio);
		void Update(size_t animationIndex = 0, bool isPlaying = false, bool pause = false);
		void Render(const Graphics::Camera& camera, Graphics::EffectType type = Graphics::EffectType::Skinning);

		void SetUp();


		TransformComponent* mTransformComponent;
		Graphics::RiggedModel* mModel = nullptr;		//define these
		std::vector<Math::Matrix4> mBoneTransforms;
		std::vector<Math::Matrix4> mTPosToParents;

		bool mShouldBlend = false;
		bool mShouldPlay = false;
		float mBlendTimeTotal = 1.f;
		float mBlendTimer = 0.0f;

		size_t mCurrentAnimationIndex = 0;
		size_t mNextAnimationIndex = 0;		//invalid index is 1000
	};
}


#endif // !INCLUDED_VISHV_COMPONENT_MODEL_ANIMATION_COMPONENT




