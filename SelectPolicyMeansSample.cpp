// SelectPolicyMeansSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "Exp.h"

int main()
{
	Exp *exp;
	Population *pop;
	int n;
	long cpu_time;
	double sec;
	// 乱数のタネ設定
	srand((unsigned int)time(NULL));

	double geneAve[100];
	double ave = 0;

	exp = new Exp();
	// for (n = 0; n < 50; n++)
	// {
	exp->search();
	// 	ave += exp->pop->ind[0]->fitness;
	// 	printf("第%d世代：fitness=%f\n", exp->pop->iteNum, exp->pop->ind[0]->fitness);
	// 	printf("-----------------\n");
	// }
	// ave /= n;
	printf("世代交代数：%d　個体群数：%d　\n", ITERATION_NUM, POP_SIZE);
	cpu_time = clock();
	sec = (double)cpu_time / CLOCKS_PER_SEC;
	printf("処理時間: %f秒\n", sec);
	exp->pop->ind[0]->writeResult();
	delete exp;
}
