#pragma once
#include "Manager.h"

// enum OBJ_STAT { OBJ_NULL, OBJ_SPAWNING, OBJ_ACTIVE, OBJ_DYING, OBJ_DEAD };


class cObj {
private:
	POINT op;   //Object Position 오브젝트 좌표
	bool isSummon;
	int objKind;   //1 = obj1, 2 = obj2, 3 = obj3, 4 = helmet
	POINT size;   //obj size
	RECT ObjRect;
	OBJ_STAT stat_;
	int hp;
	int spawning_cnt;
public:
	cObj();
	~cObj();
public:
	void drawObj(HDC);

	void InitObjSetting(POINT ObjP, int kind);
	void turnIsSummon();
public:
	bool ObjSpawning(HDC hDC); // 스폰중 (착지중)
public:
	const RECT& GetObjRect();
	const bool& GetObjisSummon();
	const OBJ_STAT& GetObjStat();
	const int& GetHp();
public:
	void SetObjStat(OBJ_STAT val);
	void SetHp(int val);
};