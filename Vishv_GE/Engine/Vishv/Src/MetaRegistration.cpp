#include "Precompiled.h"
#include "MetaRegistration.h"
#include "GameObject.h"
#include "Component.h"

#include "TransformComponent.h"
#include "ModelAnimation.h"
#include "AIAgent.h"
#include "AISteering.h"
#include "AIStateMachine.h"
#include "ColliderComponent.h"


void Vishv::StaticMetaRegister()
{
	META_REGISTER(GameObject);
	META_REGISTER(Components::Component);

	//Math Components
	META_REGISTER(Components::TransformComponent);

	//Graphics Components
	META_REGISTER(Components::ModelAnimation);

	//AI Components
	META_REGISTER(Components::AIAgent);
	META_REGISTER(Components::AISteering);
	META_REGISTER(Components::AIStateMachine);

	//Physics Components
	META_REGISTER(Components::ColliderComponent);

	//Networking Components once started
}
