#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer()
{
	ScreenInit();
}

void DoubleBuffer::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	//화면에 버퍼 2개 만들기
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//커서 숨기기
	cci.dwSize = 1;
	cci.bVisible - FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);

}

void DoubleBuffer::ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void DoubleBuffer::ScreenClear()
{
	
	for (int i = 0; i < mapSizeX; i++)
	{
		COORD Coor = { i,0 };
		DWORD dw;
		FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 44 * 44, Coor, &dw);
	}

}

void DoubleBuffer::ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void DoubleBuffer::ScreenPrint(int x, int y, string string)
{
	DWORD dw;
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string.c_str(), string.size(), &dw, NULL);
}


