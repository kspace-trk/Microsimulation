// SelectPolicyMeansSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "Exp.h"

int main()
{
	printf("aa");
	Exp *exp;

	// 乱数のタネ設定
	srand((unsigned int)time(NULL));

	exp = new Exp();
	exp->search();
	exp->harmonyMemory->mem[0]->writeResult();
	delete exp;
}
