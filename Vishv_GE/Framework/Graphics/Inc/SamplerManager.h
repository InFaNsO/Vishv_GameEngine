#ifndef INCLUDED_VISHV_GRAPHICS_SAMPLER_MANAGER_H
#define INCLUDED_VISHV_GRAPHICS_SAMPLER_MANAGER_H

#include "Sampler.h"

namespace Vishv::Graphics {

class SamplerManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static SamplerManager* Get();

public:
	enum class SamplerType
	{
		PointClamp,
		PointWrap,
		LinearClamp,
		LinearWrap,
		AnistropicClamp,
		AnistropicWrap
	};

	SamplerManager() = default;
	~SamplerManager();

	void Initialize();
	void Terminate();

	bool AddSampler(std::string name, Sampler::Filter filter, Sampler::AddressMode adderessMode);
	bool AddSampler(SamplerType name, Sampler::Filter filter, Sampler::AddressMode adderessMode);
	Sampler* GetSampler(std::string name);
	Sampler* GetSampler(SamplerType name);

private:
	SamplerType StringToEnum(std::string name);

	std::unordered_map<SamplerType, std::unique_ptr<Sampler>> mInventory;

};	//SamplerManager

}	//Grphics//Vishv
#endif // defined INCLUDED_VISHV_GRAPHICS_SAMPLER_H