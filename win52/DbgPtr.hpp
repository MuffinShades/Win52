#pragma once

/**
 *
 * DbgPtr.hpp
 * 
 * Pointer debug library written by muffinshades
 * 
 * allows for easy debugging of pointers
 * 
 */

/*template<class Ty> class DbgPtr {
private:
	Ty* ptr = nullptr;
	size_t sz = 0;
	size_t origin_off = 0;
	bool free = false;
public:
	DbgPtr operator+(const size_t off) {
		if (off + this->origin_off >= sz) {
			std::cout << "DbgPtr error! Trying to reference out of bounds memory!!!" << std::endl;
			return nullptr;
		}
		else {
			return {
				.ptr = this->ptr,
				.sz = this->sz,
				.origin_off = off + this->origin_off
			};
		}
	}

	operator Ty* () {
		return this->ptr + this->origin_off;
	}

	Ty operator*() {

	}

	void operator delete(void* p) {
		DbgPtr
		delete[] p;
	}
};*/