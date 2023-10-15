#pragma once
#include "Manager.h"
#include "cMap.h"
#include "vectorLine.h"

#define PLAYER_SPEED 5
#define POLY 5
#define MAX_LIFE 5
#define SWORD 13
#define MAX_INVINCIBLE_TIME 200


enum Direction {
	dontMove = 0,
	right,
	left,
	up,
	down
};

enum PlayerStatus {
	PLAYER_ACTIVE = 0,
	PLAYER_FALL_START,
	PLAYER_FALLING
};

//ȸ�� �Լ� ����

// ȸ������� : tx // ȸ���߽��� : cx // ȸ�������� : nx // ���� : q
void Rotate(LONG* nx, LONG* ny, float tx, float ty, float cx, float cy, float q);

class cPlayer {
private:
	POINT pp; // �÷��̾� �ٸ� ��ġ(�׸��� �߾�)
	int life; // ���� ������
	int swordLength;	//Į����

	POINT swordPlace;
	POINT hitRect[POLY];
	POINT originHit[POLY];
	POINT originPoly[SWORD];
	POINT drawPoly[SWORD];
	Direction lastSwordDirection;

	double temp_Rad;
	double rad_Damaged;

	int angle;

	double Accel;
	double Accel_M;
	double Accel_Damaged;
	int curr_invincible_time; // ���� �����ð�

	RECT PlayerRect;
	bool isCollide; // �÷��̾�� ���浹�Ƴ�?
	bool isExitMap; // �÷��̾ ��Ż���߳� ?

public:
	cPlayer();
	~cPlayer();
public:
	void SetInvincibleCheat(bool val);
public:
	PlayerStatus player_stat = PLAYER_ACTIVE;
	bool is_active_invincible_cheat = FALSE;
public:
	bool MovePlayer(cMap map); // ������ ������
	void AccelMove(cMap map); // �̲������� ���� ����
	void RotateSword(Direction dir);
	void Acceleration(int i);
	void Deceleration(int i);
	void damaged(double rad);
	void increaseSword();
	void decreaseSword();
	void bossHit();
	void interSectObj(RECT);
	bool interRect(double left, double top, double right, double bottom);
	bool interRectPlayer(double left, double top, double right, double bottom);
	int DropPlayer();
	void DyingPlayer();
public:
	const POINT& GetPlayerPoint();
	void SetPlayerPoint(POINT val);
	const int& GetPlayerLife();
	void SetPlayerLife(int val);
	const RECT& GetPlayerRect();
	const bool& GetIsExitMap();
public:
	void DrawPlayer(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawLife(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
};