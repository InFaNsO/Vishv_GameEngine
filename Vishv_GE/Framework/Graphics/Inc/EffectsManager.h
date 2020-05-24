#ifndef INCLUDED_VISHV_GRAPHICS_SHADER_MANAGER_H
#define INCLUDED_VISHV_GRAPHICS_SHADER_MANAGER_H

#include "Common.h"
#include "Effect.h"

namespace Vishv::Graphics {
	ENUM_MACRO(EffectType,Blur,DoLighting,DoNothing,DoSomething,Merge,Particle,PostProcessing,SimpleDraw,Skinning,Standard,Texturing,Mixamo,CellShader,Count)

	/*enum class EffectType
	{
		Blur, DoLighting,
		DoNothing,
		DoSomething,
		Merge,
		Particle,
		PostProcessing,
		SimpleDraw,
		Skinning,
		Standard,
		Texturing,
		Mixamo,
		CellShader,
		Count
	};*/

	class EffectsManager
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static EffectsManager* Get();

	public:
		EffectsManager() = default;
		~EffectsManager();

		void Initialize();
		void Terminate();

		bool AddEffect(EffectType type);
		bool BindBuffer(EffectType type);
		bool BindEffect(EffectType type);

		uint32_t GetBufferFormat(EffectType type);
		uint32_t GetBufferType(EffectType type);
		EffectBufferData* GetBufferData(EffectType type);
		void Set(EffectType type);

	private:
		std::string GetPath(EffectType type);
		uint32_t GetShaderType(EffectType type);
		uint32_t GetVertexType(EffectType type);

		std::unordered_map<EffectType, std::unique_ptr<Effect>> mInventory;

		std::filesystem::path mRootPath = L"../../Assets/Shaders";
	};	//SamplerManager

}	//Grphics//Vishv
#endif // defined INCLUDED_VISHV_GRAPHICS_SAMPLER_H