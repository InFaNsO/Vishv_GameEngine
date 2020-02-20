#ifndef INCLUDED_VISHV_GRAPHICS_MESH_BUFFER_H
#define INCLUDED_VISHV_GRAPHICS_MESH_BUFFER_H

//#include "../Vishv_GE/Math/Inc/VishvMath.h"
//#include "VertexShader.h"


namespace Vishv::Graphics
{
class MeshBuffer
{
public:
	MeshBuffer() = default;
	enum Topology {Points, Lines, Triangles};

	template<class MeshType>
	void Initialize(const MeshType& mesh, bool dynamic = false);
	
	void Initialize(int dataSize, int vertexSize, const void* data, const uint32_t* indexData, uint32_t numIndices, bool dynamic = false);
	void Initialize(int dataSize, int vertexSize, const void* data, bool dynamic = false);
	void Terminate();

	void Bind();
	void Draw();
	void Render();
	void Update(int vertexSize, const void* data);
	void Update(int vertexSize, const void* data, int indexSize, uint32_t* indexData);

	void SetTopology(Topology topology);

	~MeshBuffer()	
	{
		VISHVASSERT(!mVertexBuffer || !mIndexBuffer, "[Vishv::Graphics::MeshBubber] Didnt call terminate on mesh buffer.\n");
	}

private:
	void CreateVertexBuffer(int dataSize, int vertexSize, const void* data, bool dynamic);
	void CreateIndexBuffer(const uint32_t* indexData, uint32_t numIndices, bool dynamic);

	ID3D11Buffer* mVertexBuffer =  nullptr;
	ID3D11Buffer* mIndexBuffer = nullptr;
	size_t mVertexCount{0};
	size_t mVertexSize{0};
	size_t mIndexCount{ 0 };

	D3D11_PRIMITIVE_TOPOLOGY mTopology;

	bool mDynamic{ false };
};

template<class MeshType>
inline void Vishv::Graphics::MeshBuffer::Initialize(const MeshType & mesh, bool dynamic)
{
	Initialize(static_cast<int>(mesh.mVertices.size()), static_cast<int>(sizeof(MeshType::VertexType)), mesh.mVertices.data(), mesh.mIndices.data(), static_cast<uint32_t>(mesh.mIndices.size()), dynamic);

}


}		//Vishv::Graphics

#endif //INCLUDED_VISHV_GRAPHICS_MESH_BUFFER_H