 #pragma once
#ifndef INCLUDED_VISHV_EDITOR_GIZMO_H
#define INCLUDED_VISHV_EDITOR_GIZMO_H

namespace Vishv
{
	class GameObject;
	class GameWorld;

	class EditorManager;
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

		bool SetSelectedObject(GameObject* go);

		void Update();

	private:
		friend class GameWorld;
		friend class EditorManager;

		CameraSystem* CamService = nullptr;
		GizmoMode mMode = GizmoMode::Translate;

		Components::TransformComponent* currentObjectTransform = nullptr;
	};
}

#endif // !INCLUDED_VISHV_EDITOR_GIZMO_H


