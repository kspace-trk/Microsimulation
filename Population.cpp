#include "Population.h"

Para *Population::para = NULL;

// �R���X�g���N�^
Population::Population()
{
	int i;
	iteNum = 1;

	ind = new Individual *[POP_SIZE];	  //ind[100]�錾
	nextInd = new Individual *[POP_SIZE]; //nextInd[100]�錾
	for (i = 0; i < POP_SIZE; i++)
	{
		ind[i] = new Individual();
		nextInd[i] = new Individual();
		ind[i]->calcFit();
		nextInd[i]->calcFit();
	}
	evaluate(); // �K���x���Z�o����
}

// �f�X�g���N�^
Population::~Population()
{
	int i;

	for (i = 0; i < POP_SIZE; i++)
	{
		delete ind[i];
		delete nextInd[i];
	}
	delete[] ind;
	delete[] nextInd;
}
// ���ׂĂ̌̂�]�����āC�K���x���ɕ��ёւ���
void Population::evaluate()
{
	int i;

	for (i = 0; i < POP_SIZE; i++)
	{
		ind[i]->calcFit();
	}
	sort(0, POP_SIZE - 1);
}
// ind[lb]�`ind[ub]���N�C�b�N�\�[�g�ŕ��ёւ���
// lb: ���ёւ��̑Ώۗv�f�̓Y�����̉���
// ub: ���ёւ��̑Ώۗv�f�̓Y�����̏��
void Population::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	Individual *tmp;

	if (lb < ub)
	{
		k = (lb + ub) / 2;
		pivot = ind[k]->fitness;
		i = lb;
		j = ub;
		do
		{
			while (ind[i]->fitness < pivot)
			{
				i++;
			}
			while (ind[j]->fitness > pivot)
			{
				j--;
			}
			if (i <= j)
			{
				tmp = ind[i];
				ind[i] = ind[j];
				ind[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

// ������
void Population::alternate()
{
	int i, j, p1, p2;
	Individual **tmp;
	iteNum++;

	// �G���[�g�ۑ��헪�Ŏq�̂����
	for (i = 0; i < ELITE; i++)
	{
		for (j = 0; j < Individual::solutionLen; j++)
		{
			nextInd[i]->solution[j] = ind[i]->solution[j];
		}
	}

	// �e��I������������
	for (; i < POP_SIZE; i++)
	{
		p1 = select();
		p2 = select();
		nextInd[i]->crossover(ind[p1], ind[p2]);
	}

	// �ˑR�ψق��N����
	for (i = 1; i < POP_SIZE; i++)
	{
		nextInd[i]->mutate();
	}

	// �������������ɕύX����
	tmp = ind;
	ind = nextInd;
	nextInd = tmp; //mem��nextMem�ł��ꂩ��

	// �]������
	evaluate();
}
// ���ʂɊ�Â������L���O�I���Őe�̂�1�I������
// �߂�l: �I�������e�̂̓Y����
int Population::select()
{
	int num, denom, r;

	denom = POP_SIZE * (POP_SIZE + 1) / 2; //50��
	r = ((rand() << 16) + (rand() << 1) + (rand() % 2)) % denom + 1;
	for (num = POP_SIZE; 0 < num; num--)
	{
		if (r <= num)
		{
			break;
		}
		r -= num;
	}
	return POP_SIZE - num;
}