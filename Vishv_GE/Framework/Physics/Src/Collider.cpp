#include "Precompiled.h"
#include "Collider.h"
#include "AxisAlignedBoundingBox.h"

using namespace Vishv;
using namespace Vishv::Physics;

META_CLASS_BEGIN(Collider)
	META_FIELD_BEGIN
		META_FIELD(mIsTrigger, "IsTrigger")
	META_FIELD_END
META_CLASS_END


bool Vishv::Physics::Collider::IsTrigger()
{
	return mIsTrigger;
}



