#include "Precompiled.h"
#include "ActorBase.h"

#include "SimulationBase.h"

using namespace Vishv;
using namespace Vishv::Physics;
using namespace Vishv::Math;
/*
class Vishv::Physics::Compound {};


ActorBase::ActorBase(SimulationBase* scene) :
	mScene(scene),
	mMinConvexSize(scene->mMinConvexSize),
	mDepthLimit(100),
	mDestroyIfAtDepthLimit(false)
{

}

ActorBase::~ActorBase()
{
	mScene->getScene()->lockWrite();
	clear();
	mScene->getScene()->unlockWrite();
	mScene->removeActorBase(this);
}

void ActorBase::clear()
{
	for (int i = 0; i < (int)mCompounds.size(); i++) {
		PX_DELETE(mCompounds[i]);
	}
	mCompounds.clear();
}

void ActorBase::addCompound(Compound *c)
{
	mCompounds.pushBack(c);
	PxRigidDynamic *a = c->getPxActorBase();
#if 1
	if (a) {
		//		a->setContactReportFlags(Px_NOTIFY_ON_TOUCH_FORCE_THRESHOLD | Px_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD);
		a->setContactReportThreshold(mScene->mFractureForceThreshold);
	}
#endif
	c->mActorBase = this;
	++(mScene->mSceneVersion);
}

void ActorBase::removeCompound(Compound *c)
{
	int num = 0;
	for (int i = 0; i < (int)mCompounds.size(); i++) {
		if (mCompounds[i] != c) {
			mCompounds[num] = mCompounds[i];
			num++;
		}
	}
	if (mScene->mPickActorBase == c->getPxActorBase())
		mScene->mPickActorBase = NULL;

	c->clear();
	//delCompoundList.push_back(c);
	//delete c;
	mScene->delCompoundList.pushBack(c);
	mCompounds.resize(num);
	++mScene->mSceneVersion;
}

void ActorBase::preSim(float dt)
{
	int num = 0;
	for (int i = 0; i < (int)mCompounds.size(); i++) {
		mCompounds[i]->step(dt);
		if (mCompounds[i]->getLifeFrames() == 0) {
			mCompounds[i]->clear();
			//delCompoundList.push_back(mCompounds[i]);
			//delete mCompounds[i];
			mScene->delCompoundList.pushBack(mCompounds[i]);
		}
		else {
			mCompounds[num] = mCompounds[i];
			num++;
		}
	}
	mCompounds.resize(num);
}

void ActorBase::postSim(float /*dt*//*)
{
}

bool ActorBase::rayCast(const PxVec3 &orig, const PxVec3 &dir, float &dist, int &compoundNr, int &convexNr, PxVec3 &normal) const
{
	dist = PX_MAX_F32;
	compoundNr = -1;
	convexNr = -1;

	for (int i = 0; i < (int)mCompounds.size(); i++) {
		float d;
		int cNr;
		PxVec3 n;
		if (mCompounds[i]->rayCast(orig, dir, d, cNr, n)) {
			if (d < dist) {
				dist = d;
				compoundNr = i;
				convexNr = cNr;
				normal = n;
			}
		}
	}
	return compoundNr >= 0;
}

bool ActorBase::findCompound(const Compound* c, int& compoundNr)
{
	for (int i = 0; i < (int)mCompounds.size(); i++)
	{
		if (mCompounds[i] == c)
		{
			compoundNr = i;
			return true;
		}
	}
	return false;
}

*/