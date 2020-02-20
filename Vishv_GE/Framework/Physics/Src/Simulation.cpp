#include "Precompiled.h"
#include "Simulation.h"

//using namespace physx;
/*
namespace
{
	std::unique_ptr<Vishv::Physics::Simulation> sInstance = nullptr;
}

void Vishv::Physics::Simulation::StaticInitialize()
{
	VISHVASSERT(sInstance == nullptr, "[SamplerManager] already Initialized");
	sInstance = std::make_unique<Vishv::Physics::Simulation>();
	sInstance->Initialize();
}

void Vishv::Physics::Simulation::StaticTerminate()
{
	if (sInstance != nullptr)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

Vishv::Physics::Simulation* Vishv::Physics::Simulation::Get()
{
	VISHVASSERT(sInstance != nullptr, "[SamplerManager] not Initialized");

	return sInstance.get();
}

void Vishv::Physics::Simulation::Initialize()
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocator, mErrorCallBack);
	mVisualDebugger = physx::PxCreatePvd(*mFoundation);

	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(hostIP.c_str(), 5425, 10);
	//mVisualDebugger->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), true, mVisualDebugger);

	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = { 0.0f, -9.81f, 0.0f };
	mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = mDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	mScene = mPhysics->createScene(sceneDesc);

	physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// (0, 1, 0, 0);

	physx::PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0.0f, 1.0f, 0.0f, 0.0f), *mMaterial);
	mScene->addActor(*groundPlane);

	for (physx::PxU32 i = 0; i < 5; i++)
	{
		//physx::createstack(physx::PxTransform(physx::PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
	}
}
*/
