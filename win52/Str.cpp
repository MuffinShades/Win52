#include "Str.hpp"
#include "strutil.hpp"
#include "quickmem.hpp"
#include "util.hpp"

//if this class doesn't work then make sure to check all the functions to make sure theyre converting correctly

void Win52::Str::_cstr_ini(char *c_str, size_t len) {
	this->free();

	//inst stuff
	this->d_share_count = new size_t;
	*this->d_share_count = 0;

	//
	if (!c_str) return;

	//len stuff
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

void Win52::Str::_wstr_ini(wchar_t* w_str, size_t len) {
	this->free();

	//inst stuff
	this->d_share_count = new size_t;
	*this->d_share_count = 0;

	//len stuff
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

Win52::Str::operator wchar_t*() const {
	return this->w_str;
}

Win52::Str::operator char* () const {
	return this->c_str;
}

Win52::Str::operator std::string() const {
	if (!this->c_str) return "";
	return std::string(this->c_str);
}

Win52::Str Win52::Str::operator=(wchar_t* w_str) {
	this->_wstr_ini(w_str);
	return *this;
}

Win52::Str Win52::Str::operator=(char* c_str) {
	this->_cstr_ini(c_str);
	return *this;
}

Win52::Str Win52::Str::operator=(std::string str) {
	if (this->len = str.length() <= 0) return *this;
	const char* c_str = str.c_str();
	this->_cstr_ini(const_cast<char*>(c_str));
	return *this;
}

Win52::Str::Str(wchar_t* w_str) {
	this->_wstr_ini(w_str);
}

Win52::Str::Str(char* c_str) {
	this->_cstr_ini(c_str);
}

Win52::Str::Str(std::string str) {
	if (this->len = str.length() <= 0) return;
	const char* c_str = str.c_str();
	this->_cstr_ini(const_cast<char*>(c_str));
}

void Win52::Str::free() {
	if (this->free_prevent > 0) {
		this->free_prevent--;
		return;
	}

	//if (this->d_share_count)
		//std::cout << "Free: " << *this->d_share_count << " | " << this->d_share_count << " | " << this << std::endl;
	//else {
		//std::cout << "Null Inst: " << this << std::endl;
	//}

	//
	if (this->d_share_count && *this->d_share_count > 0) {
		//std::cout << "Share Dec: " << *this->d_share_count << std::endl;
		(*this->d_share_count) = (*this->d_share_count) - 1;
	}
	else {

		//ERROR something weird is happening here with the whole sharing pointers thing
		//conditions under which this occurs is unknown
		//likely referencing unallowed memory or something a long those lines somehwere else in the program
		
		
		//if (this->w_str)
			//delete[] this->w_str;

		//if (this->c_str)
			//delete[] this->c_str;

		//if (this->d_share_count)
			//delete this->d_share_count;
	}

	this->w_str = nullptr;
	this->c_str = nullptr;
	this->d_share_count = nullptr;
	this->len = 0;
}

Win52::Str::~Str() {
	this->free();
}

Win52::Str::operator const wchar_t*() const {
	return const_cast<const wchar_t*>(this->w_str);
}

Win52::Str::operator const char*() const {
	return const_cast<const char*>(this->c_str);
}

//

Win52::Str Win52::Str::operator=(const wchar_t* cw_str) {
	this->_wstr_ini(const_cast<wchar_t*>(cw_str));
	return *this;
}

Win52::Str Win52::Str::operator=(const char* cc_str) {
	this->_cstr_ini(const_cast<char*>(cc_str));
	return *this;
}

//

Win52::Str::Str(const wchar_t* cw_str) {
	this->_wstr_ini(const_cast<wchar_t*>(cw_str));
}

Win52::Str::Str(const char* cc_str) {
	this->_cstr_ini(const_cast<char*>(cc_str));
}

Win52::Str::Str() {
	this->len = 0;
	this->c_str = nullptr;
	this->w_str = nullptr;

	//
	this->d_share_count = new size_t;
	*this->d_share_count = 0;
}

void Win52::Str::prevent_free() {
	this->free_prevent++;
}

//like handshake type thing
Win52::Str Win52::Str::operator=(Win52::Str m_str) {
	Win52::Str* m_str_p = &m_str;

	//std::cout << "Str Cpy" << std::endl;

	this->free();

	memcpy(this, m_str_p, sizeof(Win52::Str));

	if (!this->d_share_count) {
		this->d_share_count = new size_t;
		m_str_p->d_share_count = this->d_share_count;
		(*this->d_share_count) = 1;
	}
	else
		(*this->d_share_count) = (*this->d_share_count) + 1;

	//std::cout << "Mem share count: " << *this->d_share_count << " | Count: " << this->d_share_count << " | This: " << this << " | That: " << m_str_p << std::endl;

	//normal constructor buisness
	m_str_p->prevent_free(); //account for free of m_str_p at the end of this function
	return *this;
}

//std::cout


size_t Win52::Str::length() {
	return this->len;
}