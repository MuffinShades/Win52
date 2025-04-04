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
	class Str {
	private:
		wchar_t* w_str = nullptr;
		char* c_str = nullptr;
		size_t len = 0;

		void _cstr_ini(char* c_str, size_t len = 0);
		void _wstr_ini(wchar_t* w_str, size_t len = 0);

		size_t* d_share_count = nullptr;
		size_t free_prevent = 0;

		void free();
		void prevent_free(); //used in constructors to prevent certain issue
	public:
		operator wchar_t* () const;
		operator char* () const;
		operator std::string() const;

		operator const wchar_t* () const;
		operator const char* () const;

		Str operator=(wchar_t* w_str);
		Str operator=(char* c_str);
		Str operator=(std::string str);

		Str operator=(const wchar_t* cw_str);
		Str operator=(const char* cc_str);
		Str operator=(Str m_str);

		Str();
		Str(wchar_t* w_str);
		Str(char* c_str);
		Str(std::string str);

		Str(const wchar_t* cw_str);
		Str(const char* cc_str);
		Str(Str* m_str);

		std::string* __std_string_edit_instance_start();
		void __std_string_edit_instance_end();

		size_t length();

		~Str();

		friend std::ostream& operator<<(std::ostream& __out_stream, const Win52::Str& __str) {
			if (__str.c_str)
				return __out_stream << __str.c_str;
			else
				return __out_stream << "";
		}
	};
};