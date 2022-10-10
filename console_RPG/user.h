#pragma once
#include <stdlib.h>
using namespace std;

class CUser {
	char user_name[12];
	//����, HP, ���ݷ�, ����Ʈ, HP�ѷ�
	int level, max_hp, u_attack, u_defense, point;
	//���� ����ġ, ����ġ �ѷ�,
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

	//���� ȸ��
	void userRecovery();
	//���� ���翩��
	bool isUser() { return user_live; }

	//�������� ���
	void printUser();

	//������ ���ݹ��� ���
	void userDamaged(int damage);

	//������
	void levelUp();
};