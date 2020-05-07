#include "Precompiled.h"
#include "Camera.h"
#include "GraphicsSystem.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	bool customCompare(const Math::Vector3& a, const Math::Vector3& b, int order = 1000)
	{
		int ax = (int)(a.x * order);
		int ay = (int)(a.y * order);
		int az = (int)(a.z * order);

		int bx = (int)(b.x * order);
		int by = (int)(b.y * order);
		int bz = (int)(b.z * order);

		return ax == bx && ay == by && az == bz;
	}
}

Math::Matrix4 Vishv::Graphics::ComputeViewMatrix(const Math::Vector3 &right, const Math::Vector3 &up, const Math::Vector3 &look, const Math::Vector3 &position)
{
	const float dx = - Math::Dot(right, position);
	const float dy = - Math::Dot(up, position);
	const float dz = - Math::Dot(look, position);

	return {
		right.x, up.x, look.x, 0.0f,
		right.y, up.y, look.y, 0.0f,
		right.z, up.z, look.z, 0.0f,
		dx     , dy  , dz    , 1.0f
	};
}

Math::Matrix4 Vishv::Graphics::ComputePerspectiveMatrix(float n, float f, float fov, float aspectRatio)
{
	const float h = 1 / tan(fov * 0.5f);
	const float w = h / aspectRatio;
	const float zf = f;
	const float zn = n;
	const float d = zf / (zf - zn);


	return {
		w,		0.0f,	0.0f,		0.0f,
		0.0f,	h,		0.0f,		0.0f,
		0.0f,	0.0f,	d,			1.0f,
		0.0f,	0.0f,	-zn * d,	0.0f
	};
}

const Math::Matrix4& Vishv::Graphics::Camera::GetViewMatrix() const
{
	return mViewMatrix;
}

const Math::Matrix4& Vishv::Graphics::Camera::GetPerspectiveMatrix() const
{
	return mPerspectiveMatrix;
}

void Vishv::Graphics::Camera::ComputeMatricies(float aspectRatio)
{
	//mLookAt = { 0.0f };
	//mLookAt.z += 1.0f;
	//mLookAt = (Math::Matrix4::RotateMatrix(transform.Rotation()) * Math::Matrix4::TranslateMatrix(transform.mPosition)) * mLookAt;
	
	const Math::Vector3 look = Vishv::Math::Normalize(transform->Forward());
	const Math::Vector3 right = Math::Normalize(Math::Cross(transform->Up(), look));
	const Math::Vector3 up = Math::Normalize(transform->Up());
	mViewMatrix = ComputeViewMatrix(right, up, look, transform->mPosition);

	if (aspectRatio == 0.0f)
	{
		auto w = GraphicsSystem::Get()->GetBackBufferWidth();
		auto h = GraphicsSystem::Get()->GetBackBufferHeight();
		aspectRatio = static_cast<float>(w) / static_cast<float>(h);
	}
	mPerspectiveMatrix = ComputePerspectiveMatrix(mNearPlane, mFarPlane, mFov, aspectRatio);
}

void Vishv::Graphics::Camera::ComputeMatricies(const Math::Transform& transformation)
{
	//mLookAt = { 0.0f };
	//mLookAt.z += 1.0f;
	//mLookAt = (Math::Matrix4::RotateMatrix(transform.Rotation()) * Math::Matrix4::TranslateMatrix(transform.mPosition)) * mLookAt;

	const Math::Vector3 look = Vishv::Math::Normalize(transformation.Forward());
	const Math::Vector3 right = Math::Normalize(Math::Cross(transformation.Up(), look));
	const Math::Vector3 up = Math::Normalize(transform->Up());
	mViewMatrix = ComputeViewMatrix(right, up, look, transformation.mPosition);

	auto w = GraphicsSystem::Get()->GetBackBufferWidth();
	auto h = GraphicsSystem::Get()->GetBackBufferHeight();
	float aspectRatio = static_cast<float>(w) / static_cast<float>(h);
	
	mPerspectiveMatrix = ComputePerspectiveMatrix(mNearPlane, mFarPlane, mFov, aspectRatio);
}

Math::Vector3 Vishv::Graphics::Camera::GetCameraUp() const
{
	return transform->Up();
}

void Vishv::Graphics::Camera::LookAt(const Math::Vector3& target)
{
	auto dir = target - transform->mPosition;
	if (dir.MagnitudeSq() == 0.0f)
		return;
	dir.Normalize();
	if (customCompare(dir,transform->Forward()))
		return;
	float angle = Vishv::Math::GetAngle(transform->Forward(), dir);

	transform->RotateUp(angle * Math::Constans::RadToDeg);
}
