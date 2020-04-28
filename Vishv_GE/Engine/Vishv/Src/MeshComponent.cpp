#include "Precompiled.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"

#include "CameraService.h"
#include "CameraComponent.h"

#include "imfilebrowser.h"

using namespace Vishv::Components;


META_DERIVED_BEGIN(MeshComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(mShape, "Shape")
		META_FIELD(mLength1, "Length1")
		META_FIELD(mLength2, "Length2")
		META_FIELD(mLength3, "Length3")
	META_FIELD_END
META_CLASS_END

namespace
{
	std::unique_ptr<ImGui::FileBrowser> modelImporterFileBrowser = nullptr;

	enum class Shape
	{
		none = -1,
		Cube,
		Cuboid,
		Sphere,
		Cylinder,
		max
	};

	std::string ToString(Shape s)
	{
		switch (s)
		{
		case Shape::Cube:
			return "Cube";
			break;
		case Shape::Cuboid:
			return "Cuboid";
			break;
		case Shape::Sphere:
			return "Sphere";
			break;
		case Shape::Cylinder:
			return "Cylinder";
			break;
		default:
			return "none";
			break;
		}
	}
}

void MeshComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();

	mModel.mMeshes.resize(1);
	mModel.mMaterials.resize(1);

	mModel.mMeshes[0].mIndex = 0;

	//setup file browser
	modelImporterFileBrowser = std::make_unique<ImGui::FileBrowser>(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_SelectDirectory);
	modelImporterFileBrowser->SetTitle("Texture Import");
	modelImporterFileBrowser->SetPwd(L"../../Assets");
	modelImporterFileBrowser->SetTypeFilters({ ".png", ".jpg" });

	mColor = Graphics::Colors::Coral;

	mCamSys = GetOwner().GetWorld().GetService<CameraSystem>();
}

void MeshComponent::SimpleDraw()
{
	if (shouldRender)
		return;

	Shape shape = (Shape)mShape;
	Vishv::Math::Shapes::Cuboid c;

	switch (shape)
	{
	case Shape::Cube:
		Vishv::Graphics::SimpleDraw::AddCube(mTransformComponent->Position(), mLength1, mColor);
		break;
	case Shape::Cuboid:
		c.mTransform.mPosition = mTransformComponent->Position();
		c.mTransform.SetRotation(mTransformComponent->Rotation());
		c.SetLengthX(mLength1);
		c.SetLengthY(mLength2);
		c.SetLengthZ(mLength3);
		Vishv::Graphics::SimpleDraw::AddCuboid(c, mColor);
		//Vishv::Graphics::SimpleDraw::AddCuboid(mTransformComponent->Position(), mLength1, mLength2, mLength3, mColor);
		break;
	case Shape::Sphere:
		Vishv::Graphics::SimpleDraw::AddSphere(mTransformComponent->Position(), mLength1, mColor);
		break;
	case Shape::Cylinder:
		Vishv::Graphics::SimpleDraw::AddCylinder(mTransformComponent->Position(), mLength1, mLength2, mColor);
		break;
	default:
		break;
	}
}

void MeshComponent::Render()
{
	if (!shouldRender)
		return;

	auto em = Graphics::EffectsManager::Get();

	if(!mCamSys->GetMainCamera().IsValid())
		return;
	auto cameraObj = mCamSys->GetMainCamera();
	auto& camera = cameraObj.Get()->GetComponent<CameraComponent>()->GetCamera();

	auto type = Graphics::EffectType::Standard;
	
	auto v = camera.GetViewMatrix();
	auto p = camera.GetPerspectiveMatrix();
	auto w = Vishv::Math::Matrix4::RotateMatrix(mTransformComponent->Rotation().GetConjugate()) * Vishv::Math::Matrix4::TranslateMatrix(mTransformComponent->Position());
	em->BindEffect(type);
	em->GetBufferData(type)->GetTransform()->viewPosition = camera.GetPosition();
	em->GetBufferData(type)->GetTransform()->world = w.Transpose();
	em->GetBufferData(type)->GetTransform()->wvp = (w * v *p).Transpose();
	
	em->Set(type);
	em->BindBuffer(type);

	mModel.Render();
}

