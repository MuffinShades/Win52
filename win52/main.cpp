#include <iostream>
#include "util.hpp"
#include "win52.hpp"

int main() {
	std::cout << "Banana" << std::endl;

	Win52::Window w = Win52::Window("Test", 0,0,750,750);

	return 0;
}