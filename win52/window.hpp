#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include "Str.hpp"

namespace Win52 {
class Region {
private:
	i32 _x, _y, _w, _h;
	i32 _l, _r, _t, _b;
public:
	Region();
	Region(i32 x, i32 y, i32 w, i32 h, bool useLtrb = false);

	i32 x() const { return this->_x; };
	i32 y() const { return this->_y; };
	i32 w() const { return this->_w; };
	i32 h() const { return this->_h; };

	i32 l() const { return this->_l; };
	i32 r() const { return this->_r; };
	i32 t() const { return this->_t; };
	i32 b() const { return this->_b; };
};

class WinPane {
public:
	//wins
	//TODO: maybe add rebar and footer win (may not actually be needed)
	HWND hwnd;
	HWND contentWin;

	//regions
	Region contentArea;
	Region rebarArea;
	Region footerArea;
};

class Window {
	private:
		bool running = false;
		HDC hdc = NULL;
		std::vector<WinPane> panes;
		size_t defPane = 0;
		HWND _hwnd = NULL;
	public:
		HWND hwnd() const { return this->_hwnd; }
		Window(Str title, int x, int y, int w, int h);
		bool Update();
		bool Running();
		HDC getHDC();

		//pane control functions
		void SetPane(size_t paneId);
		void NextPane();
		void PrevPane();
};
}