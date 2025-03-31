#pragma once
#include "WinElement.hpp"

namespace Win52 {
	class GroupBox : public WinContainer {
	private:
		void HWNDCreate() override;
		Str group_label = "";
	public:
		GroupBox(Win52::Window* win, WinId id, Str text, int x = -1, int y = -1, int w = -1, int h = -1);
	};
}