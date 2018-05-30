#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#pragma comment(lib, "gwlibd.lib")
#else
#pragma comment(lib, "gwlib.lib")
#endif

#include "graphics.h"
#include "extgraph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

typedef struct WStruct *Widget;
typedef struct SStruct *Scroll;
typedef struct DStruct *Design;

typedef void(*MouseClickCall)(Widget w, int x, int y, int button, int event);
typedef void(*MouseMoveCall)(Widget w, int x, int y);
typedef void(*TimeCall)(Widget w, int timerID);
typedef void(*CharCall)(Widget w, char c);
typedef void(*KeyCall)(Widget w, int key, int event);
typedef void(*InputCall)(Widget w);

typedef void(*ScrollMouseClickCall)(Scroll s, int x, int y, int button, int event);
typedef void(*ScrollMouseMoveCall)(Scroll s, int x, int y);

enum WidgetType
{
	GW_BUTTON,
	GW_INPUT,
	GW_LABEL,
	GW_OUTPUT,
	GW_SLIDER,
	GW_LIST,
	GW_SPINBOX
};

enum WidgetStatus
{
	GW_DEFAULT,
	GW_ON,
	GW_SELECTED,
	GW_CLICKED,
	//particular for spinbox
	GW_ONUP,
	GW_ONDOWN,
	GW_CLICKEDUP,
	GW_CLICKEDDOWN,
	GW_SELECTEDUP,
	GW_SELECTEDDOWN
};

struct SStruct
{
	double x;
	double y;
	double height;
	
	enum WidgetStatus status;
	double sliderHeight;
	double sliderPos;
	double oy;
	int visible;
	ScrollMouseMoveCall mouseMove;
	ScrollMouseClickCall mouseClick;
	void(*show)(Scroll s);
	void(*hide)(Scroll s);
	void(*autoRecalculate)(Widget w);
	void(*toBottom)(Scroll s);
	Widget parent;
};

struct WStruct
//warning: should not directly change the private values
{
//public:
	//common members of widgets
	double x;
	double y;
	double width;
	double height;
	int value;
	void(*valueChangedEvent)(Widget w);
	void(*setRange)(Widget w, int a, int b);
	char *content;
	Design design;
	enum WidgetStatus status;
	MouseClickCall mouseClick;
	void(*show)(Widget w);
	void(*hide)(Widget w);
	void(*activateScroll)(Widget w);
	void(*update)(Widget w);

	//particular for input widget
	bool cursorVisible;
	int cursorPos;
	CharCall charInput;
	KeyCall keyPress;
	InputCall inputCall;

	//particular for label and output
	int size;

	//particular for output
	void(*append)(Widget w, char *s);

	//particular for slider and spinbox
	int range[2];

//private:
	//common members of widgets
	char *name;
	enum WidgetType type;
	bool visible;
	MouseMoveCall mouseMove;
	Scroll scroll;

	//particular for input widget
	TimeCall timer;

	//particular for output widget
	int lines;
	int displayLines;
	int curLine;
};

struct DStruct
{
	char colorOn[50];
	char colorClicked[50];
	char colorDefault[50];
	char colorButtonDefault[50];
	char colorFrame[50];
	char colorFrameClicked[50];
	char colorFrameOn[50];
	int frameThick;
	int frameThickClicked;
};

Widget newWidget(char *name, enum WidgetType type);
void registerWidget(Widget w);
void freeWidget(Widget w);
void destroyWidget(char *name);
void drawWidget(Widget w);
Widget findWidgetByName(char *name);
bool inWidget(Widget w, double rx, double ry);
void setWidgetPos(Widget w, double x, double y, double width, double height);

void widgetMouseEvent(int x, int y, int button, int event);
void buttonMouseClick(Widget w, int x, int y, int button, int event);
void widgetCharEvent(char c);
void widgetKeyEvent(int key, int event);
void update(void);