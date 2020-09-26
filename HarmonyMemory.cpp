#include "HarmonyMemory.h"

Para *HarmonyMemory::para = NULL;

// コンストラクタ
HarmonyMemory::HarmonyMemory()
{
	int i, best, worst;
	Harmony *tmp;
	iteNum = 1;
	best = 0;
	worst = 0;
	mem = new Harmony *[HM_SIZE]; //HM_SIZE = 100
	for (i = 0; i < HM_SIZE; i++)
	{
		mem[i] = new Harmony();
		mem[i]->calcFit();
		while (mem[i]->fitness == DBL_MAX)
		{
			mem[i]->renewal();
			mem[i]->calcFit();
		}
		if (mem[best]->fitness > mem[i]->fitness)
			best = i;
		if (mem[worst]->fitness < mem[i]->fitness)
			worst = i;
	}
	if (best != 0)
	{
		tmp = mem[0];
		mem[0] = mem[best];
		mem[best] = tmp;
	}
	if (worst == 0)
		worst = best;
	if (worst != HM_SIZE - 1)
	{
		tmp = mem[HM_SIZE - 1];
		mem[HM_SIZE - 1] = mem[worst];
		mem[worst] = tmp;
	}

	newHarmony = new Harmony();
}

// デストラクタ
HarmonyMemory::~HarmonyMemory()
{
	for (int i = 0; i < HM_SIZE; i++)
		delete mem[i];
	delete[] mem;
	delete newHarmony;
}

// 新しいハーモニーを生成
void HarmonyMemory::makeHarmony()
{
	int i, k, worst;
	double r;
	Harmony *tmp;

	iteNum++;

	// 新解候補を生成
	for (i = 0; i < Harmony::solutionLen; i++)
	{
		if (rand() < R_CONSIDER * RAND_MAX)
		{
			k = rand() % HM_SIZE; //k = 0~99
			if (rand() < R_ADJUST * RAND_MAX)
				newHarmony->solution[i] = (mem[k]->solution[i] + 1) % 2; //35%(R_ADJUST * 100)の確率でif文にかかる
			else
				newHarmony->solution[i] = mem[k]->solution[i];
		}
		else
		{
			if (i < Harmony::solutionLen - Harmony::solutionSubLen)
			{
				r = (double)rand() / RAND_MAX;
				if (r > 0.1)
					newHarmony->solution[i] = 0;
				else
					newHarmony->solution[i] = 1;
			}
			else
			{
				newHarmony->solution[i] = rand() % 2;
			}
		}
	}

	// 新解候補を評価
	newHarmony->calcFit();

	// 最悪解候補よりよかったら置き換える
	if (mem[HM_SIZE - 1]->fitness > newHarmony->fitness)
	{
		worst = 1;
		for (i = 2; i < HM_SIZE - 1; i++)
		{
			if (mem[worst]->fitness < mem[i]->fitness)
				worst = i;
		}
		tmp = mem[HM_SIZE - 1];
		if (mem[0]->fitness > newHarmony->fitness)
		{ // 最良解候補より良い
			mem[HM_SIZE - 1] = mem[worst];
			mem[worst] = mem[0];
			mem[0] = newHarmony;
		}
		else if (mem[worst]->fitness < newHarmony->fitness)
		{ // 第2最悪解候補より悪い
			mem[HM_SIZE - 1] = newHarmony;
		}
		else
		{ // 最良でも最悪でもない
			mem[HM_SIZE - 1] = mem[worst];
			mem[worst] = newHarmony;
		}
		newHarmony = tmp;
	}
	//printf("%f\n", newHarmony->fitness);
}
