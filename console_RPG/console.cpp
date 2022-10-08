#include "console.h"
#include <iostream>
#pragma warning(disable:4996)

void gotoxy(SHORT x, SHORT y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;			//커서 굵기
	cursor.bVisible = FALSE;	//커서 visible
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void setConsoleSize(int x, int y) {
	char command[100];
	sprintf(command, "mode con lines=%d cols=%d", y, x);
	system(command);
}