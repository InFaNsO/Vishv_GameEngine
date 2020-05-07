#pragma once
#ifndef INCLUDED_VISHV_COMPONENT_ANIMATION_3D_H
#define INCLUDED_VISHV_COMPONENT_ANIMATION_3D_H

#include "Component.h"

namespace Vishv::Components
{
	class Model3D;
	class TransformComponent;

	class Animation3D : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;
		void DebugUI() override;

		void Terminate() override
		{
			mAnimations->animationClips.clear();
			delete mAnimations;
		}

		void SetAnimations(Graphics::AnimationSet& animationSet);
		bool SetAnimationIndex(int index);



	private:
		friend class Model3D;
		void BindBonesToBuffer();

		Model3D* myModel = nullptr;
		TransformComponent* myTransform = nullptr;

		Graphics::AnimationSet* mAnimations = nullptr;
		std::unique_ptr<Graphics::AnimationStateMachine> mAniamtionStateMachine = nullptr;
		
		int currentAnim = 0;

		std::vector<Math::Matrix4> mBoneTransforms	; //holds animation position transform matrix for the model
	};
}

#endif // !INCLUDED_VISHV_COMPONENT_MODEL_3D


