#include "groupBox.hpp"

/*

obj_class = L"Button";
style = WS_CHILD | WS_VISIBLE | BS_GROUPBOX;

*/

#define WIN52_GBOX_DEF_PADDING_LEFT 5 
#define WIN52_GBOX_DEF_PADDING_ADD_TOP 5

using namespace Win52;

GroupBox::GroupBox(Win52::Window* win, WinId id, Str text, int x, int y, int w, int h) : WinContainer(WinType_GroupBox, win, id, x, y, w, h) {
	this->group_label = text;

	//compute some padding values
	this->paddingLeft = WIN52_GBOX_DEF_PADDING_LEFT;
	this->paddingTop = this->font.getPixSize() + WIN52_GBOX_DEF_PADDING_ADD_TOP;

	this->EleGen();
}

void GroupBox::HWNDCreate() {
	HWND p_win = this->getParentHWND();

	this->hwnd = CreateWindowExW(
		NULL,
		L"Button",
		this->group_label,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
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