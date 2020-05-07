#include "Precompiled.h"
#include "AnimationStateMachine.h"
#include "Bone.h"

Vishv::Graphics::AnimationStateMachine::AnimationStateMachine(AnimationSet& set, RiggedModel& model, int StartAnimation)
	:myAnimations(set)
	,mModel(model)
{
	mTPose.reserve(mModel.mTPosToParent.size());
	for (auto& pos : mModel.mTPosToParent)
	{
		mTPose.emplace_back(pos);
	}

	mStates.reserve(myAnimations.animationClips.size());
	for (int i = 0; i < myAnimations.animationClips.size(); ++i)
		mStates.emplace_back(i);

	mCurrentState = &mStates[StartAnimation];
	auto [iter, success] = mIntVariables.insert({ "Index", std::make_unique<int>(StartAnimation) });
}

bool Vishv::Graphics::AnimationStateMachine::SetIndex(int indexVal)
{
	return SetInt(mIntVariables.find("Index"), indexVal);
}
bool Vishv::Graphics::AnimationStateMachine::SetInt(std::string& variableName, int val)
{
	return SetInt(mIntVariables.find(variableName), val);
}
bool Vishv::Graphics::AnimationStateMachine::SetInt(std::string&& variableName, int val)
{
	return SetInt(mIntVariables.find(std::move(variableName)), val);
}
bool Vishv::Graphics::AnimationStateMachine::SetInt(std::map<std::string, std::unique_ptr<int>>::iterator iter, int val)
{
	if (iter == mIntVariables.end())
	{
		return false;
	}

	int nextState = -1;

	float currentExitVal = animationStartTime + myAnimations.animationClips[mCurrentState->AnimationIndex]->duration / Core::Time::Get()->CurrentTime();
	if (mCurrentState->IsConnectedToAnyState)
	{
		if (!mCurrentState->canExitAnytime)
		{
			if (currentExitVal >= mCurrentState->exitTime)
				nextState = val;
		}
		else nextState = val;

		if (nextState > -1)
		{
			for (auto& intTrans : mCurrentState->mTransitionsOnIndex)
			{
				if (intTrans.variableName == iter->first && val == intTrans.indexValue)
				{
					nextState = val;
					mCurrentTransition = &intTrans;
					break;
				}
			}
		}
	}
	else
	{
		bool canChange = false;
		if (!mCurrentState->canExitAnytime)
		{
			if (currentExitVal >= mCurrentState->exitTime)
				canChange = true;
		}

		if (canChange)
		{
			for (auto& intTrans : mCurrentState->mTransitionsOnIndex)
			{
				if (intTrans.variableName == iter->first && val == intTrans.indexValue)
				{
					nextState = val;
					mCurrentTransition = &intTrans;
					break;
				}
			}
		}
	}

	if (nextState == -1)
		return false;

	//do transition;
	//animationDuration = myAnimations.animationClips[mCurrentState->AnimationIndex].get()->duration;
	mNextState = &mStates[nextState];
	mAnimationTransitionStartTime = Core::Time::Get()->CurrentTime();
	*iter->second.get() = val;
	return false;
}

bool Vishv::Graphics::AnimationStateMachine::SetBool(std::string& variableName, bool val)
{
	return SetBool(mBoolVariables.find(variableName), val);
}
bool Vishv::Graphics::AnimationStateMachine::SetBool(std::string&& variableName, bool val)
{
	return SetBool(mBoolVariables.find(std::move(variableName)), val);
}
bool Vishv::Graphics::AnimationStateMachine::SetBool(std::map<std::string, std::unique_ptr<bool>>::iterator iter, bool val)
{
	if (iter == mBoolVariables.end())
		return false;

	int nextStateInd = -1;

	float currentExitVal = animationStartTime + myAnimations.animationClips[mCurrentState->AnimationIndex]->duration / Core::Time::Get()->CurrentTime();
	bool canChange = true;
	if (!mCurrentState->canExitAnytime)
	{
		if (currentExitVal < mCurrentState->exitTime)
			canChange = false;
	}

	if (canChange)
	{
		for (auto& boolTrans : mCurrentState->mTransitionsOnBool)
		{
			if (boolTrans.variableName == iter->first && val == boolTrans.condition)
			{
				nextStateInd = boolTrans.nextAnimation->AnimationIndex;
				mCurrentTransition = &boolTrans;
				break;
			}
		}
	}

	if (nextStateInd == -1)
		return false;

	//do transition;
	//animationDuration = myAnimations.animationClips[mCurrentState->AnimationIndex].get()->duration;
	mNextState = &mStates[nextStateInd];
	mAnimationTransitionStartTime = Core::Time::Get()->CurrentTime();
	*iter->second.get() = val;
	return false;
}

