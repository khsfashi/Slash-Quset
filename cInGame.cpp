#include "cInGame.h"

extern RECT Camera;

extern CImage g_cimgPlayerDeadBG;

extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern DWORD dwID[MAX_SOUND_SIZE];

extern cMap Map;
extern cPlayer Player;

std::uniform_int_distribution<int> MobSpawnRandom(0, 9);

cInGame::cInGame()
{
	curr = CURR_NULL;
	currMob = 0;
	MaxMob = 0;
	maxObj = 0;
	currObj = 0;
	game_end_state = GAME_ACTIVE;
	temp_curr = CURR_NULL;
	camera_stat = CAMERA_NORMAL;
}

cInGame::~cInGame()
{
}

const CURR_STAGE& cInGame::GetStage()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return curr;
}

void cInGame::SetStage(CURR_STAGE val)
{
	curr = val;
}

const int& cInGame::GetCurrMobNum()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return currMob;
}

const int& cInGame::GetMaxMobNum()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return MaxMob;
}

void cInGame::SetCurrMobNum(int n)
{
	currMob = n;
	currObj = n;
}

const GAME_END_STATE& cInGame::GetGameEndState()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return game_end_state;
}

void cInGame::SetGameEndState(GAME_END_STATE val)
{
	game_end_state = val;
}

const cMonster& cInGame::GetMob(int i)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return MobList[i];
}

void cInGame::InitStage1(POINT pp)
{
	currMob = 15;
	MaxMob = currMob;
	MobList = new cMonster[MaxMob];
	for (int i = 0; i < MaxMob; ++i) {
		POINT mp;
		//int range1 = MobRange(dre);
		//int range2 = MobRange(dre);
		mp.x = 0;
		mp.y = 0;
		//mp.x = GAME_WIDTH / 2 + range1;
		//mp.y = GAME_HEIGHT / 2 + range2;

		//double lenVec = sqrt((pp.x - mp.x) * (pp.x - mp.x)
		//   + (pp.y - mp.y) * (pp.y - mp.y));
		//if (Map.IsCollideMap(mp) == TRUE) {
		//   i--;
		//   continue;
		//}
		//else if (lenVec < 400) {
		//   i--;
		//   continue;
		//}
		MobList[i].InitMobSetting(mp, 1);
	}

	maxObj = 20;
	objList = new cObj[maxObj];
	for (int i = 0; i < maxObj; ++i) {
		POINT mp = { 0,0 };
		objList[i].InitObjSetting(mp, 1);
	}
}

void cInGame::InitStage2()
{
	int max_mob1_size = 15;
	int max_mob2_size = 10;

	currMob = 25;
	MaxMob = currMob;
	MobList = new cMonster[MaxMob];
	for (int i = 0; i < MaxMob; ++i) {
		POINT mp;
		//int range1 = MobRange(dre);
		//int range2 = MobRange(dre);
		mp.x = 0;
		mp.y = 0;
		//mp.x = GAME_WIDTH / 2 + range1;
		//mp.y = GAME_HEIGHT / 2 + range2;

		//double lenVec = sqrt((pp.x - mp.x) * (pp.x - mp.x)
		//   + (pp.y - mp.y) * (pp.y - mp.y));
		//if (Map.IsCollideMap(mp) == TRUE) {
		//   i--;
		//   continue;
		//}
		//else if (lenVec < 400) {
		//   i--;
		//   continue;
		//}
		if (i < max_mob2_size) {
			MobList[i].InitMobSetting(mp, 2);
		}
		else
			MobList[i].InitMobSetting(mp, 1);
	}

	maxObj = 25;
	objList = new cObj[maxObj];
	for (int i = 0; i < maxObj; ++i) {
		POINT mp = { 0,0 };
		if (i < max_mob2_size) {
			objList[i].InitObjSetting(mp, 2);
		}
		else
			objList[i].InitObjSetting(mp, 1);
	}
}

