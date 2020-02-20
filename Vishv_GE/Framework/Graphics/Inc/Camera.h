#ifndef INCLUDED_VISHV_GRAPHICS_CAMERA_H
#define INCLUDED_VISHV_GRAPHICS_CAMERA_H

namespace Vishv {
namespace Graphics {

	Math::Matrix4 ComputeViewMatrix(const Math::Vector3 &right, const Math::Vector3 &up, const Math::Vector3 &look, const Math::Vector3 &position);
	Math::Matrix4 ComputePerspectiveMatrix(float n, float f, float fov, float aspectRatio);

//This assumes y axis is up direction
//Cannot look straight up or down
class Camera {

	//work on this next

public:
	Camera() = default;
	void SetPosition(const Math::Vector3& position) { transform.mPosition = position; }
	//void SetDirection(const Math::Vector3& direction) { mLookAt = Math::Normalize(direction); }
	//void SetTarget(const Math::Vector3& target) { VISHVASSERT(target.MagnitudeSq() > 0.0f, "[Camera] direction is wrong"); mDirection = target; }

	void SetFov(float angle, bool rad = false) { mFov = !rad ? angle * Vishv::Math::Constans::DegToRad : angle; }
	void SetNearPlane(float distance) { mNearPlane = distance; }
	void SetFarPlane(float distance) { mFarPlane = distance; }

	//3 degrees of freedom for translation
	void Walk(float distance) { transform.mPosition.z += distance; }
	void Strafe(float distance) { transform.mPosition.x += distance; }
	void Rise(float distance) { transform.mPosition.y += distance; }

	void LookAt(const Math::Vector3& target);

	//2 degrees of freedom for rotation
	//void Yaw(float rotation) { mDirection.x += rotation; }		//Rotate along global Y axis
	//void Pitch(float rotation) { mDirection.y += rotation; }	//Rotate along local  X axis

	const Math::Vector3& GetPosition() const { return transform.mPosition; };
	const Math::Vector3& GetDirection()const { return transform.Forward(); };

	float GetFov()const { return mFov; };
	float GetNearPlane()const { return mNearPlane; };
	float GetFarPlane()const { return mFarPlane; };

	const Math::Matrix4& GetViewMatrix() const;
	const Math::Matrix4& GetPerspectiveMatrix() const;
	Math::Vector3 GetCameraUp() const;

	void ComputeMatricies(float aspectRatio = 0.0f);

	Math::Transform transform;
private:
	//Math::Vector3 mPosition{ 0.0f };
	//Math::Vector3 mLookAt;
	//Math::Vector3 mDirection{ 0.0f, 0.0f, 1.0f };

	float mFov = 60.0f * Math::Constans::DegToRad; //multiply by deg to rad in Math::Constants
	float mNearPlane{ 1.0f };
	float mFarPlane{ 5000.0f };

	Vishv::Math::Matrix4 mTransformation{ Vishv::Math::Matrix4::Identity() };
	Vishv::Math::Matrix4 mViewMatrix;
	Vishv::Math::Matrix4 mPerspectiveMatrix;
};
}
}

#endif // defined INCLUDED_VISHV_GRAPHICS_CAMERA_H