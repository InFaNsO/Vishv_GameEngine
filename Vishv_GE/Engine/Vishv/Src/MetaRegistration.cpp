#include "Precompiled.h"
#include "MetaRegistration.h"
#include "GameObject.h"
#include "Component.h"

//Components
//Ai
#include "AIAgent.h"
#include "AIPathFinding.h"
#include "AIStateMachine.h"
#include "AISteering.h"

//Graphics
#include "Animation3D.h"
#include "CameraComponent.h"
#include "Model3D.h"
//Put ths as a service
#include "MeshComponent.h"

//Math
#include "TransformComponent.h"

//Physics
#include "OBBColliderComponent.h"
#include "SphereColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "RigidBodyComponent.h"

//Services
#include "Service.h"
#include "AIWorldService.h"
#include "PhysicsWorldService.h"
#include "CameraService.h"

void Vishv::StaticMetaRegister()
{
	//Objects
	META_REGISTER(GameObject);
	META_REGISTER(Components::Component);

	//Math Components
	META_REGISTER(Components::TransformComponent);

	//Graphics Components
	META_REGISTER(Components::Animation3D);
	META_REGISTER(Components::CameraComponent);
	META_REGISTER(Components::Model3D);

	META_REGISTER(Components::MeshComponent);


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
