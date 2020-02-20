#ifndef INCLUDED_VISHV_SCENE_H
#define INCLUDED_VISHV_SCENE_H

#include "Common.h"

namespace Vishv
{
	struct Scene
	{
		void Render(bool isScene = true)
		{
			for (uint32_t i = 0; i < mObjects.size(); ++i)
			{
				mObjects[i]->Render(*sceneCamera, currentEffect, isScene);
			}
		}

		std::vector<std::unique_ptr<Vishv::Graphics::Object3D>> mObjects;
		std::vector < std::unique_ptr<Vishv::Graphics::AnimationSet>> mAnimationSets;
		Vishv::Graphics::Camera mGameCamera;
		Vishv::Graphics::Camera* sceneCamera;

		Vishv::Graphics::EffectType currentEffect = Vishv::Graphics::EffectType::Skinning;
	};
}


#endif // !INCLUDED_VISHV_SCENE_H

