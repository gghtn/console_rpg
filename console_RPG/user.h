#pragma once
#include <stdlib.h>
using namespace std;

class CUser {
	bool user_live;
	char* user_name;
	//레벨, HP, 공격력, 포인트, HP총량
	int level, u_hp, u_attack, u_defense, point, max_hp = 100;
	//현재 경험치, 경험치 총량,
	int exp, max_exp = 100;

public:
	CUser(const char* name);
	~CUser() { delete[] user_name; }

	//get
	char* getName() { return user_name; };
	int getLevel() { return level; };
	int getHp() { return u_hp; };
	int getAttack() { return u_attack; };
	int getDefense() { return u_defense; };
	int getPoint() { return point; };
	int getExp() { return exp; };
	//set
	void setExp(int num);

	//유저 회복
	void userRecovery();
	//유저 생사여부
	bool isUser() { return user_live; };

	//공격력 설정
	void setAttack();

	//유저정보 출력
	void printUser();

	//유저가 공격받을 경우
	void userDamaged(int damage);

	//레벨업
	void levelUp();
};