void cInGame::InitStage3()
{
	int max_mob1_size = 30;
	int max_mob2_size = 5;
	int max_mob3_size = 5;

	currMob = 40;
	MaxMob = currMob;
	MobList = new cMonster[MaxMob];
	for (int i = 0; i < MaxMob; ++i) {
		POINT mp;
		//int range1 = MobRange(dre);
		//int range2 = MobRange(dre);
		mp.x = 0;
		mp.y = 0;
		//mp.x = GAME_WIDTH / 2 + range1;
		//mp.y = GAME_HEIGHT / 2 + range2;

		//double lenVec = sqrt((pp.x - mp.x) * (pp.x - mp.x)
		//   + (pp.y - mp.y) * (pp.y - mp.y));
		//if (Map.IsCollideMap(mp) == TRUE) {
		//   i--;
		//   continue;
		//}
		//else if (lenVec < 400) {
		//   i--;
		//   continue;
		//}
		if (i < max_mob1_size) {
			MobList[i].InitMobSetting(mp, 1);
		}
		else if (max_mob1_size <= i && i < max_mob1_size + max_mob2_size) {
			MobList[i].InitMobSetting(mp, 2);
		}
		else if (max_mob1_size + max_mob2_size <= i && i < MaxMob) {
			MobList[i].InitMobSetting(mp, 3);
		}
	}

	maxObj = 40;
	objList = new cObj[maxObj];
	for (int i = 0; i < maxObj; ++i) {
		POINT mp = { 0,0 };
		if (i < max_mob1_size) {
			objList[i].InitObjSetting(mp, 1);
		}
		else if (max_mob1_size <= i && i < max_mob1_size + max_mob2_size) {
			objList[i].InitObjSetting(mp, 2);
		}
		else if (max_mob1_size + max_mob2_size <= i && i < MaxMob) {
			objList[i].InitObjSetting(mp, 3);
		}
	}
}

void cInGame::InitStage4()
{
	int max_mob1_size = 10;
	int max_mob2_size = 15;
	int max_mob3_size = 5;
	int max_mob4_size = 20;

	currMob = 50;
	MaxMob = currMob;
	MobList = new cMonster[MaxMob];
	for (int i = 0; i < MaxMob; ++i) {
		POINT mp;
		//int range1 = MobRange(dre);
		//int range2 = MobRange(dre);
		mp.x = 0;
		mp.y = 0;
		//mp.x = GAME_WIDTH / 2 + range1;
		//mp.y = GAME_HEIGHT / 2 + range2;

		//double lenVec = sqrt((pp.x - mp.x) * (pp.x - mp.x)
		//   + (pp.y - mp.y) * (pp.y - mp.y));
		//if (Map.IsCollideMap(mp) == TRUE) {
		//   i--;
		//   continue;
		//}
		//else if (lenVec < 400) {
		//   i--;
		//   continue;
		//}
		MobList[i].InitMobSetting(mp, 4);

		if (i < max_mob1_size) {
			MobList[i].InitMobSetting(mp, 1);
		}
		else if (max_mob1_size <= i && i < max_mob1_size + max_mob2_size) {
			MobList[i].InitMobSetting(mp, 2);
		}
		else if (max_mob1_size + max_mob2_size <= i && i < max_mob1_size + max_mob2_size + max_mob3_size) {
			MobList[i].InitMobSetting(mp, 3);
		}
		else if (max_mob1_size + max_mob2_size + max_mob3_size <= i && i < MaxMob) {
			MobList[i].InitMobSetting(mp, 4);
		}
	}

	maxObj = 50;
	objList = new cObj[maxObj];
	for (int i = 0; i < maxObj; ++i) {
		POINT mp = { 0,0 };
		if (i < max_mob1_size) {
			objList[i].InitObjSetting(mp, 1);
		}
		else if (max_mob1_size <= i && i < max_mob1_size + max_mob2_size) {
			objList[i].InitObjSetting(mp, 2);
		}
		else if (max_mob1_size + max_mob2_size <= i && i < max_mob1_size + max_mob2_size + max_mob3_size) {
			objList[i].InitObjSetting(mp, 3);
		}
		else if (max_mob1_size + max_mob2_size + max_mob3_size <= i && i < MaxMob) {
			objList[i].InitObjSetting(mp, 4);
		}
	}
}

