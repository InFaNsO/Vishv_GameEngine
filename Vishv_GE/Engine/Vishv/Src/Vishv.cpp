#include "Precompiled.h"
#include "Vishv.h"
#include "App.h"

Vishv::App& VishvApp::GetApp()
{
	static Vishv::App sApp;
	return sApp;
}

void VishvApp::ChangeState(std::string name)
{
	GetApp().ChangeState(std::move(name));
}

void VishvApp::Run(Vishv::AppConfig appConfig)
{
	GetApp().Run(std::move(appConfig));
}

void VishvApp::ShutDown()
{
	PostQuitMessage(0);
}