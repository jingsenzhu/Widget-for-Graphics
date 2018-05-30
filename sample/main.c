#include "widget.h"

void event1(Widget w, int x, int y, int button, int event)
{
	Widget input = findWidgetByName("4");
	buttonMouseClick(w, x, y, button, event);
	if (w->status == GW_SELECTED)
		input->show(input);
}

void vce(Widget w)
{
	Widget o = findWidgetByName("3");
	char tmp[30];
	_itoa(w->value, tmp, 10);
	o->append(o, tmp);
	if(o->scroll)
		o->scroll->toBottom(o->scroll);
	drawWidget(w);
	drawWidget(o);
}

void event2(Widget w, int x, int y, int button, int event)
{
	Widget input = findWidgetByName("4");
	buttonMouseClick(w, x, y, button, event);
	if (w->status == GW_SELECTED)
		input->hide(input);
}

void inputEvent(Widget w)
{
	Widget output = findWidgetByName("3");
	output->append(output, w->content);
	if (output->scroll)
	{
		output->scroll->toBottom(output->scroll);
	}
	drawWidget(output);
}


void Main()
{
	Widget w1, w2;

	InitGraphics();

	w1 = newWidget("Please Select", GW_LIST);
	w2 = newWidget("2", GW_SLIDER);

	setWidgetPos(w1, 1, 6, 2, 0.25);
	setWidgetPos(w2, 1, 3, 2, 1);

	strcpy(w2->content, "Show");
	w1->append(w1, "1");
	w1->append(w1, "2");
	w1->append(w1, "3");
	w1->append(w1, "4");
	w2->valueChangedEvent = vce;
	w1->show(w1);
	w2->show(w2);

	registerWidget(w1);
	registerWidget(w2);

	free(w1);
	free(w2);

	w2 = newWidget("3", GW_OUTPUT);
	setWidgetPos(w2, 5, 6, 3, 3);
	strcpy(w2->content, "");
	w2->show(w2);
	registerWidget(w2);
	free(w2);

	w1 = newWidget("4", GW_INPUT);
	setWidgetPos(w1, 5, 2.5, 3, 0.25);
	strcpy(w1->content, "");
	w1->inputCall = inputEvent;
	w1->show(w1);
	registerWidget(w1);
	free(w1);

	w1 = newWidget("5", GW_BUTTON);
	setWidgetPos(w1, 5, 2, 1, 0.25);
	strcpy(w1->content, "show");
	w1->mouseClick = event1;
	w1->show(w1);
	registerWidget(w1);
	free(w1);
	w1 = newWidget("6", GW_BUTTON);
	setWidgetPos(w1, 6.5, 2, 1, 0.25);
	strcpy(w1->content, "hide");
	w1->mouseClick = event2;
	w1->show(w1);
	registerWidget(w1);
	free(w1);
	w1 = newWidget("7", GW_SPINBOX);
	setWidgetPos(w1, 2, 2, 1, 0);
	w1->show(w1);
	registerWidget(w1);
	free(w1);
}