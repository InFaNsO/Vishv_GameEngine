#ifndef INCLUDED_VISHV_GRAPHICS_BLENDMANAGER_H
#define INCLUDED_VISHV_GRAPHICS_BLENDMANAGER_H

#include "BlendState.h"

namespace Vishv::Graphics {

	namespace Blend
	{
		const extern std::string Opaque;
		const extern std::string AlphaBlend;
		const extern std::string AlphaPremultiplied;
		const extern std::string Additive;
	}

class BlendManager {

public:
	static void StaticInitialize();
	static void StaticTerminate();
	static BlendManager* Get();

public:


	BlendManager() = default;
	~BlendManager();

	void Initialize();
	
	bool AddState(std::string name);
	bool AddState(BlendState::Mode mode);
	
	bool SetState(std::string name);
	bool SetState(BlendState::Mode mode);
	
	bool ClearState(std::string name = "");
	bool ClearState(BlendState::Mode mode);
	
	void Terminate();

private:
	bool TerminateState(BlendState::Mode mode);
	BlendState::Mode StringToEnum(std::string name);

	std::unordered_map< BlendState::Mode, std::unique_ptr<BlendState>> mInventory;

};
}

#endif // !INCLUDED_VISHV_GRAPHICS_BLENDMANAGER_H
