#include "user.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

CUser::CUser(const char* name, int* arr) : user_live(true) {
	strcpy_s(user_name, strlen(name) + 1, name);

	level = *(arr);
	max_hp = *(arr + 1);
	u_attack = *(arr + 2);
	u_defense = *(arr + 3);
	point = *(arr + 4);
	exp = *(arr + 5);
	max_exp = *(arr + 6);
	max_stage = *(arr + 7);
	total_kill = *(arr + 8);
	u_hp = max_hp;
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
	max_exp += max_exp / 10;
}
