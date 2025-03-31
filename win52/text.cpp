#include "text.hpp"

using namespace Win52;

Text::Text(Window* win, WinId id, Str text, int x, int y, int w, int h) : WinElement(WinType_Text, win, id, x, y, w, h) {
	this->text = text;
	this->EleGen();
}

Text::Text(WinContainer* winContain, WinId id, Str text, int x, int y, int w, int h) : WinElement(WinType_Text, winContain, id, x, y, w, h) {
	this->text = text;
	this->EleGen();
}

void Text::HWNDCreate() {
	HWND p_win = this->getParentHWND();

	this->hwnd = CreateWindowExW(
		NULL,
		L"Static",
		this->text,
		WS_VISIBLE | WS_CHILD,
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