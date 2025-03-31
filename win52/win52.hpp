#pragma once
#include "window.hpp"
#include "WinRgstr.hpp"
#include "CloseService.hpp"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace Win52 {

//all the ini calls
	static void Ini();

static void Close() {
	CloseService::Close(0); //close with zero since idk what to do with this rn
}

}