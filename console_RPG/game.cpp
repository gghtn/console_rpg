#include "game.h"
#include "console.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
using namespace std;

enum {
	ATTACK = 48, RECOVERY, STACK, ESC = 27, ENTER = 13,
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77
};

void selectMenu(int key, int y) {
	if (key == UP) y = max(y - 4, 5);
	else if (key == DOWN) y = min(y + 4, 13);
	gotoxy(8, y);
	cout << "▶";
}

void CGame::gameStart() {
	int key, y = 5;
	while (1) {
		menuPrint();
		gotoxy(8, 5);
		cout << "▶";
		int key = _getch();
		if (key == ENTER) {

		}

	}
}

void CGame::menuPrint() {
	system("cls");
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
	cout << left << CMonster::death_count << "■";
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

void CGame::battleStart() {
	setConsoleSize(75, 40);
	while (user.isUser()) {	// 1
		CMonster monster;	//몬스터 생성
		int num, stack = 0, damage;
		int key = 0;
		stage++;

		while (user.isUser() && monster.isMonster()) {	//2
			system("cls");
			battlePrint(monster);
			gotoxy(3, 15);
			cout << "[0-공격, 1-회복, 2-턴 넘기기(공격력 축적), ESC:게임종료]\n\n▶ ";
			key = _getch();
			if (key == ESC) break;
			num = key;

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
		if (key == ESC) break;
	}	//1

}