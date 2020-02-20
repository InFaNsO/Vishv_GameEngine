#ifndef INCLUDED_VISHV_GRAPHICS_VERTEX_SHADER_H
#define INCLUDED_VISHV_GRAPHICS_VERTEX_SHADER_H

//#include "../Vishv_GE/Math/Inc/VishvMath.h"

namespace Vishv
{
namespace Graphics
{
	class VertexShader
	{
	public:
		bool Initialize(std::filesystem::path shaderPath, uint32_t vertexFormat);
		void Terminate();

		void Bind();
		~VertexShader();
	private:
	std::wstring ConvertString(std::string& s);
		
	ID3D11VertexShader* mVertexShader {nullptr};
	ID3D11InputLayout* mInputLayout{ nullptr };
};

}	//namespace Graphics
}	//namespace Vishv


#endif // INCLUDED_VISHV_GRAPHICS_VERTEX_SHADER_H
