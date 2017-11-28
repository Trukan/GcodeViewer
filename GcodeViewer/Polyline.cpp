#include "Polyline.h"

using namespace GData;
using namespace System;
using namespace System::Collections;
//конструктор Polyline, инициализирует массивы координат по соответствующей длине
GData::Polyline::Polyline(int _n)
{
	Polyline::x = gcnew Collections::Generic::List<float>(_n);
	Polyline::y = gcnew Collections::Generic::List<float>(_n);
	Polyline::z = gcnew Collections::Generic::List<float>(_n);
}

bool GData::Polyline::update()
{
	return false;
}
/*
//берем последнюю точку с заданной линии как начальную для новой
//основные состояния так же копируются
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
//оператор деления, делит координаты на конкретное число, 
//Возвращает измененный экземпляр переданого параметра
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