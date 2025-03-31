#include "WinElement.hpp"

using namespace Win52;

WinFont WinElement::def_font = {};
HDC WinElement::globalDc = GetDC(NULL);
HFONT WinElement::def_font_handle = NULL;

void WinElement::LoadDC() {
	//free old hdc
	if (this->hdc)
		DeleteDC(this->hdc);

	//load dc from possible stores
	if (this->parent.hwnd)
		this->hdc = GetDC(this->parent.hwnd);
	else if (this->win_origin)
		this->hdc = this->win_origin->getHDC();
	else if (!this->hdc)
		this->hdc = GetDC(NULL);
	else {
		std::cout << "Error, failed to load WinElement device context!" << std::endl;
		this->hdc = NULL;
	}
}

void WinElement::SetDimensions(i32 x, i32 y, i32 w, i32 h) {
	this->pos = {
		.x = x,
		.y = y,
		.w = w,
		.h = h
	};

	if (this->pos.w < 0) this->pos.w = CW_USEDEFAULT;
	if (this->pos.h < 0) this->pos.h = CW_USEDEFAULT;

	if (this->parent.ty == gwit_Elem) {
		WinContainer* p = (WinContainer*)this->parent.p.ele;

		if (p) {
			const WinDimension pad = p->getPadding();

			this->pos.x += pad.x;
			this->pos.y += pad.y;
		}
	}
}

void WinElement::SetDimensions(WinDimension pos) {
	this->pos = pos;

	if (this->pos.w < 0) this->pos.w = CW_USEDEFAULT;
	if (this->pos.h < 0) this->pos.h = CW_USEDEFAULT;

	if (this->parent.ty == gwit_Elem) {
		WinContainer* p = (WinContainer*)this->parent.p.ele;

		if (p) {
			const WinDimension pad = p->getPadding();

			this->pos.x += pad.x;
			this->pos.y += pad.y;
		}
	}
}

WinElement::WinElement(WinType ty, Win52::Window* win, WinId id) : ty(ty) {
	this->win_origin = win;

	if (id.id.length() <= 0)
		return;

	this->id = id;
	this->hwnd = NULL;
	this->pos = {};

	this->parent = {
		.hwnd = win->hwnd,
		.ty = gwit_Win,
		.p = {
			.win = win
		}
	};

	this->LoadDC();
}

WinElement::WinElement(WinType ty, Win52::Window* win, WinId id, i32 x, i32 y, i32 w, i32 h) : ty(ty) {
	this->win_origin = win;

	if (id.id.length() <= 0) {
		return;
	}

	this->id = id;
	this->hwnd = NULL;

	this->parent = {
		.hwnd = win->hwnd,
		.ty = gwit_Win,
		.p = {
			.win = win
		}
	};

	//NOTE: must do this step after setting parent since it
	//adds padding values based on the value of parent
	this->SetDimensions(x, y, w, h);

	this->LoadDC();
}

WinElement::WinElement(WinType ty, Win52::Window* win, WinId id, WinDimension pos) : ty(ty) {
	this->win_origin = win;

	if (id.id.length() <= 0) {
		return;
	}

	this->id = id;
	this->hwnd = NULL;

	this->parent = {
		.hwnd = win->hwnd,
		.ty = gwit_Win,
		.p = {
			.win = win
		}
	};

	//NOTE: must do this step after setting parent since it
	//adds padding values based on the value of parent
	this->SetDimensions(pos);

	this->LoadDC();
}

WinId WinElement::getId() {
	return this->id;
}

WinElement::operator HWND() {
	return this->hwnd;
}

void WinElement::show() {
	if (this->hwnd)
		ShowWindow(this->hwnd, SW_SHOW);
}

void WinElement::hide() {
	if (this->hwnd)
		ShowWindow(this->hwnd, SW_HIDE);
}

void WinElement::setText(Str str) {
	this->text = str;
	if (this->hwnd)
		SetWindowText(this->hwnd, str);
}

Str WinElement::getText() {
	if (this->hwnd) {
		size_t t_len = GetWindowTextLength(this->hwnd);
		this->text = new wchar_t[t_len];
		GetWindowText(this->hwnd, this->text, t_len);
	}
	else
		this->text = "";

	return this->text;
}

