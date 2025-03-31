#include "Font.hpp"

using namespace Win52;

i32 WinFont::_FntPoint_to_lUnit(HDC hdc, size_t pnt) {
	//if this function is failing it may be this if statement
	if (hdc)
		return -MulDiv(pnt, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	else
		return 0;
}

WinFont::WinFont(HDC hdc, Str font_name) {
	this->hdc = hdc;

	if (!this->hdc)
		this->hdc = GetDC(NULL);

	this->pnt = WIN52_FONT_DEFAULT_SZ;
	this->font_name = font_name;

	this->font = CreateFontA(
		_FntPoint_to_lUnit(hdc, WIN52_FONT_DEFAULT_SZ),
		0,
		0, 0,
		FontWeight_Normal,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		0,
		DEFAULT_PITCH,
		font_name
	);

	//font failed ;-;
	if (this->font == NULL) {
		this->hdc = NULL;
#ifdef WIN32_DEBUG
		std::cout << "Error failed to create font 1: " << font_name << std::endl;
#endif
		return;
	}
}

WinFont::WinFont(HDC hdc, Str font_name, size_t pnt) {
	this->hdc = hdc;
	this->pnt = pnt;
	this->font_name = font_name;
	
	this->font = CreateFontA(
		_FntPoint_to_lUnit(hdc, pnt),
		0,
		0, 0,
		FontWeight_Normal,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		0,
		DEFAULT_PITCH,
		font_name
	);

	//font failed ;-;
	if (this->font == NULL) {
		this->hdc = NULL;
#ifdef WIN32_DEBUG
		std::cout << "Error failed to create font 2: " << font_name << std::endl;
#endif
		return;
	}
}

WinFont::WinFont(HDC hdc, Str font_name, size_t pnt, FontStyle style) {
	this->hdc = hdc;

	const size_t weight = ((const size_t)style.weight == 0x8000) ?
		(FontWeight_Normal + style.bold * (FontWeight_Bold - FontWeight_Normal)) :
		min(style.weight, FontWeight_Max);

	this->pnt = pnt;
	this->font_name = font_name;

	this->font = CreateFontA(
		_FntPoint_to_lUnit(hdc, pnt),
		0,
		0, 0,
		weight,
		style.italic, style.underline, style.strike,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		0,
		DEFAULT_PITCH,
		font_name
	);

	//font failed ;-;
	if (this->font == NULL) {
		this->hdc = NULL;
#ifdef WIN32_DEBUG
		std::cout << "Error failed to create font 3: " << font_name << std::endl;
#endif
		return;
	}
}

WinFont::WinFont(HDC hdc, Font f) {
	this->hdc = hdc;

	const size_t weight = ((const size_t)f.style.weight == 0x8000) ?
		(FontWeight_Normal + f.style.bold * (FontWeight_Bold - FontWeight_Normal)) :
		min(f.style.weight, FontWeight_Max);

	this->pnt = f.pnt;
	this->font_name = f.font_name;

	this->font = CreateFontA(
		_FntPoint_to_lUnit(hdc, f.pnt),
		0,
		0, 0,
		weight,
		f.style.italic, f.style.underline, f.style.strike,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		0,
		DEFAULT_PITCH,
		this->font_name
	);

	//font failed ;-;
	if (this->font == NULL) {
		this->hdc = NULL;
#ifdef WIN32_DEBUG
		std::cout << "Error failed to create font 3: " << font_name << std::endl;
#endif
		return;
	}
}

HFONT WinFont::getFontHandle() {
	return this->font;
}

Str WinFont::getName() {
	return this->font_name;
}

Font::Font(Str font_name) {
	this->font_name = font_name;
	this->pnt = WIN52_FONT_DEFAULT_SZ;
	this->style = {};
}

Font::Font(Str font_name, size_t pnt) {
	this->font_name = font_name;
	this->pnt = pnt;
	this->style = {};
}

Font::Font(Str font_name, size_t pnt, FontStyle style) {
	this->font_name = font_name;
	this->pnt = pnt;
	this->style = style;
}

i32 WinFont::getPntSize() {
	return this->pnt;
}

//TODO: do some fancy calculations to get an actual pixel estimation value
i32 WinFont::getPixSize() {
	return this->pnt;
}