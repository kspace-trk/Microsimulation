#include "Individual.h"

Para *Individual::para = NULL;
int Individual::centerZoneNum = -1;
int Individual::surroundingZoneNum = -1;
int Individual::solutionLen = -1;
int Individual::solutionSubLen = -1;
int Individual::distanceMax = 0;
double Individual::transFitBase = 0.0;

// コンストラクタ
Individual::Individual()
{
	int i, j;
	double r;

	solution = new int[solutionLen];			//solutionの配列数宣言
	housePop = new int *[para->zoneVNum];		//housePopの配列数宣言
	facilityPop = new double *[para->zoneVNum]; //facilityPopの配列数の宣言
	for (i = 0; i < solutionLen; i++)
		solution[i] = -1; //中に全部-1を入れる

	for (i = 0; i < para->zoneVNum; i++)
	{
		housePop[i] = new int[para->zoneHNum];		 //housePop配列を2次元配列にしてる
		facilityPop[i] = new double[para->zoneHNum]; //facilityPop配列を2次元配列にしてる
		for (j = 0; j < para->zoneHNum; j++)		 //9回回る
		{
			r = (double)rand() / RAND_MAX; //0~1までの少数型の乱数
			if (r > 0.1)
				solution[i * para->zoneHNum + j] = 0; //90%で0を代入
			else
				solution[i * para->zoneHNum + j] = 1; //10%で1を代入
			housePop[i][j] = para->initialZonePopNum; //housePop[0~9][0~9]の全部に20(初期ゾーン人口)を代入
			facilityPop[i][j] = 0.0;				  //facilityPop[0~9][0~9]の全部に0.0を代入
		}
	}
	for (i = 0; i < solutionSubLen; i++)
		solution[solutionLen - solutionSubLen + i] = rand() % 2; //solution[82~86]に 0or1
	subsidy = 0.0;
	moveNum = 0;
	facilityNum = 0;
	moveProb = 0.0;
	fitness = 0.0;
}

// デストラクタ
Individual::~Individual()
{
	for (int i = 0; i < para->zoneVNum; i++)
	{
		delete[] housePop[i];
		delete[] facilityPop[i];
	}
	delete[] solution;
	delete[] housePop;
	delete[] facilityPop;
}
// p1とp2から一点交叉で作った子にする
// p1: 親個体1
// p2: 親個体2
void Individual::crossover(Individual *p1, Individual *p2)
{
	int point, i;

	point = rand() % (solutionLen - 1);
	for (i = 0; i <= point; i++)
	{
		solution[i] = p1->solution[i];
	}
	for (; i < solutionLen; i++)
	{
		solution[i] = p2->solution[i];
	}
}
// 突然変異を起こす
void Individual::mutate()
{
	int i;

	for (i = 0; i < solutionLen; i++)
	{
		if (RAND_01 < MUTATE_PROB)
		{
			solution[i] = 1 - solution[i];
		}
	}
}

