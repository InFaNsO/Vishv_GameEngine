#include "Precompiled.h"
#include "GraphicsSystem.h"


using namespace Vishv;
using namespace Vishv::Graphics;


// nameless namespace/anonymous namespace 
// used for internal linkage
//when namespace has no name, everything is internal linkage
// only this file can touch this

namespace
{
	std::unique_ptr<GraphicsSystem> sGraphicsSystem = nullptr;
	Core::WindowMessageHandler sWindowMessageHandler;
}

LRESULT CALLBACK Graphics::GraphicsSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (sGraphicsSystem)
	{
		switch (message)
		{
		case WM_SIZE:
			const uint32_t width = static_cast<uint32_t>(LOWORD(lParam));
			const uint32_t height = static_cast<uint32_t>(HIWORD(lParam)); //HIWORD
			sGraphicsSystem->Resize(width, height);
			break;
		}
	}

	return sWindowMessageHandler.ForwardMessage(window, message, wParam, lParam);
}

void GraphicsSystem::StaticInitialize(HWND window, bool fullscreen)
{
	// use unique pointers instead of normal pointers. Newer c++
	VISHVASSERT(sGraphicsSystem == nullptr, "[Graphics::GraphicsSystem] System already initiaized!");
	sGraphicsSystem = std::make_unique<GraphicsSystem>();
	sGraphicsSystem->Initialize(window, fullscreen);
}

void GraphicsSystem::StaticTerminate()
{
	if (sGraphicsSystem != nullptr)
	{
		sGraphicsSystem->Terminate();
		// have to call reset instead of delete, (smart pointer functionality)
		sGraphicsSystem.reset();
	}
}

GraphicsSystem* GraphicsSystem::Get()
{
	VISHVASSERT(sGraphicsSystem != nullptr, "[Graphics::GraphicsSystem] No System Registered.");

	return sGraphicsSystem.get();
}

Vishv::Graphics::GraphicsSystem::~GraphicsSystem()
{
	VISHVASSERT(mD3DDdevice == nullptr, "[Graphics::GraphicsSystem] Terminate() must be called to clean up!");
}

void Vishv::Graphics::GraphicsSystem::Initialize(HWND window, bool fullscreen)
{
	//getting window dimensions
	RECT clientRect = {};
	GetClientRect(window, &clientRect);
	UINT width = (UINT)(clientRect.right - clientRect.left);
	UINT height = (UINT)(clientRect.bottom - clientRect.top);

	//What is this??
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 	// buffer is a 3d array, so the format RGB and alpha 8  bits for each equal to 32 bits. unorm means its ---- and normalized
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // what we are using this buffer for
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullscreen;

	const D3D_FEATURE_LEVEL kFeatureLevel = { D3D_FEATURE_LEVEL_11_0 };


	//HResult is just a typedef for a long
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&kFeatureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mSwapChain,
		&mD3DDdevice,
		nullptr,
		&mImmediateContext
	);

	VISHVASSERT(SUCCEEDED(hr), "[Graphics::GraphicsSystem] Failed to create device or swapchain. ");

	//cache swap chain description
	mSwapChain->GetDesc(&mSwapChainDesc);

	Resize(GetBackBufferWidth(), GetBackBufferHeight());

	sWindowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
}

void Vishv::Graphics::GraphicsSystem::Terminate()
{
	sWindowMessageHandler.UnHook();
	SafeRelease(mDepthStencilView);
	SafeRelease(mDepthStencilBuffer);
	SafeRelease(mImmediateContext);
	SafeRelease(mD3DDdevice);
	SafeRelease(mRenderTargetView);
	SafeRelease(mSwapChain);
}

void Vishv::Graphics::GraphicsSystem::BeginRender()
{
	//const FLOAT clear[4] = { 1.0f,0.0f,1.0f,1.0f };
	mImmediateContext->ClearRenderTargetView(mRenderTargetView, (FLOAT*)(&mBGColor));
	mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Vishv::Graphics::GraphicsSystem::EndRender()
{
	mSwapChain->Present(mVSync ? 1 : 0, 0);
}

void Vishv::Graphics::GraphicsSystem::ToggleFullscreen()
{
	BOOL fullscreen;
	mSwapChain->GetFullscreenState(&fullscreen, nullptr);
	mSwapChain->SetFullscreenState(!fullscreen, nullptr);
}

void Vishv::Graphics::GraphicsSystem::Resize(uint32_t width, uint32_t height)
{
	mImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

	SafeRelease(mRenderTargetView);
	SafeRelease(mDepthStencilView);

	HRESULT hr;
	if (width != GetBackBufferWidth() || height != GetBackBufferHeight())
	{
		hr = mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		VISHVASSERT(SUCCEEDED(hr), "[Graphics::GraphicsSyste] Failed to resize swap chain buffer.");

		//Cache swapchain descpription
		mSwapChain->GetDesc(&mSwapChainDesc);
	}

	//Create a render target view
	ID3D11Texture2D* backBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::GraphicsSystem::Resize] Failed to access swap chain buffer.");

	hr = mD3DDdevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);
	SafeRelease(backBuffer);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::GraphicsSystem::Resize] Failed to create render target view.");

	//Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth = {};

	descDepth.Width = GetBackBufferWidth();
	descDepth.Height = GetBackBufferHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	hr = mD3DDdevice->CreateTexture2D(&descDepth, nullptr, &mDepthStencilBuffer);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::GraphicsSystem::Resize] Failed to create depth stencil buffer.");

	//Create Depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDsv = {};
	descDsv.Format = descDepth.Format;
	descDsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDsv.Texture2D.MipSlice = 0;
	hr = mD3DDdevice->CreateDepthStencilView(mDepthStencilBuffer, &descDsv, &mDepthStencilView);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::GraphicsSystem::Resize] Failed to create depth stencil view.");

	//Set the render target view and Depth stencil view
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	//setup viewport
	mViewport.Width = static_cast<FLOAT>(width);
	mViewport.Height = static_cast<FLOAT>(height);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mImmediateContext->RSSetViewports(1, &mViewport);
}

uint32_t Vishv::Graphics::GraphicsSystem::GetBackBufferWidth() const
{
	return mSwapChainDesc.BufferDesc.Width;
}

uint32_t Vishv::Graphics::GraphicsSystem::GetBackBufferHeight() const 
{
	return mSwapChainDesc.BufferDesc.Height;
}

void Vishv::Graphics::GraphicsSystem::ResetRenderTarget()
{
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

void Vishv::Graphics::GraphicsSystem::ResetViewPort()
{
	mImmediateContext->RSSetViewports(1, &mViewport);
}