void cInGame::InitStage5()
{
	currMob = 1;
	MaxMob = currMob;
	MobList = new cMonster[MaxMob];
	for (int i = 0; i < MaxMob; ++i) {
		POINT mp;
		//int range1 = MobRange(dre);
		//int range2 = MobRange(dre);
		mp.x = 0;
		mp.y = 0;
		//mp.x = GAME_WIDTH / 2 + range1;
		//mp.y = GAME_HEIGHT / 2 + range2;

		//double lenVec = sqrt((pp.x - mp.x) * (pp.x - mp.x)
		//   + (pp.y - mp.y) * (pp.y - mp.y));
		//if (Map.IsCollideMap(mp) == TRUE) {
		//   i--;
		//   continue;
		//}
		//else if (lenVec < 400) {
		//   i--;
		//   continue;
		//}
		MobList[i].InitMobSetting(mp, 5);
	}

	maxObj = 30;
	objList = new cObj[maxObj];
	for (int i = 0; i < maxObj; ++i) {
		POINT mp = { 0,0 };
		objList[i].InitObjSetting(mp, 1);
	}
}

void cInGame::DelStage1() {
	delete[] MobList;
	delete[] objList;
}

void cInGame::DelStage2()
{
	delete[] MobList;
	delete[] objList;
}

void cInGame::DelStage3()
{
	delete[] MobList;
	delete[] objList;
}

void cInGame::DelStage4()
{
	delete[] MobList;
	delete[] objList;
}

void cInGame::DelStage5()
{
	delete[] MobList;
	delete[] objList;
}

void cInGame::SpawnManage(POINT pp)
{
	for (int i = 0; i < MaxMob; ++i) {
		if (MobList[i].SpawnMonster(pp) == true) {
			MobList[i].calculAngle(pp);
			return;
		}
	}
}

