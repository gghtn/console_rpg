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
	cout << "��";
}

void CGame::gameStart() {
	int key, y = 5;
	while (1) {
		menuPrint();
		gotoxy(8, 5);
		cout << "��";
		int key = _getch();
		if (key == ENTER) {

		}

	}
}

void CGame::menuPrint() {
	system("cls");
	cout << "����������������\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "��                          ��\n";
	cout << "����������������";

	gotoxy(10, 5);
	cout << "���� ����";
	gotoxy(10, 9);
	cout << "�������ͽ�";
	gotoxy(10, 13);
	cout << "���� ����";
}

void CGame::battlePrint(CMonster monster) {
	gotoxy(3, 1);
	cout << "�����������������";
	gotoxy(3, 2);
	cout << "��                            ��";
	gotoxy(3, 3);
	cout << "�� Stage : ";
	cout.width(19);
	cout << left << stage << "��";
	gotoxy(3, 4);
	cout << "��                            ��";
	gotoxy(3, 5);
	cout << "�� óġ ���� : ";
	cout.width(13);
	cout << left << CMonster::death_count << "��";
	gotoxy(3, 6);
	cout << "��                            ��";
	gotoxy(3, 7);
	cout << "�����������������";

	gotoxy(40, 1);
	cout << "�����������������";
	gotoxy(40, 2);
	cout << "�� ";
	cout.width(27);
	cout << user.getName() << "��";
	gotoxy(40, 3);
	cout << "�� Level: ";
	cout.width(7);
	cout << left << user.getLevel();
	cout << "Exp: ";
	cout.width(8);
	cout << left << user.getExp() << "��";
	gotoxy(40, 4);
	cout << "�� ATK: ";
	cout.width(9);
	cout << left << user.getAttack();
	cout << "DEF: ";
	cout.width(8);
	cout << left << user.getDefense() << "��";
	gotoxy(40, 5);
	cout << "�� HP: ";
	cout.width(23);
	cout << left << user.getHp() << "��";
	gotoxy(40, 6);
	cout << "�� Point: ";
	cout.width(20);
	cout << left << user.getPoint() << "��";
	gotoxy(40, 7);
	cout << "�����������������";

	//���� hp���
	gotoxy(3, 11);
	int tmpHP = monster.getMonsterHp();
	cout << "�� Monster HP: ";
	while (tmpHP--) cout << '|';

}

void CGame::battleStart() {
	setConsoleSize(75, 40);
	while (user.isUser()) {	// 1
		CMonster monster;	//���� ����
		int num, stack = 0, damage;
		int key = 0;
		stage++;

		while (user.isUser() && monster.isMonster()) {	//2
			system("cls");
			battlePrint(monster);
			gotoxy(3, 15);
			cout << "[0-����, 1-ȸ��, 2-�� �ѱ��(���ݷ� ����), ESC:��������]\n\n�� ";
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
					cout << "���Ϳ��� " << damage << "��ŭ�� �������� �־����ϴ�.";
				}
				else {
					gotoxy(3, 15);
					cout << "���Ϳ��� " << damage << "��ŭ�� �������� �־����ϴ�.";
					gotoxy(3, 16);
					cout << "���͸� óġ�߽��ϴ�!!";
					user.setExp(50 + (stage / 5) * 10);		//����ġȹ��
				}
				battlePrint(monster);
				stack = 0;	//�����ʱ�ȭ
				Sleep(1000);
				break;

			case RECOVERY:
				system("cls");
				user.userRecovery();
				battlePrint(monster);
				gotoxy(3, 15);
				cout << "������� ȸ���߽��ϴ�!";
				Sleep(1000);
				break;

			case STACK:
				system("cls");
				battlePrint(monster);
				stack = min(stack++, 5);
				gotoxy(3, 15);

				if (stack != 5) cout << "���� �ѱ�ϴ�.";
				else {
					cout << "���̻� ���ݷ��� �������� �ʽ��ϴ�. ���� �ѱ�ðڽ��ϱ�?(Y/N)\n\n�� ";
					if (_getch() != 121) continue;
					cout << "���� �ѱ�ϴ�.";
				}
				Sleep(1000);
				break;
			default:
				gotoxy(3, 17);
				cout << "�߸��� �Է��� ���Խ��ϴ�!! 0, 1, 2 �߿� �ϳ��� �Է��ϼ���!!";
				Sleep(1000);
				continue;
			}

			if (monster.isMonster()) {
				damage = 5 + rand() % monster.getMonsterAttack() + (stage / 10) * 5; //10������������ �� ���ݷ� ����
				user.userDamaged(damage);
				system("cls");
				battlePrint(monster);
				gotoxy(3, 15);
				if (user.isUser()) {
					cout << "���Ϳ��� " << damage << "��ŭ�� ���ظ� �Ծ����ϴ�.";
				}
				else {
					cout << "���� ����";
				}
				Sleep(1000);
			}

		}	//2
		if (key == ESC) break;
	}	//1

}