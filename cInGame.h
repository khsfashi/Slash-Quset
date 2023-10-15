#pragma once

#ifndef __INGAME_H__
#define __INGAME_H__

#include "Manager.h"
#include "cMonster.h"
#include "cPlayer.h"
#include "cObj.h"

#define MAX_CLEAR_CNT 200

enum CAMERA_STATE {
	CAMERA_NORMAL = 0,
	CAMERA_START_SHAKE,
	CAMERA_SHAKING,
	CAMERA_START_STUMP,
	CAMERA_STUMPING,
};

enum GAME_END_STATE {
	GAME_ACTIVE = 0,
	GAME_PRE_END,
	GAME_END,
};

class cInGame {
private: // cInGame 클래스 내부에서만 접근 가능
	CURR_STAGE curr;
	CURR_STAGE temp_curr;

	CAMERA_STATE camera_stat;

	cMonster* MobList;
	int currMob;
	int MaxMob;

	cObj* objList;
	int currObj;
	int maxObj;

	GAME_END_STATE game_end_state;
public:
	cInGame();
	~cInGame();
public:
	const CURR_STAGE& GetStage();
	void SetStage(CURR_STAGE val);
	const int& GetCurrMobNum();
	const int& GetMaxMobNum();
	void SetCurrMobNum(int n);

	const GAME_END_STATE& GetGameEndState();
	void SetGameEndState(GAME_END_STATE val);

	const cMonster& GetMob(int i);
public:
	void InitStage1(POINT pp);
	void InitStage2();
	void InitStage3();
	void InitStage4();
	void InitStage5();

	void DelStage1();
	void DelStage2();
	void DelStage3();
	void DelStage4();
	void DelStage5();

	void SpawnManage(POINT pp);
	void MoveMonster(cPlayer& p);
	void checkObj(cPlayer& p);
public: // 외부에서도 접근 가능
	void DrawStage(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawStage1(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawStage2(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawStage3(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawStage4(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawStage5(HDC hDC, HWND hWnd, HINSTANCE g_hInst);

	void DrawChangeStage(HDC hDC, HWND hWnd, HINSTANCE g_hInst);

	void DrawDead(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawDeadEnd(HDC hDC, HWND hWnd, HINSTANCE g_hInst);

	void DrawPrepareEnding(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawEnding(HDC hDC, HWND hWnd, HINSTANCE g_hInst);

	void DrawMob(HDC hDC,HINSTANCE g_hInst);
	void DrawObj(HDC hDC);

	void ShakeCamera();

public:
	bool active_kill_cheat = FALSE;
};

#endif // !__INGAME_H__