#include "MainState.h"

void MainState::Initialize()
{
	mGameWorld.AddService<Vishv::PhysicsSystem>();
	auto camSys = mGameWorld.AddService<Vishv::CameraSystem>();
	mGameWorld.AddService<Vishv::PostProcessService>();
	mGameWorld.AddService<Vishv::SkyBox>();
	mGameWorld.AddService<Vishv::SimpleDrawer>();
	mGameWorld.AddService<Vishv::Lighting>();
	
	auto modelService = mGameWorld.AddService<Vishv::ModelService>();
	std::filesystem::path path = L"C:\\Users\\bhavi\\OneDrive\\Documents\\GitHub\\Vishv_GameEngine\\Vishv_GE\\Assets\\3D_Models\\VishMesh\\Swat";


	mGameWorld.Initialize(10000);
	modelService->AddNew();
	modelService->Load(path / "Swat.vmesh");
	modelService->Load(path / "Walking.vanim");
	modelService->Load(path / "IdleStanding1.vanim");
	modelService->Load(path / "IdleCrouching1.vanim");


	//auto modelObj = mGameWorld.CreateNewGameObject();
	//modelObj.Get()->AddComponent<Vishv::Components::TransformComponent>();
	//modelObj.Get()->SetName("Model");
	//auto model = modelObj.Get()->AddComponent<Vishv::Components::Model3D>();
	//
	//model->SetModel(modelService->GetModels()[0].model);
	//modelObj.Get()->Initialize();

	auto transform = camSys->GetMainCamera().Get()->GetComponent<Vishv::Components::TransformComponent>();
	auto tMat = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(88.f, 25.f, -300.f));
	transform->SetTransformation(transform->GetTransformMatrix() * tMat);
}


void MainState::RenderDebugUI()
{
 
}

