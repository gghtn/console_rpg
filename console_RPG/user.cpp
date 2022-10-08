#include "user.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

CUser::CUser(const char* name) : user_live(true) {
	user_name = new char[strlen(name) + 1];
	strcpy_s(user_name, strlen(name) + 1, name);

	srand((unsigned)time(NULL));
	level = 1;
	u_hp = max_hp;
	u_attack = rand() % 10 + 10;
	u_defense = rand() % 10 + 10;
	point = 0;
	exp = 0;
}

void CUser::setExp(int num) {
	exp += num;
	if (exp >= max_exp) {
		exp = exp - max_exp;
		levelUp();
	}
}

void CUser::userRecovery() {
	u_hp += (max_hp / 10) * 2;
	if (u_hp > max_hp) u_hp = max_hp;
}

void CUser::setAttack() {
	srand((unsigned)time(NULL));
	u_attack = rand() % 10 + 10;
}

void CUser::printUser() {
	cout << "===========================\n";
	cout << "| 이름  : ";
	cout.width(16);
	cout << left << user_name << "|\n";

	cout << "| HP    : ";
	cout.width(16);
	cout << left << u_hp << "|\n";

	cout << "| 공격력: ";
	cout.width(16);
	cout << left << u_attack << "|\n";
	cout << "===========================\n";
}

void CUser::userDamaged(int damage) {
	u_hp -= damage - u_defense / 10;
	if (u_hp <= 0) user_live = false, u_hp = 0;
}

void CUser::levelUp() {
	level++, max_hp++, u_attack++, u_defense++;
	point += 5;
	exp = 0;
	max_exp += max_exp / 10;
}
