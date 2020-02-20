#ifndef INCLUDED_VISHV_GRAPHICS_RASTERIZERSTATE_H
#define INCLUDED_VISHV_GRAPHICS_RASTERIZERSTATE_H

namespace Vishv::Graphics {

	class RasterizerState
	{
	public:
		enum class CullMode { Front, Back, None };
		enum class FillMode { Solid, Wireframe};

		RasterizerState() = default;
		~RasterizerState();

		RasterizerState(const RasterizerState& other) = delete;
		RasterizerState& operator= (const RasterizerState& other) = delete;

		void Initialize(CullMode cMode = CullMode::Back, FillMode fMode = FillMode::Solid);
		void Terminate();

		void Set();
		void Clear();

	private:
		ID3D11RasterizerState* mRasteriserState = nullptr;

	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_RASTERIZERSTATE_H
