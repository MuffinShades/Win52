#pragma once
#include "WinElement.hpp"

namespace Win52 {
	class Text : public WinElement {
	private:
		void HWNDCreate() override;
	public:
		Text(Win52::Window* win, WinId id, Str text, int x = -1, int y = -1, int w = -1, int h = -1);
		Text(WinContainer* win, WinId id, Str text, int x = -1, int y = -1, int w = -1, int h = -1);
	};
}