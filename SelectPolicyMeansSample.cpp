// SelectPolicyMeansSample.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
//
#include "Exp.h"

int main()
{
	Exp *exp;
	Population *pop;

	long cpu_time;
	double sec;
	// �����̃^�l�ݒ�
	srand((unsigned int)time(NULL));



	exp = new Exp();

	exp->search();

	printf("�����㐔�F%d�@�̌Q���F%d \n", ITERATION_NUM, POP_SIZE);
	cpu_time = clock();
	sec = (double)cpu_time / CLOCKS_PER_SEC;
	printf("��������: %f�b\n", sec);
	exp->pop->ind[0]->writeResult();
	delete exp;
}