void cInGame::MoveMonster(cPlayer& p)
{
	RECT rtTemp;

	if (active_kill_cheat == TRUE) {
		for (int i = 0; i < MaxMob; ++i) {
			MobList[i].turnDie();
			if(camera_stat != CAMERA_STUMPING)
				camera_stat = CAMERA_START_SHAKE; // 카메라 흔들기 시작
		}
		active_kill_cheat = FALSE;
	}

	for (int i = 0; i < MaxMob; ++i) {
		MobList[i].calculAngle(p.GetPlayerPoint());
		MobList[i].MoveMonster();
		MobList[i].monsterPattern();


		RECT mobrect = MobList[i].GetMonsterRect();

		if (p.interRect(mobrect.left, mobrect.top, mobrect.right, mobrect.bottom) &&
			(MobList[i].GetIsDie() == false)) {
			if (MobList[i].GetMonsterKind() == 5) {
				MobList[i].bossHit();
				p.bossHit();
				if (camera_stat != CAMERA_STUMPING)
					camera_stat = CAMERA_START_SHAKE; // 카메라 흔들기 시작
			}
			else {
				MobList[i].turnDie();
				if (camera_stat != CAMERA_STUMPING)
					camera_stat = CAMERA_START_SHAKE; // 카메라 흔들기 시작

				// 오브젝트 세팅(2번몹 죽을 때)
				if (MobList[i].GetMonsterKind() == 2 && currObj < maxObj - 1) {
					objList[currObj].InitObjSetting(MobList[i].GetMonsterPoint(), 4);
					objList[currObj].SetObjStat(OBJ_SPAWNING);
					//objList[currObj].turnIsSummon();
					MobList[i].setObjNum(currObj);
					currObj++;
				}
				if (MobList[i].GetMonsterKind() == 3) {
					mciSendCommand(dwID[9], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					mciSendCommand(dwID[9], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				}
				p.increaseSword();
				currMob--;
			}
		}
		// 오브젝트 사망처리
		if (MobList[i].GetMonsterKind() == 2 &&
			(MobList[i].GetRemoveObj() == 1 || objList[MobList[i].GetObjNum()].GetHp() <= 0)) {
			objList[MobList[i].GetObjNum()].turnIsSummon();
			MobList[i].removeObj2Zero();
		}
		if (MobList[i].returnDie() == false) {
			if (IntersectRect(&rtTemp, &p.GetPlayerRect(), &MobList[i].GetMonsterRect())) {
				p.damaged(MobList[i].GetMonsterRadian());
			}
			//몬스터 장애물 충돌
			for (int j = 0; j < currObj; ++j) {
				//몬스터 장애물 충돌
				if (objList[j].GetObjisSummon()) {
					if (IntersectRect(&rtTemp, &MobList[i].GetMonsterRect(), &objList[j].GetObjRect())) {
						SetRect(&rtTemp, 0, 0,
							rtTemp.right - rtTemp.left,
							rtTemp.bottom - rtTemp.top);

						if (rtTemp.right > rtTemp.bottom) {
							if ((MobList[i].GetMonsterRect().bottom + MobList[i].GetMonsterRect().top) / 2
								< (objList[j].GetObjRect().bottom + objList[j].GetObjRect().top) / 2) {
								MobList[i].pointHandle(0, -rtTemp.bottom);
							}
							else {
								MobList[i].pointHandle(0, rtTemp.bottom);
							}
						}
						else
						{
							if ((MobList[i].GetMonsterRect().right + MobList[i].GetMonsterRect().left) / 2
								< (objList[j].GetObjRect().right + objList[j].GetObjRect().left) / 2) {
								MobList[i].pointHandle(-rtTemp.right, 0);
							}
							else {
								MobList[i].pointHandle(rtTemp.right, 0);
							}
						}
					}
				}
			}
		}
		for (int j = 0; j < BULLET; ++j) {
			if (p.interRectPlayer(MobList[i].GetBulletPoint(j).x, MobList[i].GetBulletPoint(j).y,
				MobList[i].GetBulletPoint(j).x + (55 / 2), MobList[i].GetBulletPoint(j).y + (55 / 2))) {
				p.damaged(MobList[i].GetBulletRadian(j));
				MobList[i].turnShoot(j);
			}
		}
	}
}

void cInGame::checkObj(cPlayer& p) {
	std::uniform_int_distribution<int> hit_sound_random(12, 13);
	for (int i = 0; i < currObj; ++i) {
		if (objList[i].GetObjisSummon()) {
			p.interSectObj(objList[i].GetObjRect());
			if (p.interRect(objList[i].GetObjRect().left, objList[i].GetObjRect().top, objList[i].GetObjRect().right, objList[i].GetObjRect().bottom)) {
// 플레이어와 2번몹 장애물 오브젝트 충돌
				p.decreaseSword();
				p.decreaseSword();
				objList[i].SetHp(objList[i].GetHp() - 1);
				int temp_sound = hit_sound_random(dre);
				mciSendCommand(dwID[temp_sound], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				mciSendCommand(dwID[temp_sound], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
			}
		}
	}
}

void cInGame::DrawStage(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	switch (curr)
	{
	case CURR_NULL:
		break;
	case CURR_STAGE1:
		DrawStage1(hDC, hWnd, g_hInst);
		break;
	case CURR_STAGE2:
		DrawStage2(hDC, hWnd, g_hInst);
		break;
	case CURR_STAGE3:
		DrawStage3(hDC, hWnd, g_hInst);
		break;
	case CURR_STAGE4:
		DrawStage4(hDC, hWnd, g_hInst);
		break;
	case CURR_STAGE5:
		DrawStage5(hDC, hWnd, g_hInst);
		break;
	case CURR_DEAD:
		DrawDead(hDC, hWnd, g_hInst);
		break;
	case CURR_DEADEND:
		game_end_state = GAME_END;
		DrawDeadEnd(hDC, hWnd, g_hInst);
		break;
	case CURR_STAGECHANGE:
		DrawChangeStage(hDC, hWnd, g_hInst);
		break;
	case CURR_PREPARE_GAMEEND:
		DrawPrepareEnding(hDC, hWnd, g_hInst);
		break;
	case CURR_GAMEEND:
		game_end_state = GAME_END;
		DrawEnding(hDC, hWnd, g_hInst);
		break;
	}
}

void cInGame::DrawStage1(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int clearcnt = 0;
	RECT PrintRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 300,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 150 };
	RECT PrintSubRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 200,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 100 };

	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	HFONT oldFont = (HFONT)SelectObject(hDC, myFont);

	SetBkMode(hDC, TRANSPARENT);
	TCHAR str[] = TEXT("Stage 1");
	SetTextColor(hDC, RGB(180, 180, 180));
	DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	TCHAR str2[1000] = TEXT("");
	if (currMob == 0) {
		if (clearcnt > MAX_CLEAR_CNT) {
			temp_curr = curr;
			curr = CURR_STAGECHANGE;
		}
		else if (clearcnt > MAX_CLEAR_CNT - 50) {
			wsprintf(str2, TEXT("Clear!!"));
			clearcnt++;
		}
		else {
			clearcnt++;
			wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
		}
	}
	else {
		wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
	}
	DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	SelectObject(hDC, oldFont);
	DeleteObject(myFont);
}

void cInGame::DrawStage2(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int clearcnt = 0;
	RECT PrintRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 300,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 150 };
	RECT PrintSubRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 200,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 100 };

	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	HFONT oldFont = (HFONT)SelectObject(hDC, myFont);

	SetBkMode(hDC, TRANSPARENT);
	TCHAR str[] = TEXT("Stage 2");
	SetTextColor(hDC, RGB(180, 180, 180));
	DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	TCHAR str2[1000] = TEXT("");
	if (currMob == 0) {
		if (clearcnt > MAX_CLEAR_CNT) {
			temp_curr = curr;
			curr = CURR_STAGECHANGE;
		}
		else if (clearcnt > MAX_CLEAR_CNT - 50) {
			wsprintf(str2, TEXT("Clear!!"));
			clearcnt++;
		}
		else {
			clearcnt++;
			wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
		}
	}
	else {
		wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
	}
	DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	SelectObject(hDC, oldFont);
	DeleteObject(myFont);
}

