#pragma once
#include "WinElement.hpp"

namespace Win52 {
	class TextInput : public WinElement {
	private:
		void HWNDCreate() override;
	public:
		TextInput(Win52::Window* win, WinId id, int x = -1, int y = -1, int w = -1, int h = -1);
		TextInput(Win52::WinContainer* wContain, WinId id, int x = -1, int y = -1, int w = -1, int h = -1);
		void SetPlaceHolder(Str placeholder);
	};
}