#pragma once
#include <iostream>
#include <Windows.h>

/*

MultiStr.hpp

Class used for fast on-the-fly conversion between
all the string types and pointers.

Allows for easier use of every string type

*/

namespace Win52 {
	class _MultiStr {
	private:
		wchar_t* w_str;
		char* c_str;
		size_t len;

		void _cstr_ini(char* c_str, size_t len = 0);
		void _wstr_ini(wchar_t* w_str, size_t len = 0);
	public:
		operator wchar_t*() const;
		operator char*() const;
		operator std::string() const;

		operator const wchar_t*() const;
		operator const char*() const;

		_MultiStr operator=(wchar_t* w_str);
		_MultiStr operator=(char* c_str);
		_MultiStr operator=(std::string str);

		_MultiStr operator=(const wchar_t* cw_str);
		_MultiStr operator=(const char* cc_str);

		_MultiStr(wchar_t* w_str);
		_MultiStr(char* c_str);
		_MultiStr(std::string str);

		_MultiStr(const wchar_t* cw_str);
		_MultiStr(const char* cc_str);

		void free();

		std::string* __std_string_edit_instance_start();
		void __std_string_edit_instance_end();

		friend std::ostream& operator<<(std::ostream& __out_stream, const Win52::_MultiStr& __str) {
			if (__str.c_str)
				return __out_stream << __str.c_str;
			else
				return __out_stream << "";
		}
	};
}