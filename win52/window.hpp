#pragma once
#include <windows.h>
#include <iostream>

namespace win52 {
	class Window {
	public:
		HWND hwnd = NULL;
		Window(std::string title, int x, int y, int w, int h);
	};
}