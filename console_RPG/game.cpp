#include "game.h"
#include "console.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

enum {
	ATTACK = 48, RECOVERY, STACK, ESC = 27, ENTER = 13,
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77
};

//메인 메뉴이동 함수
void mainMenu(int key, int& y) {
	gotoxy(7, y);
	cout << "  ";
	if (key == UP) y = max(y - 4, 5);
	else if (key == DOWN) y = min(y + 4, 13);
	gotoxy(7, y);
	cout << "▶";
}
//스테이터스 메뉴이동 함수
void statusMenu(int key, int& x, int& y) {
	if (key == UP) {
		if (y == 14) y -= 4;
		else y = max(y - 2, 6);
	}
	else if (key == DOWN) {
		if (y == 10) y += 4;
		else y = min(y + 2, 14);
	}
	cout << ' ';
	if (y == 14) {
		x = 7;
		gotoxy(x, y);
		cout << "▶";
	}
	else {
		x = 3;
		gotoxy(x, y);
		cout << '+';
	}

}



void CGame::gameStart() {
	int key, y = 5;
	while (1) {
		start:
		setConsoleSize(30, 20);
		CursorView(FALSE);
		menuPrint();
		while (1) {
			gotoxy(7, y);
			cout << "▶";
			key = _getch();
			if (key == ENTER) {
				switch (y) {
				case 5:
					battleStart();
					goto start;
				case 9:
					statusPrint();
					goto start;
				case 13:
					goto end;
				default:
					break;
				}
			}
			else if (key == ESC) goto end;
			mainMenu(key, y);
		}
	end: break;
	}
	system("cls");
	cout << "게임 종료";
	user.setTotalKill(monster_kill);	//게임 종료시 총 처치수 set
	saveData();	//게임 종료시 데이터 저장
}

void CGame::battleStart() {
	setConsoleSize(75, 40);
	int total_exp = 0, key, num, damage, stack;	//총 획득 exp, 입력 키, 키를 저장할 변수, 데미지, 스택, 처치 수
	stage = 0, user.setHP(), user.setLive();	//스테이지, 유저 hp, 유저 생존여부 초기화
	while (user.isUser()) {	// 1
		CMonster monster;	//몬스터 생성
		stack = 0, key = 0;
		stage++;

		while (user.isUser() && monster.isMonster()) {	//2
			system("cls");
			battlePrint(monster);
			gotoxy(3, 15);
			cout << "[0-공격, 1-회복, 2-턴 넘기기(공격력 축적), ESC:게임종료]\n\n▶ ";
			key = _getch();
			if (key == ESC) break;
			num = key;

			//유저 턴(공격, 회복, 턴 넘기기)
			switch (num) {
			case ATTACK:
				system("cls");
				damage = 5 + rand() % user.getAttack() + int(pow(stack, 2)) * 10;
				monster.monsterDamaged(damage);
				if (monster.isMonster()) {
					gotoxy(3, 15);
					cout << "몬스터에게 " << damage << "만큼의 데미지를 주었습니다.";
				}
				else {
					gotoxy(3, 15);
					cout << "몬스터에게 " << damage << "만큼의 데미지를 주었습니다.";
					gotoxy(3, 16);
					cout << "몬스터를 처치했습니다!!";
					total_exp += 50 + (stage / 5) * 10;
					user.setExp(50 + (stage / 5) * 10);		//경험치획득
				}
				battlePrint(monster);
				stack = 0;	//스택초기화
				Sleep(1000);
				break;

			case RECOVERY:
				system("cls");
				user.userRecovery();
				battlePrint(monster);
				gotoxy(3, 15);
				cout << "생명력을 회복했습니다!";
				Sleep(1000);
				break;

			case STACK:
				system("cls");
				battlePrint(monster);
				stack = min(stack++, 5);
				gotoxy(3, 15);

				if (stack != 5) cout << "턴을 넘김니다.";
				else {
					cout << "더이상 공격력이 강해지지 않습니다. 턴을 넘기시겠습니까?(Y/N)\n\n▶ ";
					if (_getch() != 121) continue;
					cout << "턴을 넘김니다.";
				}
				Sleep(1000);
				break;
			default:
				gotoxy(3, 17);
				cout << "잘못된 입력이 들어왔습니다!! 0, 1, 2 중에 하나를 입력하세요!!";
				Sleep(1000);
				continue;
			}

			//몬스터 턴
			if (monster.isMonster()) {
				damage = 5 + rand() % monster.getMonsterAttack() + (stage / 10) * 5; //10스테이지마다 적 공격력 증가
				user.userDamaged(damage);
				system("cls");
				battlePrint(monster);
				gotoxy(3, 15);
				if (user.isUser()) {
					cout << "몬스터에게 " << damage << "만큼의 피해를 입었습니다.";
				}
				else {
					cout << "게임 오버";
				}
				Sleep(1000);
			}
		}	//2
		monster_kill = monster.death_count; //총 처치 수
		if (key == ESC) break;
	}	//1

	/*게임 종료 출력문*/
	if (stage > user.getStage()) user.setStage(stage);
	char exit_print[100];
	int j = 5;
	key = 0;
	CursorView(TRUE);
	system("cls");

	memset(exit_print, '\0', 100);
	sprintf(exit_print, "최대 도달 %d층.현재 도달 %d층.처치 몬스터 %d.총 획득 exp %d.총 처치 몬스터 %d",
		user.getStage(), stage, stage-1, total_exp, user.getTotalKill() + monster_kill);

	gotoxy(25, j);
	for (unsigned int i = 0; i < strlen(exit_print); i++) {
		if (_kbhit()) {
			key = getch();
			if (key == ESC) break;
		}
		if (exit_print[i] == '.') {
			j += 3;
			gotoxy(25, j);
			continue;
		}
		cout << exit_print[i];
		Sleep(50);
	}
	if (key != ESC) Sleep(1000);
}

