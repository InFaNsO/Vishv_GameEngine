#ifndef INCLUDED_VISHV_GRAPHICS_SHADER_MANAGER_H
#define INCLUDED_VISHV_GRAPHICS_SHADER_MANAGER_H

#include "Common.h"
#include "Effect.h"

namespace Vishv::Graphics {
	//enum class EffectType
	//{
	//	Blur, DoLighting, DoNothing, DoSomething, Merge, Particle, PostProcessing, SimpleDraw, Skinning, Standard, Texturing, Mixamo, CellShader, Count)
	//}
	enum class EffectType
	{
		Blur			= 0x1 << 0,
		DoLighting		= 0x1 << 1,
		DoNothing		= 0x1 << 2,
		DoSomething		= 0x1 << 3,
		Merge			= 0x1 << 4,
		Particle		= 0x1 << 5,
		PostProcessing	= 0x1 << 6,
		SimpleDraw		= 0x1 << 7,
		Skinning		= 0x1 << 8,
		Standard		= 0x1 << 9,
		Texturing		= 0x1 << 10,
		Mixamo			= 0x1 << 11,
		CellShader		= 0x1 << 12,
		Count			= 13
	}; 

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