#include "monster.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

int CMonster::death_count = 0;

CMonster::CMonster() : monster_live(true) {
	srand((unsigned)time(NULL));
	m_hp = rand() % 50 + 10;
	m_attack = rand() % 10 + 10;
}

void CMonster::monsterDamaged(int damage) {
	m_hp -= damage;
	if (m_hp <= 0) {
		monster_live = false;
		m_hp = 0;
		death_count++;
	}
}