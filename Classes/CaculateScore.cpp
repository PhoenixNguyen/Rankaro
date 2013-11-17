//============================================================================
// Name        : CaculateScore.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : CaculateScore in cocos2dx C++, Ansi-style
//============================================================================


#include "cocos2d.h"
#include "CaculateScore.h"

USING_NS_CC;

bool CaculateScore::init()
{
	//detection();
	return true;
}

int CaculateScore::detection(int pArray[MAP_X][MAP_Y])
{
	
	int MAP[MAP_X][MAP_Y];

	for(int i = 0; i < MAP_X; i++)
		for( int j = 0; j <MAP_Y; j++)
		{
      MAP[i][j] = pArray[i][j];
			//CCLog ("%d", a[i][j]);
		}

	
	int SUM = 0;

	//Tinh Diem theo hang
	for (int i = 0; i < MAP_Y; i++)
	{
		/*
			Duyet tren 1 hang neu
			- gia tri dang xet = gia tri tiep theo tang bien dem
			  neu la gia tri cuoi hang thi tinh tong
			- neu khong bang :
				+ bien dem nho hon 3 thi break  gan lai tmp  = 1
				+ neu bien dem >= 3, tinh Tong cua block do

		*/
		int SUB = 0;
		int tmp = 1;
		for (int j = 0; j < (MAP_X - 1); j++)
		{
			if( MAP[i][j] == -1){
				tmp = 1;
				continue;
			}

			if (MAP[i][j] ==MAP[i][j+1] )
			{
				tmp ++;
			}
			else
			{
				if (tmp >= 3)
					SUB += MAP[i][j] * tmp;
				tmp = 1;
			}

			//Cuoi hang
			if( j == (MAP_X - 2) && (MAP[i][j] ==MAP[i][j+1]) && tmp >= 3 )
				SUB += MAP[i][j] * tmp;
		}
		//Tinh tong diem tat ca cac hang
		SUM += SUB;
	}

	//Tinh Diem theo cot
	//cot
	for (int i = 0; i < MAP_X; i++)
	{
		/*
			Duyet tren 1 cot neu
			- gia tri dang xet = gia tri tiep theo tang bien dem
			  neu la gia tri cuoi hang thi tinh tong
			- neu khong bang :
				+ bien dem nho hon 3 thi break  gan lai tmp  = 1
				+ neu bien dem >= 3, tinh Tong cua block do
		*/
		int SUB = 0;
		int tmp = 1;
		//hang
		for (int j = 0; j < (MAP_Y - 1); j++)
		{
			if( MAP[j][i] == -1){
				tmp = 1;
				continue;
			}

			if (MAP[j][i] ==MAP[j+1][i] )
			{
				tmp ++;
			}
			else
			{
				if (tmp >= 3)
					SUB += MAP[j][i] * tmp;
				tmp = 1;
			}

			//Cuoi cot
			if( j == (MAP_Y - 2) && (MAP[j][i] ==MAP[j+1][i]) && tmp >= 3 )
				SUB += MAP[j][i] * tmp;
		}
		//Tinh tong diem tat ca cac cot
		SUM += SUB;
	}

	//Tinh diem theo hang cheo phai (nua duoi theo hang)
	for (int i = 0; i < (MAP_Y - 2); i++)
	{
		/*
			Duyet tren  hang cheo sang phai neu
			- gia tri dang xet = gia tri tiep theo tang bien dem
			- neu khong bang :
				+ bien dem nho hon 3 thi break  gan lai tmp  = 1
				+ neu bien dem >= 3, tinh Tong cua block do
		*/
		int SUB = 0;
		int tmp = 1;
		for (int j = 0; j < (MAP_Y - i - 1); j++)
		{
			if( MAP[i+j][j] == -1){
				tmp = 1;
				continue;
			}

			if (MAP[i+j][j] ==MAP[i+j+1][j+1] )
			{
				tmp ++;
			}
			else
			{
				if (tmp >= 3)
					SUB += MAP[i+j][j] * tmp;
				tmp = 1;
			}

			//Cuoi duong cheo
			if( j == (MAP_Y - i - 2) && (MAP[i+j][j] ==MAP[i+j+1][j+1]) && tmp >= 3 )
				SUB += MAP[i+j][j] * tmp;

		}
		//Tinh tong diem tat ca cac hang
		SUM += SUB;
	}

	//Tinh diem theo hang cheo phai (nua tren theo cot)
	for (int i = 1; i <= (MAP_X - 3); i++) //cot
	{
		/*
			Duyet tren  hang cheo sang phai neu
			- gia tri dang xet = gia tri tiep theo tang bien dem
			- neu khong bang :
				+ bien dem nho hon 3 thi break  gan lai tmp  = 1
				+ neu bien dem >= 3, tinh Tong cua block do
		*/
		int SUB = 0;
		int tmp = 1;
		//Hang
		for (int j = 0; j < (MAP_Y - i - 1); j++)
		{
			if( MAP[j][i+j] == -1){
				tmp = 1;
				continue;
			}

			if (MAP[j][i+j] ==MAP[j+1][i+j+1] )
			{
				tmp ++;
			}
			else
			{
				if (tmp >= 3)
					SUB += MAP[j][i+j] * tmp;
				tmp = 1;
			}

			//Cuoi duong cheo
			if( j == (MAP_Y - i - 2) && (MAP[j][i+j] ==MAP[j+1][i+j+1] ) && tmp >= 3 )
				SUB += MAP[j][i+j] * tmp;
		}
		//Tinh tong diem tat ca cac hang
		SUM += SUB;
	}

	//Tinh diem theo hang cheo trai (nua duoi theo hang)
	for (int i = 0; i < (MAP_Y - 2); i++)
	{
		/*
			Duyet tren  hang cheo sang phai neu
			- gia tri dang xet = gia tri tiep theo tang bien dem
			- neu khong bang :
				+ bien dem nho hon 3 thi break  gan lai tmp  = 1
				+ neu bien dem >= 3, tinh Tong cua block do
		*/
		int SUB = 0;
		int tmp = 1;
		for (int j = 0; j < (MAP_Y - i - 1); j++)
		{
			if( MAP[i+j][MAP_X - j -1] == -1){
				tmp = 1;
				continue;
			}

			if (MAP[i+j][MAP_X - j - 1] ==MAP[i+j+1][MAP_X - j - 2] )
			{
				tmp ++;
			}
			else
			{
				if (tmp >= 3)
					SUB += MAP[i+j][MAP_X - j - 1] * tmp;
				tmp = 1;
			}

			//Cuoi duong cheo
			if( j == (MAP_Y - i - 2) && (MAP[i+j][MAP_X - j - 1] ==MAP[i+j+1][MAP_X - j - 2] ) && tmp >= 3 )
				SUB += MAP[i+j][MAP_X - j - 1] * tmp;
		}
		//Tinh tong diem tat ca cac hang
		SUM += SUB;
	}

	//Tinh diem theo hang cheo trai (nua tren theo cot)
	//Cot
	for (int i =2; i < (MAP_X - 1) ; i++)
	{
		/*
			Duyet tren  hang cheo sang phai neu
			- gia tri dang xet = gia tri tiep theo tang bien dem
			- neu khong bang :
				+ bien dem nho hon 3 thi break  gan lai tmp  = 1
				+ neu bien dem >= 3, tinh Tong cua block do
		*/
		int SUB = 0;
		int tmp = 1;
		//hang
		for (int j = 0; j < (i); j++)
		{
			if( MAP[j][i-j] == -1){
				tmp = 1;
				continue;
			}

			if (MAP[j][i - j] == MAP[j+1][i - j - 1] )
			{
				tmp ++;
			}
			else
			{
				if (tmp >= 3)
					SUB += MAP[j][i - j] * tmp;
				tmp = 1;
			}

			//Cuoi duong cheo
			if( j == (i - 1) && (MAP[j][i - j] == MAP[j+1][i - j - 1] ) && tmp >= 3 )
				SUB += MAP[j][i - j] * tmp;
		}
		//Tinh tong diem tat ca cac hang
		SUM += SUB;
	}

  return SUM;
	//for (int i =0; i < WIDTH; i++)
		//for(int j= 0; j < HEIGHT; j++)
			//printf("%d", MAP[i][j]);
			//CCLOG("%d", MAP[i][j]);
}