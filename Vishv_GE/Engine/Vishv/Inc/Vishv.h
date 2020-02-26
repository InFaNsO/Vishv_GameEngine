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
#include "TransformComponent.h"
#include "ModelAnimation.h"
#include "AIAgent.h"
#include "AISteering.h"
#include "AIStateMachine.h"
#include "ThirdPersonControllerComponent.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "AIPathFinding.h"


//Services
#include "Service.h"

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