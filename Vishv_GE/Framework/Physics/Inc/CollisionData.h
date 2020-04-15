#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_COLLISIONDATA_H
#define INCLUDED_VISHV_PHYSICS_COLLISIONDATA_H

#include "RigidBody.h"

namespace Vishv::Physics
{
	struct CollisionData
	{
		bool IsColliding = false;
		RigidBody* other = nullptr;
		float distanceInsertion = -1.0f;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_COLLISIONDATA_H


