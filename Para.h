#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

class Para
{
public:
	Para();
	~Para();

	int zoneHNum;		   // 横方向ゾーン数
	int zoneVNum;		   // 縦方向ゾーン数
	int centerZoneHID1;	   // 都心ゾーン横方向開始ID
	int centerZoneHID2;	   // 都心ゾーン横方向終了ID
	int centerZoneVID1;	   // 都心ゾーン縦方向開始ID
	int centerZoneVID2;	   // 都心ゾーン縦方向終了ID
	int initialZonePopNum; // 初期ゾーン人口(人)
	int transTimeUnit;	   // 隣接ゾーンへの移動時間(分)
	int transTimeLimit;	   // 移送時間上限(分)
	int facilityCapacity;  // 1施設の受入人数上限(人)
	int runningCost;	   // 施設の新設費＋10年間の維持管理費(万円)
	int subsidyMax;		   // 1人あたりの移転補助金の上限値(万円)
	int transCostUnit;	   // 1人1分あたりの移送サービス費(円)
	int subsidyLevelNum;   // 移転補助金の段階数（20のときは1/20刻み）
	double receiveRatio;   // 介護福祉サービス受給率
};