void cInGame::DrawStage3(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int clearcnt = 0;
	RECT PrintRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 300,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 150 };
	RECT PrintSubRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 200,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 100 };

	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	HFONT oldFont = (HFONT)SelectObject(hDC, myFont);

	SetBkMode(hDC, TRANSPARENT);
	TCHAR str[] = TEXT("Stage 3");
	SetTextColor(hDC, RGB(180, 180, 180));
	DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	TCHAR str2[1000] = TEXT("");
	if (currMob == 0) {
		if (clearcnt > MAX_CLEAR_CNT) {
			temp_curr = curr;
			curr = CURR_STAGECHANGE;
		}
		else if (clearcnt > MAX_CLEAR_CNT - 50) {
			wsprintf(str2, TEXT("Clear!!"));
			clearcnt++;
		}
		else {
			clearcnt++;
			wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
		}
	}
	else {
		wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
	}
	DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	SelectObject(hDC, oldFont);
	DeleteObject(myFont);
}

void cInGame::DrawStage4(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int clearcnt = 0;
	RECT PrintRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 300,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 150 };
	RECT PrintSubRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 200,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 100 };

	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	HFONT oldFont = (HFONT)SelectObject(hDC, myFont);

	SetBkMode(hDC, TRANSPARENT);
	TCHAR str[] = TEXT("Stage 4");
	SetTextColor(hDC, RGB(180, 180, 180));
	DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	TCHAR str2[1000] = TEXT("");
	if (currMob == 0) {
		if (clearcnt > MAX_CLEAR_CNT) {
			temp_curr = curr;
			curr = CURR_STAGECHANGE;
		}
		else if (clearcnt > MAX_CLEAR_CNT - 50) {
			wsprintf(str2, TEXT("Clear!!"));
			clearcnt++;
		}
		else {
			clearcnt++;
			wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
		}
	}
	else {
		wsprintf(str2, TEXT("Kill %d Mobs"), currMob);
	}
	DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	SelectObject(hDC, oldFont);
	DeleteObject(myFont);
}

void cInGame::DrawStage5(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int clearcnt = 0;
	RECT PrintRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 300,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 150 };
	RECT PrintSubRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 200,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 100 };

	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	HFONT oldFont = (HFONT)SelectObject(hDC, myFont);
	SetBkMode(hDC, TRANSPARENT);
	TCHAR str[] = TEXT("Stage 5");
	SetTextColor(hDC, RGB(180, 180, 180));
	DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	TCHAR str2[1000] = TEXT("");
	if (MobList[0].GetBossHp() == 0) {
		if (clearcnt > MAX_CLEAR_CNT) {
			temp_curr = curr;
			curr = CURR_PREPARE_GAMEEND;
			game_end_state = GAME_PRE_END;
		}
		else if (clearcnt > MAX_CLEAR_CNT - 50) {
			wsprintf(str2, TEXT("Clear!!"));
			clearcnt++;
		}
		else {
			clearcnt++;
			wsprintf(str2, TEXT("Hit %d More!!"), MobList[0].GetBossHp());
		}
	}
	else {
		wsprintf(str2, TEXT("Hit %d More!!"), MobList[0].GetBossHp());
	}
	DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	SelectObject(hDC, oldFont);
	DeleteObject(myFont);
}

