#ifndef INCLUDED_VISHV_GRAPHICS_RASTERISERSTATEMANAGER_H
#define INCLUDED_VISHV_GRAPHICS_RASTERISERSTATEMANAGER_H

#include "RasterizerState.h"

namespace Vishv::Graphics {

class RasterizerManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static RasterizerManager* Get();

public:
	RasterizerManager() = default;

	void Initialize();
	bool AddState(std::string name, RasterizerState::CullMode cMode = RasterizerState::CullMode::Back, RasterizerState::FillMode fMode = RasterizerState::FillMode::Solid);
	bool SetState(std::string name);
	bool ClearState(std::string name);
	void Terminate();
	bool ChangeState(std::string name);


private:
	bool TerminateState(std::string name);
	std::unordered_map<std::string, std::unique_ptr<RasterizerState>> mStates;
	std::string mCurrentState;
};

}


#endif // !INCLUDED_VISHV_GRAPHICS_RASTERISERSTATEMANAGER_H
