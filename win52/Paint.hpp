#pragma once
#include "util.hpp"
#include "Str.hpp"
#include "Color.hpp"

namespace Win52 {
	class PaintContext {
	private:
		HWND win;
		HDC hdc;
		PAINTSTRUCT ps;
		bool b = false;
		HBRUSH brush = NULL;
	public:
		PaintContext(class WinContext* ctx = nullptr, bool autoBegin = true);
		void Begin();
		void End();
		void FillRect(i32 x, i32 y, i32 w, i32 h);
		void LineRect(i32 x, i32 y, i32 w, i32 h);
		void DrawLine(i32 x1, i32 y1, i32 x2, i32 y2);
		void DrawRoundRect(i32 r, i32 x, i32 y, i32 w, i32 h);
		void DrawInvertedRect(i32 x, i32 y, i32 w, i32 h);
		void RenderText(Str str, i32 x, i32 y);
		void SetLineThickness(u32 thickness);
		void SetDrawColor(Color c);
		void SetDrawColorGradient(Gradient g);
	};
}