#pragma once
#include "WinElement.hpp"

namespace Win52 {
	class Button : public WinElement {
	private:
		void HWNDCreate() override;
	public:
		Button(Win52::Window* win, WinId id, Str text, int x = -1, int y = -1, int w = -1, int h = -1);
		Button(Win52::WinContainer* wContain, WinId id, Str text, int x = -1, int y = -1, int w = -1, int h = -1);
	};
}