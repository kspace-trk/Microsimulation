#pragma once

#include "HarmonyMemory.h"

class Exp
{
public:
	Exp();
	~Exp();
	void search();

	HarmonyMemory *harmonyMemory;
	Para *para;
};
