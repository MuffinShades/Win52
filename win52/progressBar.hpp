#pragma once
#include "WinElement.hpp"
#include "Color.hpp"

//TODO: add vertical scroll bars
//TODO: make sure the ranges can be negative in the documentation 
// since if they aren't we need to used u16's instead of floats
// 
// ok so we need to use u16 just looked it up
//TODO: consider adding return values to report errors

namespace Win52 {
	struct ProgressStyle {
		bool vertical = false;
		Color barColor;
		bool marqee = false;
	};

	class ProgressBar : public WinElement {
	private:
		void HWNDCreate() override;
		f32 p = 0.0f, max = 100.0f, min = 0.0f;
		bool marq = false, vert = false;
		void __rangeUpdate();
		void __applyStyle(ProgressStyle style);
		void __theme_disable();
	public:
		ProgressBar(Win52::Window* win, WinId id, i32 x = -1, i32 y = -1, i32 w = -1, i32 h = -1);
		ProgressBar(Win52::WinContainer* wContain, WinId id, i32 x = -1, i32 y = -1, i32 w = -1, i32 h = -1);
		ProgressBar(Win52::Window* win, WinId id, ProgressStyle style, i32 x = -1, i32 y = -1, i32 w = -1, i32 h = -1);
		ProgressBar(Win52::WinContainer* wContain, WinId id, ProgressStyle style, i32 x = -1, i32 y = -1, i32 w = -1, i32 h = -1);
		void SetProgressPercent(f32 p);
		void SetProgress(f32 v);
		void SetRange(f32 min, f32 max);
		void SetMin(f32 min);
		void SetMax(f32 max);
		void SetBarColor(Color c);
		void EnableMarqee();
		void DisableMarqee();
	};
}