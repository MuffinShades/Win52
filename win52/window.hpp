#pragma once
#include <windows.h>
#include <iostream>
#include "Str.hpp"

namespace Win52 {
	class Window {
	private:
		bool running = false;
		HDC hdc = NULL;
	public:
		HWND hwnd = NULL;
		Window(Str title, int x, int y, int w, int h);
		bool Update();
		bool Running();
		HDC getHDC();
	};
}