void CGame::battlePrint(CMonster monster) {
	gotoxy(3, 1);
	cout << "■■■■■■■■■■■■■■■■";
	gotoxy(3, 2);
	cout << "■                            ■";
	gotoxy(3, 3);
	cout << "■ Stage : ";
	cout.width(19);
	cout << left << stage << "■";
	gotoxy(3, 4);
	cout << "■                            ■";
	gotoxy(3, 5);
	cout << "■ 처치 몬스터 : ";
	cout.width(13);
	cout << left << stage - 1 << "■";
	gotoxy(3, 6);
	cout << "■                            ■";
	gotoxy(3, 7);
	cout << "■■■■■■■■■■■■■■■■";

	gotoxy(40, 1);
	cout << "■■■■■■■■■■■■■■■■";
	gotoxy(40, 2);
	cout << "■ ";
	cout.width(27);
	cout << user.getName() << "■";
	gotoxy(40, 3);
	cout << "■ Level: ";
	cout.width(7);
	cout << left << user.getLevel();
	cout << "Exp: ";
	cout.width(8);
	cout << left << user.getExp() << "■";
	gotoxy(40, 4);
	cout << "■ ATK: ";
	cout.width(9);
	cout << left << user.getAttack();
	cout << "DEF: ";
	cout.width(8);
	cout << left << user.getDefense() << "■";
	gotoxy(40, 5);
	cout << "■ HP: ";
	cout.width(23);
	cout << left << user.getHp() << "■";
	gotoxy(40, 6);
	cout << "■ Point: ";
	cout.width(20);
	cout << left << user.getPoint() << "■";
	gotoxy(40, 7);
	cout << "■■■■■■■■■■■■■■■■";

	//몬스터 hp출력
	gotoxy(3, 11);
	int tmpHP = monster.getMonsterHp();
	cout << "□ Monster HP: ";
	while (tmpHP--) cout << '|';

}

void CGame::menuPrint() {
	system("cls");
	cout << "\n";
	cout << "■■■■■■■■■■■■■■■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■                          ■\n";
	cout << "■■■■■■■■■■■■■■■";

	gotoxy(10, 5);
	cout << "게임 시작";
	gotoxy(10, 9);
	cout << "스테이터스";
	gotoxy(10, 13);
	cout << "게임 종료";
}

void CGame::statusPrint() {
	int key, x = 3, y = 6;
	while (1) {
		system("cls");
		gotoxy(5, 2);
		cout << "Lv. " << user.getLevel();
		gotoxy(15, 2);
		cout << "Point:" << user.getPoint();
		gotoxy(5, 4);
		cout << "닉네임: " << user.getName();
		gotoxy(5, 6);
		cout << "ATK: " << user.getAttack();
		gotoxy(5, 8);
		cout << "DEF: " << user.getDefense();
		gotoxy(5, 10);
		cout << "HP : " << user.getMaxHp();
		gotoxy(10, 14);
		cout << "메인 메뉴";
		gotoxy(x, y);
		if(y == 14) cout << "▶";
		else cout << '+';

		key = getch();
		if (key == ENTER) {
			switch (y) {
			case 6:
				if (user.getPoint() == 0) break;
				user.setAttack();
				user.setPoint();
				break;
			case 8:
				if (user.getPoint() == 0) break;
				user.setDefense();
				user.setPoint();
				break;
			case 10:
				if (user.getPoint() == 0) break;
				user.setMaxHp();
				user.setPoint();
				break;
			case 14:
				goto end;
			default:
				break;
			}
		}
		else if (key == ESC) break;
		else statusMenu(key, x, y);
	}
end:{}
}

//데이터 저장
void CGame::saveData() {
	FILE* out;
	out = fopen("savedata.bin", "wb");
	if (out == NULL) return;
	fwrite(&user, sizeof(user), 1, out);
	fclose(out);
}