#pragma once
#include <stdlib.h>

class CMonster {
	bool monster_live;
	int m_hp, m_attack;

public:
	static int death_count;

	CMonster();

	//몬스터의 생사여부
	bool isMonster() { return monster_live; };

	//몬스터 get
	int getMonsterHp() { return m_hp; };
	int getMonsterAttack() { return rand() % m_attack + 5; };

	//몬스터가 공격받을 때
	void monsterDamaged(int damage);
};