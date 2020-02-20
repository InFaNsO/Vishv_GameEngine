#ifndef VISHV_GRAPHICS_MESHIO_H
#define VISHV_GRAPHICS_MESHIO_H

#include "Model.h"
#include "VertexTypes.h"

namespace Vishv::Graphics {

	

class MeshIO 
{
public:
	bool SaveMesh(ModelImport& mesh, std::string name);

	//bool SaveMesh(ModelImport &mesh, std::string name);
	bool SaveMesh(ModelImport& mesh, std::filesystem::path path);
	
	//template <class MODELTYPE, class MESHTYPE> where MODELTYPE : ModelBase<MESHTYPE>
	bool LoadMeshGeneral(std::filesystem::path fileName);

	std::filesystem::path rootPath = L"../../Assets/3D_Models/";

	bool GetModel(Model& model);
	bool GetModel(ModelPNX& model);

	bool IsMeshLoaded() { return isLoaded; }

private:
	bool isLoaded = false;
	ModelImport load;
};

}

#endif // defined VISHV_GRAPHICS_MESHIO_HSS
