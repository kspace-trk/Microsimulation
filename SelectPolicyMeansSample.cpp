// SelectPolicyMeansSample.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
//
#include "Exp.h"

int main()
{
	Exp *exp;

	// �����̃^�l�ݒ�
	srand((unsigned int)time(NULL));

	exp = new Exp();
	exp->search();
	exp->pop->ind[0]->writeResult();
	delete exp;
}
