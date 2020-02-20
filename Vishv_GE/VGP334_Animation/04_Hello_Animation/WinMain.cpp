#include "GameState.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	VishvApp::AddState<GameState>("GameState");
	VishvApp::Run(Vishv::AppConfig("Hello Animation"));
	return 0;

}