void cInGame::DrawChangeStage(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	RECT PrintRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 300,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 150 };
	RECT PrintSubRect = { GAME_WIDTH / 2 - 310, GAME_HEIGHT / 2 - 200,  GAME_WIDTH / 2 + 310, GAME_HEIGHT / 2 - 100 };
	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	HFONT oldFont = (HFONT)SelectObject(hDC, myFont);

	SetBkMode(hDC, TRANSPARENT);
	TCHAR str[] = TEXT("Game End");
	SetTextColor(hDC, RGB(180, 180, 180));
	TCHAR str2[] = TEXT("Thanks For Playing");

	static bool func_first_run = TRUE;

	if (func_first_run == TRUE) {
		mciSendCommand(dwID[0], MCI_PAUSE, MCI_CLOSE, (DWORD)(LPVOID)& mciPlay);
		mciSendCommand(dwID[1], MCI_PAUSE, MCI_CLOSE, (DWORD)(LPVOID)& mciPlay);
		mciSendCommand(dwID[10], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(dwID[10], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
		func_first_run = FALSE;
	}

	static int dir = 0; // 0일때 증가 1일때 감소
	static int i = 15;
	static int isDelete = 0; 
	static HBITMAP hBit1 = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);
	int templife = 0;

	if (isDelete == 1) {
		hBit1 = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
		MemDC1 = CreateCompatibleDC(hDC);
		oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);
		isDelete = 0;
	}

	if (i < 255 && dir == 0) {
		BLENDFUNCTION _bf;
		_bf.BlendOp = AC_SRC_OVER;
		_bf.BlendFlags = 0;
		_bf.SourceConstantAlpha = i;
		_bf.AlphaFormat = 0;

		if (i < 255) {
			i += 5;
		if (i == 255) {
			dir = 1;
			}
		}

		RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
		//GetClientRect(hWnd, &window);
		//const int MidX = (window.left + window.right) / 2;
		//const int MidY = (window.top + window.bottom) / 2;

		FillRect(MemDC1, &window, (HBRUSH)GetStockObject(WHITE_BRUSH));

		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, _bf);
		if (temp_curr == CURR_GAMEEND) {
			DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
	}
	else if (dir == 1){
		BLENDFUNCTION _bf;
		_bf.BlendOp = AC_SRC_OVER;
		_bf.BlendFlags = 0;
		_bf.SourceConstantAlpha = i;
		_bf.AlphaFormat = 0;

		if (i > 0) {
			i -= 5;
		}
		else if (i == 0) {
			dir = 2;
		}

		RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
		//GetClientRect(hWnd, &window);
		//const int MidX = (window.left + window.right) / 2;
		//const int MidY = (window.top + window.bottom) / 2;

		FillRect(MemDC1, &window, (HBRUSH)GetStockObject(WHITE_BRUSH));

		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, _bf);
		if (temp_curr == CURR_GAMEEND) {
			DrawText(hDC, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DrawText(hDC, str2, lstrlen(str2), &PrintSubRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
	}
	else if(dir == 2){
		switch (temp_curr)
		{
		case CURR_STAGE1:
			curr = CURR_STAGE2;
			DelStage1();
			InitStage2();
			templife = Player.GetPlayerLife();
			if (templife < 5) {
				Player.SetPlayerLife(++templife);
			}
			break;
		case CURR_STAGE2:
			curr = CURR_STAGE3;
			DelStage2();
			InitStage3();
			templife = Player.GetPlayerLife();
			if (templife < 5) {
				Player.SetPlayerLife(++templife);
			}
			break;
		case CURR_STAGE3:
			curr = CURR_STAGE4;
			DelStage3();
			InitStage4();
			templife = Player.GetPlayerLife();
			if (templife < 5) {
				Player.SetPlayerLife(++templife);
			}
			break;
		case CURR_STAGE4:
			curr = CURR_STAGE5;
			DelStage4();
			InitStage5();
			templife = Player.GetPlayerLife();
			if (templife < 5) {
				Player.SetPlayerLife(++templife);
			}
			break;
		case CURR_STAGE5:
			temp_curr = CURR_PREPARE_GAMEEND;
			DelStage5();
			break;
		}
		if (temp_curr != CURR_PREPARE_GAMEEND) {
			temp_curr = CURR_NULL;
		}

		SelectObject(MemDC1, oldBit1);
		DeleteObject(hBit1);
		DeleteDC(MemDC1);

		mciSendCommand(dwID[0], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(dwID[1], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(dwID[0], MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);
		mciSendCommand(dwID[1], MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);
		mciSendCommand(dwID[10], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		func_first_run = TRUE;

		dir = 0;
		i = 15;
		isDelete = 1;
	}
	SelectObject(hDC, oldFont);
	DeleteObject(myFont);
}



void cInGame::DrawDead(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int i = 15;
	static HBITMAP hBit1 = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);
	if (i < 255) {
		BLENDFUNCTION _bf;
		_bf.BlendOp = AC_SRC_OVER;
		_bf.BlendFlags = 0;
		_bf.SourceConstantAlpha = i;
		_bf.AlphaFormat = 0;

		if (i < 255) {
			i += 5;
		}

		RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
		//GetClientRect(hWnd, &window);
		//const int MidX = (window.left + window.right) / 2;
		//const int MidY = (window.top + window.bottom) / 2;

		FillRect(MemDC1, &window, (HBRUSH)GetStockObject(BLACK_BRUSH));

		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, _bf);
	}
	else {
		curr = CURR_DEADEND;
		RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
		FillRect(hDC, &window, (HBRUSH)GetStockObject(BLACK_BRUSH));
		SelectObject(MemDC1, oldBit1);
		DeleteObject(hBit1);
		DeleteDC(MemDC1);
	}
}

void cInGame::DrawDeadEnd(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int i = 0;
	static int cnt = 0;
	Camera.left = 0;
	Camera.top = 0;
	Camera.right = CLIENT_WIDTH;
	Camera.bottom = CLIENT_HEIGHT;

	BLENDFUNCTION _bf;
	_bf.BlendOp = AC_SRC_OVER;
	_bf.BlendFlags = 0;
	_bf.SourceConstantAlpha = i;
	_bf.AlphaFormat = 0;


	RECT window = { 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT };
	FillRect(hDC, &window, (HBRUSH)GetStockObject(BLACK_BRUSH));
	// 1132 x 637
	static HBITMAP hBit1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_DEADBG));
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);

	static HFONT myFont = CreateFont(150, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	static HFONT oldFont = (HFONT)SelectObject(MemDC1, myFont);

	SetBkMode(MemDC1, TRANSPARENT);
	TCHAR str[] = TEXT("You are Lose");
	SetTextColor(MemDC1, RGB(180, 180, 180));

	RECT PrintRect = { 0, 637 / 4 - 100, 1132, 637 / 4 + 100 };
	DrawText(MemDC1, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	if (i < 255) {
		// 95 x 82
		g_cimgPlayerDeadBG.SetTransparentColor(RGB(255, 0, 0));
		g_cimgPlayerDeadBG.Draw(MemDC1, 1132 / 2 - 48, 637 / 2 - 41,
			96, 82);
		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, 1132, 637, _bf);
		cnt++;
		if (cnt % 2 == 0) {
			i += 1;
		}
	}
	else {
		g_cimgPlayerDeadBG.SetTransparentColor(RGB(255, 0, 0));
		g_cimgPlayerDeadBG.Draw(MemDC1, 1132 / 2 - 48, 637 / 2 - 41,
			96, 82);
		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, 1132, 637, _bf);
	}

	//SelectObject(MemDC1, oldBit1);
	//DeleteObject(hBit1);
	//DeleteDC(MemDC1);
}

