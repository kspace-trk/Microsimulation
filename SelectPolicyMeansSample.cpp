// SelectPolicyMeansSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "Exp.h"

int main()
{
	Exp *exp;
	Population *pop;
	int n;
	double e = 0;//評価値
	long cpu_time;
	double sec;
	// 乱数のタネ設定
	srand((unsigned int)time(NULL));

	double geneAve[100];
	double ave = 0;

	printf("開始\n");

	exp = new Exp();
	// for (n = 0; n < 10; n++)
	// {
	exp->search();
	 //		ave += exp->pop->ind[0]->fitness;
	 //		printf("-----------------\n");
	//	 }
	 //ave /= n;
	printf("世代交代数：%d　個体群数：%d \n", ITERATION_NUM, POP_SIZE);
	printf("第%d世代：fitness=%f\n", exp->pop->iteNum, exp->pop->ind[0]->fitness);
	cpu_time = clock();
	sec = (double)cpu_time / CLOCKS_PER_SEC;
	e = sqrt(pow(exp->pop->ind[0]->fitness / 100, 2.0) + pow(sec / 70, 2.0));
	printf("処理時間: %f秒\n", sec);
	printf("評価値：%f\n", e);
	exp->pop->ind[0]->writeResult();
	delete exp;
}
