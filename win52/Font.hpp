#pragma once
#include "Str.hpp"
#include "util.hpp"
#include "window.hpp"

#define WIN52_FONT_DEFAULT_SZ 12 //default point size of a font
#define WIN32_FONT_NOWEIGHT 0x8000 //value used to specify that the weight param isn't used and bold is used instead
#define WIN32_FONT_DEFWEIGHT FW_NORMAL

namespace Win52 {
	enum FontWeight {
		FontWeight_Min = FW_DONTCARE,
		FontWeight_Auto = FW_DONTCARE,
		FontWeight_Thin = FW_THIN,
		FontWeight_UltraLight = 150,
		FontWeight_ExtraLight = FW_EXTRALIGHT,
		FontWeight_Light = FW_LIGHT,
		FontWeight_Normal = FW_NORMAL,
		FontWeight_Medium = FW_MEDIUM,
		FontWeight_SemiBold = FW_SEMIBOLD,
		FontWeight_Bold = FW_BOLD,
		FontWeight_ExtraBold = FW_EXTRABOLD,
		FontWeight_UltraBold = 850,
		FontWeight_Heavy = FW_HEAVY,
		FontWeight_Max = FW_HEAVY
	};

	struct FontStyle {
		bool italic = false;
		bool underline = false;
		bool bold = false;
		bool strike = false;
		size_t weight = WIN32_FONT_NOWEIGHT;
	};

	class Font {
	private:
		size_t pnt = WIN52_FONT_DEFAULT_SZ;
		Str font_name = "";
		FontStyle style;
	public:
		Font(Str font_name);
		Font(Str font_name, size_t pnt);
		Font(Str font_name, size_t pnt, FontStyle style);
		Font() {};
		friend class WinFont;
	};

	class WinFont {
	private:
		size_t pnt = WIN52_FONT_DEFAULT_SZ;
		Str font_name = "";
		static i32 _FntPoint_to_lUnit(HDC hdc, size_t pnt);
		HFONT font = NULL;
		HDC hdc = NULL;
	public:
		WinFont(HDC hdc, Str font_name);
		WinFont(HDC hdc, Str font_name, size_t pnt);
		WinFont(HDC hdc, Str font_name, size_t pnt, FontStyle style);
		WinFont(HDC hdc, Font f);
		WinFont() {};
		HFONT getFontHandle();
		Str getName();
		i32 getPntSize();
		i32 getPixSize();
	};
}