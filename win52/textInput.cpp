#include "textInput.hpp"
#include <CommCtrl.h>

using namespace Win52;

TextInput::TextInput(Win52::Window* win, WinId id, int x, int y, int w, int h) : WinElement(WinType_TextInput, win, id, x, y, w, h) {
	this->EleGen();
}

TextInput::TextInput(Win52::WinContainer* wContain, WinId id, int x, int y, int w, int h) : WinElement(WinType_TextInput, wContain, id, x, y, w, h) {
	this->EleGen();
}

void TextInput::SetPlaceHolder(Str placeholder) {
	if (placeholder.length() <= 0) return;

	if (!this->hwnd) return;

	if (!SendMessage(this->hwnd, EM_SETCUEBANNER, FALSE, (LPARAM)(wchar_t*)placeholder)) {
		std::cout << "Text Input Error, failed to set placeholder!" << std::endl;
	}
}

void TextInput::HWNDCreate() {
	HWND p_win = this->getParentHWND();

	this->hwnd = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		this->text,
		WS_OVERLAPPED | WS_VISIBLE | WS_CHILD | ES_LEFT,
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