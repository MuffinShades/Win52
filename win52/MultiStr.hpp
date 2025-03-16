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

		void _cstr_ini();
		void _wstr_ini();
	public:
		operator wchar_t*() const;
		operator char*() const;
		operator std::string() const;

		operator LPCWSTR() const;
		operator PCWSTR() const;
		operator LPWSTR() const;
		operator PWSTR() const;

		operator PSTR() const;
		operator PCSTR() const;
		operator LPSTR() const;
		operator PSTR() const;

		_MultiStr operator=(wchar_t* w_str);
		_MultiStr operator=(char* c_str);
		_MultiStr operator=(std::string str);

		_MultiStr operator=(LPCWSTR cw_str);
		_MultiStr operator=(PCWSTR cw_str);
		_MultiStr operator=(LPWSTR w_str);
		_MultiStr operator=(PWSTR w_str);

		_MultiStr operator=(PSTR cc_str);
		_MultiStr operator=(PCSTR cc_str);
		_MultiStr operator=(PSTR c_str);
		_MultiStr operator=(LPSTR c_str);

		_MultiStr(wchar_t* w_str);
		_MultiStr(char* c_str);
		_MultiStr(std::string str);
		void free();

		std::string* __std_string_edit_instance_start();
		void __std_string_edit_instance_end();
	};
}