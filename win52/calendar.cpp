#include "calendar.hpp"
#include <CommCtrl.h>

using namespace Win52;

Calendar::Calendar(Win52::Window* win, WinId id, int x, int y, int w, int h) : WinElement(WinType_Calendar, win, id, x, y, w, h) {
	this->EleGen();
}

Calendar::Calendar(Win52::WinContainer* wContain, WinId id, int x, int y, int w, int h) : WinElement(WinType_Calendar, wContain, id, x, y, w, h) {
	this->EleGen();
}

void Calendar::HWNDCreate() {
	HWND p_win = this->getParentHWND();

	this->hwnd = CreateWindowExW(
		NULL,
		MONTHCAL_CLASS,
		L"",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
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

void Calendar::SetDate(Date d) {
	SYSTEMTIME _t = d.getSysTime();
	if (this->hwnd)
		SendMessage(this->hwnd, MCM_SETCURSEL, 0, (LPARAM) &_t);
}

Date Calendar::GetSelectedDate() {

}