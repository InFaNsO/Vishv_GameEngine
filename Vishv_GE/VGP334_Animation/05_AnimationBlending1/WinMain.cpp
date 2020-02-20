#include "GameStateAnimBlending.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	VishvApp::AddState<GameStateAnimBlending>("GameState");
	VishvApp::Run(Vishv::AppConfig("Animation Blending"));
	return 0;

}