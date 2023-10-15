#pragma once
#include "Manager.h"
#include "cMap.h"
#define BULLET 3

struct sBullet {
	POINT bp;   //Bullet Position 총알 위치
	bool isShoot;
	double rad;
};

class cMonster {
private:
	POINT mp;   //Monster Position 애새기 위치
	RECT MonsterRect;
	double M_angle;   //몬스터가 주인공을 향해 바라보고 있는 각도
	double chargeRad;
	bool isDie;   //죽었니?
	bool isSummon;   //소환됐니?
	bool isAttack;   //공격하니?
	bool isRage; // 보스 분노

	sBullet bullet[BULLET];

	int monsterKind;   //몬스터 종류
	int deathCnt;      //죽고나서 시간지나면 시체 사라지게할 카운트
	int patternCnt;      //패턴이 실행되는 시간
	int SpawnCnt; // 스폴될때 걸리는 시간
	int MaxSpawnCnt;
	int objNum;
	int removeObj;
	int hp;      //보스 체력

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
	void turnShoot(int);   //총알 캐릭터가 맞은거 사라지게 하려고.
	void pointHandle(LONG, LONG);
	bool returnDie();
	void setObjNum(int num);   //2번몹 뒤질때 오브젝트 놓은거 번호 저장하는용도 ㅅㅂ
	void removeObj2Zero();
	void bossHit();   //보스가 맞았을때
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
	const int& GetObjNum();   //2번몹 오브젝트 몇번에다가 저장했는지 알려고,,
	const int& GetRemoveObj();   //2번몹 시발년 오브젝트 사라질 때가 됐는지 안 됐는지 확인하려고
	const int& GetBossHp();

	void SetBossHp(int val);

	void InitMobSetting(POINT Mobp, int kind);
};