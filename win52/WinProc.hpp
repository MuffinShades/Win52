#pragma once
#include <windows.h>
#include <iostream>
#include "util.hpp"

namespace Win52 {
	LRESULT WinProc_Default(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};