#include "Precompiled.h"
#include "ParticleSystem.h"
/*
void Vishv::ParticleSystem::Initialize(uint32_t maxEmmiter)
{
	mMaxEmmiters = maxEmmiter;

	mTexturePixelShader.Initialize("../../Assets/Shaders/Texturing.fx");
	mTextureVertexShader.Initialize("../../Assets/Shaders/Texturing.fx", Vishv::Graphics::VertexPX::Format);

	mParticlePixelShader.Initialize("../../Assets/Shaders/Particle.fx");
	mParticleVertexShader.Initialize("../../Assets/Shaders/Particle.fx", Vishv::Graphics::VertexPNC::Format);
	mParticleGeometryShader.Initialize("../../Assets/Shaders/Particle.fx");

	mTextureBuffer.Initialize();
	mParticleBuffer.Initialize();

	Vishv::Graphics::BlendManager::Get()->SetState(Vishv::Graphics::BlendState::Mode::AlphaBlend);
	Vishv::Graphics::RasterizerManager::Get()->ChangeState("NoneSolid");

	mParticleEmmiters.reserve(mMaxEmmiters);
	mParticlePresets.reserve(mMaxEmmiters);
}

void Vishv::ParticleSystem::Update(float deltaTime)
{
	for (auto& e : mParticleEmmiters)
		e.emmiter.Update(deltaTime);
}

void Vishv::ParticleSystem::RenderSimpleDraw(const Vishv::Graphics::Camera& camera)
{
	for (int i = 0; i < mParticleEmmiters.size(); ++i)
	{
		Vishv::Graphics::SimpleDraw::AddSphere(mParticlePresets[i].emmiterPosition, mParticlePresets[i].emmiterRadius, mParticleEmmiters[i].sphereColor, 12, 6);
	}

	Vishv::Graphics::SimpleDraw::Render(camera);
}

void Vishv::ParticleSystem::Render(const Vishv::Graphics::Camera& camera)
{
	for (int i = 0; i < mParticleEmmiters.size(); ++i)
	{
		if (mParticleEmmiters[i].useGPUacceleration)
			RenderParticle(camera, i);
		else
			RenderMesh(camera, i);
	}
}

void Vishv::ParticleSystem::RenderMesh(const Vishv::Graphics::Camera& camera, int i)
{
	auto view = camera.GetViewMatrix();
	auto proj = camera.GetPerspectiveMatrix();

	auto vp = view * proj;

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();
	for (int j = 0; j < mParticleEmmiters[i].emmiter.GetParticles().size(); ++j)
	{
		if (mParticleEmmiters[i].emmiter.GetParticles()[j].particle.IsAlive())
		{
			auto world = Vishv::Math::Matrix4::TranslateMatrix(mParticleEmmiters[i].emmiter.GetParticles()[j].particle.GetPosition());
			auto transform = (world * vp).Transpose();

			float time = mParticleEmmiters[i].emmiter.GetParticles()[j].particle.GetTime() / mParticleEmmiters[i].emmiter.GetParticles()[j].particle.GetTotalTime();
			float timeStep = 1.0f / (float)mParticlePresets[i].numTextures;

			int count = 0;
			for (int k = 0; i < (int)mParticlePresets[i].numTextures; ++k)
			{
				time -= timeStep;
				if (time < 0.0f)
					break;
				count++;
			}

			Vishv::Graphics::TextureManager::Get()->GetTexture(mParticlePresets[i].mTextureIDS[count])->BindPS();
			//			Vishv::Graphics::TextureManager::Get()->GetTexture(blue)->BindPS();

			mTextureBuffer.Set(transform);
			mTextureBuffer.BindVS(0);

			mParticleEmmiters[i].meshBuffer[j]->SetTopology(Vishv::Graphics::MeshBuffer::Topology::Triangles);
			mParticleEmmiters[i].meshBuffer[j]->Render();
		}
	}

}

void Vishv::ParticleSystem::RenderParticle(const Vishv::Graphics::Camera& camera, int i)
{
	auto view = camera.GetViewMatrix();
	auto projection = camera.GetPerspectiveMatrix();

	GeometryShaderConstantBufferData cbd;
	cbd.vp = (view * projection).Transpose();
	cbd.cameraPos = camera.GetPosition();
	cbd.cameraUp = camera.GetCameraUp();

	mParticleBuffer.Set(cbd);
	mParticleBuffer.BindVS(0);
	mParticleBuffer.BindGS(0);
	mParticleBuffer.BindPS(0);

	mParticlePixelShader.Bind();
	mParticleVertexShader.Bind();
	mParticleGeometryShader.Bind();

	Vishv::Graphics::SamplerManager::Get()->GetSampler(Vishv::Graphics::SamplerManager::SamplerType::AnistropicWrap)->BindPS();

	for (int j = 0; j < mParticleEmmiters[i].emmiter.GetParticles().size(); ++j)
	{
		if (!mParticleEmmiters[i].emmiter.GetParticles()[j].particle.IsAlive())
			continue;

		float time = mParticleEmmiters[i].emmiter.GetParticles()[j].particle.GetTime() / mParticleEmmiters[i].emmiter.GetParticles()[j].particle.GetTotalTime();
		float timeStep = 1.0f / (float)mParticlePresets[i].numTextures;

		int count = 0;
		for (int k = 0; i < (int)mParticlePresets[i].numTextures; ++k)
		{
			time -= timeStep;
			if (time < 0.0f)
				break;
			count++;
		}

		Vishv::Graphics::TextureManager::Get()->GetTexture(mParticlePresets[i].mTextureIDS[count])->BindPS();


		if(mParticleEmmiters[i].sortZBuffer)
			mParticleEmmiters[i].emmiter.Sort(camera.GetDirection());
		ParticleToMesh(mesh, i);
		if (mesh.mVertices.size() == 0)
			return;

		mParticleEmmiters[i].pointMeshBuffer.Update(static_cast<int>(mesh.mVertices.size()), mesh.mVertices.data());
		
	}
	mParticleEmmiters[i].pointMeshBuffer.SetTopology(Vishv::Graphics::MeshBuffer::Topology::Points);
	mParticleEmmiters[i].pointMeshBuffer.Render();

	mParticleGeometryShader.UnBind();
}

void Vishv::ParticleSystem::SortParticles(std::vector<Vishv::Physics::ParticleEmitter::ParticleData>& v, const Vishv::Graphics::Camera& camera)
{
	std::sort(v.begin(), v.end(), [&](auto& a, auto& b)
	{
		auto s = Math::Dot(a.particle.GetPosition(), camera.GetDirection());
		auto t = Math::Dot(b.particle.GetPosition(), camera.GetDirection());
		return s > t;
	});
}

void Vishv::ParticleSystem::ParticleToMesh(Vishv::Graphics::MeshPNC& mesh, int i)
{
	mesh.mVertices.clear();
	mesh.mVertices.reserve(mParticlePresets[i].maxNumberOfParticles);
	int count = 0;

	//auto& vec = mEmmiter.GetParticles();
	for (auto& p : mParticleEmmiters[i].emmiter.GetParticles())
	{
		if (!p.particle.IsAlive())
			continue;


		Vishv::Graphics::VertexPNC vertex;
		vertex.position.x = p.particle.GetPosition().x;
		vertex.position.y = p.particle.GetPosition().y;
		vertex.position.z = p.particle.GetPosition().z;

		vertex.normal.x = p.mRadius;
		vertex.normal.y = p.mRadius;
		vertex.normal.z = 0.0f;

		vertex.color = Vishv::Graphics::Colors::White;
		mesh.mVertices.emplace_back(vertex);
		count++;
	}
}

void Vishv::ParticleSystem::RenderDebugUI()
{
	ImGuiGlobal();
}

void Vishv::ParticleSystem::ImGuiGlobal()
{
	ImGui::Begin("Particle System", 0, ImGuiWindowFlags_AlwaysAutoResize);

	size_t total = 0;
	for (auto& pe : mParticleEmmiters)
	{
		total += pe.emmiter.GetParticles().size();
	}
	ImGui::Text("Total Particles: %zd", total);
	if (ImGui::CollapsingHeader("Add Particle Emmiter"))
	{
		if (ImGui::Button("Flame Effect"))
		{
			AddPresetFlame();
		}
		if (ImGui::Button("Smoke Effect"))
		{
			AddPresetSmoke();
		}
	}
	if (ImGui::Button("Clear Particles"))
	{
		mParticleEmmiters.clear();
		mParticlePresets.clear();
	}
	if (ImGui::CollapsingHeader("Emmiters"))
	{
		for (auto& em : mParticleEmmiters)
		{
			char* buffer = em.mName.data();
			ImGui::InputText(buffer, buffer, 20);
		}
	}

	ImGui::End();

	for (int i = 0; i < mParticleEmmiters.size(); ++i)
	{
		ImGuiIndividual(i);
	}

}
void Vishv::ParticleSystem::ImGuiIndividual(int i)
{
	ImGui::Begin(mParticleEmmiters[i].mName.c_str(), 0, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::CollapsingHeader("Emmiter Properties"))
	{
		Vishv::Math::Vector3 pos(mParticlePresets[i].emmiterPosition);
		float rad = mParticlePresets[i].emmiterRadius;

		ImGui::DragFloat("Radius##EmmiterTransform", &rad, 0.1f);
		ImGui::DragFloat3("Position##EmmiterTransform", &pos.x, 0.1f);
		ImGui::ColorEdit4("Emmiter_color##EmmiterTransform", &mParticleEmmiters[i].sphereColor.r);

		if (!(pos == mParticlePresets[i].emmiterPosition))
		{
			mParticlePresets[i].emmiterPosition = pos;
			mParticleEmmiters[i].emmiter.SetPosition(pos);
		}
		if (rad != mParticlePresets[i].emmiterRadius)
		{
			mParticlePresets[i].emmiterRadius = rad;
			mParticleEmmiters[i].emmiter.SetRadius(rad);
		}
	}
	if (ImGui::CollapsingHeader("Particle Properties"))
	{
		float grav = mParticlePresets[i].gravity;
		float life = mParticlePresets[i].lifeTime;
		float lifeJitter = mParticlePresets[i].lifeTimeJitter;
		float roe = mParticlePresets[i].rateOfEmmision;
		Vishv::Math::Vector3 vel(mParticlePresets[i].velocity);
		float velJit = mParticlePresets[i].velocityJitter;
		bool withinCollide = mParticlePresets[i].collideWithin;
		bool outsideCollide = mParticlePresets[i].outsideCollide;
		bool burst = mParticlePresets[i].burst;

		ImGui::DragFloat("Gravity##pp", &grav, 0.1f);
		ImGui::DragFloat("RateOfEmmision##pp", &roe, 0.1f, 0.0f);
		ImGui::DragFloat("Particle Life##pp", &life, 0.1f, 0.0f);
		ImGui::DragFloat("Particle Life Jitter##pp", &lifeJitter, 0.1f);
		ImGui::DragFloat3("Velocity##pp", &vel.x, 0.1f);
		ImGui::DragFloat("Velocity Jitter##pp", &velJit, 0.1f, 0.1f);
		ImGui::Checkbox("Collide Within##pp", &withinCollide);
		ImGui::Checkbox("Collide Outside##pp", &outsideCollide);
		ImGui::Checkbox("burst##pp", &burst);
		ImGui::Checkbox("Use GPU Acceleration##pp", &mParticleEmmiters[i].useGPUacceleration);
		if (mParticleEmmiters[i].useGPUacceleration)
		{
			ImGui::Checkbox("Alpha channel Sorting##pp", &mParticleEmmiters[i].sortZBuffer);
		}
		if (ImGui::CollapsingHeader("Burst") && burst)
		{
			mParticlePresets[i].burst = true;
			mParticleEmmiters[i].emmiter.SetBurst(true);

			int countp = static_cast<int>(mParticleEmmiters[i].burstholder.particleCount);
			ImGui::DragInt("Particle Count##Burst", &countp);
			ImGui::DragFloat("Loop Time", &mParticleEmmiters[i].burstholder.time);
			ImGui::Checkbox("Is Looping", &mParticleEmmiters[i].burstholder.loop);
			if(countp >= 0)
				mParticleEmmiters[i].burstholder.particleCount = static_cast<uint32_t>(countp);

			if (ImGui::Button("Add Burst"))
			{
				mParticleEmmiters[i].emmiter.AddBurst(mParticleEmmiters[i].burstholder);
			}
		}
		else if(!burst)
		{
			mParticlePresets[i].burst = false;
			mParticleEmmiters[i].emmiter.SetBurst(false);
		}
		if (burst)
		{
			if (ImGui::CollapsingHeader("Emitter Bursts"))
			{
				int count = 0;
				for (auto& b : mParticleEmmiters[i].emmiter.GetBursts())
				{
					ImGuiEmmiterBurst(b, count);
					count++;
				}
			}
		}

		

		if (!(vel == mParticlePresets[i].velocity))
		{
			mParticlePresets[i].velocity = vel;
			mParticleEmmiters[i].emmiter.SetVelocity(vel);
		}
		if (burst != mParticlePresets[i].burst)
		{
			mParticlePresets[i].burst = burst;
			mParticleEmmiters[i].emmiter.SetBurst(burst);
		}
		if (withinCollide != mParticlePresets[i].collideWithin)
		{
			mParticlePresets[i].collideWithin = withinCollide;
			mParticleEmmiters[i].emmiter.SetCollideWithin(withinCollide);
		}
		if (outsideCollide != mParticlePresets[i].outsideCollide)
		{
			mParticlePresets[i].outsideCollide = outsideCollide;
			mParticleEmmiters[i].emmiter.SetCollideOutside(outsideCollide);
		}
		if (mParticlePresets[i].velocityJitter != velJit)
		{
			mParticlePresets[i].velocityJitter = velJit;
			mParticleEmmiters[i].emmiter.SetVelocityJitter(velJit);
		}
		if (roe != mParticlePresets[i].rateOfEmmision)
		{
			mParticlePresets[i].rateOfEmmision = roe;
			mParticleEmmiters[i].emmiter.SetRateOfEmmision(roe);
		}
		if (grav != mParticlePresets[i].gravity)
		{
			mParticlePresets[i].gravity = grav;
			mParticleEmmiters[i].emmiter.SetGravity(grav);
		}
		if (life != mParticlePresets[i].lifeTime)
		{
			mParticlePresets[i].lifeTime = life;
			mParticleEmmiters[i].emmiter.SetLife(life);
		}
		if (lifeJitter != mParticlePresets[i].lifeTimeJitter)
		{
			mParticlePresets[i].lifeTimeJitter = lifeJitter;
			mParticleEmmiters[i].emmiter.SetLifeJitter(lifeJitter);
		}
	}

	ImGui::End();
}

void Vishv::ParticleSystem::ImGuiEmmiterBurst(Vishv::Physics::ParticleEmitter::ParticleBurstData & b , int i)
{
	std::string name = std::to_string(i);
	if (ImGui::CollapsingHeader(name.c_str()))
	{
		int count = static_cast<int>(b.count);
		ImGui::DragInt("Particle Count burst", &count);
		ImGui::DragFloat("Loop Time", &b.time);

		if (count >= 0)
		{
			b.count = static_cast<uint32_t>(count);
		}
	}
}

void Vishv::ParticleSystem::Terminate()
{

}

void Vishv::ParticleSystem::AddPresetFlame()
{
	Vishv::Physics::ParticlePreset p;

	//texture
	p.numTextures = 4;
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("flame1.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("flame2.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("flame3.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("flame4.png"));

	//Particle Effect Global
	p.gravity = 0.10f;
	p.emmiterRadius = 2.0f;
	p.emmiterPosition = Vishv::Math::Vector3();
	p.maxNumberOfParticles = 2000;
	p.rateOfEmmision = 20.0f;

	p.lifeTime = 3.0f;
	p.lifeTimeJitter = 2.0f;

	p.positionJitter = p.emmiterRadius;

	p.velocity = { 0.0f, 14.0f, 0.0f };
	p.velocityJitter = 7.0f;

	p.radius = 3.0f;
	p.radiusJitter = 1.0f;

	mParticlePresets.emplace_back(p);
	std::string name = "Flame";
	InitializeEmmiter(p, name);
}

void Vishv::ParticleSystem::AddPresetSmoke()
{
	Vishv::Physics::ParticlePreset p;

	//texture
	p.numTextures = 5;
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("Smoke1.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("Smoke2.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("Smoke3.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("Smoke4.png"));
	p.mTextureIDS.push_back(Vishv::Graphics::TextureManager::Get()->LoadTexture("Smoke5.png"));

	//Particle Effect Global
	p.gravity = 2.10f;
	p.emmiterRadius = 5.0f;
	p.emmiterPosition = Vishv::Math::Vector3();
	p.maxNumberOfParticles = 2000;
	p.rateOfEmmision = 20.0f;

	p.lifeTime = 7.0f;
	p.lifeTimeJitter = 2.0f;

	p.positionJitter = p.emmiterRadius;

	p.velocity = { 0.0f, 8.0f, 0.0f };
	p.velocityJitter = 6.0f;

	p.radius = 4.0f;
	p.radiusJitter = 1.0f;

	mParticlePresets.emplace_back(p);
	InitializeEmmiter(p, "Smoke");
}

void Vishv::ParticleSystem::InitializeEmmiter(Vishv::Physics::ParticlePreset& preset, std::string name)
{
	ParticleEmmiterData pd;
	pd.emmiter.Initialize(preset);

	Vishv::Graphics::MeshPNC mesh;
	mesh.mVertices.reserve(preset.maxNumberOfParticles);
	pd.meshBuffer.reserve(preset.maxNumberOfParticles);

	Vishv::Graphics::VertexPNC v;
	v.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	v.normal = { 0.0f, 1.0f, 0.0f };
	v.position = { 0.0f, 0.0f, 0.0f };

	for (uint32_t i = 0; i < preset.maxNumberOfParticles; ++i)
	{
		pd.meshBuffer.emplace_back(std::make_unique<Vishv::Graphics::MeshBuffer>());
	}
	for (uint32_t i = 0; i < preset.maxNumberOfParticles; ++i)
	{
		Vishv::Graphics::MeshPX plane = Vishv::Graphics::Meshbuilder::CreatePlaneUV(1, 1, pd.emmiter.GetParticles()[i].mRadius * 2.0f, pd.emmiter.GetParticles()[i].mRadius * 2.0f);
		pd.meshBuffer[i]->Initialize(plane);

		mesh.mVertices.emplace_back(v);
	}
	pd.pointMeshBuffer.Initialize(static_cast<int>(mesh.mVertices.size()), sizeof(Vishv::Graphics::VertexPNC), mesh.mVertices.data(), true);
	pd.mName = name + std::to_string(mParticleEmmiters.size());
	mParticleEmmiters.emplace_back(std::move(pd));
}
*/


