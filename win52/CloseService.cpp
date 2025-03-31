#include "CloseService.hpp"

std::vector<__CloseCallback> CloseService::cc;

void CloseService::RegisterClose(__CloseCallback c) {
	if (c)
		cc.push_back(c);
}

void CloseService::Close(const i32 code) {
	for (__CloseCallback c : cc) {
		if (c)
			c(code);
	}
}