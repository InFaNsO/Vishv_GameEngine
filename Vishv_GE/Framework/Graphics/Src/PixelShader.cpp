#include"Precompiled.h"
#include"PixelShader.h"
#include "D3DUtil.h"

bool Vishv::Graphics::PixelShader::Initialize(std::filesystem::path shaderPath)
{
	//Compile our vertex shader code
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr;

	hr = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, &shaderBlob, &errorBlob);
	VISHVASSERT(SUCCEEDED(hr), "Failed to compile pixel shader. Error: %s", (const char*)errorBlob->GetBufferPointer());


	hr = GetDevice()->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &mPixelShader);
	VISHVASSERT(SUCCEEDED(hr), "Failed to Create pixel shader.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	return true;
}

std::wstring Vishv::Graphics::PixelShader::ConvertString(std::string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Vishv::Graphics::PixelShader::Terminate()
{
	SafeRelease(mPixelShader);
}

void Vishv::Graphics::PixelShader::Bind()
{
	GetContext()->PSSetShader(mPixelShader, nullptr, 0);

}