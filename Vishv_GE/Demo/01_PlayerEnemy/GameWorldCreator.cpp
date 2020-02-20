#include "GameWorldCreator.h"

using namespace Vishv;

void GameWorldCreator::SetWorld(Vishv::GameWorld & w)
{
	mWorld = &w;
}

void GameWorldCreator::Update(float deltaTime)
{
	//for (auto& go : mGameObjects)
	//	go.Update(deltaTime);
}

void GameWorldCreator::SimpleDraw()
{

}

void GameWorldCreator::DebugUI()
{
	ImGui::Begin("World Creator");

	if (ImGui::Button("Add Object##worldCreator"))
	{
		std::filesystem::path p;

		auto go = mWorld->Create(p, "Asset");

		go.Get()->AddComponent<Components::TransformComponent>();
		go.Get()->AddComponent<Components::MeshComponent>();
		mWorld->Register(*go.Get());
		go.Get()->Initialize();
		mGameObjects.emplace_back(go);
	}

	if (ImGui::Button("Save##worldCreator"))
	{
		Save();
	}
	if (ImGui::Button("Load##worldcreator"))
		Load("World.vscene");

	ImGui::End();
}

void GameWorldCreator::Save()
{
	std::filesystem::path p = "World.vscene";

	std::fstream file;
	file.open(p);

	VISHVASSERT(file.is_open(), "cannot open file");

	file.clear();
	file << "NumObj: " << mGameObjects.size() << "\n";
	for (auto& go : mGameObjects)
	{
		Components::MeshComponent* mesh = go.Get()->GetComponent<Components::MeshComponent>();
		file << "Transform: \nPosition: " << go.Get()->GetComponent<Components::TransformComponent>()->Position().ToString() << "\n";
		file << "Mesh: \nShape: " << mesh->GetShape() << "\n";
		file << "Lengths: " << mesh->Getlengths().ToString();
		file << "\nMaterial:\n";
		auto& mat = mesh->GetModel().mMaterials[0];
		file << "Diffuse: " << mat.diffuseName << "\n";
		file << "Normal: " << mat.normalName<< "\n";
		file << "Specular: " << mat.specularName << "\n";
	}

	file.close();
}

void GameWorldCreator::Load(std::filesystem::path p)
{
	std::fstream file;
	file.open(p);

	VISHVASSERT(file.is_open(), "cannot open file");

	std::string holder;
	size_t numObj;
	file >> holder >> numObj;
	mGameObjects.reserve(numObj);
	for (uint32_t i = 0; i < numObj; ++i)
	{
		int shape;
		Math::Vector3 pos, lengths;
		std::filesystem::path diffPath, specPath, normPath;
		file >> holder >> holder >> pos.x >> pos.y >> pos.z;
		file >> holder >> holder >> shape;
		file >> holder >> lengths.x >> lengths.y >> lengths.z;
		file >> holder;
		file >> holder >> diffPath;
		file >> holder >> normPath;
		file >> holder >> specPath;

		auto go = mWorld->Create(p, "Asset");

		auto transform = go.Get()->AddComponent<Components::TransformComponent>();
		auto mesh = go.Get()->AddComponent<Components::MeshComponent>();
		mWorld->Register(*go.Get());
		
		go.Get()->Initialize();

		transform->GetPosition() = pos;
		mesh->Set(shape, lengths.x, lengths.y, lengths.z, diffPath, normPath, specPath);

		mGameObjects.emplace_back(go);
	}
}

void GameWorldCreator::Render()
{
//	for (auto& go : mGameObjects)
//		go.Render();
}
