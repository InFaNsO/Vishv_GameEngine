//====================================================================================================
// Filename:	Gui.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_VISHV_GRAPHICS_DEBUGUI_H
#define INCLUDED_VISHV_GRAPHICS_DEBUGUI_H

namespace Vishv::Graphics::DebugUI {

enum class Theme
{
	Classic,
	Dark,
	Light
};

void StaticInitialize(HWND window, bool docking = true, bool multiWin = true);
void StaticTerminate();
void BeginRender();
void EndRender();

void SetTheme(Theme theme);

} // namespace Vishv::Graphics::DebugUI

#endif // #ifndef INCLUDED_VISHV_GRAPHICS_DEBUGUI_H