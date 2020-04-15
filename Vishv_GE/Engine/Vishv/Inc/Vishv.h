#ifndef INCLUDED_VISHV_H
#define INCLUDED_VISHV_H


#include "Common.h"
#include "App.h"
#include "AppState.h"
#include "GlobalHeaders.h"

//file import
#include "imfilebrowser.h"

#include "GameWorld.h"

//components
//AI Components
#include "AIAgent.h"
#include "AISteering.h"
#include "AIStateMachine.h"
#include "AIPathFinding.h"
//Graphics Components
#include "MeshComponent.h"
#include "ModelAnimation.h"
#include "ThirdPersonControllerComponent.h"
//Math Components
#include "TransformComponent.h"
//Physics Components
#include "OBBColliderComponent.h"
#include "SphereColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "RigidBodyComponent.h"


//Services
#include "Service.h"
#include "AIWorldService.h"
#include "PhysicsWorldService.h"
#include "CameraService.h"

//template classes completed
//Steering behaviours
#include "SteeringBehaviour_Arrive.h"
#include "SteeringBehaviour_Evade.h"
#include "SteeringBehaviour_Flee.h"
#include "SteeringBehaviour_Flocking.h"
#include "SteeringBehaviour_ObstacleAvoidance.h"
#include "SteeringBehaviour_Pursuit.h"
#include "SteeringBehaviour_Seek.h"
#include "SteeringBehaviour_Wander.h"

//terrain
//#include "QuadTree.h"


//Editor
#include "Editor.h"

namespace VishvApp
{
	Vishv::App& GetApp();

	template <class T>
	void AddState(std::string name)
	{
		GetApp().AddState<T>(name);
	}

	void ChangeState(std::string name);
	void Run(Vishv::AppConfig appConfig);
	void ShutDown();
}


#endif //! defined INCLUDED_VISHV_H
