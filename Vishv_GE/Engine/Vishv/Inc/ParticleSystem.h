#ifndef INCLUDED_VISHV_PARTICLE_SYSTEM
#define INCLUDED_VISHV_PARTICLE_SYSTEM
/*
namespace Vishv
{
class ParticleSystem
{
public:
	void Initialize(uint32_t maxEmitter = 5);
	void Update(float deltaTime);
	void Render(const Vishv::Graphics::Camera& camera);
	void RenderDebugUI();
	void Terminate();
	void RenderSimpleDraw(const Vishv::Graphics::Camera& camera);

private:
	void RenderMesh(const Vishv::Graphics::Camera& camera, int i);
	void RenderParticle(const Vishv::Graphics::Camera& camera, int i);
	void SortParticles(std::vector<Vishv::Physics::ParticleEmitter::ParticleData>& v, const Vishv::Graphics::Camera& camera);
	void ParticleToMesh(Vishv::Graphics::MeshPNC& mesh, int i = 0);

	void ImGuiGlobal();
	void ImGuiEmmiterBurst(Vishv::Physics::ParticleEmitter::ParticleBurstData& b, int i);
	void ImGuiIndividual(int i);

	void AddPresetFlame();
	void AddPresetSmoke();

	void InitializeEmmiter(Vishv::Physics::ParticlePreset& preset, std::string name);

	struct GeometryShaderConstantBufferData
	{
		Vishv::Math::Matrix4 vp;
		Vishv::Math::Vector3 cameraPos;
		Vishv::Math::Vector3 cameraUp;
		Vishv::Math::Vector3 gravity;

		float padding[3];
	};

	struct ParticleEmmiterData
	{
		Vishv::Physics::ParticleEmitter emmiter;
		std::vector<std::unique_ptr<Vishv::Graphics::MeshBuffer>> meshBuffer;
		Vishv::Graphics::MeshBuffer pointMeshBuffer;

		Vishv::Graphics::Color sphereColor = Vishv::Graphics::Colors::Black;

		bool useGPUacceleration = false;
		bool sortZBuffer = false;

		Vishv::Physics::BurstPreset burstholder;

		std::string mName;
	};

	uint32_t mMaxEmmiters = 5;

	Vishv::Graphics::VertexShader	mTextureVertexShader;
	Vishv::Graphics::PixelShader	mTexturePixelShader;

	Vishv::Graphics::GeometryShader	mParticleGeometryShader;
	Vishv::Graphics::VertexShader	mParticleVertexShader;
	Vishv::Graphics::PixelShader	mParticlePixelShader;

	size_t mMaxParticles;
	std::vector<std::unique_ptr<Vishv::Graphics::MeshBuffer>> mParticleMeshBuffer;

	std::vector<Vishv::Physics::ParticlePreset> mParticlePresets;
	std::vector<ParticleEmmiterData> mParticleEmmiters;

	using TextureBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Math::Matrix4>;
	using ParticleBuffer = Vishv::Graphics::TypedConstantBuffer<GeometryShaderConstantBufferData>;

	TextureBuffer mTextureBuffer;
	ParticleBuffer mParticleBuffer;
	
	Vishv::Graphics::MeshPNC mesh;
};
}*/

#endif // !INCLUDED_VISHV_PARTICLE_SYSTEM

