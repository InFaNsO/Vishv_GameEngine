#include "Precompiled.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"

Vishv::Math::Vector3 Vishv::Math::Vector3::operator*(const Quaternion & quat)
{
	Matrix4 m(quat);
	Vector3 v = m * *this;

	 return v;
}
Vishv::Math::Vector3 Vishv::Math::Vector3::operator*=(const Quaternion & quat)
{
	Matrix4 m(quat);

	*this = m * *this;

	return *this;
}

void Vishv::Math::Vector3::Rotate(const Quaternion & quat)
{
	Matrix4 m(quat);
	*this =  m * *this;
	return;
	//Quaternion q;
	//Quaternion norm = quat;
	//norm.Normalize();
	//
	//q = norm * Quaternion(x, y, z) *Quaternion::GetConjugate(norm);
	//
	//x = q.x;
	//y = q.y;
	//z = q.z;
	//Normalize();
}