void MeshComponent::DebugUI()
{
	std::string name = GetOwner().GetName();

	std::string Title = "Simple Mesh##" + name;

	if (!ImGui::CollapsingHeader(Title.c_str()))
		return;

	if (mIsFinal)
	{
		ImGui::Text(ToString((Shape)mShape).c_str());
		//ImportUI();
		return;
	}

	Title = "Mesh Settings##" + name;
	if (ImGui::CollapsingHeader(Title.c_str()))
	{
		Shape s = (Shape)mShape;
		ImGui::SliderInt("Mesh Shape", &mShape, (int)Shape::none, (int)Shape::max);
		ImGui::Text(ToString(s).c_str());
		Math::Vector3 dimensions(mLength1, mLength2, mLength3);

		switch (s)
		{
		case Shape::Cube:
			ImGui::DragFloat("Length", &mLength1);
			break;
		case Shape::Cuboid:
			if (ImGui::DragFloat3("Dimensions", &dimensions.x))
			{
				mLength1 = dimensions.x;
				mLength2 = dimensions.y;
				mLength3 = dimensions.z;
			}
			break;
		case Shape::Sphere:
			ImGui::DragFloat("Radius", &mLength1);
			break;
		case Shape::Cylinder:
			ImGui::DragFloat("Radius", &mLength1);
			ImGui::DragFloat("height", &mLength2);
			break;
		default:
			break;
		}
	}

	Title = "Texture Settings##" + name;
	if(ImGui::CollapsingHeader(Title.c_str()))
		ImportUI();

	if (mShape != (int)Shape::none && mShape != (int)Shape::max)
	{
		if (ImGui::Button("Set"))
		{
			mIsFinal = !mIsFinal;
			InitMesh();
		}
	}

}

void MeshComponent::ImportUI()
{
	static char loadTex[128]{};

	ImGui::InputText("Texture Name##ModelLoader", loadTex, std::size(loadTex));

	if (ImGui::Button("Diffuse"))
		mModel.mMaterials[0].diffuseName = loadTex;
	if (ImGui::Button("Normal"))
		mModel.mMaterials[0].normalName = loadTex;
	if (ImGui::Button("Specular"))
		mModel.mMaterials[0].specularName = loadTex;
}

void MeshComponent::Set(int shape, float l1, float l2, float l3, std::filesystem::path& diffPath, std::filesystem::path& normPath, std::filesystem::path& specPath)
{
	mShape = shape;
	mLength1 = l1;
	mLength2 = l2;
	mLength3 = l3;

	auto& mat = mModel.mMaterials[0];
	mat.diffuseName = diffPath.string();
	mat.normalName = normPath.string();
	mat.specularName = specPath.string();

	InitMesh();
}

void Vishv::Components::MeshComponent::InitMesh()
{
	Shape s = (Shape)mShape;

	switch (s)
	{
	case Shape::Cube:
		mModel.mMeshes[0].mBuffer.Initialize(std::move(Graphics::Meshbuilder::CreateCubeUV(mLength1, mLength1, mLength1)));
		break;
	case Shape::Cuboid:
		mModel.mMeshes[0].mBuffer.Initialize(std::move(Graphics::Meshbuilder::CreateCubeUV(mLength2, mLength1, mLength3)));
		break;
	case Shape::Sphere:
		mModel.mMeshes[0].mBuffer.Initialize(std::move(Graphics::Meshbuilder::CreateSphereUV(12,12, mLength1)));
		break;
	case Shape::Cylinder:
		mModel.mMeshes[0].mBuffer.Initialize(std::move(Graphics::Meshbuilder::CreateCylinderUV(3,12, mLength1, mLength2 / 3.0f, true)));
		break;
	default:
		return;
		break;
	}

	auto textureManager = Vishv::Graphics::TextureManager::Get();

	auto& material = mModel.mMaterials[0];
	if (material.diffuseName != "empty")
		material.diffuseID = textureManager->LoadTexture(material.diffuseName);
	else
		material.diffuseID = textureManager->LoadTexture("black.jpg");
	if (material.bumpName != "empty")
		material.bumpID = textureManager->LoadTexture(material.bumpName);
	else
		material.bumpID = textureManager->LoadTexture("black.jpg");
	if (material.normalName != "empty")
		material.normalID = textureManager->LoadTexture(material.normalName);
	else
		material.normalID = textureManager->LoadTexture("black.jpg");
	if (material.specularName != "empty")
		material.specularID = textureManager->LoadTexture(material.specularName);
	else
		material.specularID = textureManager->LoadTexture("black.jpg");

	shouldRender = true;
}

