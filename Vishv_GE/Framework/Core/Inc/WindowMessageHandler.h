#ifndef INCLUDED_VISHV_CORE_WindowMessageHandler_H
#define INCLUDED_VISHV_CORE_WindowMessageHandler_H


namespace Vishv::Core{

class WindowMessageHandler
{
public:
	using Callback = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

	void Hook(HWND window, Callback cb);
	void UnHook();

	LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND mWindow{ nullptr };
	Callback mPreviousCallback{ nullptr };
};

}	//namespace Vishv::Core


#endif	//Defined INCLUDED_VISHV_CORE_WindowMessageHandler_H
