#pragma once
#include <windows.h>
#include <iostream>

static LPWSTR StrToWide(std::string str) {
	const size_t len = str.length();
	if (len < 0)
		return nullptr;
	wchar_t* r = new wchar_t[len + 1], * cu = r;
	memset(r, 0, (len + 1) * sizeof(wchar_t));
	for (char c : str)
		*cu++ = (wchar_t)c;
	return (LPWSTR)r;
}

static size_t GetWideLen(const wchar_t* w_str) {
	if (!w_str) return 0;
	size_t sz = 0;
	while (*w_str++)
		sz++;
	return sz;
}

static std::string WideToStr(LPWSTR w_str) {
	if (!w_str)
		return "";
	std::string str;
	while (*w_str)
		str += *w_str++;
	return str;
}

static bool WideStrCmp(LPWSTR str1, LPWSTR str2) {
	if (!str1 || !str2) return false;
	while (*str1 && *str2)
		if (!*str1++ == *str2++)
			return false;
	return true;
}