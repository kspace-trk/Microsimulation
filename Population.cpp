#include "Population.h"

Para *Population::para = NULL;

// コンストラクタ
Population::Population()
{
	int i;
	iteNum = 1;

	ind = new Individual *[POP_SIZE];	  //ind[100]宣言
	nextInd = new Individual *[POP_SIZE]; //nextInd[100]宣言
	for (i = 0; i < POP_SIZE; i++)
	{
		ind[i] = new Individual();
		nextInd[i] = new Individual();
		ind[i]->calcFit();
		nextInd[i]->calcFit();
	}
	evaluate(); // 適応度を算出する
}

// デストラクタ
Population::~Population()
{
	int i;

	for (i = 0; i < POP_SIZE; i++)
	{
		delete ind[i];
		delete nextInd[i];
	}
	delete[] ind;
	delete[] nextInd;
}
// すべての個体を評価して，適応度順に並び替える
void Population::evaluate()
{
	int i;

	for (i = 0; i < POP_SIZE; i++)
	{
		ind[i]->calcFit();
	}
	sort(0, POP_SIZE - 1);
}
// ind[lb]〜ind[ub]をクイックソートで並び替える
// lb: 並び替えの対象要素の添え字の下限
// ub: 並び替えの対象要素の添え字の上限
void Population::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	Individual *tmp;

	if (lb < ub)
	{
		k = (lb + ub) / 2;
		pivot = ind[k]->fitness;
		i = lb;
		j = ub;
		do
		{
			while (ind[i]->fitness < pivot)
			{
				i++;
			}
			while (ind[j]->fitness > pivot)
			{
				j--;
			}
			if (i <= j)
			{
				tmp = ind[i];
				ind[i] = ind[j];
				ind[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

// 世代交代
void Population::alternate()
{
	int i, j, p1, p2;
	Individual **tmp;
	iteNum++;

	// エリート保存戦略で子個体を作る
	for (i = 0; i < ELITE; i++)
	{
		for (j = 0; j < Individual::solutionLen; j++)
		{
			nextInd[i]->solution[j] = ind[i]->solution[j];
		}
	}

	// 親を選択し交叉する
	for (; i < POP_SIZE; i++)
	{
		p1 = select();
		p2 = select();
		nextInd[i]->crossover(ind[p1], ind[p2]);
	}

	// 突然変異を起こす
	for (i = 1; i < POP_SIZE; i++)
	{
		nextInd[i]->mutate();
	}

	// 次世代を現世代に変更する
	tmp = ind;
	ind = nextInd;
	nextInd = tmp; //memとnextMemでいれかえ

	// 評価する
	evaluate();
}
// 順位に基づくランキング選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
int Population::select()
{
	int num, denom, r;

	denom = POP_SIZE * (POP_SIZE + 1) / 2; //50万
	r = ((rand() << 16) + (rand() << 1) + (rand() % 2)) % denom + 1;
	for (num = POP_SIZE; 0 < num; num--)
	{
		if (r <= num)
		{
			break;
		}
		r -= num;
	}
	return POP_SIZE - num;
}