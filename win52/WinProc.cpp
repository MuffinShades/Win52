#include "WinProc.hpp"

const HBRUSH __testBg = CreateSolidBrush(RGB(0, 0, 0));

LRESULT Win52::WinProc_Default(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (!hwnd) return false;

	switch (msg) {
		
	case WM_CTLCOLORBTN: {
		HDC btnHdc = (HDC)wParam;
		SetBkMode(btnHdc, TRANSPARENT);
		return (LONG)__testBg;
	}

	case WM_CTLCOLORDLG: {
		HDC dlcHdc = (HDC)wParam;
		SetBkMode(dlcHdc, TRANSPARENT);
		return (LONG)__testBg;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}