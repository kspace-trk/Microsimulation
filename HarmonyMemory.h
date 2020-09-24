#pragma once

#include "Harmony.h"

class HarmonyMemory
{
public:
	static Para *para;

	HarmonyMemory();
	~HarmonyMemory();

	void makeHarmony();

	int iteNum;
	Harmony **mem;

private:
	Harmony *newHarmony;
};
