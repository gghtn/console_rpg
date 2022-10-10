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

//���� �޴��̵� �Լ�
void mainMenu(int key, int& y) {
	gotoxy(7, y);
	cout << "  ";
	if (key == UP) y = max(y - 4, 5);
	else if (key == DOWN) y = min(y + 4, 13);
	gotoxy(7, y);
	cout << "��";
}
//�������ͽ� �޴��̵� �Լ�
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
		cout << "��";
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
			cout << "��";
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
	cout << "���� ����";
	user.setTotalKill(monster_kill);	//���� ����� �� óġ�� set
	saveData();	//���� ����� ������ ����
}

void CGame::battleStart() {
	setConsoleSize(75, 40);
	int total_exp = 0, key, num, damage, stack;	//�� ȹ�� exp, �Է� Ű, Ű�� ������ ����, ������, ����, óġ ��
	stage = 0, user.setHP(), user.setLive();	//��������, ���� hp, ���� �������� �ʱ�ȭ
	while (user.isUser()) {	// 1
		CMonster monster;	//���� ����
		stack = 0, key = 0;
		stage++;

		while (user.isUser() && monster.isMonster()) {	//2
			system("cls");
			battlePrint(monster);
			gotoxy(3, 15);
			cout << "[0-����, 1-ȸ��, 2-�� �ѱ��(���ݷ� ����), ESC:��������]\n\n�� ";
			key = _getch();
			if (key == ESC) break;
			num = key;

			//���� ��(����, ȸ��, �� �ѱ��)
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
					total_exp += 50 + (stage / 5) * 10;
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

			//���� ��
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
		monster_kill = monster.death_count; //�� óġ ��
		if (key == ESC) break;
	}	//1

	/*���� ���� ��¹�*/
	if (stage > user.getStage()) user.setStage(stage);
	char exit_print[100];
	int j = 5;
	key = 0;
	CursorView(TRUE);
	system("cls");

	memset(exit_print, '\0', 100);
	sprintf(exit_print, "�ִ� ���� %d��.���� ���� %d��.óġ ���� %d.�� ȹ�� exp %d.�� óġ ���� %d",
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
	cout << left << stage - 1 << "��";
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

void CGame::menuPrint() {
	system("cls");
	cout << "\n";
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

void CGame::statusPrint() {
	int key, x = 3, y = 6;
	while (1) {
		system("cls");
		gotoxy(5, 2);
		cout << "Lv. " << user.getLevel();
		gotoxy(15, 2);
		cout << "Point:" << user.getPoint();
		gotoxy(5, 4);
		cout << "�г���: " << user.getName();
		gotoxy(5, 6);
		cout << "ATK: " << user.getAttack();
		gotoxy(5, 8);
		cout << "DEF: " << user.getDefense();
		gotoxy(5, 10);
		cout << "HP : " << user.getMaxHp();
		gotoxy(10, 14);
		cout << "���� �޴�";
		gotoxy(x, y);
		if(y == 14) cout << "��";
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

//������ ����
void CGame::saveData() {
	FILE* out;
	out = fopen("savedata.bin", "wb");
	if (out == NULL) return;
	fwrite(&user, sizeof(user), 1, out);
	fclose(out);
}