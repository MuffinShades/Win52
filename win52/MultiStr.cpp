#include "MultiStr.hpp"
#include "strutil.hpp"
#include "quickmem.hpp"
#include "util.hpp"

//if this class doesn't work then make sure to check all the functions to make sure theyre converting correctly

void Win52::_MultiStr::_cstr_ini(char *c_str, size_t len) {
	this->free();
	if (!c_str) return;
	if (this->len = len <= 0)
		this->len = strlen(c_str);
	if (this->len <= 0) return;

	//set w_str
	if (!(this->w_str = new wchar_t[this->len+1])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::_cstr_ini,char*,size_t]!" << std::endl;
		this->free();
		return;
	}

	ZeroMem(this->w_str, this->len + 1);
	forrange(this->len)
		this->w_str[i] = (wchar_t)*(c_str + i);

	//set c_str
	if (!(this->c_str = new char[this->len+1])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::_cstr_ini,char*,size_t]!" << std::endl;
		this->free();
		return;
	}

	ZeroMem(this->c_str, this->len + 1);
	in_memcpy(this->c_str, c_str, this->len);
}

void Win52::_MultiStr::_wstr_ini(wchar_t* w_str, size_t len) {
	this->free();
	if (this->len = len <= 0)
		this->len = wstr_len(w_str);
	if (this->len <= 0) return;

	//set w_str
	if (!(this->w_str = new wchar_t[this->len+1])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::_wstr_ini,wchar_t*,len]!" << std::endl;
		this->free();
		return;
	}

	ZeroMem(this->w_str, this->len + 1);
	in_memcpy(this->w_str, w_str, this->len);

	//set c_str
	if (!(this->c_str = new char[this->len+1])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::_wstr_ini,wchar_t*,len]!" << std::endl;
		this->free();
		return;
	}

	ZeroMem(this->c_str, this->len + 1);
	forrange(this->len)
		this->c_str[i] = (char)(*(w_str + i) & 0xff);
}

Win52::_MultiStr::operator wchar_t*() const {
	return this->w_str;
}

Win52::_MultiStr::operator char* () const {
	return this->c_str;
}

Win52::_MultiStr::operator std::string() const {
	if (!this->c_str) return "";
	return std::string(this->c_str);
}

Win52::_MultiStr Win52::_MultiStr::operator=(wchar_t* w_str) {
	this->_wstr_ini(w_str);
	return *this;
}

Win52::_MultiStr Win52::_MultiStr::operator=(char* c_str) {
	this->_cstr_ini(c_str);
	return *this;
}

Win52::_MultiStr Win52::_MultiStr::operator=(std::string str) {
	if (this->len = str.length() <= 0) return *this;
	const char* c_str = str.c_str();
	this->_cstr_ini(const_cast<char*>(c_str));
	return *this;
}

Win52::_MultiStr::_MultiStr(wchar_t* w_str) {
	this->_wstr_ini(w_str);
}

Win52::_MultiStr::_MultiStr(char* c_str) {
	this->_cstr_ini(c_str);
}

Win52::_MultiStr::_MultiStr(std::string str) {
	if (this->len = str.length() <= 0) return;
	const char* c_str = str.c_str();
	this->_cstr_ini(const_cast<char*>(c_str));
}

void Win52::_MultiStr::free() {
	if (this->w_str)
		delete[] this->w_str;

	if (this->c_str)
		delete[] this->c_str;

	this->w_str = nullptr;
	this->c_str = nullptr;
	this->len = 0;
}

Win52::_MultiStr::operator const wchar_t*() const {
	return const_cast<const wchar_t*>(this->w_str);
}

Win52::_MultiStr::operator const char*() const {
	return const_cast<const char*>(this->c_str);
}

//

Win52::_MultiStr Win52::_MultiStr::operator=(const wchar_t* cw_str) {
	this->_wstr_ini(const_cast<wchar_t*>(cw_str));
	return *this;
}

Win52::_MultiStr Win52::_MultiStr::operator=(const char* cc_str) {
	this->_cstr_ini(const_cast<char*>(cc_str));
	return *this;
}

//

Win52::_MultiStr::_MultiStr(const wchar_t* cw_str) {
	this->_wstr_ini(const_cast<wchar_t*>(cw_str));
}

Win52::_MultiStr::_MultiStr(const char* cc_str) {
	this->_cstr_ini(const_cast<char*>(cc_str));
}

//std::cout