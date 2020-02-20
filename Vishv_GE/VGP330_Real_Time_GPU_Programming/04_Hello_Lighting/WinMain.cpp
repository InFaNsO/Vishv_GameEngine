//#include <Core/Inc/Core.h>
//#include <Graphics/Inc/Graphics.h>
//#include <Math/Inc/VishvMath.h>
//#include <Input/Inc/Input.h>
//#include <ImGui/Inc/imgui.h>
//
#include "GameState.h"

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;
using namespace Vishv::Input;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	VishvApp::AddState<GameState>("GameState");
	VishvApp::Run(Vishv::AppConfig("Hello Lighting"));
	return 0;

}
