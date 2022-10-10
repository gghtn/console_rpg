#pragma once
#include <stdlib.h>
using namespace std;

class CUser {
	char user_name[12];
	//레벨, HP, 공격력, 포인트, HP총량
	int level, max_hp, u_attack, u_defense, point;
	//현재 경험치, 경험치 총량,
	int exp, max_exp;
	int max_stage;
	int u_hp;
	bool user_live;

public:
	CUser(const char* name, int* arr);
	~CUser() {}

	//get
	char* getName() { return user_name; };
	int getLevel() { return level; };
	int getHp() { return u_hp; };
	int getMaxHp() { return max_hp; };
	int getAttack() { return u_attack; };
	int getDefense() { return u_defense; };
	int getPoint() { return point; };
	int getExp() { return exp; };
	int getStage() { return max_stage; };
	//set
	void setExp(int num);
	void setStage(int num) { max_stage = num; };
	void setHP() { u_hp = max_hp; };
	void setLive() { user_live = true; };
	void setAttack() { u_attack++; };
	void setMaxHp() { max_hp++; };
	void setDefense() { u_defense++; };
	void setPoint() { point--; };

	//유저 회복
	void userRecovery();
	//유저 생사여부
	bool isUser() { return user_live; }

	//유저정보 출력
	void printUser();

	//유저가 공격받을 경우
	void userDamaged(int damage);

	//레벨업
	void levelUp();
};