#include "window.hpp"
#include "WinUtil.hpp"
#include "WinRgstr.hpp"
#include "WinProc.hpp"
#include "Str.hpp"

#define WIN52_WINCLASS_DEFAULT "win52_win_base"

using namespace Win52;

Win52::Window::Window(Str title, int x, int y, int w, int h) {
	if (title.length() <= 0) return;

	Str t_str = title; //convert title

	if (!WinRgstr::registered(WIN52_WINCLASS_DEFAULT)) {
		WNDCLASSEX win_class = {};

		win_class.cbSize = sizeof(WNDCLASSEX);
		win_class.lpfnWndProc = &Win52::WinProc_Default;
		win_class.lpszClassName = TEXT(WIN52_WINCLASS_DEFAULT);
		//win_class.

		if (!WinRgstr::registerClassEx(WIN52_WINCLASS_DEFAULT, win_class)) {
			std::cout << "Win class register failed!" << std::endl;
			return;
		}
	}

	//create the window
	this->_hwnd = CreateWindowEx(
		NULL,
		TEXT(WIN52_WINCLASS_DEFAULT),
		t_str,
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		w, 
		h,
		NULL,
		NULL,
		NULL,
		NULL //use this to pass some sort of struct to the windwo
	);

	if (!this->_hwnd) {
		std::cout << "Failed to create window :/" << std::endl;
		return;
	}

	this->hdc = GetDC(this->_hwnd);

	ShowWindow(this->_hwnd, SW_SHOW);
}

bool Window::Update() {
	if (!this->_hwnd) return 0;

	//TODO: thread this so when get message doesnt return a message the whole program doesn't stop
	MSG msg;
	i32 win_run = GetMessage(&msg, this->_hwnd, 0, 0);

	//
	TranslateMessage(&msg);
	DispatchMessage(&msg);

	this->running = win_run > 0;

	return 1;
}

bool Window::Running() {
	return this->running;
}

HDC Window::getHDC() {
	return this->hdc;
}