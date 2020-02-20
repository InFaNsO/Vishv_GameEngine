#ifndef INCLUDED_VISHV_APPSTATE_H
#define INCLUDED_VISHV_APPSTATE_H

#include "Scene.h"

namespace Vishv 
{

	class AppState
	{
	public:
		virtual void Initialize() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void RenderDebugUI() {}
		virtual void RenderSimpleDraw() {}
		virtual void Terminate() {}

		Scene scene;
	};

}	

#endif 