// 評価
void Individual::calcFit()
{
	int i, j, k, x, y, neighbour, fromv, fromh, to, tov, toh;
	double oneDayPop;

	// 施設数の算出，facilityPopとhousePopの初期化
	facilityNum = 0;
	for (i = 0; i < para->zoneVNum; i++)
	{
		for (j = 0; j < para->zoneHNum; j++)
		{
			facilityPop[i][j] = 0.0;
			facilityNum += solution[i * para->zoneHNum + j];
			housePop[i][j] = para->initialZonePopNum;
		}
	}

	// 補助金の算出
	subsidy = 0.0;
	for (i = 0; i < solutionSubLen; i++)
		subsidy += pow(2, i) * solution[solutionLen - solutionSubLen + i];
	if (para->subsidyLevelNum < subsidy)
		subsidy = para->subsidyLevelNum;
	subsidy = subsidy / (double)para->subsidyLevelNum * para->subsidyMax;

	// 移転率の算出
	moveProb = 1 / (1 + exp(-0.25 * subsidy + 10));

	// 居住者数の算出(マイクロシミュレーション)
	moveNum = 0;
	for (fromv = 0; fromv < para->centerZoneVID1; fromv++)
	{
		for (fromh = 0; fromh < para->zoneHNum; fromh++)
		{
			for (i = 0; i < para->initialZonePopNum; i++)
			{
				if ((double)rand() / (double)RAND_MAX < moveProb)
				{
					housePop[fromv][fromh]--;
					to = rand() % centerZoneNum;
					toh = to % (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneHID1;
					tov = to / (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneVID1;
					housePop[tov][toh]++;
					moveNum++;
				}
			}
		}
	}
	for (; fromv <= para->centerZoneVID2; fromv++)
	{
		for (fromh = 0; fromh < para->centerZoneHID1; fromh++)
		{
			for (i = 0; i < para->initialZonePopNum; i++)
			{
				if ((double)rand() / (double)RAND_MAX < moveProb)
				{
					housePop[fromv][fromh]--;
					to = rand() % centerZoneNum;
					toh = to % (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneHID1;
					tov = to / (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneVID1;
					housePop[tov][toh]++;
					moveNum++;
				}
			}
		}
		for (fromh = para->centerZoneHID2 + 1; fromh < para->zoneHNum; fromh++)
		{
			for (i = 0; i < para->initialZonePopNum; i++)
			{
				if ((double)rand() / (double)RAND_MAX < moveProb)
				{
					housePop[fromv][fromh]--;
					to = rand() % centerZoneNum;
					toh = to % (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneHID1;
					tov = to / (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneVID1;
					housePop[tov][toh]++;
					moveNum++;
				}
			}
		}
	}
	for (; fromv < para->zoneVNum; fromv++)
	{
		for (fromh = 0; fromh < para->zoneHNum; fromh++)
		{
			for (i = 0; i < para->initialZonePopNum; i++)
			{
				if ((double)rand() / (double)RAND_MAX < moveProb)
				{
					housePop[fromv][fromh]--;
					to = rand() % centerZoneNum;
					toh = to % (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneHID1;
					tov = to / (para->centerZoneHID2 - para->centerZoneHID1 + 1) + para->centerZoneVID1;
					housePop[tov][toh]++;
					moveNum++;
				}
			}
		}
	}

	// 介護福祉施設新設・維持管理費用＋移転補助費用
	fitness = (double)para->runningCost * (double)facilityNum + subsidy * moveNum;

	// 移送サービス費用
	for (y = 0; y < para->zoneVNum; y++)
	{
		for (x = 0; x < para->zoneHNum; x++)
		{
			if (housePop[y][x])
			{
				if (solution[y * para->zoneVNum + x])
				{
					oneDayPop = housePop[y][x] * para->receiveRatio;
					facilityPop[y][x] += oneDayPop;
					if (facilityPop[y][x] > para->facilityCapacity)
					{
						fitness = DBL_MAX;
						return;
					}
					else
					{
						fitness += (double)para->transCostUnit * para->transTimeUnit * oneDayPop * 0.365;
					}
				}
				else
				{
					neighbour = 0;
					for (i = 1; i <= distanceMax; i++)
					{
						for (j = y - i, k = x; j < y; j++, k++)
							if ((0 <= j) && (k < para->zoneHNum) && solution[j * para->zoneHNum + k])
								neighbour++;
						for (; j < y + i; j++, k--)
							if ((j < para->zoneVNum) && (k < para->zoneHNum) && solution[j * para->zoneHNum + k])
								neighbour++;
						for (; j > y; j--, k--)
							if ((j < para->zoneVNum) && (0 <= k) && solution[j * para->zoneHNum + k])
								neighbour++;
						for (; j > y - i; j--, k++)
							if ((0 <= j) && (0 <= k) && solution[j * para->zoneHNum + k])
								neighbour++;
						if (neighbour)
						{
							oneDayPop = housePop[y][x] * para->receiveRatio / neighbour;
							for (j = y - i, k = x; j < y; j++, k++)
							{
								if ((0 <= j) && (k < para->zoneHNum) && solution[j * para->zoneHNum + k])
								{
									facilityPop[j][k] += oneDayPop;
									if (facilityPop[j][k] > para->facilityCapacity)
									{
										fitness = DBL_MAX;
										return;
									}
								}
							}
							for (; j < y + i; j++, k--)
							{
								if ((j < para->zoneVNum) && (k < para->zoneHNum) && solution[j * para->zoneHNum + k])
								{
									facilityPop[j][k] += oneDayPop;
									if (facilityPop[j][k] > para->facilityCapacity)
									{
										fitness = DBL_MAX;
										return;
									}
								}
							}
							for (; j > y; j--, k--)
							{
								if ((j < para->zoneVNum) && (0 <= k) && solution[j * para->zoneHNum + k])
								{
									facilityPop[j][k] += oneDayPop;
									if (facilityPop[j][k] > para->facilityCapacity)
									{
										fitness = DBL_MAX;
										return;
									}
								}
							}
							for (; j > y - i; j--, k++)
							{
								if ((0 <= j) && (0 <= k) && solution[j * para->zoneHNum + k])
								{
									facilityPop[j][k] += oneDayPop;
									if (facilityPop[j][k] > para->facilityCapacity)
									{
										fitness = DBL_MAX;
										return;
									}
								}
							}
							fitness += (double)i * housePop[y][x] * transFitBase;
							break;
						}
					}
					if (!neighbour)
					{
						fitness = DBL_MAX;
						return;
					}
				}
			}
		}
	}
}

// 結果書込み
void Individual::writeResult()
{
	int i, j;
	FILE *resultFP;

	// ファイルオープン
	if ((resultFP = fopen("result.csv", "w")) == NULL)
	{
		printf("Cannot open result.txt for output.\n");
		exit(1);
	}

	// 書込み
	fprintf(resultFP, "%f\n", subsidy);
	for (j = 0; j < para->zoneVNum; j++)
	{
		for (i = 0; i < para->zoneHNum; i++)
			fprintf(resultFP, "%d,", solution[j * para->zoneHNum + i]);
		fprintf(resultFP, "\n");
	}

	// ファイルクローズ
	fclose(resultFP);
}