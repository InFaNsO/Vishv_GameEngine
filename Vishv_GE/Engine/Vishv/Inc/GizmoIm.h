 #pragma once
#ifndef INCLUDED_VISHV_EDITOR_GIZMO_H
#define INCLUDED_VISHV_EDITOR_GIZMO_H

namespace Vishv
{
	class GameObject;
	class GameWorld;

	class CameraSystem;

	namespace Components
	{
		class TransformComponent;
	}
}

namespace Vishv::Editor
{
	class ScreenGizmo
	{
	public:
		static void StaticInitialize();
		static ScreenGizmo* Get();
		static void Terminate();

	public:
		enum class GizmoMode
		{
			Translate,
			Rotate,
			Scale
		};

	public:
		void Initialzie();

		bool IsActive();
		bool SetSelectedObject(GameObject* go);


	private:
		friend class GameWorld;

		 

		Components::TransformComponent* currentObjectTransform = nullptr;
	};
}

#endif // !INCLUDED_VISHV_EDITOR_GIZMO_H


