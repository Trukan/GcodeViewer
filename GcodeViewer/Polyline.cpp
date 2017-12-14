#include "Polyline.h"

using namespace GData;
using namespace System;
using namespace System::Collections;
//конструктор Polyline, инициализирует массивы координат по соответствующей длине
GData::Polyline::Polyline(int _n)
{
	n = 0;
	Polyline::x = gcnew Collections::Generic::List<float>(_n);
	Polyline::y = gcnew Collections::Generic::List<float>(_n);
	Polyline::z = gcnew Collections::Generic::List<float>(_n);
}

bool GData::Polyline::update()
{
	return false;
}

//вычисл€ет толщину снимаемого за оборот шпиндел€ сло€, отражает валидность в цвете,
//в виде чисел red, green, blue
void GData::Polyline::stickToColor()
{
	float sr = (float)this->speedrate;
	float stick = this->feed / 8000;
	if (this->feed > Polyline::feedLimit) this->red=100;
	if (stick < Polyline::stickLimit) {
		if (stick*2 < Polyline::stickLimit) {
			this->blue = 255;
			this->green = 0;
		}
		else {
			this->blue = 0;
			this->green = 255;
		}	
	//	float t = 2*stick / stickLimit;
	//	this->blue = (int)(2 - t) * 255 + (int)(t - 0.001)*(int)((2 - t) * 255);
	//	this->green = (int)(t - 0.001) * 255 + (int)(2-t)*(int)(t * 255);
	}
	else {
		this->blue = 0;
		this->green = 100;
		this->red += 155;
	}
}
/*
//берем последнюю точку с заданной линии как начальную дл€ новой
//основные состо€ни€ так же копируютс€
bool GData::Polyline::setLastPointAsFirst(Polyline^ pl)
{
	if (pl->x->Count>0) {
		this->x->Insert(0, pl->x[pl->x->Count - 1]);
		this->y->Insert(0, pl->y[pl->y->Count - 1]);
		this->z->Insert(0, pl->z[pl->z->Count - 1]);
		this->mstate = pl->mstate;
		this->gstate = pl->gstate;
		this->speedrate = pl->speedrate;

		return true;
	}
	Console::WriteLine("plUpdateFalse");
	return false;
}
*/
//оператор делени€, делит координаты на конкретное число, 
//¬озвращает измененный экземпл€р переданого параметра
Polyline ^ GData::Polyline::operator/(Polyline ^ p, float d)
{
	for (int i = 0; i < p->n; i++)
	{
		p->x[i] = p->x[i] / d;
		p->y[i] = p->y[i] / d;
		p->z[i] = p->z[i] / d;
	}
	return p;
}

void GData::Polyline::setColor(Polyline^p, int r, int g, int b)
{
	p->red = r;
	p->green = g;
	p->blue = b;
}
