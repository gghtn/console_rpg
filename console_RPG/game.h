#pragma once
#include "user.h"
#include "monster.h"

class CGame {
	int stage;
	CUser& user;
public:
	CGame(CUser& other) : user(other), stage(0) {};

	void gameStart();

	void battlePrint(CMonster monster);

	void menuPrint();

	void battleStart();
};