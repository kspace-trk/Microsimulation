// SelectPolicyMeansSample.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
//
#include "Exp.h"

int main()
{
	Exp *exp;
	Population *pop;
	int n;
	double e = 0;//�]���l
	long cpu_time;
	double sec;
	// �����̃^�l�ݒ�
	srand((unsigned int)time(NULL));

	double geneAve[100];
	double ave = 0;

	printf("�J�n\n");

	exp = new Exp();
	// for (n = 0; n < 10; n++)
	// {
	exp->search();
	 //		ave += exp->pop->ind[0]->fitness;
	 //		printf("-----------------\n");
	//	 }
	 //ave /= n;
	printf("�����㐔�F%d�@�̌Q���F%d \n", ITERATION_NUM, POP_SIZE);
	printf("��%d����Ffitness=%f\n", exp->pop->iteNum, exp->pop->ind[0]->fitness);
	cpu_time = clock();
	sec = (double)cpu_time / CLOCKS_PER_SEC;
	e = sqrt(pow(exp->pop->ind[0]->fitness / 100, 2.0) + pow(sec / 70, 2.0));
	printf("��������: %f�b\n", sec);
	printf("�]���l�F%f\n", e);
	exp->pop->ind[0]->writeResult();
	delete exp;
}
