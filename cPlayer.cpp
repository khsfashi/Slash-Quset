#include "cPlayer.h"
extern RECT Camera;

extern CImage g_cimgPlayerLeft;
extern CImage g_cimgPlayerRight;
extern CImage g_cimgPlayerLeftHit;
extern CImage g_cimgPlayerRightHit;

extern CImage g_cimgHeartFull;
extern CImage g_cimgHeartBlank;
extern CImage g_cimgError;
extern CImage g_cimgPlayerDeadLeft;
extern CImage g_cimgPlayerDeadRight;

cPlayer::cPlayer()
{
	pp.x = GAME_WIDTH / 2;
	pp.y = GAME_HEIGHT / 2;
	life = MAX_LIFE;

	angle = 0;
	swordPlace.x = pp.x;
	swordPlace.y = pp.y - 45;
	swordLength = 0;
	hitRect[0].x = swordPlace.x + 30 + 10;
	hitRect[0].y = swordPlace.y - (55 / 4);
	hitRect[1].x = swordPlace.x + 30 + 10;
	hitRect[1].y = swordPlace.y + (55 / 4);
	hitRect[2].x = swordPlace.x + (268 / 2) - 10;
	hitRect[2].y = swordPlace.y + (55 / 4);
	hitRect[3].x = swordPlace.x + (268 / 2);
	hitRect[3].y = (hitRect[0].y + hitRect[1].y) / 2;
	hitRect[4].x = swordPlace.x + (268 / 2) - 10;
	hitRect[4].y = swordPlace.y - (55 / 4);
	Accel = 0;
	Accel_M = 0;
	Accel_Damaged = 0;
	curr_invincible_time = MAX_INVINCIBLE_TIME;
	for (int i = 0; i < POLY; ++i) {
		originHit[i] = hitRect[i];
	}
	lastSwordDirection = dontMove;
	temp_Rad = 0;

	PlayerRect.left = pp.x - 50;
	PlayerRect.top = pp.y - 84;
	PlayerRect.right = pp.x + 26;
	PlayerRect.bottom = pp.y;
	//playerRect[0].x = pp.x - 50;
	//playerRect[0].y = pp.y - 84;
	//playerRect[1].x = pp.x - 50;
	//playerRect[1].y = pp.y;
	//playerRect[2].x = pp.x + 26;
	//playerRect[2].y = pp.y;
	//playerRect[3].x = pp.x + 26;
	//playerRect[3].y = pp.y - 84;
	isCollide = false;
	isExitMap = false;

	//폴리곤
	drawPoly[0] = hitRect[0];
	drawPoly[1] = hitRect[1];
	drawPoly[2].x = hitRect[1].x + 10;
	drawPoly[2].y = hitRect[1].y;
	drawPoly[3].x = drawPoly[2].x;
	drawPoly[3].y = drawPoly[2].y + 10;
	drawPoly[4].x = drawPoly[3].x + 10;
	drawPoly[4].y = drawPoly[3].y;
	drawPoly[5].x = drawPoly[4].x;
	drawPoly[5].y = drawPoly[2].y;
	drawPoly[6] = hitRect[2];
	drawPoly[7] = hitRect[3];
	drawPoly[8] = hitRect[4];
	drawPoly[9].x = drawPoly[0].x + 20;
	drawPoly[9].y = drawPoly[0].y;
	drawPoly[10].x = drawPoly[9].x;
	drawPoly[10].y = drawPoly[9].y - 10;
	drawPoly[11].x = drawPoly[10].x - 10;
	drawPoly[11].y = drawPoly[10].y;
	drawPoly[12].x = drawPoly[0].x + 10;
	drawPoly[12].y = drawPoly[0].y;
	for (int i = 0; i < SWORD; ++i) {
		originPoly[i] = drawPoly[i];
	}
}

cPlayer::~cPlayer()
{
}

void cPlayer::SetInvincibleCheat(bool val)
{
	if (val == TRUE) {
		curr_invincible_time = MAX_INVINCIBLE_TIME - 10;
		isCollide = TRUE;
	}
	else {
		curr_invincible_time = 0;
		isCollide = FALSE;
	}
}

