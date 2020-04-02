#ifndef INCLUDED_VISHV_PHYSICS_H
#define INCLUDED_VISHV_PHYSICS_H

#include "Common.h"

#include "ShapeCollision.h"
#include "RayCast.h"

#include "PhysicsWorld.h"

#include "Ray.h"


#include "Octree.h"
#include "RigidBody.h"

#include "Collider.h"
#include "AxisAlignedBoundingBox.h"
#include "SphereCollider.h"
#include "OrientedBoundingBox.h"


//#include "Particle.h"		will readd them later
//#include "World.h"		will readd them later


/*
Physics Engine
|
+---Simulation
    |
	+----Object Representation
	     +----Particle
		 +----Ridgid Body
		 +----Soft Body
		 +----Voxel
	+----Kinematics / Motion
	     +----Newtons Laws of motion
	+----Collision Detection
	     +----Hirarchical (Broad/Narrow phases)
		 +----Spatial Partitioning 
		 +----Soft Bodies
	+----Collision Resolution
	     +----Physics Equations
*/

//OldCode saved for reference 

//#include "Constants.h"
//#include "PhysicsVectors.h"
//#include "Particle.h"
//#include "Firework.h"
//#include "ParticleForceGenerator.h"
//#include "RigidBody.h"
//#include "ParticleContact.h"
//#include "World.h"
//#include "BoundingVolumeHirarchy.h"
//#include "BinarySpacePartitioning.h"		//To be done later
////To Be Made
////Quad Tree
////Grid
//#include "Contact.h"
//#include "PhyShapes.h"
//#include "ParticleEmitter.h"
//
//PhysX Simulation
//#include "Simulation.h"
//
//nvidia classes~
//#include "RigidActor.h"
//#include "InputStream.h"
//#include "PPhysics.h"
//#include "Scene.h"
//#include "ActorBase.h"
//#include "Actor.h"
//#include "PFlags.h"
//#include "PhysicsBase.h"
//#include "ActorBase.h"
//#include "SimulationBase.h"



#endif	// defined INCLUDED_VISHV_PHYSICS_H
