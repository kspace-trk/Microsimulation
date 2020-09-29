#include "Exp.h"

// コンストラクタ
Exp::Exp()
{
	// パラメータ設定
	pop = NULL;
	para = new Para();
	Individual::para = para;
	Population::para = para;
	Individual::centerZoneNum = (para->centerZoneVID2 - para->centerZoneVID1 + 1) * (para->centerZoneHID2 - para->centerZoneHID1 + 1);
	Individual::surroundingZoneNum = para->zoneVNum * para->zoneHNum - Individual::centerZoneNum;
	Individual::solutionSubLen = (int)(log((double)para->subsidyLevelNum) / log(2.0) + 1);
	Individual::solutionLen = Individual::centerZoneNum + Individual::surroundingZoneNum + Individual::solutionSubLen;
	Individual::distanceMax = para->transTimeLimit / para->transTimeUnit;
	Individual::transFitBase = (double)para->transCostUnit * para->transTimeUnit * para->receiveRatio * 0.73;
}

// デストラクタ
Exp::~Exp()
{
	if (pop)
		delete pop;
	delete para;
}

// 解探索
void Exp::search()
{
	pop = new Population();
	while (pop->iteNum < ITERATION_NUM)
	{
		pop->alternate();
		printf("第%d世代：fitness=%f\n", pop->iteNum, pop->ind[0]->fitness);
	}
}