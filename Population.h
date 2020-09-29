#pragma once

#include "Individual.h"

class Population
{
public:
	static Para *para;

	Population();
	~Population();

	void alternate();

	int iteNum;
	Individual **ind;

private:
	Individual *newHarmony;
	Individual **nextInd;
	int select();			   // eŒÂ‘Ì‚ğ‘I‘ğ‚·‚é
	void evaluate();		   // ŒÂ‘Ì‚ğ•]‰¿‚·‚é
	void sort(int lb, int ub); // ŒÂ‘Ì‚ğ—Ç‚¢‡‚É•À‚Ñ‘Ö‚¦‚é
};
