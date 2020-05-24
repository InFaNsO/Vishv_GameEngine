#include "TestShaderState.h"

void TestShaderState::Initialize()
{
	mGameWorld.AddService<Vishv::PhysicsSystem>();
	mGameWorld.AddService<Vishv::CameraSystem>();
	mGameWorld.AddService<Vishv::PostProcessService>();
	auto modelService = mGameWorld.AddService<Vishv::ModelService>();
	std::filesystem::path path = L"C:\\Users\\bhavi\\OneDrive\\Documents\\GitHub\\Vishv_GameEngine\\Vishv_GE\\Assets\\3D_Models\\VishMesh\\Swat\\Swat.vmesh";


	mGameWorld.Initialize(10000);
	modelService->AddNew();
	modelService->Load(std::move(path));

	auto modelObj = mGameWorld.CreateNewGameObject();
	modelObj.Get()->AddComponent<Vishv::Components::TransformComponent>();
	modelObj.Get()->SetName("Model");
	auto model = modelObj.Get()->AddComponent<Vishv::Components::Model3D>();

	model->SetModel(modelService->GetModels()[0].model);
	modelObj.Get()->Initialize();
}


