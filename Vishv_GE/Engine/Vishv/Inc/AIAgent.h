#ifndef INCLUDED_VISHV_COMPONENT_AIAGENT_COMPONENT
#define INCLUDED_VISHV_COMPONENT_AIAGENT_COMPONENT

#include "Component.h"

namespace Vishv::Components
{
	class TransformComponent;
	//class Camera;	Camera Component

	class AIAgent : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update(float deltaTime) override;
		void SimpleDraw() override;
		void DebugUI() override;
		void Render() override;
		void Terminate() override;

		//void SetWorld(AI::World& world) { mWorld = &world; }
		Vishv::AI::World<AIAgent>& GetAIWorld() { return *mWorld; }


		bool operator== (const AIAgent& other)
		{
			return mIndex == other.mIndex;
		}
		bool operator!= (const AIAgent& other)
		{
			return mIndex != other.mIndex;
		}

		const Math::Vector3& Position();
		const Math::Vector3& Forward();

		const std::vector<AIAgent*>& Neighbours() { return mMyNearbyAgents; }
		Math::Vector3& Target() { return mTarget; }
		const Math::Vector3& Target() const { return mTarget; }

		float Mass() { return mMass; }
		float& MaxSpeed() { return mMaxSpeed; }

		float CalucalteLengthValue(float bufferValue);

		bool IsFlatSurface() { return mIsOnSurface; }

	private:
		void UpdateNearByAgents();
		void FindNearByAgents();


		TransformComponent* mTransformComponent;
		
		Vishv::AI::World<AIAgent>* mWorld;

		float mSafeDistance = 3.0f;
		float mSafeDistanceIncrementValue = 0.4f;
		float mNeighbourDistanceBuffer = 3.0f;

		float mMass = 1.0f;
		float mMaxSpeed = 10.0f;

		size_t mIndex = 0;

		Math::Vector3 mTarget;
		std::vector<AIAgent*> mMyNearbyAgents;

		bool mIsOnSurface = true;
	};
}


#endif // !INCLUDED_VISHV_COMPONENT_MODEL_ANIMATION_COMPONENT




