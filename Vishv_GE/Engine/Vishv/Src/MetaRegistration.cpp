#include "Precompiled.h"
#include "MetaRegistration.h"
#include "GameObject.h"
#include "Component.h"

#include "TransformComponent.h"
#include "ModelAnimation.h"
#include "AIAgent.h"
#include "AISteering.h"
#include "AIStateMachine.h"
#include "OBBColliderComponent.h"
#include "SphereColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "RigidBodyComponent.h"

#include "Service.h"
#include "AIWorldService.h"
#include "PhysicsWorldService.h"


void Vishv::StaticMetaRegister()
{
	//Objects
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
	META_REGISTER(Components::OBBCollider);
	META_REGISTER(Components::SphereCollider);
	META_REGISTER(Components::CapsuleCollider);
	META_REGISTER(Components::Rigidbody);


	//Networking Components once started

	//Services
	META_REGISTER(Service);
	META_REGISTER(AIWorld);
	META_REGISTER(PhysicsSystem);


}
