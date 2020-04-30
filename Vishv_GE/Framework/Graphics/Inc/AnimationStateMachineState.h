#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATIONSTATEMACHINE_STATE_H
#define INCLUDED_VISHV_GRAPHICS_ANIMATIONSTATEMACHINE_STATE_H
#pragma once

#include "AnimationEasing.h"

namespace Vishv::Graphics
{
	class AnimationState;

	namespace AnimationTransition
	{
		struct TransitionBase
		{
			std::string variableName;

			AnimationState* myAnimation;
			AnimationState* nextAnimation;

			float transitionDuration = 1.0f;

			EasingHead TransitionAnimation = EasingHead::Sine;
		};

		struct IndexTransition : public TransitionBase
		{
			int indexValue = -1;
		};
		struct BoolTransition : public TransitionBase
		{
			bool condition = false;
		};
		struct  TriggerTransition : public TransitionBase
		{
		};
	}

	class AnimationState
	{
	public:
		AnimationState(int index)
			:AnimationIndex(index)
		{
		}

		std::vector<AnimationTransition::IndexTransition> mTransitionsOnIndex;
		std::vector<AnimationTransition::BoolTransition> mTransitionsOnBool;
		std::vector<AnimationTransition::TriggerTransition> mTransitionsOnTrigger;

		bool IsConnectedToAnyState = true;
		const int AnimationIndex = -1;

		bool canExitAnytime = true;
		float exitTime = 0.95f;		//can be between 0 & 1
	};
}


#endif // !INCLUDED_VISHV_GRAPHICS_ANIMATIONSTATEMACHINE_STATE_H

