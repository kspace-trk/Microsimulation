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
	Harmony **nextMem;
	int select();			   // 親個体を選択する
	void evaluate();		   // 個体を評価する
	void sort(int lb, int ub); // 個体を良い順に並び替える
};
