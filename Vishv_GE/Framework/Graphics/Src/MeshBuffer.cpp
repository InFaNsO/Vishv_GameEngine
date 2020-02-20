#include "Precompiled.h"
#include "MeshBuffer.h"
#include "Mesh.h"
#include "VertexTypes.h"

#include "D3DUtil.h"
//#include "VertexShader.h"

void Vishv::Graphics::MeshBuffer::Initialize(int dataSize, int vertexSize, const void* data, const uint32_t* indexData, uint32_t numIndices, bool dynamic)
{
	CreateVertexBuffer(dataSize, vertexSize, data, dynamic);
	CreateIndexBuffer(indexData, numIndices, dynamic);
	SetTopology(Topology::Triangles);
}

void Vishv::Graphics::MeshBuffer::Initialize(int dataSize, int vertexSize, const void* data, bool dynamic)
{
	CreateVertexBuffer(dataSize, vertexSize, data, dynamic);
}

void Vishv::Graphics::MeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mIndexBuffer);
}

void Vishv::Graphics::MeshBuffer::CreateVertexBuffer(int dataSize, int vertexSize, const void * data, bool dynamic)
{
	mVertexCount = dataSize;
	mVertexSize = vertexSize ;

	//Allocate memory in the vram for vertex buffer and initialize with out vertex data
	D3D11_BUFFER_DESC vertexBufferDesc{};

	vertexBufferDesc.ByteWidth = static_cast<UINT>(mVertexCount * mVertexSize);
	vertexBufferDesc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT hr = GetDevice()->CreateBuffer(&vertexBufferDesc, data ? &initData : nullptr, &mVertexBuffer);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::MeshBuffer::CreateVertexBuffer] Failed to creat vertex buffer");

}

void Vishv::Graphics::MeshBuffer::CreateIndexBuffer(const uint32_t * indexData, uint32_t numIndices, bool dynamic)
{
	mIndexCount = numIndices;

	//Buffer Description for index buffer
	D3D11_BUFFER_DESC indexBufferDesc{};

	indexBufferDesc.ByteWidth = static_cast<UINT>(mIndexCount * sizeof(uint32_t));
	indexBufferDesc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Create the index buffer using vertex buffer

	//Creat init Data
	D3D11_SUBRESOURCE_DATA initData{};
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;
	initData.pSysMem = indexData;

	HRESULT hr = GetDevice()->CreateBuffer(&indexBufferDesc, &initData, &mIndexBuffer);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::MeshBuffer::CreateIndexBuffer] Failed to creat index buffer");

}

void Vishv::Graphics::MeshBuffer::Bind()
{
	UINT stride = static_cast<UINT>(mVertexSize);
	UINT offset = 0;
	GetContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
}

void Vishv::Graphics::MeshBuffer::Update(int count, const void * data)
{
	mVertexCount = count;
	auto context = GetContext();
	size_t s = mVertexCount * mVertexSize;

	D3D11_MAPPED_SUBRESOURCE resource;
	context->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, data, s);
	context->Unmap(mVertexBuffer, 0);
}

void Vishv::Graphics::MeshBuffer::Update(int count, const void * data, int indexSize, uint32_t* indexData)
{
	mVertexCount = count;
	mIndexCount = indexSize;
	auto context = GetContext();

	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT hr = context->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, data, mVertexCount * mVertexSize);
	context->Unmap(mVertexBuffer, 0);

	D3D11_MAPPED_SUBRESOURCE resource1;
	hr = context->Map(mIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource1);
	memcpy(resource1.pData, indexData, mIndexCount * sizeof(uint32_t));
	context->Unmap(mIndexBuffer, 0);

}

void Vishv::Graphics::MeshBuffer::Draw()
{
	Render();
	//GetContext()->Draw(static_cast<UINT>(mVertexCount), 0);
}

void Vishv::Graphics::MeshBuffer::Render()
{
	ID3D11DeviceContext* context = GetContext();

	// Set vertex buffer
	UINT stride = static_cast<UINT>(mVertexSize);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset); //UNCOMMENT THIS

	// Set primitive topology
	context->IASetPrimitiveTopology(mTopology);

	//DRAW USING INDEX BUFFER
	if (mIndexBuffer != nullptr)
	{
		//Set Index Buffer
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
		//Draw Indexed Mesh
		context->DrawIndexed(static_cast<UINT>(mIndexCount), 0, 0);
	}
	else //Draw it raw, without the index buffer
	{
		context->Draw(static_cast<UINT>(mVertexCount), 0);
	}

	//context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//set it back to default so others dont have any problem;
}

void Vishv::Graphics::MeshBuffer::SetTopology(Topology topology)
{
	switch (topology)
	{
	case Topology::Points:
		mTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case Topology::Lines:
		mTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case Topology::Triangles:
		mTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	default:
		mTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	}
}


