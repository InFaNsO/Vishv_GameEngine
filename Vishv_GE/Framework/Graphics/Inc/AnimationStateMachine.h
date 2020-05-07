#pragma once
#ifndef INCLUDED_ANIMATIONSTATEMACHINE_H
#define INCLUDED_ANIMATIONSTATEMACHINE_H

#include "AnimationSet.h"
#include "AnimationStateMachineState.h"
#include "RiggedModel.h"

namespace Vishv::Graphics
{
	class AnimationStateMachine
	{
	public:
		AnimationStateMachine(AnimationSet& set, RiggedModel& model, int StartAnimation = 0);

		bool AddIntVariable(std::string& name);
		bool AddIntVariable(std::string&& name);

		bool AddBoolVariable(std::string& name);
		bool AddBoolVariable(std::string&& name);

		bool AddTriggerVariable(std::string& name);
		bool AddTriggerVariable(std::string&& name);

		void GetBoneTransforms(std::vector<Math::Matrix4>& bTransforms);

		bool SetIndex(int indexVal);
		bool SetInt(std::string& variableName, int val);
		bool SetInt(std::string&& variableName, int val);
		
		bool SetBool(std::string& variableName, bool val);
		bool SetBool(std::string&& variableName, bool val);
		
		bool SetTrigger(std::string& variableName);
		bool SetTrigger(std::string&& variableName);

	private:
		void EndTransition();

		void BlendedBoneTransforms(std::vector<Math::Matrix4>& bTransforms);
		void UnBlendedBoneTransforms(std::vector<Math::Matrix4>& bTransforms);

		bool SetInt(std::map<std::string, std::unique_ptr<int>>::iterator iter, int val);
		bool SetBool(std::map<std::string, std::unique_ptr<bool>>::iterator iter, bool val);
		bool SetTrig(std::vector<std::string>::iterator iter);

	private:
		AnimationSet& myAnimations;
		std::vector<AnimationState> mStates;
		AnimationState* mCurrentState;
		
		AnimationState* mNextState= nullptr;
		AnimationTransition::TransitionBase* mCurrentTransition = nullptr;
		float mAnimationTransitionStartTime = 0.0f;

		float animationDuration = 1.0f;
		float animationStartTime = 0.0f;

		std::vector<Math::Matrix4> mTPose;

		std::map<std::string, std::unique_ptr<int>> mIntVariables;
		std::map<std::string, std::unique_ptr<bool>> mBoolVariables;
		std::vector<std::string> mTriggerVariables;

		RiggedModel& mModel;
	};
}

#endif // !INCLUDED_ANIMATIONSTATEMACHINE_H


