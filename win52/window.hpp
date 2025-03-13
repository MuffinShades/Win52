#pragma once
#include <windows.h>
#include <iostream>

namespace Win52 {
	class Window {
	public:
		HWND hwnd = NULL;
		Window(std::string title, int x, int y, int w, int h);
	};
}