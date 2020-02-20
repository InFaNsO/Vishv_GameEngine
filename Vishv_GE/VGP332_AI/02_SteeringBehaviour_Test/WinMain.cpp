#include "MainState.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	VishvApp::AddState<MainState>("MainState");

	VishvApp::Run(Vishv::AppConfig("Steering Behaviour"));

	return 0;
}

