#pragma once

#ifndef INCLUDED_VISHV_EDITOR
#define INCLUDED_VISHV_EDITOR

namespace Vishv
{
	class GameObject;
	class GameWorld;

	class Editor
	{
	public:
		Editor(GameWorld& world);

		void ShowWorldView();
		void ShowInspectorView();

	private:
		GameWorld& mWorld;

		GameObject* mCurrentGameObject = nullptr;
	};
}

#endif 


