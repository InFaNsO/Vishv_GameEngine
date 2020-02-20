#ifndef INCLUDED_VISHV_AI_META_REGISTRATION_H
#define INCLUDED_VISHV_AI_META_REGISTRATION_H

#include "State.h"
#include "StateMachine.h"

#include "SteeringBehaviour.h"
#include "SteeringModule.h"

#include "Graph.h"
#include "GraphSearch.h"

//Primitive basic declaration
//template <class agentType>
//META_TEMPLATE_TYPE_DECLARE(Vishv::AI::SteeringModule<agentType>, agentType)

//template <class agentType>
//META_TYPE_DEFINE(Vishv::AI::SteeringModule<agentType>, "SteeringModule", agentType)

//META_TYPE_DECLARE(Vishv::AI::Node)
//META_TYPE_DECLARE(Vishv::AI::GraphSearch::SearchNode)

namespace Vishv::AI
{
	void StaticMetaRegister();
}

#endif