void WinElement::setFont(Font f) {
	if (!this->hwnd || !this->hdc) return;

	this->font = WinFont(this->hdc, f);

	//TODO: add font handling system to prvent many calls to the font constructor
	HFONT f_handle;
	if (!(f_handle = this->font.getFontHandle())) {
		std::cout << "WinElement | Failed to create font!" << std::endl;
		return;
	}

	//set hwnd font
	SendMessage(this->hwnd, WM_SETFONT, (WPARAM) f_handle, TRUE);
}


WinElement::WinElement(WinType ty, Win52::WinContainer* e, WinId id) : ty(ty) {
	this->win_origin = e->win_origin;

	if (id.id.length() <= 0)
		return;

	this->id = id;
	this->hwnd = NULL;
	this->pos = {};

	this->parent = {
		.hwnd = e->hwnd,
		.ty = gwit_Elem,
		.p = {
			.ele = e
		}
	};

	this->LoadDC();
}

WinElement::WinElement(WinType ty, Win52::WinContainer* e, WinId id, i32 x, i32 y, i32 w, i32 h) : ty(ty) {
	this->win_origin = e->win_origin;

	if (id.id.length() <= 0) {
		return;
	}

	this->id = id;
	this->hwnd = NULL;

	this->parent = {
		.hwnd = e->hwnd,
		.ty = gwit_Elem,
		.p = {
			.ele = e
		}
	};

	this->SetDimensions(x, y, w, h);

	this->LoadDC();
}

WinElement::WinElement(WinType ty, Win52::WinContainer* e, WinId id, WinDimension pos) : ty(ty) {
	this->win_origin = e->win_origin;

	if (id.id.length() <= 0) {
		return;
	}

	this->id = id;
	this->hwnd = NULL;

	this->parent = {
		.hwnd = e->hwnd,
		.ty = gwit_Elem,
		.p = {
			.ele = e
		}
	};

	this->SetDimensions(pos);

	this->LoadDC();
}

HWND WinElement::getParentHWND() {
	if (this->parent.hwnd)
		return this->parent.hwnd;

	if (this->win_origin)
		return this->win_origin->hwnd;
}

void WinElement::EleGen() {
	//may add stuff here later but for now just gonna call the next internal step

	//compute some stuff for containers with padding
	this->ContainerStep(); //not really used but oh well maybe need thing sometime
	this->HWNDCreate();

	//set default fonts
	if (this->hwnd) {
		if (def_font_handle)
			SendMessage(this->hwnd, WM_SETFONT, (WPARAM)def_font_handle, TRUE);
	}
}

void WinElement::SetDefaultFont(Font f) {
	if (!globalDc)
		globalDc = GetDC(NULL);
	def_font = WinFont(globalDc, f);

	if (!(def_font_handle = def_font.getFontHandle())) {
		std::cout << "WinElement | Failed to convert deafult font!" << std::endl;
		return;
	}
}

//---------------------
//-Win Container Stuff-
//---------------------


WinContainer::WinContainer(WinType ty, Win52::Window* win, WinId id) : WinElement(ty, win, id) {}
WinContainer::WinContainer(WinType ty, Win52::Window* win, WinId id, i32 x, i32 y, i32 w, i32 h) : WinElement(ty, win, id, x, y, w, h) {}
WinContainer::WinContainer(WinType ty, Win52::Window* win, WinId id, WinDimension pos) : WinElement(ty, win, id, pos) {}

WinContainer::WinContainer(WinType ty, Win52::WinContainer* parent, WinId id) : WinElement(ty, parent, id) {}
WinContainer::WinContainer(WinType ty, Win52::WinContainer* parent, WinId id, i32 x, i32 y, i32 w, i32 h) : WinElement(ty, parent, id, x, y, w, h) {}
WinContainer::WinContainer(WinType ty, Win52::WinContainer* parent, WinId id, WinDimension pos) : WinElement(ty, parent, id, pos) {}

WinDimension WinContainer::getPadding() {
	return {
		.x = this->paddingLeft,
		.y = this->paddingTop,
		.w = 0,
		.h = 0
	};
}

void WinContainer::ContainerStep() {
	return;
}