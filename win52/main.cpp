#include <iostream>
#include "util.hpp"
#include "win52.hpp"
#include "MultiStr.hpp"
#include "strutil.hpp"

//WARNING: when using multi str it returns a *this which could result in multiple copies of the
//base object which in turn could result in the other copies accessing a nullptr once the data
//stored in the original copy is deleted!!!

int main() {
	std::cout << "Banana" << std::endl;

	//Win52::Window w = Win52::Window("Test", 0,0,750,750);

	//const wchar_t testStr[] = L"asdf";

	//std::cout << (int)wstr_len(testStr) << std::endl;

	Win52::_MultiStr testStr = L"asdf";

	std::cout << "Test Str: " << std::endl;
	std::cout << testStr << std::endl;

	return 0;
}