#pragma once

#include "Population.h"

class Exp
{
public:
	Exp();
	~Exp();
	void search();

	Population *pop;
	Para *para;
};
