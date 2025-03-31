#include <iostream>
#include "util.hpp"
#include "win52.hpp"
#include "Str.hpp"
#include "strutil.hpp"
#include "button.hpp"
#include "Font.hpp"
#include "Text.hpp"
#include "groupBox.hpp"
#include "textInput.hpp"
#include "progressBar.hpp"
#include "Color.hpp"

//WARNING: when using multi str it returns a *this which could result in multiple copies of the
//base object which in turn could result in the other copies accessing a nullptr once the data
//stored in the original copy is deleted!!!

//git wont push cause of the visual studio stuff

//TODO: add delete DC to the things that need deleting

//TODO: rethink the whole Str class smart memory management
//
// all of the deletes are just not there so there ARE MEMORY
// LEAKS. Create a better system maybe using std::shared_ptr
// for the c_str and w_str pointers since the current solution
// leads to double deleting of pointers meaning your not 
// accounting for a random deconstructor
//
// it may be wise to create some sort of sub class that has
// functionality like a smart ptr instead of having each class
// that does this kind of behaviour do it itself

//TODO: create a separate style struct for each element if they
// have customization and include as a constructor
// also add more constructors that can do cool things

//WARNING: don't include CommCtrl.h in any headers or else everything
// will all the sudden become an error, learned this one the hard way ;-;

int main() {
	std::cout << "Banana" << std::endl;

	Win52::Font defFont = Win52::Font("Seigoe UI", 10, {
		.weight = Win52::FontWeight_Normal
	});

	Win52::WinElement::SetDefaultFont(defFont);

	Win52::Window w = Win52::Window("Test", 0,0,750,750);

	Win52::GroupBox gBox = Win52::GroupBox(&w, { "container1" }, "Basic Controls", 20, 20, 300, 300);

	Win52::Button b = Win52::Button((Win52::WinContainer*)  &gBox, {"button1"}, "Asdf", 0, 0, 100, 100);

	b.setFont(defFont);

	Win52::Text t = Win52::Text((Win52::WinContainer*) &gBox, { "text1" }, "Static", 0, 100, 100, 25);

	Win52::TextInput textInput = Win52::TextInput((Win52::WinContainer*)&gBox, { "textEdit1" }, 0, 125, 100, 25);
	textInput.SetPlaceHolder("Text Edit");

	Win52::ProgressBar pBar = Win52::ProgressBar(
		&w,
		{ "progress1" },
		{
			.vertical = false,
			.barColor = Win52::Color(255,0,0),
			.marqee = false

		}, 5, 400, 100, 35);
		pBar.SetProgressPercent(0.5f);

	//const wchar_t testStr[] = L"asdf";

	//std::cout << (int)wstr_len(testStr) << std::endl;

	Win52::Str testStr = L"asdf";

	std::cout << "Test Str: " << std::endl;
	std::cout << testStr << std::endl;

	do {
		w.Update();
	} while (w.Running());

	return 0;
}