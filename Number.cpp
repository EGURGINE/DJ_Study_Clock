#include "pch.h"
#include "Number.h"

//0~9까지 수
void NumOutput(HDC hdc, int x, int y, int num, int fontysize)
{
	if (num > 9)
	{
		MessageBox(NULL, L"0~9의 한 자릿수만 출력합니다.",
			       L"Error", MB_OK);
		return;
	}

	static TCHAR strTime[10][5][7] = {
		{L"■■■",
		 L"■  ■",
		 L"■  ■",
		 L"■  ■",
		 L"■■■",
		},
		{L"■■  ",
		 L"  ■  ",
		 L"  ■  ",
		 L"  ■  ",
		 L"■■■",
		},
		{L"■■■",
		 L"    ■",
		 L"■■■",
		 L"■    ",
		 L"■■■",
		},
		{L"■■■",
		 L"    ■",
		 L"■■■",
		 L"    ■",
		 L"■■■",
		},
		{L"■    ",
		 L"■  ■",
		 L"■■■",
		 L"    ■",
		 L"    ■",
		},
		{L"■■■",
		 L"■    ",
		 L"■■■",
		 L"    ■",
		 L"■■■",
		},
		{L"■■■",
		 L"■    ",
		 L"■■■",
		 L"■  ■",
		 L"■■■",
		},
		{L"■■■",
		 L"    ■",
		 L"    ■",
		 L"    ■",
		 L"    ■",
		},
		{L"■■■",
		 L"■  ■",
		 L"■■■",
		 L"■  ■",
		 L"■■■",
		},
		{L"■■■",
		 L"■  ■",
		 L"■■■",
		 L"    ■",
		 L"■■■",
		},
	};
	
	for (int i = 0; i < 5; i++)
	{
		TextOut(hdc, x, y + i * fontysize * 0.5f, 
			    strTime[num][i], wcslen(strTime[num][i]));
	}
}


void DrawNumber(HDC hdc, int fontsize, int x, int y, int number)
{
	if (number > 1000000000) return;

	TCHAR strBuff[128];
	int  nSize;
	wsprintf(strBuff, L"%d", number);
	nSize = wcslen(strBuff);

	int seedNum = 1;
	int i;
	for (i = 0; i < nSize - 1; i++) seedNum *= 10;
	int* num;
	num = (int*)malloc(nSize * sizeof(int));

	for (i = 0; i < nSize; i++)
	{
		num[i] = number / seedNum;
		number %= seedNum;
		seedNum /= 10;

		NumOutput(hdc, x, y, num[i], fontsize);
		x += fontsize * 3 + fontsize/2;
	}
	free(num);
}