#pragma once
#include <iostream>
#include "util.hpp"

typedef void(*__CloseCallback)(i32);

class CloseService {
private:
	static std::vector<__CloseCallback> cc;
public:
	static void RegisterClose(__CloseCallback c);
	static void Close(const i32 code = 0);
};