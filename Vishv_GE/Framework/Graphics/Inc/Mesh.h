#ifndef INCLUDED_VISHV_GRAPHICS_MESH_H 
#define INCLUDED_VISHV_GRAPHICS_MESH_H 

#include "VertexTypes.h"

namespace Vishv{
namespace Graphics{

template<class T>
struct MeshBase
{
	using VertexType = T;
	std::vector<T> mVertices;
	std::vector<uint32_t> mIndices;
};

using MeshPC =	MeshBase<VertexPC>;
using MeshPNX = MeshBase<VertexPNX>;
using MeshPNC = MeshBase<VertexPNC>;
using MeshPX =	MeshBase<VertexPX>;
using MeshPN = MeshBase<VertexPN>;
using Mesh = MeshBase<Vertex>;
using BoneMesh = MeshBase<BoneVertex>;
using MeshImport = MeshBase<VertexALL>;

} //Graphics
} //Vishv


#endif // !INCLUDED_VISHV_GRAPHICS_MESH_H 