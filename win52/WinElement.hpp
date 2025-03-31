#pragma once
#include "util.hpp"
#include <Windows.h>
#include "Str.hpp"
#include "window.hpp"
#include "Font.hpp"


//Use get prop / set prop to set properties for a window
namespace Win52 {

enum WinType {
	WinType_Uknown,
	WinType_Container,
	WinType_Text,
	WinType_Button,
	WinType_TextInput,
	WinType_NumInput,
	WinType_GroupBox,
	WinType_Progress
};

struct WinId {
	Win52::Str id = "";
	Win52::Str operator=(Win52::Str id){
		this->id = id;
		return id;
	}
};

struct WinDimension {
	i32 x, y, w, h;
};

enum GenericWinInfo_Ty {
	gwit_Win,
	gwit_Elem
};

struct GenericWinInfo {
	HWND hwnd;
	GenericWinInfo_Ty ty = gwit_Win;
	union {
		Win52::Window* win;
		class WinElement* ele;
	} p;
};

class WinElement {
private:
	static WinFont def_font;
	static HDC globalDc;
	static HFONT def_font_handle;
protected:
	WinDimension pos;
	WinType ty = WinType_Uknown;
	WinId id;
	HWND hwnd;
	GenericWinInfo parent;
	Str text;
	WinFont font;
	HDC hdc;
	Window* win_origin = nullptr;

	void LoadDC();

	HWND getParentHWND();
	void EleGen();

	virtual void HWNDCreate() {
		this->hwnd = NULL;
	};

	virtual void ContainerStep() {
		//do nothing for winelement
	}
public:

	//
	WinElement(WinType ty, Win52::Window* win, WinId id);
	WinElement(WinType ty, Win52::Window* win, WinId id, i32 x, i32 y, i32 w, i32 h);
	WinElement(WinType ty, Win52::Window* win, WinId id, WinDimension pos);

	//
	WinElement(WinType ty, class WinContainer* parent, WinId id);
	WinElement(WinType ty, class WinContainer* parent, WinId id, i32 x, i32 y, i32 w, i32 h);
	WinElement(WinType ty, class WinContainer* parent, WinId id, WinDimension pos);

	WinId getId();
	operator HWND();

	void show();
	void hide();

	void setText(Str text);
	Str getText();

	void SetDimensions(i32 x, i32 y, i32 w, i32 h);
	void SetDimensions(WinDimension pos);

	//functions to add
	void setFont(Font f);
	void setTextColor();
	void setBgColor();
	//...

	static void SetDefaultFont(Font f);
};

//basically same thing as win element except can contain elements
//just prevents you from having a button store something since that
//can result in some messed up stuff
class WinContainer : public WinElement {
private:
	void ContainerStep() override; //special step in element creation used to compute the padding values properly before the hwnd is created
protected:
	i32 paddingTop = 20;
	i32 paddingLeft = 5;
public:
	WinContainer(WinType ty, Win52::Window* win, WinId id);
	WinContainer(WinType ty, Win52::Window* win, WinId id, i32 x, i32 y, i32 w, i32 h);
	WinContainer(WinType ty, Win52::Window* win, WinId id, WinDimension pos);

	WinContainer(WinType ty, Win52::WinContainer* parent, WinId id);
	WinContainer(WinType ty, Win52::WinContainer* parent, WinId id, i32 x, i32 y, i32 w, i32 h);
	WinContainer(WinType ty, Win52::WinContainer* parent, WinId id, WinDimension pos);

	WinDimension getPadding();
};

}