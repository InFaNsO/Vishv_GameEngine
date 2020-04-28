#ifndef INCLUDED_VISHV_APPSTATE_H
#define INCLUDED_VISHV_APPSTATE_H

namespace Vishv 
{
	class GameWorld;

	class AppState
	{
	public:
		virtual void Initialize() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual void RenderDebugUI() {}
		virtual void RenderSimpleDraw() {}
		virtual void Terminate() {}

		GameWorld mGameWorld;
	};

}	

#endif