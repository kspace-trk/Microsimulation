#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

class Para
{
public:
	Para();
	~Para();

	int zoneHNum;		   // �������]�[����
	int zoneVNum;		   // �c�����]�[����
	int centerZoneHID1;	   // �s�S�]�[���������J�nID
	int centerZoneHID2;	   // �s�S�]�[���������I��ID
	int centerZoneVID1;	   // �s�S�]�[���c�����J�nID
	int centerZoneVID2;	   // �s�S�]�[���c�����I��ID
	int initialZonePopNum; // �����]�[���l��(�l)
	int transTimeUnit;	   // �אڃ]�[���ւ̈ړ�����(��)
	int transTimeLimit;	   // �ڑ����ԏ��(��)
	int facilityCapacity;  // 1�{�݂̎���l�����(�l)
	int runningCost;	   // �{�݂̐V�ݔ�{10�N�Ԃ̈ێ��Ǘ���(���~)
	int subsidyMax;		   // 1�l������̈ړ]�⏕���̏���l(���~)
	int transCostUnit;	   // 1�l1��������̈ڑ��T�[�r�X��(�~)
	int subsidyLevelNum;   // �ړ]�⏕���̒i�K���i20�̂Ƃ���1/20���݁j
	double receiveRatio;   // ��앟���T�[�r�X�󋋗�
};
