#include "Precompiled.h"
#include "ConstantBuffer.h"

#include "D3DUtil.h"

using namespace Vishv;
using namespace Vishv::Graphics;

//void Vishv::Graphics::ConstantBuffer::Initialize(uinte)
//{
//	D3D11_BUFFER_DESC desc = {};
//	desc.ByteWidth = 3 * sizeof(Math::Matrix4);
//	desc.Usage = D3D11_USAGE_DEFAULT;
//	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	GetDevice()->CreateBuffer(&desc, nullptr, &constantBuffer);
//}

void Vishv::Graphics::ConstantBuffer::Initialize(uint32_t size)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA subsourcedata{};
	//subsourcedata.pSysMem = initData;

	GetDevice()->CreateBuffer(&desc, nullptr, &constantBuffer);
}

void Vishv::Graphics::ConstantBuffer::Bind(const Math::Matrix4 matrix[])
{
	Set(&matrix);
	BindVS();
}

void Vishv::Graphics::ConstantBuffer::Set(const void * data) const
{
	GetContext()->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);
}

void Vishv::Graphics::ConstantBuffer::BindVS(uint32_t slot) const
{
	GetContext()->VSSetConstantBuffers(slot, 1, &constantBuffer);
}

void Vishv::Graphics::ConstantBuffer::BindPS(uint32_t slot) const
{
	GetContext()->PSSetConstantBuffers(slot, 1, &constantBuffer);
}

void Vishv::Graphics::ConstantBuffer::BindGS(uint32_t slot) const
{
	GetContext()->GSSetConstantBuffers(slot, 1, &constantBuffer);
}

void Vishv::Graphics::ConstantBuffer::BindCS(uint32_t slot) const
{
	GetContext()->CSSetConstantBuffers(slot, 1, &constantBuffer);
}



void Vishv::Graphics::ConstantBuffer::Terminate()
{
	SafeRelease(constantBuffer);
}

Vishv::Graphics::ConstantBuffer::~ConstantBuffer()
{
	VISHVASSERT(!constantBuffer, "[Vishv::Graphics::ConstantBuffer] Didn't call Terminate on constant buffer.\n");
}