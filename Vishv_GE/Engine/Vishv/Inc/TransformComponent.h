#ifndef INCLUDED_VISHV_COMPONENT_TRANSFORM_COMPONENT
#define INCLUDED_VISHV_COMPONENT_TRANSFORM_COMPONENT

#include "Component.h"

namespace Vishv::Components
{
	class TransformComponent: public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update(float deltaTime) override;
		void DebugUI() override;
		void SimpleDraw() override;
		void Render() override;
		void Terminate() override;


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

		void TranslateX(float value) { mTransform.TranslateX(value); }
		void TranslateY(float value){ mTransform.TranslateY(value); }
		void TranslateZ(float value){ mTransform.TranslateZ(value); }
		void TranslateUp(float value) { mTransform.TranslateUp(value); }
		void TranslateForward(float value) { mTransform.TranslateForward(value); }
		void TranslateRight(float value) { mTransform.TranslateRight(value); }

		void RotateX(float angleDeg)							{ mRotationWorld.x += angleDeg; }
		void RotateY(float angleDeg)							{ mRotationWorld.y += angleDeg; }
		void RotateZ(float angleDeg)							{ mRotationWorld.z += angleDeg; }
		void RotateRight(float angleDeg)						{ mRotationLocal.x += angleDeg; }
		void RotateUp(float angleDeg)							{ mRotationLocal.y += angleDeg; }
		void RotateForward(float angleDeg)						{ mRotationLocal.z += angleDeg; }
		void Rotate(const Math::Vector3& axis, float angleDeg)	{ mTransform.Rotate(axis, angleDeg); }
		void SetRotation(Math::Quaternion&& quat)				{ mTransform.SetRotation(std::move(quat)); }

		void RotateNowY(float deg) { mTransform.RotateY(deg); }

		const Math::Quaternion& Rotation() const { return mTransform.Rotation(); }
		const Math::Vector3& Position() const { return mTransform.Position(); }

		Math::Vector3& GetPosition() { return mTransform.mPosition; }

		void SwitchForard() { mTransform.SwitchForward(); }

		const Vishv::Math::Quaternion& Rotation() { return mTransform.Rotation(); }

		//Math::Vector3 mPosition;
		//Math::Vector3 mScale;
	private:
		//Math::Quaternion mQuaternion;
		//Math::Vector3 mUp;
		//Math::Vector3 mForward;
		Vishv::Math::Vector3 mRotationWorld;
		Vishv::Math::Vector3 mRotationLocal;

		Vishv::Math::Vector3 mPrvRotWorld;
		Vishv::Math::Vector3 mPrvRotLocal;

		Math::Transform mTransform;
	};
}


#endif // !INCLUDED_VISHV_TRANSFORM_COMPONENT