bool Vishv::Graphics::AnimationStateMachine::SetTrigger(std::string& variableName)
{
	for(auto iter = mTriggerVariables.begin(); iter!= mTriggerVariables.end(); ++iter)
	{
		if (*iter._Ptr == variableName)
			return SetTrig(iter);
	}
	return false;
}
bool Vishv::Graphics::AnimationStateMachine::SetTrigger(std::string&& variableName)
{
	for (auto iter = mTriggerVariables.begin(); iter != mTriggerVariables.end(); ++iter)
	{
		if (*iter._Ptr == variableName)
			return SetTrig(iter);
	}
	return false;
}
bool Vishv::Graphics::AnimationStateMachine::SetTrig(std::vector<std::string>::iterator iter)
{
	if (iter == mTriggerVariables.end())
		return false;

	int nextStateInd = -1;

	float currentExitVal = animationStartTime + myAnimations.animationClips[mCurrentState->AnimationIndex]->duration / Core::Time::Get()->CurrentTime();
	bool canChange = true;
	if (!mCurrentState->canExitAnytime)
	{
		if (currentExitVal < mCurrentState->exitTime)
			canChange = false;
	}

	if (canChange)
	{
		for (auto& trigTrans : mCurrentState->mTransitionsOnTrigger)
		{
			if (trigTrans.variableName == *iter._Ptr)
			{
				nextStateInd = trigTrans.nextAnimation->AnimationIndex;
				mCurrentTransition = &trigTrans;
				break;
			}
		}
	}

	if (nextStateInd == -1)
		return false;

	//do transition;
	//animationDuration = myAnimations.animationClips[mCurrentState->AnimationIndex].get()->duration;
	mNextState = &mStates[nextStateInd];
	mAnimationTransitionStartTime = Core::Time::Get()->CurrentTime();
	return false;
}

bool Vishv::Graphics::AnimationStateMachine::AddIntVariable(std::string& name)
{
	auto [iter, success] = mIntVariables.insert({ name, std::make_unique<int>() });
	return success;
}
bool Vishv::Graphics::AnimationStateMachine::AddIntVariable(std::string&& name)
{
	auto [iter, success] = mIntVariables.insert({ std::move(name), std::make_unique<int>() });
	return success;
}

bool Vishv::Graphics::AnimationStateMachine::AddBoolVariable(std::string& name)
{
	auto [iter, success] = mBoolVariables.insert({ name, std::make_unique<bool>() });
	return success;
}
bool Vishv::Graphics::AnimationStateMachine::AddBoolVariable(std::string&& name)
{
	auto [iter, success] = mBoolVariables.insert({ std::move(name), std::make_unique<bool>() });
	return success;
}

bool Vishv::Graphics::AnimationStateMachine::AddTriggerVariable(std::string& name)
{
	bool found = false;

	for (int i = 0; i < mTriggerVariables.size(); ++i)
	{
		if (mTriggerVariables[i] == name)
		{
			found = true;
			break;
		}
	}

	if (!found)
		mTriggerVariables.emplace_back(name);

	return found;
}
bool Vishv::Graphics::AnimationStateMachine::AddTriggerVariable(std::string&& name)
{
	bool found = false;

	for (int i = 0; i < mTriggerVariables.size(); ++i)
	{
		if (mTriggerVariables[i] == name)
		{
			found = true;
			break;
		}
	}

	if (!found)
		mTriggerVariables.emplace_back(std::move(name));

	return found;
}

namespace
{
	using namespace Vishv::Graphics;
	
	void UpdateTransformMatrixFunc(const Bone* bone, std::vector<Vishv::Math::Matrix4>& boneMatrix, const std::vector<Vishv::Math::Matrix4>& animate)
	{
		if (bone->parent)
			boneMatrix[bone->index] = ((animate[bone->index])) * boneMatrix[bone->parentId];
		else
			boneMatrix[bone->index] = (animate[bone->index]);// *bone->toParentTransform;

		for (auto child : bone->children)
			UpdateTransformMatrixFunc(child, boneMatrix, animate);
	}
}

