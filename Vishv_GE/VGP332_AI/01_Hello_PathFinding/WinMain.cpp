#include "MainState.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	VishvApp::AddState<MainState>("MainState");

	VishvApp::Run(Vishv::AppConfig("Path Finding"));

	return 0;
}

