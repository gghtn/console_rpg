#pragma once
#include <Windows.h>

//좌표이동
void gotoxy(SHORT x, SHORT y);

//커서설정
void CursorView();

//콘솔 사이즈
void setConsoleSize(int x, int y);