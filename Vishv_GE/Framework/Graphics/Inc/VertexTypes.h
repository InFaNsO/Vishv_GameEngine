#ifndef INCLUDED_VISHV_GRAPHICS_VERTEX_TYPES_H
#define INCLUDED_VISHV_GRAPHICS_VERTEX_TYPES_H

#include "Common.h"
#include "Colors.h"

namespace Vishv {
namespace Graphics {

	//Vertex Element Flags
	constexpr uint32_t VE_Position		= 0x1 << 0;
	constexpr uint32_t VE_Normal		= 0x1 << 1;
	constexpr uint32_t VE_Tangent		= 0x1 << 2;
	constexpr uint32_t VE_Color			= 0x1 << 3;
	constexpr uint32_t VE_Texcoord		= 0x1 << 4;
	constexpr uint32_t VE_Blendindex	= 0x1 << 5;
	constexpr uint32_t VE_BlendWeights	= 0x1 << 6;

#define VERTEX_FORMAT(fmt)\
	static constexpr uint32_t Format = fmt

	struct VertexPC			//Position Color
	{
		VERTEX_FORMAT(VE_Position | VE_Color);

		constexpr VertexPC() = default;
		constexpr VertexPC(const Math::Vector3& Position, const Color& colour)
			:position(Position)
			,color(colour)
		{
		}

		Math::Vector3 position;
		Color color;
	};

	struct VertexPNX			//Position Normal and texture
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Texcoord);

		VertexPNX() = default;
		
		constexpr VertexPNX(const Math::Vector3& Position, const Math::Vector3& Normal, const Math::Vector2& UV)
			:position(Position)
			, normal(Normal)
			,texCoord(UV)
		{
		}
		constexpr VertexPNX(const Math::Vector3& Position, const Math::Vector3& Normal, const float U, const float V)
			:position(Position)
			, normal(Normal)
			, texCoord({ U,V })
		{
		}

		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector2 texCoord;
	};

	struct VertexPN			//Position and Normal
	{
		VERTEX_FORMAT(VE_Position | VE_Normal);

		VertexPN() = default;

		constexpr VertexPN(const Math::Vector3& Position, const Math::Vector3& Normal)
			:position(Position)
			, normal(Normal)
		{
		}

		Math::Vector3 position;
		Math::Vector3 normal;
	};

	struct VertexPX			//Position Texture
	{
		VERTEX_FORMAT(VE_Position | VE_Texcoord);

		VertexPX() = default;
		constexpr VertexPX(const Math::Vector3& Position, const Math::Vector2& UV)
			:position(Position)
			, u(UV.x)
			, v(UV.y)
		{
		}
		constexpr VertexPX(const Math::Vector3& Position, const float U, const float V)
			: position(Position)
			, u(U)
			, v(V)
		{
		}

		Math::Vector3 position;
		float u, v;
	};

	struct VertexPNC			//Position Normal Color
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Color);

		VertexPNC() = default;
		constexpr VertexPNC(const Math::Vector3& Position, const Math::Vector3& Normal, const Math::Vector4& Colors)
			:position(Position)
			,normal(Normal)
			,color(Colors)
		{
		}

		Math::Vector3 position;
		Math::Vector3 normal;
		Color color;
	};

	struct Vertex			//Position Texture
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Tangent | VE_Texcoord);

		Vertex() = default;

		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;
		Math::Vector2 texCoord;
	};

	struct BoneVertex			//skinned vertex		limit of 4 bones affect
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Tangent | VE_Texcoord | VE_Blendindex | VE_BlendWeights);

		BoneVertex() = default;

		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;
		Math::Vector2 texCoord;

		int boneIndecies[4] = { 0 };
		float boneWeights[4] = { 0.0f };
	};

	struct VertexALL
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Tangent | VE_Color | VE_Texcoord | VE_Blendindex | VE_BlendWeights);

		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;

		Color color;
		Math::Vector2 texCoord;

		int boneIndecies[4] = { 0 };
		float boneWeights[4] = { 0.0f };
	};

} //Graphics
} //Vishv


#endif