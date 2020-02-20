#ifndef INCLUDED_VISHV_GRAPHICS_BLENDSTATE_H
#define INCLUDED_VISHV_GRAPHICS_BLENDSTATE_H

namespace Vishv::Graphics {

class BlendState
{
public:
	static void Clear();
	
public:
	enum class Mode
	{
		Opaque,
		AlphaBlend,
		AlphaPremultiplied,
		Additive
	};

	BlendState() = default;
	~BlendState();

	void Initialize(Mode mode = Mode::Opaque);
	void Terminate();

	void Set();

private:
	ID3D11BlendState* mBlendState;

};
}

#endif // !INCLUDED_VISHV_GRAPHICS_BLENDSTATE_H
