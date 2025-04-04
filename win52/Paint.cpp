#include "Paint.hpp"
#include "util.hpp"
#include "WinElement.hpp"
#include <CommCtrl.h>

using namespace Win52;

PaintContext::PaintContext(class WinContext* ctx, bool ab) {
	if (ctx) {
		this->win = ctx->hwnd;
		if (!this->win) {
			ctx->hdc = NULL;
			ctx->hwnd = NULL;
			return;
		}

		if (ab)
			this->Begin();
	}
}

void PaintContext::Begin() {
	if (!this->win)
		return;

	this->hdc = BeginPaint(this->win, &this->ps);

	if (!this->hdc) {
		std::cout << "Failed to being painting!" << std::endl;
		return;
	}

	this->b = true;
}

void PaintContext::End() {
	if (!this->win || !this->b)
		return;
	EndPaint(this->win, &this->ps);
	if (this->hdc) DeleteDC(this->hdc);
	this->hdc = NULL;
}

#define __WIN52_PAINTCALL_VERIFY(src) if (!this->b || !this->win || !this->hdc) { \
									if (!this->b) std::cout << (#src " fail! Maybe you forgot to call begin().") << std::endl; \
									return; \
								 }

void PaintContext::FillRect(i32 x, i32 y, i32 w, i32 h) {
	__WIN52_PAINTCALL_VERIFY(FillRect)

	if (!this->brush)
		this->brush = CreateSolidBrush(0x000000);

	RECT r = {
		.left = x,
		.top = y,
		.right = x + w,
		.bottom = y + h
	};

	if (!::FillRect(this->hdc, &r, this->brush)) {
		std::cout << "Error, failed to fill rect!" << std::endl;
	}
}

void PaintContext::LineRect(i32 x, i32 y, i32 w, i32 h) {
	__WIN52_PAINTCALL_VERIFY(LineRect)
	
	if (!this->brush)
		this->brush = CreateSolidBrush(0x000000);
}

void PaintContext::DrawLine(i32 x1, i32 y1, i32 x2, i32 y2) {
	__WIN52_PAINTCALL_VERIFY(DrawLine)

	//
}

void PaintContext::DrawRoundRect(i32 r, i32 x, i32 y, i32 w, i32 h) {
	__WIN52_PAINTCALL_VERIFY(DrawRoundRect)

	//
}

void PaintContext::DrawInvertedRect(i32 x, i32 y, i32 w, i32 h) {
	__WIN52_PAINTCALL_VERIFY(DrawInvertedRect)
}

void PaintContext::RenderText(Str str, i32 x, i32 y) {
	__WIN52_PAINTCALL_VERIFY(RenderText)
}

void PaintContext::SetLineThickness(u32 thickness) {

}