#include "Precompiled.h"
#include "PhysicsWorld.h"

#include "RigidBody.h"

#include <thread>

using namespace Vishv;
using namespace Physics;


namespace
{
	void HandleChunk(Octree::Node* node)
	{
		int index = 0;
		for (auto obj : node->objects)
		{
			int otherInd = 0;
			for (auto other : node->objects)
			{
				if (otherInd <= index)
				{
					otherInd++;
					continue;
				}
				obj->HandleCollision(other);
				++otherInd;
			}
			++index;
		}
	
		//LOG("figure out std::thread and how to capture");

//		for (auto obj : node->objects)
//		{
//			//apply other forces 
//			if (obj->Gravity)
//				obj->ApplyForce(*obj->Gravity);
//			else
//				obj->ApplyForce(PhysicsWorld::mGravity);
//
//			obj->Update(0.33f);	//make it use dt
//		}
	}
}

void Vishv::Physics::PhysicsWorld::Initialize(int maxObjects, int maxObjInLeaf)
{
	float worldLength = 10000.0f;
	float worldBreath = 10000.0f;
	float worldHeight = 10000.0f;

	mTree.Initialzie({ 0.0f,0.0f,0.0f }, { worldBreath, worldHeight, worldLength }, maxObjInLeaf, maxObjects);

	//mGravity.y = -9.8f;
}

void Vishv::Physics::PhysicsWorld::Register(RigidBody& body)
{
	mTree.Add(body);
}

void Vishv::Physics::PhysicsWorld::Update(float deltaTime)
{
	//get nodes
	//do colision check
	//do collision resolution
	//call update on all of them

	std::vector<std::thread> threads;
	threads.reserve(mTree.GetChunks().size());

	int count = 0;
	for (auto it : mTree.GetChunks())
	{
		threads.emplace_back(std::thread(HandleChunk, it));
	}
	for (auto& t : threads)
	{
		t.join();
	}

	mTree.Update();
}


