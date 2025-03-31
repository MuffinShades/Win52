#pragma once
#include "linked_map.hpp"
#include <Windows.h>

#define WIN52_REGISTER_HASH_BITS 15
#define WIN52_NAMESPACE

#ifdef WIN52_NAMESPACE
namespace Win52 {
#endif
struct __Win_Rgstr {
	std::string class_id;
	bool ex = false;
	WNDCLASSEX cls_ex;
	WNDCLASS cls;
	ATOM handle;
	bool good = false;
};

class WinRgstr {
private:
#ifdef WIN52_REGISTER_HASH_BITS
	static linked_map<__Win_Rgstr, WIN52_REGISTER_HASH_BITS> class_register;
#else
	static linked_map<__Win_Rgstr, 15> class_register;
#endif
public:
	static bool registerClassEx(std::string id, WNDCLASSEX cls);
	static bool registerClass(std::string id, WNDCLASS cls);
	static __Win_Rgstr getClass(std::string id);
	static bool registered(std::string id);
	static void ini();
	static void free(i32 _);
};
#ifdef WIN52_NAMESPACE
}
#endif