void cInGame::DrawPrepareEnding(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int i = 15;
	static HBITMAP hBit1 = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);
	if (i < 255) {
		BLENDFUNCTION _bf;
		_bf.BlendOp = AC_SRC_OVER;
		_bf.BlendFlags = 0;
		_bf.SourceConstantAlpha = i;
		_bf.AlphaFormat = 0;

		if (i < 255) {
			i += 1;
		}

		RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
		//GetClientRect(hWnd, &window);
		//const int MidX = (window.left + window.right) / 2;
		//const int MidY = (window.top + window.bottom) / 2;

		FillRect(MemDC1, &window, (HBRUSH)GetStockObject(WHITE_BRUSH));

		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, _bf);
	}
	else {
		curr = CURR_GAMEEND;
		RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
		FillRect(hDC, &window, (HBRUSH)GetStockObject(WHITE_BRUSH));
		SelectObject(MemDC1, oldBit1);
		DeleteObject(hBit1);
		DeleteDC(MemDC1);
	}
}

void cInGame::DrawEnding(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int i = 0;
	static int cnt = 0;
	Camera.left = 0;
	Camera.top = 0;
	Camera.right = CLIENT_WIDTH;
	Camera.bottom = CLIENT_HEIGHT;

	BLENDFUNCTION _bf;
	_bf.BlendOp = AC_SRC_OVER;
	_bf.BlendFlags = 0;
	_bf.SourceConstantAlpha = i;
	_bf.AlphaFormat = 0;


	RECT window = { 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT };
	FillRect(hDC, &window, (HBRUSH)GetStockObject(WHITE_BRUSH));

	static HBITMAP hBit1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);

	if (i < 255) {
		// 95 x 82
		//g_cimgClearCG.Draw(MemDC1, 0, 0, 1132, 637);

		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, 1132, 637, _bf);
		//BitBlt(hDC, 0, 0, Camera.right, Camera.bottom, MemDC1, 0, 0, SRCCOPY);
		cnt++;
		if (cnt % 2 == 0) {
			i += 1;
		}
	}
	else {
		//g_cimgClearCG.Draw(MemDC1, 0, 0, 1132, 637);
		GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, 0, 0, 1132, 637, _bf);
		//BitBlt(hDC, 0, 0, Camera.right, Camera.bottom, MemDC1, 0, 0, SRCCOPY);
	}
}

