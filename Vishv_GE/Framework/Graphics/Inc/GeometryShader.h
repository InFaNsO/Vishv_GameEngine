#ifndef INCLUDED_VISHV_GRAPHICS_GEOMETRY_SHADER_H
#define INCLUDED_VISHV_GRAPHICS_GEOMETRY_SHADER_H

//#include "../Vishv_GE/Math/Inc/VishvMath.h"

namespace Vishv
{
namespace Graphics
{
	class GeometryShader
	{
	public:
		bool Initialize(std::string shaderName);
		bool Initialize(std::filesystem::path shaderPath);
		void Terminate();

		void Bind();
		void UnBind();
		~GeometryShader();
	private:
	std::wstring ConvertString(std::string& s);
		
	ID3D11GeometryShader* mGeometryShader {nullptr};
	//ID3D11InputLayout* mInputLayout{ nullptr };
};

}	//namespace Graphics
}	//namespace Vishv


#endif // INCLUDED_VISHV_GRAPHICS_VERTEX_SHADER_H
