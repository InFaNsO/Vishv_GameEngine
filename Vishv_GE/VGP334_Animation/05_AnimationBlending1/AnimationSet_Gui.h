#pragma once
#include "Vishv/Inc/Vishv.h"

enum class AnimationMovement
{
	none = -1,
	IdleStanding1,
	IdleStanding2,

	IdleCrouching1,
	IdleCrouching2,

	IdleAiming1,
	IdleAiming2,

	WalkForward,
	WalkLeft,
	WalkRight,
	WalkBackward,

	CrouchWalkingForward,
	CrouchWalkingLeft,
	CrouchWalkingRight,
	CrouchWalkingBackward,

	AimWalkingForward,
	AimWalkingLeft,
	AimWalkingRight,
	AimWalkingBackward,

	Count
	//add more if needed
};



namespace Vishv::UI
{
	class AnimationSetUI
	{
	public:

		static std::string ToString(AnimationMovement move);
		void DrawUI();
		void SetAnimationSet(Vishv::Graphics::AnimationSet* anim) { animationSet = anim; }

		void DrawBlendUI();

		AnimationMovement GetBlendMovement(std::vector<AnimationMovement>& animations);

		void SetCurrrentAnimation(AnimationMovement move) { current = move; }

	private:

		void AnimationSettings(size_t animationID);
		void BoneAnimationSeting(Vishv::Graphics::BoneAnimation* animation);

		AnimationMovement current = AnimationMovement::none;
		AnimationMovement next = AnimationMovement::none;

		bool switchNow = false;
		Vishv::Graphics::AnimationSet* animationSet;
	};
}

