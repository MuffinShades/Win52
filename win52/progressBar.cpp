#include "progressBar.hpp"
#include <CommCtrl.h>
#include <uxtheme.h>

using namespace Win52;

ProgressBar::ProgressBar(Window* win, WinId id, i32 x, i32 y, i32 w, i32 h) : WinElement(WinType_Progress, win, id, x, y, w, h) {
	this->HWNDCreate();
}

ProgressBar::ProgressBar(WinContainer* wContain, WinId id, i32 x, i32 y, i32 w, i32 h) : WinElement(WinType_Progress, wContain, id, x, y, w, h)  {
	this->HWNDCreate();
}

ProgressBar::ProgressBar(Window* win, WinId id, ProgressStyle style, i32 x, i32 y, i32 w, i32 h) : WinElement(WinType_Progress, win, id, x, y, w, h) {
	this->vert = style.vertical;
	this->HWNDCreate();
	this->__applyStyle(style);
}

ProgressBar::ProgressBar(WinContainer* wContain, WinId id, ProgressStyle style, i32 x, i32 y, i32 w, i32 h) : WinElement(WinType_Progress, wContain, id, x, y, w, h) {
	this->vert = style.vertical;
	this->HWNDCreate();
	this->__applyStyle(style);
}

void ProgressBar::HWNDCreate() {
	HWND p_win = this->getParentHWND();

	DWORD p_style = WS_OVERLAPPED | WS_VISIBLE | WS_CHILD | PBS_SMOOTH;

	if (this->vert)
		p_style |= PBS_VERTICAL;

	this->hwnd = CreateWindowExW(
		NULL,
		PROGRESS_CLASS,
		L"",
		p_style,
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

void ProgressBar::SetProgressPercent(f32 p) {
	if (p < 0.0f) p = 0.0f;
	if (p > 1.0f) p = 1.0f;

	if (this->hwnd)
		SendMessage(this->hwnd, PBM_SETPOS, (WPARAM)(i32)(this->min + (p * (this->max - this->min))), NULL);
}

void ProgressBar::SetProgress(f32 v) {

}

void ProgressBar::SetRange(f32 min, f32 max) {
	if (min > max) return; //invalid range
	if (min < -0x7fff)
		min = -32767.0f;
	this->min = min;
	if (max > 0x7fff)
		max = 32767.0f;
	this->max = max;
	this->__rangeUpdate();
}

void ProgressBar::SetMin(f32 min) {
	if (min < -0x7fff)
		min = -32767.0f;
	this->min = min;
	this->__rangeUpdate();
}

void ProgressBar::SetMax(f32 max) {
	if (max > 0x7fff)
		max = 32767.0f;
	this->max = max;
	this->__rangeUpdate();
}

void ProgressBar::__rangeUpdate() {
	if (this->hwnd)
		if (!SendMessage(this->hwnd, PBM_SETRANGE, NULL, MAKELPARAM((u16)this->min, (u16)this->max))) {
			std::cout << "Failed to set progress range! " << this->hwnd << std::endl;
			return;
		}
}

void ProgressBar::EnableMarqee() {
	if (this->hwnd) {
		SendMessage(this->hwnd, PBM_SETMARQUEE, TRUE, NULL);
		this->marq = true;
	}
}

void ProgressBar::DisableMarqee() {
	if (this->hwnd) {
		SendMessage(this->hwnd, PBM_SETMARQUEE, FALSE, NULL);
		this->marq = false;
	}
}

void ProgressBar::SetBarColor(Color c) {
	COLORREF c_ref = c.cref();

	if (this->hwnd) {
		this->__theme_disable();
		SendMessage(this->hwnd, PBM_SETBARCOLOR, 0, (LPARAM)c_ref);
	}
}

void ProgressBar::__theme_disable() {
	if (!this->hwnd)
		return;

	SetWindowTheme(this->hwnd, L"", L"");
	//SetWindowTheme(hwndList, L"Explorer", NULL);
}

void ProgressBar::__applyStyle(ProgressStyle style) {
	if (style.marqee)
		this->EnableMarqee();
	else if (this->marq)
		this->DisableMarqee();

	this->SetBarColor(style.barColor);
}