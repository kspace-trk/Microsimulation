#pragma once

class Para;
#include "Para.h"

#define ITERATION_NUM 5 //世代交代数
#define POP_SIZE 40000	//個体群数
#define ELITE 1			// エリート保存戦略で残す個体の数
// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)
#define MUTATE_PROB 0.01 // 突然変異確率

class Individual
{
public:
	static Para *para;
	static int centerZoneNum;
	static int surroundingZoneNum;
	static int solutionLen;
	static int solutionSubLen;
	static int distanceMax;
	static double transFitBase;

	Individual();
	~Individual();

	void calcFit();
	void writeResult();
	void crossover(Individual *p1, Individual *p2); // 交叉による子にする
	void mutate();									// 突然変異を起こす
	void evaluate();								// 適応度を算出する
	int *solution;
	int **housePop;
	double **facilityPop;
	double subsidy;
	int moveNum;
	int facilityNum;
	double moveProb;
	double fitness;
};
