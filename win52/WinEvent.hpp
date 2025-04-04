#pragma once

#include "util.hpp"

namespace Win52 {
constexpr enum WinEventType {
	WinEvent_MouseDown,
	WinEvent_MouseUp,
	WinEvent_MouseMove,
	WinEvent_KeyDown,
	WinEvent_KeyUp,
	WinEvent_Click,
	WinEvent_KeyCombo,
	WinEvent_DoubleClick,
	WinEvent_KeyInput,
	WinEvent_Resize
};

class WinEvent {

};
}