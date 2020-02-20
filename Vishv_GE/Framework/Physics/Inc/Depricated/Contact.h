#ifndef INCLUDED_VISHV_PHYSICS_CONTACT_H
#define INCLUDED_VISHV_PHYSICS_CONTACT_H

namespace Vishv::Physics {

struct ContactData
{
	Math::Vector4 mPoint;
	Math::Vector4 mNormal;
	float mPenitration;
};

struct CollisionData
{
	std::vector<ContactData> mContacts;
	int contactsLeft;
};



}

#endif // !INCLUDED_VISHV_PHYSICS_CONTACT_H
