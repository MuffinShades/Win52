#pragma once

#include <iostream>

static const size_t wstr_len(const wchar_t* w_str) {
	if (!w_str) return 0;

	const wchar_t* p = w_str;
	size_t len = 0;

	while ((uint32_t)*p++ != 0)
		len++;

	return len;
};

static const size_t cstr_len(const char* c_str) {
	if (!c_str) return 0;

	const char* p = c_str;
	size_t len = 0;

	while (*p++ != 0)
		len++;

	return len;
};