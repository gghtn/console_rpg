#pragma once
#include <stdlib.h>

class CMonster {
	bool monster_live;
	int m_hp, m_attack;

public:
	static int death_count;

	CMonster();

	//������ ���翩��
	bool isMonster() { return monster_live; };

	//������ hp��������
	int getMonsterHp() { return m_hp; };

	//���� ���ݷ� ��������
	int getMonsterAttack() { return rand() % m_attack + 5; };

	//���Ͱ� ���ݹ��� ��
	void monsterDamaged(int damage);
};