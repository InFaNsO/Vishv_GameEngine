#ifndef INCLUDED_VISHV_GRAPHICS_SAMPLER_H
#define INCLUDED_VISHV_GRAPHICS_SAMPLER_H

namespace Vishv {
namespace Graphics {

class Sampler
{
public:
	enum class Filter {Point,Linear, Anistropic};
	enum class AddressMode {Border, Clamp, Mirror, Wrap};

	Sampler() = default;
	~Sampler();
	
	void Initialize(Filter filter, AddressMode addressMode);
	void Terminate();

	void BindPS(uint32_t slot = 0);

private:
	ID3D11SamplerState* mSampler{ nullptr };

};	//Sampler

}	//Grphics
}	//Vishv

#endif // defined INCLUDED_VISHV_GRAPHICS_SAMPLER_H