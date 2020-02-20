#ifndef INCLUDED_VISHV_COMPONENT_AISTEERING_COMPONENT
#define INCLUDED_VISHV_COMPONENT_AISTEERING_COMPONENT

#include "Component.h"

namespace Vishv::Components
{
	class TransformComponent;
	class AIAgent;
	//class Camera;	Camera Component

	class AISteering : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update(float deltaTime) override;
		void DebugUI() override;
		void Terminate() override;

		void SetBehaviour(AI::SteeringType type, bool set);
		void ResetModule() { mSteeringModule.Reset(); }

	private:
		//other functions

		TransformComponent* mTransformComponent;
		AIAgent* mAiAgentComponent;

		AI::SteeringModule<AIAgent> mSteeringModule;
	};
}


#endif // !INCLUDED_VISHV_COMPONENT_AI_STEERING_COMPONENT




