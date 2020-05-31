#include "Precompiled.h"
#include "ModelConvertorTool.h"

#include "Editor.h"
#include "imfilebrowser.h"


using namespace Vishv;
using namespace Editor;

namespace
{
	std::unique_ptr<Editor::ModelConvertor> sInstance = nullptr;
	std::unique_ptr<ImGui::FileBrowser> fileBrowser = nullptr;
}

void Vishv::Editor::ModelConvertor::StaticInitialize()
{
	if (!sInstance)
	{
		sInstance = std::make_unique<ModelConvertor>();
		sInstance->Initialize();
	}
}

void Vishv::Editor::ModelConvertor::StaticTerminate()
{
	if (sInstance)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

ModelConvertor* Vishv::Editor::ModelConvertor::Get()
{
	return sInstance.get();
}

void Vishv::Editor::ModelConvertor::Initialize()
{
	fileBrowser = std::make_unique<ImGui::FileBrowser>(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename);

	fileBrowser->SetTitle("Model Convertor");
	fileBrowser->SetPwd("..\\..\\Assets\\3D_Models");
	fileBrowser->SetTypeFilters({ ".fbx" });
}

void Vishv::Editor::ModelConvertor::Terminate()
{
	fileBrowser.release();
}

void Vishv::Editor::ModelConvertor::Update()
{
	fileBrowser->Display();
	if (fileBrowser->HasSelected() && (isImport || isExport))
	{
		if (isImport)
			importFile = fileBrowser->GetSelected();
		if (isExport)
			exportFile = fileBrowser->GetSelected();
		fileBrowser->ClearSelected();
		fileBrowser->Close();

		isImport = false;
		isExport = false;
	}
}

void Vishv::Editor::ModelConvertor::DoUI()
{
	if (!isOpen)
		return;

	Update();

	static std::filesystem::path fileexe = "..\\..\\Assets\\Tools\\ModelImporter.exe";

	ImGui::Begin("Model Convertor");

	if (ImGui::Button("Set Load File"))
	{
		fileBrowser->SetTypeFilters({ ".fbx" });
		fileBrowser->Open();
		isImport = true;
	}

	if (importFile == "")
		ImGui::Text("No Import file selected");
	else
		ImGui::Text(("Selected file: " + importFile.filename().string()).c_str());

	if (ImGui::Button("Set Export File"))
	{
		fileBrowser->SetTypeFilters({ ".vmesh" });
		fileBrowser->Open();
		isExport = true;
	}

	if (exportFile == "")
		ImGui::Text("No Export file selected");
	else
		ImGui::Text(("Selected file: " + exportFile.filename().string()).c_str());


	if (ImGui::Button("Done"))
	{
		isOpen = false;

		if (importFile != "" && exportFile != "")
		{
			std::string command = "start " + fileexe.string() + " " + importFile.string() + " " + exportFile.string();
			system(command.c_str());
		}

		importFile = "";
		exportFile = "";
	}

	ImGui::End();

}

