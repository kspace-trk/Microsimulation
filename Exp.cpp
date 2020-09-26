#include "Exp.h"

// コンストラクタ
Exp::Exp()
{
	// パラメータ設定
	harmonyMemory = NULL;
	para = new Para();
	Harmony::para = para;
	HarmonyMemory::para = para;
	Harmony::centerZoneNum = (para->centerZoneVID2 - para->centerZoneVID1 + 1) * (para->centerZoneHID2 - para->centerZoneHID1 + 1);
	Harmony::surroundingZoneNum = para->zoneVNum * para->zoneHNum - Harmony::centerZoneNum;
	Harmony::solutionSubLen = (int)(log((double)para->subsidyLevelNum) / log(2.0) + 1);
	Harmony::solutionLen = Harmony::centerZoneNum + Harmony::surroundingZoneNum + Harmony::solutionSubLen;
	Harmony::distanceMax = para->transTimeLimit / para->transTimeUnit;
	Harmony::transFitBase = (double)para->transCostUnit * para->transTimeUnit * para->receiveRatio * 0.73;
}

// デストラクタ
Exp::~Exp()
{
	if (harmonyMemory)
		delete harmonyMemory;
	delete para;
}

// 解探索
void Exp::search()
{
	harmonyMemory = new HarmonyMemory();
	while (harmonyMemory->iteNum < ITERATION_NUM)
	{
		harmonyMemory->makeHarmony();
		printf("%f mem[0]\n", harmonyMemory->mem[0]->fitness);
	}
}