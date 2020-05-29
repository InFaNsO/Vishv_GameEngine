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
#include "Animation3D.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "Model3D.h"
#include "ModelAnimation.h"
#include "PostProcessor.h"
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
#include "CameraService.h"
#include "LightService.h"
#include "ModelService.h"
#include "PhysicsWorldService.h"
#include "PostProcessService.h"
#include "SimpleDrawService.h"
#include "SkyBoxService.h"

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
#include "EditorRenderToWindow.h"
#include "GizmoIm.h"

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
