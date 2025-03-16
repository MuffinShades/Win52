#include "MultiStr.hpp"
#include "strutil.hpp"
#include "quickmem.hpp"
#include "util.hpp"

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
	this->free();
	this->len = wstr_len(w_str);
	
	if (this->len <= 0) return;

	//set w_str
	if (!(this->w_str = new wchar_t[this->len])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::operator=(wchar_t* w_str)]!" << std::endl;
		this->free();
		return;
	}

	in_memcpy(this->w_str, w_str, this->len);

	//set c_str
	if (!(this->c_str = new char[this->len])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::operator=(wchar_t* w_str)]!" << std::endl;
		this->free();
		return;
	}
	
	forrange(this->len)
		this->c_str[i] = (char)(*(w_str + i) & 0xff);
}

Win52::_MultiStr Win52::_MultiStr::operator=(char* c_str) {
	this->free();
	this->len = strlen(c_str);

	if (this->len <= 0) return;

	//set w_str
	if (!(this->w_str = new wchar_t[this->len])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::_MultiStr(char* c_str)]!" << std::endl;
		this->free();
		return;
	}

	forrange(this->len)
		this->w_str[i] = (wchar_t)*(c_str + i);

	//set c_str
	if (!(this->c_str = new char[this->len])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::_MultiStr(char* c_str)]!" << std::endl;
		this->free();
		return;
	}

	in_memcpy(this->c_str, c_str, this->len);
}

Win52::_MultiStr Win52::_MultiStr::operator=(std::string str) {
	this->free();
}

Win52::_MultiStr::_MultiStr(wchar_t* w_str) {
	this->free();
	this->len = wstr_len(w_str);
	
	if (this->len <= 0) return;

	//set w_str
	if (!(this->w_str = new wchar_t[this->len])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::operator=(wchar_t* w_str)]!" << std::endl;
		this->free();
		return;
	}

	in_memcpy(this->w_str, w_str, this->len);

	//set c_str
	if (!(this->c_str = new char[this->len])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::operator=(wchar_t* w_str)]!" << std::endl;
		this->free();
		return;
	}
	
	forrange(this->len)
		this->c_str[i] = (char)(*(w_str + i) & 0xff);
}

Win52::_MultiStr::_MultiStr(char* c_str) {
	this->free();
	this->len = strlen(c_str);

	if (this->len <= 0) return;

	//set w_str
	if (!(this->w_str = new wchar_t[this->len])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::_MultiStr(char* c_str)]!" << std::endl;
		this->free();
		return;
	}

	forrange(this->len)
		this->w_str[i] = (wchar_t)*(c_str + i);

	//set c_str
	if (!(this->c_str = new char[this->len])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::_MultiStr(char* c_str)]!" << std::endl;
		this->free();
		return;
	}

	in_memcpy(this->c_str, c_str, this->len);
}

Win52::_MultiStr::_MultiStr(std::string str) {
	this->free();
	if (this->len = str.length() <= 0) return;
	const char* c_str = str.c_str();

	//set c_str
	if (!(this->c_str = new char[this->len])) {
		std::cout << "Failed to alloc c_str! [Win52::_MultiStr::_MultiStr(char* c_str)]!" << std::endl;
		this->free();
		return;
	}

	in_memcpy(this->c_str, c_str, this->len);

	//set w_str
	if (!(this->w_str = new wchar_t[this->len])) {
		std::cout << "Failed to alloc w_str! [Win52::_MultiStr::_MultiStr(char* c_str)]!" << std::endl;
		this->free();
		return;
	}

	forrange(this->len)
		this->w_str[i] = (wchar_t)*(c_str + i);
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