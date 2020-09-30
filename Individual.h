#pragma once

class Para;
#include "Para.h"

#define ITERATION_NUM 100 //�����㐔
#define POP_SIZE 200	//�̌Q��
#define ELITE 10			// �G���[�g�ۑ��헪�Ŏc���̂̐�
// 0�ȏ�1�ȉ��̎�������
#define RAND_01 ((double)rand() / RAND_MAX)
#define MUTATE_PROB 0.001 // �ˑR�ψيm��

class Individual
{
public:
	static Para *para;
	static int centerZoneNum;
	static int surroundingZoneNum;
	static int solutionLen;
	static int solutionSubLen;
	static int distanceMax;
	static double transFitBase;

	Individual();
	~Individual();

	void calcFit();
	void writeResult();
	void crossover(Individual *p1, Individual *p2); // �����ɂ��q�ɂ���
	void mutate();									// �ˑR�ψق��N����
	void evaluate();								// �K���x���Z�o����
	int *solution;
	int **housePop;
	double **facilityPop;
	double subsidy;
	int moveNum;
	int facilityNum;
	double moveProb;
	double fitness;
};
