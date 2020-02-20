#ifndef INCLUDED_VISHV_GRAPHICS_PIXEL_SHADER_H
#define INCLUDED_VISHV_GRAPHICS_PIXEL_SHADER_H


namespace Vishv
{
	namespace Graphics
	{
		
		class PixelShader
		{
		public:
			bool Initialize(std::filesystem::path shaderPath);
			void Terminate();

			void Bind();

			~PixelShader()
			{
				VISHVASSERT(!mPixelShader, "[Vishv::Graphics::PixelShader] Didnt call terminate on Pixel Shader.\n");
			}

		private:
			std::wstring ConvertString(std::string& s);
			ID3D11PixelShader* mPixelShader{ nullptr };
		};

	}	//namespace Graphics
}	//namespace Vishv

#endif //defined INCLUDED_VISHV_GRAPHICS_PIXEL_SHADER_H