#pragma once

#include "Individual.h"

class Population
{
public:
	static Para *para;

	Population();
	~Population();

	void makeHarmony();

	int iteNum;
	Individual **mem;

private:
	Individual *newHarmony;
	Individual **nextMem;
	int select();			   // 親個体を選択する
	void evaluate();		   // 個体を評価する
	void sort(int lb, int ub); // 個体を良い順に並び替える
};
