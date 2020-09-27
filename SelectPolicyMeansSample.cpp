// SelectPolicyMeansSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "Exp.h"

int main()
{
	Exp *exp;

	// 乱数のタネ設定
	srand((unsigned int)time(NULL));

	exp = new Exp();
	exp->search();
	exp->pop->ind[0]->writeResult();
	delete exp;
}