void Vishv::Graphics::AnimationStateMachine::GetBoneTransforms(std::vector<Math::Matrix4>& bTransforms)
{
	if (mNextState)
		BlendedBoneTransforms(bTransforms);
	else
		UnBlendedBoneTransforms(bTransforms);
}

void Vishv::Graphics::AnimationStateMachine::UnBlendedBoneTransforms(std::vector<Math::Matrix4>& bTransforms)
{
	auto& currentAnimation = myAnimations.animationClips[mCurrentState->AnimationIndex];
	float duration = (Core::Time::Get()->CurrentTime() - animationStartTime) * currentAnimation->ticksPerSecond;
	for (size_t i = 0; i < mModel.skeleton.GetBoneArray().size(); ++i)
	{
		auto& bone = mModel.skeleton.GetBoneArray()[i];

		if (!currentAnimation->GetTransform(duration, i, mTPose[i]))
		{
			mTPose[i] = bone->toParentTransform;
		}
	}
	UpdateTransformMatrixFunc(mModel.skeleton.root, bTransforms, mTPose);
	
	if (currentAnimation->duration / currentAnimation->ticksPerSecond < Core::Time::Get()->CurrentTime() - animationStartTime)
	{
		if(!currentAnimation->isLooping)
		{
			mCurrentState = &mStates[0];
			animationDuration = myAnimations.animationClips[mCurrentState->AnimationIndex]->duration;
		}
		animationStartTime = Core::Time::Get()->CurrentTime();
	}
}

void Vishv::Graphics::AnimationStateMachine::BlendedBoneTransforms(std::vector<Math::Matrix4>& bTransforms)
{
	Vishv::Math::Vector3 posAnim1, posAnim2;
	Vishv::Math::Quaternion rotAnim1, rotAnim2;

	auto& currentAnimation = myAnimations.animationClips[mCurrentState->AnimationIndex];
	auto& finalAnimation = myAnimations.animationClips[mNextState->AnimationIndex];
	
	auto Time = Core::Time::Get()->CurrentTime();

	float ratio = (Time - mAnimationTransitionStartTime) / mCurrentTransition->transitionDuration;

	for (size_t i = 0; i < mModel.skeleton.GetBoneArray().size(); ++i)
	{
		auto& bone = mModel.skeleton.GetBoneArray()[i];

		bool isFirst = currentAnimation->GetTransform(Time - animationStartTime, i, posAnim1, rotAnim1);
		bool isSecond = finalAnimation->GetTransform(Time - mAnimationTransitionStartTime, i, posAnim2, rotAnim2);

		float r1 = EaseCalculation::GetTime(ratio, mCurrentTransition->TransitionAnimation, true);
		float r2 = EaseCalculation::GetTime(ratio, mCurrentTransition->TransitionAnimation, false);

			if (!isFirst)
			{
				posAnim1 = bone->toParentTransform.GetTranslation();
				rotAnim1 = Math::Quaternion::MatrixToQuaternion(bone->toParentTransform);
			}
			else if (!isSecond)
			{
				posAnim2 = bone->toParentTransform.GetTranslation();
				rotAnim2 = Math::Quaternion::MatrixToQuaternion(bone->toParentTransform);
			}

			bTransforms[i] = Vishv::Math::Matrix4::TranslationMatrix(Vishv::Math::Quaternion::Slerp(rotAnim1, rotAnim2, r1), Vishv::Math::Vector3::Lerp(posAnim1, posAnim2, r2));
	}

	UpdateTransformMatrixFunc(mModel.skeleton.root, bTransforms, mModel.mTPosToParent);

	if (ratio > 1.0f)
		EndTransition();
}

void Vishv::Graphics::AnimationStateMachine::EndTransition()
{
	animationStartTime = mAnimationTransitionStartTime;
	animationDuration = myAnimations.animationClips[mNextState->AnimationIndex]->duration;

	mCurrentState = mNextState;
	mNextState = nullptr;
	mCurrentTransition = nullptr;
	mAnimationTransitionStartTime = -1.0f;
}
