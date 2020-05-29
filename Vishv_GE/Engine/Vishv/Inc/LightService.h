#ifndef INCLUDED_VISHV_LIGHT_SERVICE_H
#define INCLUDED_VISHV_LIGHT_SERVICE_H

#pragma once
#include "Service.h"

namespace Vishv
{
	class PostProcessService;

	class Lighting : public Service
	{
	public:
		META_CLASS_DECLARE
	public:
		void Initialize() override;
		void DebugUI()override;

		void Bind(Graphics::EffectType type);

	private:
		PostProcessService* mPPService = nullptr;

		Graphics::EffectsManager* em = nullptr;

		Graphics::EffectBufferType::LightData mLightData;
		Graphics::EffectBufferType::MaterialData mMaterialData;
		Graphics::EffectBufferType::OptionsData mOptionsData;
	};
}


#endif // !INCLUDED_VISHV_LIGHT_SERVICE_H