bool cPlayer::MovePlayer(cMap map)
{
	if (isExitMap == FALSE) {
		const int speed = PLAYER_SPEED;
		double rad = angle / 180.f * PI;
		pp.x = (LONG)(pp.x + ((speed + Accel_M) * cos(rad)));
		pp.y = (LONG)(pp.y + ((speed + Accel_M) * sin(rad)));
		swordPlace.x = (LONG)(swordPlace.x + ((speed + Accel_M) * cos(rad)));
		swordPlace.y = (LONG)(swordPlace.y + ((speed + Accel_M) * sin(rad)));
		for (int i = 0; i < POLY; ++i) {
			POINT temp;
			temp.x = (LONG)(hitRect[i].x + ((speed + Accel_M) * cos(rad)));
			temp.y = (LONG)(hitRect[i].y + ((speed + Accel_M) * sin(rad)));
			hitRect[i].x = temp.x;
			hitRect[i].y = temp.y;
			originHit[i].x = (LONG)(originHit[i].x + ((speed + Accel_M) * cos(rad)));
			originHit[i].y = (LONG)(originHit[i].y + ((speed + Accel_M) * sin(rad)));
		}
		for (int i = 0; i < SWORD; ++i) {
			drawPoly[i].x = (LONG)(drawPoly[i].x + ((speed + Accel_M) * cos(rad)));
			drawPoly[i].y = (LONG)(drawPoly[i].y + ((speed + Accel_M) * sin(rad)));
			originPoly[i].x = (LONG)(originPoly[i].x + ((speed + Accel_M) * cos(rad)));
			originPoly[i].y = (LONG)(originPoly[i].y + ((speed + Accel_M) * sin(rad)));
		}

		temp_Rad = rad;
		if (map.IsCollideMap(GetPlayerPoint())) {
			isExitMap = TRUE;
		}
	}

	if ((angle >= 270 && angle <= 360) || (angle >= 0 && angle <= 90)) {
		PlayerRect.left = pp.x - 50;
		PlayerRect.top = pp.y - 84;
		PlayerRect.right = pp.x + 26;
		PlayerRect.bottom = pp.y;
	}
	else {
		PlayerRect.left = pp.x - 30;
		PlayerRect.top = pp.y - 84;
		PlayerRect.right = pp.x + 46;
		PlayerRect.bottom = pp.y;
	}
	Accel_Damaged = 0;
	return TRUE;
}

