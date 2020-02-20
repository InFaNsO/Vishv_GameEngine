#ifndef INCLUDED_VISHV_GRAPHICS_MESH_BUILDER_H 
#define INCLUDED_VISHV_GRAPHICS_MESH_BUILDER_H 

#include "Mesh.h"

namespace Vishv {
namespace Graphics {

class Meshbuilder
{
public:
	static MeshPC CreateCubePC			(float height, float width, float depth);
	static MeshPC CreatePlanePC			(int rows, int col, float thicknessRow, float thicknessCol);
	static MeshPC CreateCylinderPC		(int rows, int col, float radius, float thicknessRow, bool capped = true);
	static MeshPC CreateConePC			(int rows, int col, float radius, float thicknessRow, bool capped = true);
	static MeshPC CreateSpherePC		(int rows, int col, float radius);
	static MeshPC CreateTorusPC			(int rows, int col, float innerRadius, float outerRadius);

	static MeshPN CreateSphereNormal	(int rows, int col, float radius);
	static MeshPN CreateCylinderNormal	(int rows, int col, float radius, float thicknesRow, bool capped = true);	

	static MeshPX CreateCubeUV			(float height, float width, float depth);
	static MeshPX CreateSkyboxUV		(float height, float width, float depth);
	static MeshPX CreatePlaneUV			(int rows, int col, float thicknessRow, float thicknessCol);
	static MeshPX CreateCylinderUV		(int rows, int col, float radius, float thicknessRow, bool capped = true);
	static MeshPX CreateConeUV			(int rows, int col, float radius, float thicknessRow, bool capped = true);
	static MeshPX CreateSphereUV		(int rows, int col, float radius);
	static MeshPX CreateSkyDomeUV		(int rows, int col, float radius);
	static MeshPX CreateTorusUV			(int rows, int col, float innerRadius, float outerRadius); //just bend a cylnder 
	static MeshPX CreateNDCQuad			();
	
	static Mesh CreateSphere			(int rows, int col, float radius);
	static Mesh CreateCylinder			(int rows, int col, float radius, float thicknessRow, bool capped = true);

	static BoneMesh CreateBoneCube		(float height, float width, float depth, int boneIndex);		//just a cube with pivot at buttom;
	static BoneMesh CreateBoneCylinder	(int rows, int col, float radius, float thicknessRow, int totalBones, int boneAffect = 3, bool capped = true);

private:
};


} //Graphics
} //Vishv

#endif // defined INCLUDED_VISHV_GRAPHICS_MESH_BUILDER_H