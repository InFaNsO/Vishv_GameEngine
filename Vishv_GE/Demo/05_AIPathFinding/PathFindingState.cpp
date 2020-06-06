#include "PathFindingState.h"
#include "AnimationController.h"

void PathFindingState::Initialize()
{
	mGameWorld.AddService<Vishv::AIWorld>();
	mGameWorld.AddService<Vishv::PhysicsSystem>();
	auto camSys = mGameWorld.AddService<Vishv::CameraSystem>();
	mGameWorld.AddService<Vishv::PostProcessService>();
	mGameWorld.AddService<Vishv::SkyBox>();
	mGameWorld.AddService<Vishv::SimpleDrawer>();
	mGameWorld.AddService<Vishv::Lighting>();

	auto modelService = mGameWorld.AddService<Vishv::ModelService>();
	std::filesystem::path path = L"C:\\Users\\bhavi\\OneDrive\\Documents\\GitHub\\Vishv_GameEngine\\Vishv_GE\\Assets\\3D_Models\\VishMesh\\Swat\\Swat.vmesh";


	mGameWorld.Initialize(10000);
	modelService->AddNew();
	modelService->Load(std::move(path));
	
	auto entity = mGameWorld.CreateNewGameObject();
	entity.Get()->AddComponent<Vishv::Components::TransformComponent>();
	entity.Get()->SetName("Entity");
	entity.Get()->AddComponent<AnimationController>();
	auto model = entity.Get()->AddComponent<Vishv::Components::Model3D>();
	model->SetModel(modelService->GetModels()[0].model);
	entity.Get()->AddComponent<Vishv::Components::Animation3D>();
	entity.Get()->AddComponent<Vishv::Components::AIAgent>()
	//modelObj.Get()->Initialize();
	auto transform = camSys->GetMainCamera().Get()->GetComponent<Vishv::Components::TransformComponent>();
	auto tMat = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(88.f, 25.f, -300.f));
	transform->SetTransformation(transform->GetTransformMatrix() * tMat);
}

