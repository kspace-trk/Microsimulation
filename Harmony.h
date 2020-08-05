#pragma once

class Para;
#include "Para.h"

#define ITERATION_NUM	100000
#define HM_SIZE			100
#define R_CONSIDER		0.85
#define R_ADJUST		0.35

class Harmony
{
public:
	static Para* para;
	static int centerZoneNum;
	static int surroundingZoneNum;
	static int solutionLen;
	static int solutionSubLen;
	static int distanceMax;
	static double transFitBase;

	Harmony();
	~Harmony();

	void renewal();
	void calcFit();
	void writeResult();

	int* solution;
	int** housePop;
	double** facilityPop;
	double subsidy;
	int moveNum;
	int facilityNum;
	double moveProb;
	double fitness;
};
