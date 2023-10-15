#pragma once
#include "Manager.h"
#include "cMap.h"
#define BULLET 3

struct sBullet {
	POINT bp;   //Bullet Position �Ѿ� ��ġ
	bool isShoot;
	double rad;
};

class cMonster {
private:
	POINT mp;   //Monster Position �ֻ��� ��ġ
	RECT MonsterRect;
	double M_angle;   //���Ͱ� ���ΰ��� ���� �ٶ󺸰� �ִ� ����
	double chargeRad;
	bool isDie;   //�׾���?
	bool isSummon;   //��ȯ�ƴ�?
	bool isAttack;   //�����ϴ�?
	bool isRage; // ���� �г�

	sBullet bullet[BULLET];

	int monsterKind;   //���� ����
	int deathCnt;      //�װ��� �ð������� ��ü ��������� ī��Ʈ
	int patternCnt;      //������ ����Ǵ� �ð�
	int SpawnCnt; // �����ɶ� �ɸ��� �ð�
	int MaxSpawnCnt;
	int objNum;
	int removeObj;
	int hp;      //���� ü��

	POINT size, die_Size;
public:
	cMonster();
	~cMonster();
public:
	void drawMonster(HDC hdc, HINSTANCE g_hInst);
	bool SpawnMonster(POINT pp);
	void MoveMonster();
	void calculAngle(POINT pp);
	void turnDie();
	void monsterPattern();
	void turnShoot(int);   //�Ѿ� ĳ���Ͱ� ������ ������� �Ϸ���.
	void pointHandle(LONG, LONG);
	bool returnDie();
	void setObjNum(int num);   //2���� ������ ������Ʈ ������ ��ȣ �����ϴ¿뵵 ����
	void removeObj2Zero();
	void bossHit();   //������ �¾�����
public:
	const int& GetMonsterKind();
	const POINT& GetMonsterPoint();
	const POINT& GetBulletPoint(int);
	const POINT& GetMonstersize();
	const double& GetMonsterRadian();
	const double& GetBulletRadian(int);
	const RECT& GetMonsterRect();
	const bool& GetIsDie();
	const bool& GetIsSummon();
	const int& GetObjNum();   //2���� ������Ʈ ������ٰ� �����ߴ��� �˷���,,
	const int& GetRemoveObj();   //2���� �ù߳� ������Ʈ ����� ���� �ƴ��� �� �ƴ��� Ȯ���Ϸ���
	const int& GetBossHp();

	void SetBossHp(int val);

	void InitMobSetting(POINT Mobp, int kind);
};