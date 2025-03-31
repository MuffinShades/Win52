#include "WinRgstr.hpp"
#include "CloseService.hpp"

#ifdef WIN52_NAMESPACE
using namespace Win52;
#endif
#define WIN52_DEBUG

linked_map<__Win_Rgstr, WIN52_REGISTER_HASH_BITS> WinRgstr::class_register;

void WinRgstr::ini() {
	CloseService::RegisterClose(&WinRgstr::free);
}

void WinRgstr::free(i32 _) {
	class_register.free();
}

bool WinRgstr::registerClassEx(std::string id, WNDCLASSEX cls) {
	if (id.length() <= 0) {
#if defined(WIN52_DEBUG) || defined(WIN52_PRINT_ERRS)
		std::cout << "Class Register Ex Failed! Invalid Id!" << std::endl;
#endif
		return false;
	}

	__Win_Rgstr rgstr = {
		.class_id = id,
		.ex = true,
		.cls_ex = cls
	};

	if (!(rgstr.handle = RegisterClassEx(&cls))) {
#if defined(WIN52_DEBUG) || defined(WIN52_PRINT_ERRS)
		std::cout << "Class Register Ex Failed! Unknown!" << std::endl;
#endif
		return false;
	}

	rgstr.good = true;

	//add register so it can't be taken by any other entry
	class_register.insert(id, (const __Win_Rgstr) rgstr);
}

bool WinRgstr::registerClass(std::string id, WNDCLASS cls) {
	if (id.length() <= 0) {
#if defined(WIN52_DEBUG) || defined(WIN52_PRINT_ERRS)
		std::cout << "Class Register Failed! Invalid Id!" << std::endl;
#endif
		return false;
	}

	__Win_Rgstr rgstr = {
		.class_id = id,
		.ex = true,
		.cls = cls
	};

	if (!(rgstr.handle = RegisterClass(&cls))) {
#if defined(WIN52_DEBUG) || defined(WIN52_PRINT_ERRS)
		std::cout << "Class Register Failed! Unknown!" << std::endl;
#endif
		return false;
	}

	rgstr.good = true;

	//add register so it can't be taken by any other entry
	class_register.insert(id, (const __Win_Rgstr)rgstr);
}

bool WinRgstr::registered(std::string id) {
	if (id.length() <= 0) return false;
	
	//search the linked map
	return class_register.exists(id);
}