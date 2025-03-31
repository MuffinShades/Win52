#include "win52.hpp"
#include <CommCtrl.h>

void Win52::Ini() {
	WinRgstr::ini();

	//load common controls
	const INITCOMMONCONTROLSEX com_ini = {
		.dwSize = sizeof(INITCOMMONCONTROLSEX),
		.dwICC = ICC_WIN95_CLASSES | 
				 ICC_STANDARD_CLASSES | 
				 ICC_LINK_CLASS | 
				 ICC_INTERNET_CLASSES |
				 ICC_PAGESCROLLER_CLASS |
				 ICC_DATE_CLASSES | 
			     ICC_COOL_CLASSES |
				 ICC_NATIVEFNTCTL_CLASS |
				 ICC_USEREX_CLASSES
	};

	InitCommonControlsEx(&com_ini);
}