void cPlayer::AccelMove(cMap map)
{
	if (isExitMap == FALSE) {
		LONG temp_pp_x = pp.x;
		LONG temp_pp_y = pp.y;
		//쳐맞았을때
		pp.x = (LONG)(pp.x + (Accel_Damaged * cos(rad_Damaged)));
		pp.y = (LONG)(pp.y + (Accel_Damaged * sin(rad_Damaged)));
		swordPlace.x = (LONG)(swordPlace.x + (Accel_Damaged * cos(rad_Damaged)));
		swordPlace.y = (LONG)(swordPlace.y + (Accel_Damaged * sin(rad_Damaged)));
		for (int i = 0; i < POLY; ++i) {
			POINT temp;
			temp.x = (LONG)(hitRect[i].x + (Accel_Damaged * cos(rad_Damaged)));
			temp.y = (LONG)(hitRect[i].y + (Accel_Damaged * sin(rad_Damaged)));
			hitRect[i].x = temp.x;
			hitRect[i].y = temp.y;
			originHit[i].x = (LONG)(originHit[i].x + (Accel_Damaged * cos(rad_Damaged)));
			originHit[i].y = (LONG)(originHit[i].y + (Accel_Damaged * sin(rad_Damaged)));
		}

		for (int i = 0; i < SWORD; ++i) {
			drawPoly[i].x = (LONG)(drawPoly[i].x + (Accel_Damaged * cos(rad_Damaged)));
			drawPoly[i].y = (LONG)(drawPoly[i].y + (Accel_Damaged * sin(rad_Damaged)));
			originPoly[i].x = (LONG)(originPoly[i].x + (Accel_Damaged * cos(rad_Damaged)));
			originPoly[i].y = (LONG)(originPoly[i].y + (Accel_Damaged * sin(rad_Damaged)));
		}

		// 미끄러지듯 가는 가속
		double radian = angle / 180.f * PI;;
		pp.x = (LONG)(pp.x + (Accel_M * cos(temp_Rad)));
		pp.y = (LONG)(pp.y + (Accel_M * sin(temp_Rad)));
		swordPlace.x = (LONG)(swordPlace.x + (Accel_M * cos(temp_Rad)));
		swordPlace.y = (LONG)(swordPlace.y + (Accel_M * sin(temp_Rad)));
		for (int i = 0; i < POLY; ++i) {
			POINT temp;
			temp.x = (LONG)(hitRect[i].x + (Accel_M * cos(temp_Rad)));
			temp.y = (LONG)(hitRect[i].y + (Accel_M * sin(temp_Rad)));
			hitRect[i].x = temp.x;
			hitRect[i].y = temp.y;
			originHit[i].x = (LONG)(originHit[i].x + (Accel_M * cos(temp_Rad)));
			originHit[i].y = (LONG)(originHit[i].y + (Accel_M * sin(temp_Rad)));
		}
		for (int i = 0; i < SWORD; ++i) {
			drawPoly[i].x = (LONG)(drawPoly[i].x + (Accel_M * cos(temp_Rad)));
			drawPoly[i].y = (LONG)(drawPoly[i].y + (Accel_M * sin(temp_Rad)));
			originPoly[i].x = (LONG)(originPoly[i].x + (Accel_M * cos(temp_Rad)));
			originPoly[i].y = (LONG)(originPoly[i].y + (Accel_M * sin(temp_Rad)));
		}
		//돌아가는거 가속

		double speed = Accel;
		POINT targetTemp[POLY], polygonTemp[SWORD];
		POINT tempP, temp2Target;
		tempP.x = pp.x + 10;
		tempP.y = pp.y - 40;
		if (lastSwordDirection == left) {
			angle -= (int)(speed);
			if (angle <= 0) {
				//각도를 0도 ~ 360도로 활용. y축이 뒤집어져 있기 때문에 반시계방향으로 돌리면 각도가 감소함.
				angle = 360;
			}
			for (int i = 0; i < POLY; ++i) {
				targetTemp[i].x = originHit[i].x;
				targetTemp[i].y = originHit[i].y;
				//회전변환 공식
				temp2Target.x = (LONG)(((targetTemp[i].x - tempP.x) * cos(radian)) - ((targetTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				temp2Target.y = (LONG)(((targetTemp[i].y - tempP.y) * cos(radian)) + ((targetTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
				hitRect[i].x = temp2Target.x;
				hitRect[i].y = temp2Target.y;
			}

			for (int i = 0; i < SWORD; ++i) {
				polygonTemp[i] = originPoly[i];
				drawPoly[i].x = (LONG)(((polygonTemp[i].x - tempP.x) * cos(radian)) - ((polygonTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				drawPoly[i].y = (LONG)(((polygonTemp[i].y - tempP.y) * cos(radian)) + ((polygonTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
			}
		}


		if (lastSwordDirection == right) {
			angle += (int)(speed);
			if (angle >= 360) {
				//각도를 0도 ~ 360도로 활용. y축이 뒤집어져 있기 때문에 시계방향으로 돌리면 각도가 증가함.
				angle = 0;
			}
			for (int i = 0; i < POLY; ++i) {
				targetTemp[i].x = originHit[i].x;
				targetTemp[i].y = originHit[i].y;
				//회전변환 공식
				temp2Target.x = (LONG)(((targetTemp[i].x - tempP.x) * cos(radian)) - ((targetTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				temp2Target.y = (LONG)(((targetTemp[i].y - tempP.y) * cos(radian)) + ((targetTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
				hitRect[i].x = temp2Target.x;
				hitRect[i].y = temp2Target.y;
			}
			for (int i = 0; i < SWORD; ++i) {
				polygonTemp[i] = originPoly[i];
				drawPoly[i].x = (LONG)(((polygonTemp[i].x - tempP.x) * cos(radian)) - ((polygonTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				drawPoly[i].y = (LONG)(((polygonTemp[i].y - tempP.y) * cos(radian)) + ((polygonTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
			}
		}
		if ((angle >= 270 && angle <= 360) || (angle >= 0 && angle <= 90)) {
			PlayerRect.left = pp.x - 50;
			PlayerRect.top = pp.y - 84;
			PlayerRect.right = pp.x + 26;
			PlayerRect.bottom = pp.y;
		}
		else {
			PlayerRect.left = pp.x - 30;
			PlayerRect.top = pp.y - 84;
			PlayerRect.right = pp.x + 46;
			PlayerRect.bottom = pp.y;
		}

		if (map.IsCollideMap(GetPlayerPoint())) {
			isExitMap = TRUE;
		}
	}
}

void cPlayer::RotateSword(Direction dir)
{
	if (isExitMap == FALSE) {
		//칼 돌리는 함수
		double speed = PLAYER_SPEED + Accel;
		double radian = angle / 180.f * PI;;
		POINT targetTemp[POLY], polygonTemp[SWORD];
		POINT tempP, temp2Target;
		tempP.x = pp.x + 20;
		tempP.y = pp.y + 20;
		lastSwordDirection = dir;
		if (dir == left) {
			angle -= (int)(speed);
			if (angle <= 0) {
				//각도를 0도 ~ 360도로 활용. y축이 뒤집어져 있기 때문에 반시계방향으로 돌리면 각도가 감소함.
				angle = 360;
			}
			for (int i = 0; i < POLY; ++i) {
				targetTemp[i].x = originHit[i].x;
				targetTemp[i].y = originHit[i].y;
				//회전변환 공식
				temp2Target.x = (LONG)(((targetTemp[i].x - tempP.x) * cos(radian)) - ((targetTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				temp2Target.y = (LONG)(((targetTemp[i].y - tempP.y) * cos(radian)) + ((targetTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
				hitRect[i].x = temp2Target.x;
				hitRect[i].y = temp2Target.y;
			}
			for (int i = 0; i < SWORD; ++i) {
				polygonTemp[i] = originPoly[i];
				drawPoly[i].x = (LONG)(((polygonTemp[i].x - tempP.x) * cos(radian)) - ((polygonTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				drawPoly[i].y = (LONG)(((polygonTemp[i].y - tempP.y) * cos(radian)) + ((polygonTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
			}
		}
		if (dir == right) {
			angle += (int)(speed);
			if (angle >= 360) {
				//각도를 0도 ~ 360도로 활용. y축이 뒤집어져 있기 때문에 시계방향으로 돌리면 각도가 증가함.
				angle = 0;
			}
			for (int i = 0; i < POLY; ++i) {
				targetTemp[i].x = originHit[i].x;
				targetTemp[i].y = originHit[i].y;
				//회전변환 공식
				temp2Target.x = (LONG)(((targetTemp[i].x - tempP.x) * cos(radian)) - ((targetTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				temp2Target.y = (LONG)(((targetTemp[i].y - tempP.y) * cos(radian)) + ((targetTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
				hitRect[i].x = temp2Target.x;
				hitRect[i].y = temp2Target.y;
			}
			for (int i = 0; i < SWORD; ++i) {
				polygonTemp[i] = originPoly[i];
				drawPoly[i].x = (LONG)(((polygonTemp[i].x - tempP.x) * cos(radian)) - ((polygonTemp[i].y - tempP.y) * sin(radian)) + tempP.x);
				drawPoly[i].y = (LONG)(((polygonTemp[i].y - tempP.y) * cos(radian)) + ((polygonTemp[i].x - tempP.x) * sin(radian)) + tempP.y);
			}
		}
	}

}

void cPlayer::Acceleration(int i)
{
	if (i == 0) {
		if (Accel_M < 4) {
			Accel_M += 0.2;
		}
	}
	else if (i == 1) {
		if (Accel < 4) {
			Accel += 0.2;
		}
	}
}

void cPlayer::Deceleration(int i)
{
	if (i == 0) {
		if (Accel_M > 0) {
			Accel_M -= 0.1;
		}
		else Accel_M = 0;
		if (Accel_Damaged > 0) {
			Accel_Damaged -= 0.1;
		}
		else Accel_Damaged = 0;
	}
	else if (i == 1) {
		if (Accel > 0) {
			Accel -= 0.3;
		}
		else {
			Accel = 0;
		}
	}
}

void cPlayer::damaged(double rad) {
	if (isCollide == false) {
		if (life > 0) {
			life--;
		}
		isCollide = true;
		Accel_Damaged = 8;
		rad_Damaged = rad;
		curr_invincible_time = MAX_INVINCIBLE_TIME;
	}

}

const POINT& cPlayer::GetPlayerPoint()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return pp;
}

void cPlayer::SetPlayerPoint(POINT val)
{
	pp = val;
}

const int& cPlayer::GetPlayerLife()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return life;
}

void cPlayer::SetPlayerLife(int val)
{
	life = val;
}

const RECT& cPlayer::GetPlayerRect()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return PlayerRect;
}

const bool& cPlayer::GetIsExitMap()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return isExitMap;
}


void cPlayer::DrawPlayer(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	if (isCollide == true)
		curr_invincible_time--;

	if (curr_invincible_time <= 0) {
		isCollide = false;
		if (is_active_invincible_cheat == true) {
			curr_invincible_time = MAX_INVINCIBLE_TIME - 10;
			isCollide = true;
		}
	}

	// 검 그리기
	RECT rt = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	// 캐릭터 그리기
	// 캐릭터 오른쪽 보기 75 x 84
	//HBITMAP hBit1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER1));
	//HDC MemDC1 = CreateCompatibleDC(hDC);
	//HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);
	//// 캐릭터 왼쪽 보기 75 x 84
	//HBITMAP hBit2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER2));
	//HDC MemDC2 = CreateCompatibleDC(hDC);
	//HBITMAP oldBit2 = (HBITMAP)SelectObject(MemDC2, hBit2);

	// 그림자 그리기 45 x 26
	//static HBITMAP hBit3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_SHADOW));
	//static HDC MemDC3 = CreateCompatibleDC(hDC);
	//static HBITMAP oldBit3 = (HBITMAP)SelectObject(MemDC3, hBit3);

	//TransparentBlt(hDC, pp.x - 23, pp.y - 13, 46, 26, MemDC3, 0, 0, 45, 26, RGB(24, 52, 71));

	if (angle >= 270 || angle <= 90) {
		if (life > 0) {
			// 피격중일 때
			if (isCollide == TRUE) {
				if (MAX_INVINCIBLE_TIME - curr_invincible_time < 10) {
					g_cimgPlayerRightHit.SetTransparentColor((RGB(255, 0, 255)));
					g_cimgPlayerRightHit.Draw(hDC, pp.x - 50, pp.y - 84, 76, 84);
				}
				else if (((curr_invincible_time / 5) & 1) == 0) {
					// Nothing
				}
				else {
					g_cimgPlayerRight.SetTransparentColor((RGB(0, 255, 0)));
					g_cimgPlayerRight.Draw(hDC, pp.x - 50, pp.y - 84, 76, 84);
				}
			}
			// 평상시
			else {
			g_cimgPlayerRight.SetTransparentColor((RGB(0, 255, 0)));
			g_cimgPlayerRight.Draw(hDC, pp.x - 50, pp.y - 84, 76, 84);
			}
		}
		else {
			g_cimgPlayerDeadRight.SetTransparentColor(RGB(255, 0, 0));
			g_cimgPlayerDeadRight.Draw(hDC, pp.x - 48, pp.y - 76, 96, 76);
		}
		//TransparentBlt(hDC, pp.x-50, pp.y-84, 76, 84, MemDC1, 0, 0, 75, 84, RGB(0, 255, 0));
	}
	else {
		if (life > 0) {
			// 피격중일 때
			if (isCollide == TRUE) {
				if (MAX_INVINCIBLE_TIME - curr_invincible_time < 10) {
					g_cimgPlayerLeftHit.SetTransparentColor((RGB(255, 0, 255)));
					g_cimgPlayerLeftHit.Draw(hDC, pp.x - 25, pp.y - 84, 76, 84);
				}
				else if (((curr_invincible_time / 5) & 1) == 0) {
					// Nothing
				}
				else {
					g_cimgPlayerLeft.SetTransparentColor((RGB(0, 255, 0)));
					g_cimgPlayerLeft.Draw(hDC, pp.x - 25, pp.y - 84, 76, 84);
				}
			}
			// 평상시
			else {
				g_cimgPlayerLeft.SetTransparentColor((RGB(0, 255, 0)));
				g_cimgPlayerLeft.Draw(hDC, pp.x - 25, pp.y - 84, 76, 84);
			}
		}
		else {
			// 95x75
			g_cimgPlayerDeadLeft.SetTransparentColor(RGB(255, 0, 0));
			g_cimgPlayerDeadLeft.Draw(hDC, pp.x - 48, pp.y - 76, 96, 76);
		}
		//TransparentBlt(hDC, pp.x-25, pp.y-84, 76, 84, MemDC2, 0, 0, 75, 84, RGB(0, 255, 0));
	}

	const int sz = 3;
	//Ellipse(hDC, pp.x - sz, pp.y - sz, pp.x + sz, pp.y + sz);

	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(RGB(135, 135, 135));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 5, RGB(135, 135, 135));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	/*for (int i = 0; i < POLY; ++i) {
	   if (i == POLY - 1) {
		  MoveToEx(hDC, (int)hitRect[i].x, (int)hitRect[i].y, NULL);
		  LineTo(hDC, (int)hitRect[0].x, (int)hitRect[0].y);
	   }
	   else {
		  MoveToEx(hDC, (int)hitRect[i].x, (int)hitRect[i].y, NULL);
		  LineTo(hDC, (int)hitRect[i + 1].x, (int)hitRect[i + 1].y);
	   }
	}*/
	Polygon(hDC, drawPoly, SWORD);
	//Rectangle(hDC, PlayerRect.left, PlayerRect.top, PlayerRect.right, PlayerRect.bottom);
	SelectObject(hDC, oldPen);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	//SelectObject(MemDC1, oldBit1);
	//DeleteObject(hBit1);
	//DeleteDC(MemDC1);
	//SelectObject(MemDC2, oldBit2);
	//DeleteObject(hBit2);
	//DeleteDC(MemDC2);

	// 추락 느낌표 출력
	if (isExitMap == true) {
		static POINT setpp = { pp.x, pp.y };
		g_cimgError.SetTransparentColor((RGB(0, 0, 0)));
		g_cimgError.Draw(hDC, setpp.x - 100, setpp.y - 84, 100, 100);
	}
}


void cPlayer::DrawLife(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	//HBITMAP hBit1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_HEART));
	// HDC MemDC1 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);

	// HBITMAP hBit2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_FULLHEART));
	// HDC MemDC2 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit2 = (HBITMAP)SelectObject(MemDC2, hBit2);

	// 라이프 수 만큼 37 x 30 비트맵 크기 그리기
	// 사각형의 왼쪽위 점
	POINT HeartP[MAX_LIFE] = {
	   {Camera.left + 37, Camera.top + 30},
	   {Camera.left + 37 * 2 + 15, Camera.top + 30},
	   {Camera.left + 37 * 3 + 30, Camera.top + 30},
	   {Camera.left + 37 * 4 + 45, Camera.top + 30},
	   {Camera.left + 37 * 5 + 60, Camera.top + 30}
	};
	for (int i = 0; i < life; ++i) {
		//BitBlt(hDC, HeartP[i].x, HeartP[i].y, 37, 30, MemDC2, 0, 0, SRCCOPY);
		//TransparentBlt(hDC, HeartP[i].x, HeartP[i].y, 37, 30, MemDC2, 0, 0, 37, 30, RGB(255, 255, 255));
		g_cimgHeartFull.SetTransparentColor(RGB(0, 0, 0));
		g_cimgHeartFull.Draw(hDC, HeartP[i].x, HeartP[i].y, 37, 30);
	}
	for (int i = life; i < MAX_LIFE; ++i) {
		//   BitBlt(hDC, HeartP[i].x, HeartP[i].y, 37, 30, MemDC1, 0, 0, SRCCOPY);
		   //TransparentBlt(hDC, HeartP[i].x, HeartP[i].y, 37, 30, MemDC1, 0, 0, 37, 30, RGB(255, 255, 255));
		g_cimgHeartBlank.SetTransparentColor(RGB(0, 0, 0));
		g_cimgHeartBlank.Draw(hDC, HeartP[i].x, HeartP[i].y, 37, 30);
	}

	//SelectObject(MemDC2, oldBit2);
	//DeleteObject(hBit2);
	//DeleteDC(MemDC2);

	//SelectObject(MemDC1, oldBit1);
	//DeleteObject(hBit1);
	//DeleteDC(MemDC1);
}

void Rotate(LONG* nx, LONG* ny, float tx, float ty, float cx, float cy, float q)
{
	double cosq = cos(q), sinq = sin(q);

	// 회전중심점 C가 원점  O와 일치하도록 회전할 점 T를 함께 평행이동
	tx -= cx, ty -= cy;

	// 원점 O에 대하여 회전할 점 T를 q라디안 만큼 회전
	double temp;
	temp = tx * cosq - ty * sinq;
	*nx = (LONG)temp;
	temp = ty * cosq + tx * sinq;
	*ny = (LONG)temp;

	// 원점 O가 원래의 회전 중심점 C와 일치하도록 회전된 점 N과 함께 이동
	*nx += (LONG)cx, * ny += (LONG)cy;
}

void cPlayer::interSectObj(RECT rt) {
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &PlayerRect, &rt)) {
		SetRect(&rcTemp, 0, 0,
			rcTemp.right - rcTemp.left,
			rcTemp.bottom - rcTemp.top);

		if (rcTemp.right > rcTemp.bottom) {
			if ((PlayerRect.bottom + PlayerRect.top) / 2
				< (rt.bottom + rt.top) / 2)
			{
				pp.y -= rcTemp.bottom;
				swordPlace.y -= rcTemp.bottom;
				for (int i = 0; i < POLY; ++i) {
					hitRect[i].y -= rcTemp.bottom;
					originHit[i].y -= rcTemp.bottom;
				}
				for (int i = 0; i < SWORD; ++i) {
					drawPoly[i].y -= rcTemp.bottom;
					originPoly[i].y -= rcTemp.bottom;
				}
			}
			else
			{
				pp.y += rcTemp.bottom;
				swordPlace.y += rcTemp.bottom;
				for (int i = 0; i < POLY; ++i) {
					hitRect[i].y += rcTemp.bottom;
					originHit[i].y += rcTemp.bottom;
				}
				for (int i = 0; i < SWORD; ++i) {
					drawPoly[i].y += rcTemp.bottom;
					originPoly[i].y += rcTemp.bottom;
				}
			}
		}
		else {
			if ((PlayerRect.right + PlayerRect.left) / 2
				< (rt.right + rt.left) / 2)
			{
				pp.x -= rcTemp.right;
				swordPlace.x -= rcTemp.right;
				for (int i = 0; i < POLY; ++i) {
					hitRect[i].x -= rcTemp.right;
					originHit[i].x -= rcTemp.right;
				}
				for (int i = 0; i < SWORD; ++i) {
					drawPoly[i].x -= rcTemp.right;
					originPoly[i].x -= rcTemp.right;
				}
			}
			else {
				pp.x += rcTemp.right;
				swordPlace.x += rcTemp.right;
				for (int i = 0; i < POLY; ++i) {
					hitRect[i].x += rcTemp.right;
					originHit[i].x += rcTemp.right;
				}
				for (int i = 0; i < SWORD; ++i) {
					drawPoly[i].x += rcTemp.right;
					originPoly[i].x += rcTemp.right;
				}
			}
		}
	}
}

bool cPlayer::interRect(double left, double top, double right, double bottom) {
	//검과 오브젝트의 충돌
	//오브젝트의 히트박스의 left, top, right, bottom값을 받아와 true/false를 리턴한다.

	vector2 leftV = vector2(left, bottom), topV = vector2(left, top), rightV = vector2(right, top), bottomV = vector2(right, bottom);
	vector2 hit0 = vector2(hitRect[0].x, hitRect[0].y), hit1 = vector2(hitRect[1].x, hitRect[1].y), hit2 = vector2(hitRect[2].x, hitRect[2].y),
		hit3 = vector2(hitRect[3].x, hitRect[3].y), hit4 = vector2(hitRect[4].x, hitRect[4].y);

	if (sementIntersects(leftV, topV, hit0, hit1) == 1) {
		return true;
	}
	else if (sementIntersects(leftV, topV, hit1, hit2)) {
		return true;
	}
	else if (sementIntersects(leftV, topV, hit2, hit3)) {
		return true;
	}
	else if (sementIntersects(leftV, topV, hit3, hit4)) {
		return true;
	}
	else if (sementIntersects(leftV, topV, hit0, hit4)) {
		return true;
	}
	else if (sementIntersects(topV, rightV, hit0, hit1)) {
		return true;
	}
	else if (sementIntersects(topV, rightV, hit1, hit2)) {
		return true;
	}
	else if (sementIntersects(topV, rightV, hit2, hit3)) {
		return true;
	}
	else if (sementIntersects(topV, rightV, hit3, hit4)) {
		return true;
	}
	else if (sementIntersects(topV, rightV, hit0, hit4)) {
		return true;
	}
	else if (sementIntersects(rightV, bottomV, hit0, hit1)) {
		return true;
	}
	else if (sementIntersects(rightV, bottomV, hit1, hit2)) {
		return true;
	}
	else if (sementIntersects(rightV, bottomV, hit2, hit3)) {
		return true;
	}
	else if (sementIntersects(rightV, bottomV, hit3, hit4)) {
		return true;
	}
	else if (sementIntersects(rightV, bottomV, hit0, hit4)) {
		return true;
	}
	else if (sementIntersects(leftV, bottomV, hit0, hit1)) {
		return true;
	}
	else if (sementIntersects(leftV, bottomV, hit1, hit2)) {
		return true;
	}
	else if (sementIntersects(leftV, bottomV, hit2, hit3)) {
		return true;
	}
	else if (sementIntersects(leftV, bottomV, hit3, hit4)) {
		return true;
	}
	else if (sementIntersects(leftV, bottomV, hit0, hit4)) {
		return true;
	}
	else return false;
}

int cPlayer::DropPlayer()
{
	static int cnt = 0;
	static bool isfall = true;
	int temp = 0;
	if (cnt > 50 && isfall) {
		angle = 90;
		const int speed = PLAYER_SPEED * 5;
		double rad = angle / 180.f * PI;
		pp.x = (LONG)(pp.x + ((speed + Accel_M) * cos(rad)));
		pp.y = (LONG)(pp.y + ((speed + Accel_M) * sin(rad)));
		swordPlace.x = (LONG)(swordPlace.x + ((speed + Accel_M) * cos(rad)));
		swordPlace.y = (LONG)(swordPlace.y + ((speed + Accel_M) * sin(rad)));
		for (int i = 0; i < POLY; ++i) {
			POINT temp;
			temp.x = (LONG)(hitRect[i].x + ((speed + Accel_M) * cos(rad)));
			temp.y = (LONG)(hitRect[i].y + ((speed + Accel_M) * sin(rad)));
			hitRect[i].x = temp.x;
			hitRect[i].y = temp.y;
			originHit[i].x = (LONG)(originHit[i].x + ((speed + Accel_M) * cos(rad)));
			originHit[i].y = (LONG)(originHit[i].y + ((speed + Accel_M) * sin(rad)));
		}
		temp_Rad = rad;
		if (life != 0 && pp.y >= 1080) {
			life = 0;
			if (pp.x < 640) {
				temp = 640;
			}
			else if (pp.x > 1920) {
				temp = 1920;
			}
			else {
				temp = pp.x;
			}
			static POINT stop_pp = { temp, 1080 };
			Camera.left = stop_pp.x - CLIENT_WIDTH / 2;
			Camera.top = stop_pp.y - CLIENT_HEIGHT / 2;
			Camera.right = Camera.left + CLIENT_WIDTH;
			Camera.bottom = Camera.top + CLIENT_HEIGHT;
		}
		if (pp.y >= 2000) {
			isfall = false;
		}
	}
	else
		cnt++;
	return cnt;
}

void cPlayer::DyingPlayer()
{
	static POINT stop_pp = { pp.x, pp.y };
	Camera.left = stop_pp.x - CLIENT_WIDTH / 2;
	Camera.top = stop_pp.y - CLIENT_HEIGHT / 2;
	Camera.right = Camera.left + CLIENT_WIDTH;
	Camera.bottom = Camera.top + CLIENT_HEIGHT;

	Accel_Damaged = 0;
	rad_Damaged = 0;
}

bool cPlayer::interRectPlayer(double left, double top, double right, double bottom) {
	if (left < PlayerRect.right && top < PlayerRect.bottom && right > PlayerRect.left && bottom > PlayerRect.top) {
		return true;
	}
	else return false;
}

void cPlayer::increaseSword() {
	if (swordLength < 10) {
		double rad = angle / 180.f * PI;
		swordLength++;
		for (int i = 2; i < POLY; ++i) {
			hitRect[i].x = (LONG)(hitRect[i].x + ((10) * cos(rad)));
			hitRect[i].y = (LONG)(hitRect[i].y + ((10) * sin(rad)));
			originHit[i].x += 10;
		}
		for (int i = 6; i < 9; ++i) {
			drawPoly[i].x = (LONG)(drawPoly[i].x + (10 * cos(rad)));
			drawPoly[i].y = (LONG)(drawPoly[i].y + (10 * sin(rad)));
			originPoly[i].x += 10;
		}
	}
}

void cPlayer::decreaseSword() {
	double rad = angle / 180.f * PI;
	if (swordLength > 0) {
		swordLength--;
		for (int i = 2; i < POLY; ++i) {
			hitRect[i].x = (LONG)(hitRect[i].x - ((10) * cos(rad)));
			hitRect[i].y = (LONG)(hitRect[i].y - ((10) * sin(rad)));
			originHit[i].x -= 10;
		}
		for (int i = 6; i < 9; ++i) {
			drawPoly[i].x = (LONG)(drawPoly[i].x - (10 * cos(rad)));
			drawPoly[i].y = (LONG)(drawPoly[i].y - (10 * sin(rad)));
			originPoly[i].x -= 10;
		}
	}
	if (lastSwordDirection == left) {
		angle += 20;
	}
	else if (lastSwordDirection == right) {
		angle -= 20;
	}
	rad = angle / 180.f * PI;
	POINT targetTemp[POLY], polygonTemp[SWORD];
	POINT tempP, temp2Target;
	tempP.x = pp.x + 10;
	tempP.y = pp.y - 40;
	for (int i = 0; i < POLY; ++i) {
		targetTemp[i].x = originHit[i].x;
		targetTemp[i].y = originHit[i].y;
		//회전변환 공식
		temp2Target.x = (LONG)(((targetTemp[i].x - tempP.x) * cos(rad)) - ((targetTemp[i].y - tempP.y) * sin(rad)) + tempP.x);
		temp2Target.y = (LONG)(((targetTemp[i].y - tempP.y) * cos(rad)) + ((targetTemp[i].x - tempP.x) * sin(rad)) + tempP.y);
		hitRect[i].x = temp2Target.x;
		hitRect[i].y = temp2Target.y;
	}
	for (int i = 0; i < SWORD; ++i) {
		polygonTemp[i] = originPoly[i];
		drawPoly[i].x = (LONG)(((polygonTemp[i].x - tempP.x) * cos(rad)) - ((polygonTemp[i].y - tempP.y) * sin(rad)) + tempP.x);
		drawPoly[i].y = (LONG)(((polygonTemp[i].y - tempP.y) * cos(rad)) + ((polygonTemp[i].x - tempP.x) * sin(rad)) + tempP.y);
	}
}

void cPlayer::bossHit() {
	double rad = angle / 180.f * PI;
	if (lastSwordDirection == left) {
		angle += 20;
	}
	else if (lastSwordDirection == right) {
		angle -= 20;
	}
	rad = angle / 180.f * PI;
	POINT targetTemp[POLY], polygonTemp[SWORD];
	POINT tempP, temp2Target;
	tempP.x = pp.x + 10;
	tempP.y = pp.y - 40;
	for (int i = 0; i < POLY; ++i) {
		targetTemp[i].x = originHit[i].x;
		targetTemp[i].y = originHit[i].y;
		//회전변환 공식
		temp2Target.x = (LONG)(((targetTemp[i].x - tempP.x) * cos(rad)) - ((targetTemp[i].y - tempP.y) * sin(rad)) + tempP.x);
		temp2Target.y = (LONG)(((targetTemp[i].y - tempP.y) * cos(rad)) + ((targetTemp[i].x - tempP.x) * sin(rad)) + tempP.y);
		hitRect[i].x = temp2Target.x;
		hitRect[i].y = temp2Target.y;
	}
	for (int i = 0; i < SWORD; ++i) {
		polygonTemp[i] = originPoly[i];
		drawPoly[i].x = (LONG)(((polygonTemp[i].x - tempP.x) * cos(rad)) - ((polygonTemp[i].y - tempP.y) * sin(rad)) + tempP.x);
		drawPoly[i].y = (LONG)(((polygonTemp[i].y - tempP.y) * cos(rad)) + ((polygonTemp[i].x - tempP.x) * sin(rad)) + tempP.y);
	}
}