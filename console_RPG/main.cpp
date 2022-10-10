#include <iostream>
#include <string>
#include "game.h"
#include "user.h"
#include "console.h"
#pragma warning(disable:4996)
using namespace std;

#define YES 121
char name[12];
int save_arr[9]={1, 100, 15, 15, 0, 0, 100, 1, 0}; //level, maxHP, ATK, DEF, point, exp, maxExp, maxStage, totalKill

int main() {
	memset(name, '\0', 10);
	FILE* in;
	in = fopen("savedata.bin", "rb");
	if (!in) {
		gotoxy(3, 10);
		cout << "캐릭터 이름을 설정하시오: ";
		cin >> name;
	}
	else {
		gotoxy(3, 10);
		cout << "이전 정보를 로드하시겠습니까?(Y/N) ";
		char ch;
		cin >> ch;
		system("cls");
		gotoxy(3, 10);
		if (ch == YES) {
			fread(name, sizeof(char), 12, in);
			fread(save_arr, sizeof(int), 9, in);

			cout << "이전 정보를 로드했습니다.";
			Sleep(500);
		}
		else {
			cout << "캐릭터 이름을 설정하시오: ";
			cin >> name;
		}
		fclose(in);
	}

	CUser hero(name, save_arr);

	CGame _new(hero);

	_new.gameStart();

	return 0;
}