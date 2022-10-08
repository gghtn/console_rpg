#pragma once
#include <stdlib.h>
using namespace std;

class CUser {
	bool user_live;
	char* user_name;
	//����, HP, ���ݷ�, ����Ʈ, HP�ѷ�
	int level, u_hp, u_attack, u_defense, point, max_hp = 100;
	//���� ����ġ, ����ġ �ѷ�,
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

	//���� ȸ��
	void userRecovery();
	//���� ���翩��
	bool isUser() { return user_live; };

	//���ݷ� ����
	void setAttack();

	//�������� ���
	void printUser();

	//������ ���ݹ��� ���
	void userDamaged(int damage);

	//������
	void levelUp();
};