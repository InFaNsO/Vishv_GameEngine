#ifndef INCLUDED_VISHV_APPSTATE_H
#define INCLUDED_VISHV_APPSTATE_H

#include "GameWorld.h"

namespace Vishv 
{
	class AppState
	{
	public:
		virtual void MetaRegister() {}
		virtual void Initialize() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual void RenderDebugUI() {}
		virtual void RenderSimpleDraw() {}
		virtual void Terminate() {}

		GameWorld mGameWorld;
		Graphics::EffectType mCurrentEffect = Graphics::EffectType::Skinning;
	};

}	

#endif