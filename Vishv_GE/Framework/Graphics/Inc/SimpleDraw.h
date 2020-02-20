#ifndef INCLUDED_VISHV_GRAPHICS_SIMPLE_DRAW_H
#define INCLUDED_VISHV_GRAPHICS_SIMPLE_DRAW_H

#include "Camera.h"
#include "Colors.h"
#include "VertexTypes.h"
#include "Skeleton.h"

namespace Vishv::Graphics::SimpleDraw 
{
	void StaticInitialize(uint32_t maxVertex);
	void StaticTerminate();
	   
	void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Vishv::Graphics::Color& color);
	void AddLine(const VertexPC& v0, const VertexPC& v1);
	void AddSphere(const Math::Vector3& center, const float radius, const Vishv::Graphics::Color& color, int row = 12, int col = 12);
	void AddScreen(const Math::Vector2& center, const float radius, const Vishv::Graphics::Color& color);

	void AddCube(const Math::Vector3& center, float lx, const Vishv::Graphics::Color& color);
	void AddCuboid(const Math::Vector3& center, float lx, float ly, float lz, const Vishv::Graphics::Color& color);
	void AddCuboid(const Math::Shapes::Cuboid& cuboid, const Vishv::Graphics::Color& color);
	void AddCapsule(const Math::Shapes::Capsule& capsule, const Vishv::Graphics::Color& color);
	void AddCylinder(const Math::Vector3& center, float radius, float height, const Vishv::Graphics::Color& color, int rows = 4);
	void AddCylinder(const Math::Vector3& center, const Vishv::Graphics::Color& color, float radius = 3.0f, int rows = 6, int col = 10, float rowThickness = 3.0f, bool capped = true);



	inline void MakeLine(const std::vector<VertexPC>& vertices, int row, int col);

	void AddCone(const Math::Vector3& start, Math::Vector3& end, const Vishv::Graphics::Color& color, float radius = 3.0f, int rows = 6, int col = 10, bool capped = true);

	void AddSkeleton(const Skeleton& skeleton, const std::vector<Vishv::Math::Matrix4>& boneTransform);

	//void AddTransformMatrix(const Math::Matrix4& m);

	void Render(const Camera& camera);
}	// Vishv::Graphics::SimpleDraw 


#endif	//defined INCLUDED_VISHV_GRAPHICS_SIMPLE_DRAW_H


