#include <Vishv/Inc/Vishv.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//VishvApp::AddState<StarteState>("StartState");
	//VishvApp::AddState<MainState>("MainState");
	//VishvApp::ChangeState("StartState");
	VishvApp::Run(Vishv::AppConfig("Vishv v0.1"));		//Default starts with the first state

	return 0;
}