void cInGame::DrawMob(HDC hDC, HINSTANCE g_hInst)
{
	for (int i = 0; i < MaxMob; ++i) {
		MobList[i].drawMonster(hDC, g_hInst);
	}
}

// 오브젝트 그리기
void cInGame::DrawObj(HDC hDC) {
	for (int i = 0; i < currObj; ++i)
	{
		if (objList[i].GetObjStat() == OBJ_SPAWNING) {
			if (objList[i].ObjSpawning(hDC) == TRUE) {
				camera_stat = CAMERA_START_STUMP; // 카메라 마구흔들기 시작
			}
		}

		else if (objList[i].GetObjisSummon()) {
			objList[i].drawObj(hDC);
		}
	}
}

void cInGame::ShakeCamera()
{
	std::uniform_int_distribution<int> shake_x(-10, 10);
	std::uniform_int_distribution<int> shake_y(-5, 5);
	std::uniform_int_distribution<int> stump_x(-50, 50);
	std::uniform_int_distribution<int> stump_y(-30, 30);

	static int curr_shaking_time = 0;
	const int MAX_SHAKING_TIME = 10;
	const int MAX_STUMPING_TIME = 10;

	if (camera_stat == CAMERA_START_SHAKE) {
		curr_shaking_time = 0;
		camera_stat = CAMERA_SHAKING;
	}
	if (camera_stat == CAMERA_START_STUMP) {
		curr_shaking_time = 0;
		camera_stat = CAMERA_STUMPING;
	}
	
	if (camera_stat == CAMERA_SHAKING && (curr_shaking_time < MAX_SHAKING_TIME)) {
		curr_shaking_time++;
		Camera.left = Player.GetPlayerPoint().x - CLIENT_WIDTH / 2 + shake_x(dre);
		Camera.top = Player.GetPlayerPoint().y - CLIENT_HEIGHT / 2 + shake_y(dre);
		Camera.right = Camera.left + CLIENT_WIDTH;
		Camera.bottom = Camera.top + CLIENT_HEIGHT;
		return;
	}
	else if (camera_stat == CAMERA_STUMPING && (curr_shaking_time < MAX_STUMPING_TIME)) {
		curr_shaking_time++;
		Camera.left = Player.GetPlayerPoint().x - CLIENT_WIDTH / 2 + stump_x(dre);
		Camera.top = Player.GetPlayerPoint().y - CLIENT_HEIGHT / 2 + stump_y(dre);
		Camera.right = Camera.left + CLIENT_WIDTH;
		Camera.bottom = Camera.top + CLIENT_HEIGHT;
		return;
	}
	else {
		camera_stat = CAMERA_NORMAL;
		Camera.left = Player.GetPlayerPoint().x - CLIENT_WIDTH / 2;
		Camera.top = Player.GetPlayerPoint().y - CLIENT_HEIGHT / 2;
		Camera.right = Camera.left + CLIENT_WIDTH;
		Camera.bottom = Camera.top + CLIENT_HEIGHT;
		return;
	}
}

