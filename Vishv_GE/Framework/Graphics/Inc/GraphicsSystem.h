#ifndef INCLUDED_VISHV_GRAPHICS_GRAPHICSSYSTEM_H
#define INCLUDED_VISHV_GRAPHICS_GRAPHICSSYSTEM_H

#include "Colors.h"

namespace Vishv::Graphics {
class  GraphicsSystem
{
public:
	// basic singleton functions for the graphics system
	static void StaticInitialize(HWND window, bool fullscreen);
	static void StaticTerminate();
	static GraphicsSystem* Get();

public:
	GraphicsSystem() = default;
	~GraphicsSystem();

	GraphicsSystem(const GraphicsSystem&) = delete;
	GraphicsSystem& operator=(const GraphicsSystem&) = delete;

	void Initialize(HWND window, bool fullscreen);
	void Terminate();

	void BeginRender();
	void EndRender();

	void ToggleFullscreen();
	void Resize(uint32_t width, uint32_t height);

	void SetBackGroundColor(Color color)					{ mBGColor = color; }
	void SetVSync(bool vsync)								{ mVSync = vsync; }

	//ID3D11Device* GetDevice() { return mD3DDdevice; }
	//ID3D11DeviceContext* GetContext() { return mImmediateContext; }

	uint32_t GetBackBufferWidth() const;
	uint32_t GetBackBufferHeight() const;

	void ResetRenderTarget();
	void ResetViewPort();

private:
	friend LRESULT CALLBACK GraphicsSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

	friend ID3D11Device* GetDevice();
	friend ID3D11DeviceContext* GetContext();

	// device pointer, used for memory management
	ID3D11Device* mD3DDdevice{ nullptr };
	//context pointer, used for draw calls
	ID3D11DeviceContext* mImmediateContext{ nullptr };

	//swap chain
	IDXGISwapChain* mSwapChain{ nullptr };
	//
	ID3D11RenderTargetView* mRenderTargetView{ nullptr };


	ID3D11Texture2D* mDepthStencilBuffer{ nullptr };
	ID3D11DepthStencilView* mDepthStencilView{ nullptr };

	

	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;
	D3D11_VIEWPORT mViewport;

	Color mBGColor = Graphics::Colors::Gray;
	bool mVSync = true;
};
}// namespace Graphics // namespace Vishv





#endif // #ifndef INCLUDED_VISHV_GRAPHICS_GRAPHICS_SYSTEM