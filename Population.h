#pragma once

#include "Individual.h"

class Population
{
public:
	static Para *para;

	Population();
	~Population();

	void alternate();

	int iteNum;
	Individual **ind;

private:
	Individual *newHarmony;
	Individual **nextInd;
	int select();			   // �e�̂�I������
	void evaluate();		   // �̂�]������
	void sort(int lb, int ub); // �̂�ǂ����ɕ��ёւ���
};
