#include "button.hpp"

using namespace Win52;

Button::Button(Window* win, WinId id, Str text, int x, int y, int w, int h) : WinElement(WinType_Button, win, id, x, y, w, h) {
	this->text = text;
	this->EleGen();
}

Button::Button(WinContainer* wContain, WinId id, Str text, int x, int y, int w, int h) : WinElement(WinType_Button, wContain, id, x, y, w, h)  {
	this->text = text;
	this->EleGen();
}

void Button::HWNDCreate() {
	HWND p_win = this->getParentHWND();

	this->hwnd = CreateWindowExW(
		NULL,
		L"Button",
		this->text,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		this->pos.x,
		this->pos.y,
		this->pos.w,
		this->pos.h,
		p_win,
		NULL,
		(HINSTANCE)GetWindowLongPtr(p_win, GWLP_HINSTANCE),
		NULL
	);
}