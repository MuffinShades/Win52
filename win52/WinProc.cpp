#include "WinProc.hpp"
#include "WinElement.hpp"

const HBRUSH __testBg = CreateSolidBrush(RGB(0, 0, 0));

LRESULT Win52::WinProc_Default(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (!hwnd) return false;

	WinContext* wCtx = decodeContext(hwnd, msg, wParam, lParam);

	//proc to use if no win context is found
	if (!wCtx) {
		switch (msg) {
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}

	//normal proc
	switch (msg) {
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}