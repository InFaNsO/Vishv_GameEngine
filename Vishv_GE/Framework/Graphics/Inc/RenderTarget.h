#ifndef INCLUDED_VISHV_GRAPHICS_RENDERTARGET_H
#define INCLUDED_VISHV_GRAPHICS_RENDERTARGET_H

#include "Colors.h"

namespace Vishv::Graphics {

class RenderTarget
{
public:
	enum class Format
	{
		RGBA_U8,
		RGBA_F16,
		RGBA_U32,
		R_F16,
		R_S32
	};

	RenderTarget() = default;
	~RenderTarget();

	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	
	void Initialize(uint32_t width, uint32_t height, Format format);
	void Terminate();
	
	void BeginRender();
	void EndRender();

	void SetBackGroundColor(Vishv::Graphics::Color bgColor) { mBGColor = bgColor; }

	void BindPS(uint32_t slot = 0);
	void UnbindPS(uint32_t slot = 0);

	void Resize(uint32_t width, uint32_t height);

	ID3D11ShaderResourceView* GetShaderResourceView() const { return mShaderResourceView; }
	
	uint32_t GetBackBufferWidth() const;
	uint32_t GetBackBufferHeight() const;

private:
	ID3D11ShaderResourceView* mShaderResourceView = nullptr;
	ID3D11RenderTargetView* mRenderTargetView = nullptr;		//color bufer
	ID3D11DepthStencilView* mDepthStencilView = nullptr;		//z valu
	D3D11_VIEWPORT mViewport;
	D3D11_MAPPED_SUBRESOURCE mSubresource;

	//swap chain
	IDXGISwapChain* mSwapChain{ nullptr };
	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

	Vishv::Graphics::Color mBGColor = Vishv::Graphics::Colors::Black;
};

} // namespace Siege::Graphics

#endif // #ifndef INCLUDED_GRAPHICS_RENDERTARGET_H
