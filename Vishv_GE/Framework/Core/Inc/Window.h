#ifndef INCLUDED_VISHV_CORE_WINDOW_H
#define INCLUDED_VISHV_CORE_WINDOW_H

namespace Vishv::Core {

class Window
{
public:
	Window() = default;

	void Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height, bool maximize = false);
	void Terminate();
	bool ProcessMessage();
	HWND GetWindowHandle() const { return mWindow; }

	
private:
	HINSTANCE mInstance { nullptr };
	HWND mWindow { nullptr };
	std::string mAppName;
};

} // namespace Vishv::Core

#endif //Defined INCLUDED_VISHV_CORE_WINDOW_H