#pragma once
#include "user.h"
#include "monster.h"

class CGame {
	int stage, monster_kill;
	CUser& user;
public:
	CGame(CUser& other) : user(other), stage(0), monster_kill(0){};

	void gameStart();
	void battleStart();
	void saveData();

	void battlePrint(CMonster monster);
	void menuPrint();
	void statusPrint();
};