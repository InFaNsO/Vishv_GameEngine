#ifndef INCLUDED_VSHV_EDITOR_MODEL_CONVERTOR_TOOL_H
#define INCLUDED_VSHV_EDITOR_MODEL_CONVERTOR_TOOL_H

#pragma once


namespace Vishv::Editor
{
	class ModelConvertor
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();

		static ModelConvertor* Get();

	public:
		void Initialize();
		void Terminate();

		void DoUI();

		void Open() { isOpen = true; }

	private:
		void Update();

		std::filesystem::path importFile = "";
		std::filesystem::path exportFile = "";

		bool isImport = false;
		bool isExport = false;

		bool isOpen = false;
	};
}


#endif // !INCLUDED_VSHV_EDITOR_MODEL_CONVERTOR_TOOL_H





