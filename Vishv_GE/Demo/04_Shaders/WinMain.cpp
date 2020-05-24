#include <Vishv/Inc/Vishv.h>
#include "TestShaderState.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//VishvApp::AddState<StarteState>("StartState");
	VishvApp::AddState<TestShaderState>("MainState");
	VishvApp::ChangeState("MainState");
	VishvApp::Run(Vishv::AppConfig("Vishv v0.1"));		//Default starts with the first state

	return 0;
}
