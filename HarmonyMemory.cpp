#include "HarmonyMemory.h"

Para *HarmonyMemory::para = NULL;

// コンストラクタ
HarmonyMemory::HarmonyMemory()
{
	int i;
	iteNum = 1;

	mem = new Harmony *[HM_SIZE];	  //mem[100]宣言
	nextMem = new Harmony *[HM_SIZE]; //nextMem[100]宣言
	for (i = 0; i < HM_SIZE; i++)
	{
		mem[i] = new Harmony();
		nextMem[i] = new Harmony();
		mem[i]->calcFit();
		nextMem[i]->calcFit();
	}
	evaluate(); // 適応度を算出する
}

// デストラクタ
HarmonyMemory::~HarmonyMemory()
{
	int i;

	for (i = 0; i < HM_SIZE; i++)
	{
		delete mem[i];
		delete nextMem[i];
	}
	delete[] mem;
	delete[] nextMem;
}
// すべての個体を評価して，適応度順に並び替える
void HarmonyMemory::evaluate()
{
	int i;

	for (i = 0; i < HM_SIZE; i++)
	{
		mem[i]->calcFit();
	}
	sort(0, HM_SIZE - 1);
}
// mem[lb]〜mem[ub]をクイックソートで並び替える
// lb: 並び替えの対象要素の添え字の下限
// ub: 並び替えの対象要素の添え字の上限
void HarmonyMemory::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	Harmony *tmp;

	if (lb < ub)
	{
		k = (lb + ub) / 2;
		pivot = mem[k]->fitness;
		i = lb;
		j = ub;
		do
		{
			while (mem[i]->fitness < pivot)
			{
				i++;
			}
			while (mem[j]->fitness > pivot)
			{
				j--;
			}
			if (i <= j)
			{
				tmp = mem[i];
				mem[i] = mem[j];
				mem[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

// 新しいハーモニーを生成
void HarmonyMemory::makeHarmony()
{
	int i, j, p1, p2;
	Harmony **tmp;
	iteNum++;

	// ルーレット選択のための処理
	/*
   denom = 0.0;
   for(i = 0; i < POP_SIZE; i++) {
      trFit[i] = (mem[POP_SIZE - 1]->fitness - mem[i]->fitness)
                 / (mem[POP_SIZE - 1]->fitness - mem[0]->fitness);
      denom += trFit[i];
   }
   */

	// エリート保存戦略で子個体を作る
	for (i = 0; i < ELITE; i++)
	{
		for (j = 0; j < Harmony::solutionLen; j++)
		{
			nextMem[i]->solution[j] = mem[i]->solution[j];
		}
	}

	// 親を選択し交叉する
	for (; i < HM_SIZE; i++)
	{
		p1 = select();
		p2 = select();
		nextMem[i]->crossover(mem[p1], mem[p2]);
	}

	// 突然変異を起こす
	for (i = 1; i < HM_SIZE; i++)
	{
		nextMem[i]->mutate();
	}

	// 次世代を現世代に変更する
	tmp = mem;
	mem = nextMem;
	nextMem = tmp; //memとnextMemでいれかえ

	// 評価する
	evaluate();
}
// 順位に基づくランキング選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
int HarmonyMemory::select()
{
	int num, denom, r;

	denom = HM_SIZE * (HM_SIZE + 1) / 2; //50万
	r = ((rand() << 16) + (rand() << 1) + (rand() % 2)) % denom + 1;
	for (num = HM_SIZE; 0 < num; num--)
	{
		if (r <= num)
		{
			break;
		}
		r -= num;
	}
	return HM_SIZE - num;
}