#include "Vishv/Inc/Vishv.h"
#include "EditState.h"
#include "PlayState.h"

#include "GameStateAnimBlending.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	Vishv::AppConfig config("Vishv Editor");

	config.maximize = true;
	config.docking = true;

	//VishvApp::AddState<PlayState>("PlayState");
	VishvApp::AddState<EditState>("EditState");
	VishvApp::Run(std::move(config));		//Default starts with the first state

	return 0;
}



