#include "cObj.h"

extern CImage g_cimgOBJ1;
extern CImage g_cimgOBJ2;
extern CImage g_cimgOBJ3;
extern CImage g_cimgHelmet;

extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern DWORD dwID[MAX_SOUND_SIZE];


cObj::cObj() {
	op = { 1000,750 };
	isSummon = false;
	objKind = 1;
	size = { 84,84 };
	ObjRect = { op.x,op.y,op.x + size.x,op.y + size.y };
	stat_ = OBJ_NULL;
	hp = 3;
	spawning_cnt = 0;
}

cObj::~cObj() {

}



void cObj::drawObj(HDC hdc) {
	switch (objKind) {
		if (isSummon) {
	case 1:
		size = { 84,84 };
		ObjRect = { op.x,op.y,op.x + size.x,op.y + size.y };
		g_cimgOBJ1.SetTransparentColor(RGB(255, 0, 0));
		g_cimgOBJ1.Draw(hdc, op.x, op.y, size.x, size.y);
		break;
	case 2:
		size = { 84,84 };
		ObjRect = { op.x,op.y,op.x + size.x,op.y + size.y };
		g_cimgOBJ2.SetTransparentColor(RGB(255, 0, 0));
		g_cimgOBJ2.Draw(hdc, op.x, op.y, size.x, size.y);
		break;
	case 3:
		size = { 84,84 };
		ObjRect = { op.x,op.y,op.x + size.x,op.y + size.y };
		g_cimgOBJ3.SetTransparentColor(RGB(255, 0, 0));
		g_cimgOBJ3.Draw(hdc, op.x, op.y, size.x, size.y);
		break;
	case 4:
		size = { 161,216 };
		ObjRect = { op.x,op.y,op.x + (size.x / 2),op.y + (size.y / 2) };
		g_cimgHelmet.SetTransparentColor(RGB(255, 0, 0));
		g_cimgHelmet.Draw(hdc, op.x, op.y, size.x / 2, size.y / 2);
		break;
	default:
		break;
		}
	}
}

void cObj::InitObjSetting(POINT ObjP, int kind) {
	op = ObjP;
	isSummon = false;
	objKind = kind;
	if (kind == 4) {
		size = { 161,216 };
		ObjRect = { op.x,op.y,op.x + (size.x / 2),op.y + (size.y / 2) };
	}
	else {
		size = { 84,84 };
		ObjRect = { op.x,op.y,op.x + size.x,op.y + size.y };
	}
}

void cObj::turnIsSummon() {
	if (isSummon == TRUE && stat_ == OBJ_ACTIVE) {
		isSummon = false;
		stat_ = OBJ_DEAD;
	}
	else if((stat_ != OBJ_NULL) && (stat_ != OBJ_DEAD) ){
		isSummon = true;
		stat_ = OBJ_ACTIVE;
	}
}

bool cObj::ObjSpawning(HDC hDC)
{
	const int max_spawning_int = 100;

	if (spawning_cnt < max_spawning_int) {
		spawning_cnt++;
		size = { 161,216 };
		ObjRect = { op.x,op.y,
			op.x + (size.x / 2), op.y + (size.y / 2) };

		int moving_y = 0;
		if (0 < spawning_cnt && spawning_cnt <= max_spawning_int / 2) {
			moving_y = spawning_cnt;
		}
		else if (max_spawning_int / 2 < spawning_cnt && spawning_cnt <= max_spawning_int) {
			moving_y = max_spawning_int - spawning_cnt;
		}

		g_cimgHelmet.SetTransparentColor(RGB(255, 0, 0));
		g_cimgHelmet.Draw(hDC, op.x, op.y - (moving_y) * 10,
			size.x / 2, size.y / 2 - (moving_y) * 0.5);
	}
	else {
		if (stat_ == OBJ_SPAWNING) {
			stat_ = OBJ_ACTIVE;
			turnIsSummon();
			mciSendCommand(dwID[14], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
			mciSendCommand(dwID[14], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
			return TRUE;
		}
	}
	return FALSE;
}

const RECT& cObj::GetObjRect()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return ObjRect;
}

const bool& cObj::GetObjisSummon() {
	return isSummon;
}

const OBJ_STAT& cObj::GetObjStat()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return stat_;
}

const int& cObj::GetHp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return hp;
}

void cObj::SetObjStat(OBJ_STAT val)
{
	stat_ = val;
}

void cObj::SetHp(int val)
{
	hp = val;
}
