#ifndef INCLUDED_VISHV_COMPONENT_TRANSFORM_COMPONENT
#define INCLUDED_VISHV_COMPONENT_TRANSFORM_COMPONENT

#include "Component.h"

namespace Vishv::Components
{
	class TransformComponent: public Component
	{
	public:
		META_CLASS_DECLARE

		void Update() override;
		void SimpleDraw() override;
		void Initialize() override;

		bool operator==(const TransformComponent& other)
		{
			return mTransform == other.mTransform;
		}
		bool operator!= (const TransformComponent& other)
		{
			return mTransform != other.mTransform;
		}

		const Math::Vector3& Up() const { return mTransform.Up(); }
		const Math::Vector3& Forward() const { return mTransform.Forward(); }

		void TranslateX(float value) { mTransform.TranslateX(value); changePos = true; }
		void TranslateY(float value){ mTransform.TranslateY(value); changePos = true; }
		void TranslateZ(float value){ mTransform.TranslateZ(value); changePos = true;}
		void TranslateUp(float value) { mTransform.TranslateUp(value); changePos = true;}
		void TranslateForward(float value) { mTransform.TranslateForward(value); changePos = true;}
		void TranslateRight(float value) { mTransform.TranslateRight(value); changePos = true;}

		void RotateX(float angleDeg)							{ mRotationWorld.x += angleDeg; }
		void RotateY(float angleDeg)							{ mRotationWorld.y += angleDeg; }
		void RotateZ(float angleDeg)							{ mRotationWorld.z += angleDeg; }
		void RotateRight(float angleDeg)						{ mRotationLocal.x += angleDeg; }
		void RotateUp(float angleDeg)							{ mRotationLocal.y += angleDeg; }
		void RotateForward(float angleDeg)						{ mRotationLocal.z += angleDeg; }
		void Rotate(const Math::Vector3& axis, float angleDeg)	{ mTransform.Rotate(axis, angleDeg); }
		void SetRotation(Math::Quaternion&& quat)				{ mQuaternion = quat; }

		//void RotateNowY(float deg) { mTransform.RotateY(deg); }

		const Math::Quaternion& Rotation() const { return mQuaternion; }
		const Math::Vector3& Position() const { return mTransform.Position(); }

		Math::Vector3& GetPosition() { return mTransform.mPosition; }

		void SwitchForard() { mTransform.SwitchForward(); }

		const Vishv::Math::Quaternion& Rotation() { return mQuaternion; }

		const Vishv::Math::Transform& Transform() const { return mTransform; }
		Vishv::Math::Transform& Transform() { return mTransform; }

		//Math::Vector3 mPosition;
		//Math::Vector3 mScale;
	private:
		bool changePos = false;

		Math::Quaternion mQuaternion;
		//Math::Vector3 mUp;
		//Math::Vector3 mForward;
		Vishv::Math::Vector3 mRotationWorld;
		Vishv::Math::Vector3 mRotationLocal;

		Vishv::Math::Vector3 mPrvRotWorld;
		Vishv::Math::Vector3 mPrvRotLocal;

		Math::Transform mTransform;

		Math::Vector3 pos;
		Math::Vector3 scale;
	};
}


#endif // !INCLUDED_VISHV_TRANSFORM_COMPONENT


