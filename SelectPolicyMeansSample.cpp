// SelectPolicyMeansSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "Exp.h"

int main()
{
	Exp *exp;
	Population *pop;

	long cpu_time;
	double sec;
	// 乱数のタネ設定
	srand((unsigned int)time(NULL));



	exp = new Exp();

	exp->search();

	printf("世代交代数：%d　個体群数：%d \n", ITERATION_NUM, POP_SIZE);
	cpu_time = clock();
	sec = (double)cpu_time / CLOCKS_PER_SEC;
	printf("処理時間: %f秒\n", sec);
	exp->pop->ind[0]->writeResult();
	delete exp;
}
