#include "Precompiled.h"
#include "WindowMessageHandler.h"

#include "Debug.h"

void Vishv::Core::WindowMessageHandler::Hook(HWND window, Callback cb)
{
	mWindow = window;
	mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void Vishv::Core::WindowMessageHandler::UnHook()
{
	SetWindowLongA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
	mWindow = nullptr;
}

LRESULT Vishv::Core::WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	VISHVASSERT(mPreviousCallback, "[Core::WindowMessageHandler] No callback is hooked.");
	return CallWindowProc((WNDPROC)mPreviousCallback, window, message, wParam, lParam);
}