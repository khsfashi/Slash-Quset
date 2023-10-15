#include "cMap.h"
extern RECT Camera;

extern CImage g_cimgMapFloor;
extern CImage g_cimgMapDecal1;
extern CImage g_cimgMapDecal2;
extern CImage g_cimgMapDecal8;
extern CImage g_cimgMapDecal10;
extern CImage g_cimgMapDecal11;
extern CImage g_cimgMapObj1;
extern CImage g_cimgMapObjDead1;

cMap::cMap()
{
	obj[0].area.left = 1450;
	obj[0].area.top = 712;
	obj[1].area.left = 1526;
	obj[1].area.top = 553;
	obj[2].area.left = 1669;
	obj[2].area.top = 656;
	obj[3].area.left = 1086;
	obj[3].area.top = 563;
	obj[4].area.left = 978;
	obj[4].area.top = 657;
	obj[5].area.left = 939;
	obj[5].area.top = 479;
	obj[6].area.left = 724;
	obj[6].area.top = 806;
	obj[7].area.left = 1207;
	obj[7].area.top = 1022;
	obj[8].area.left = 1680;
	obj[8].area.top = 470;
	obj[9].area.left = 1056;
	obj[9].area.top = 1006;

	for (int i = 0; i < OBJMAX; ++i) {
		obj[i].stat = OBJ_ACTIVE;
		obj[i].area.right = obj[i].area.left + 57;
		obj[i].area.bottom = obj[i].area.top + 90;
	}
		//obj[i].area.left = GAME_WIDTH / 2 + 150;
		//obj[i].area.top = GAME_HEIGHT / 2 - 192;
}

cMap::~cMap()
{
}

bool cMap::IsCollideMap(POINT p)
{
	// 바닥 크기 2048 x 1044
	POINT MapPoint[4] = { // 상 좌 하 우 순
	{GAME_WIDTH / 2, GAME_HEIGHT / 2 - 522 - 20},
	{GAME_WIDTH / 2 - 1024 - 10, GAME_HEIGHT / 2 - 25},
	{GAME_WIDTH / 2, GAME_HEIGHT / 2 + 522 - 40},
	{GAME_WIDTH / 2 + 1024 + 30, GAME_HEIGHT / 2 - 25}
	};

	// 기울기
	//상좌
	double VectorX = ((double)MapPoint[0].x - MapPoint[1].x);
	double VectorY = ((double)MapPoint[0].y - MapPoint[1].y);
	double slope = VectorY / VectorX;
	if (p.y <= ((slope * ( p.x - MapPoint[1].x )) + MapPoint[1].y) ) {
		return true;
	}

	// 상우
	VectorX = ((double)MapPoint[3].x - MapPoint[0].x);
	VectorY = ((double)MapPoint[3].y - MapPoint[0].y);
	slope = VectorY / VectorX;
	if (p.y <= ((slope * (p.x - MapPoint[0].x)) + MapPoint[0].y)) {
		return true;
	}

	// 좌하
	VectorX = ((double)MapPoint[1].x - MapPoint[2].x);
	VectorY = ((double)MapPoint[1].y - MapPoint[2].y);
	slope = VectorY / VectorX;
	if (p.y >= ((slope * (p.x - MapPoint[2].x)) + MapPoint[2].y)) {
		return true;
	}

	// 하우
	VectorX = ((double)MapPoint[2].x - MapPoint[3].x);
	VectorY = ((double)MapPoint[2].y - MapPoint[3].y);
	slope = VectorY / VectorX;
	if (p.y >= ((slope * (p.x - MapPoint[3].x)) + MapPoint[3].y)) {
		return true;
	}

	RECT MapSize = {
		GAME_WIDTH / 2 - 1024 + 25,
		GAME_HEIGHT / 2 - 522 + 10,
		GAME_WIDTH / 2 + 1024 - 25,
		GAME_HEIGHT / 2 + 522 - 60
	};

	if (!PtInRect(&MapSize, p)) {
		return true;
	}

	return false;
}

const RECT& cMap::GetObjRect(int i)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return obj[i].area;
}

const OBJ_STAT& cMap::GetObjStat(int i)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return obj[i].stat;
}

void cMap::SetObjStat(int i, OBJ_STAT st)
{
	obj[i].stat = st;
}

void cMap::DrawMap(HDC hDC, HWND hWnd, HINSTANCE g_hInst) {
	DrawBG(hDC, hWnd);
	DrawFloor(hDC, hWnd, g_hInst);
	DrawPlate(hDC, hWnd, g_hInst);
	for (int i = 0; i < OBJMAX; ++i) {
		DrawObj(hDC, hWnd, g_hInst, obj[i]);
	}

	// 파란선 드로잉
	const int sz = 2;
	POINT MapPoint[4] = { // 상 좌 하 우 순
	{GAME_WIDTH / 2, GAME_HEIGHT / 2 - 522 - 20},
	{GAME_WIDTH / 2 - 1024 - 10, GAME_HEIGHT / 2 - 25},
	{GAME_WIDTH / 2, GAME_HEIGHT / 2 + 522 - 40},
	{GAME_WIDTH / 2 + 1024 + 30, GAME_HEIGHT / 2 - 25}
	};

	// 펜 그리기
	//HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	//HPEN OldPen = (HPEN)SelectObject(hDC, MyPen);
	//for (int i = 0; i < 3; ++i) {
	//	MoveToEx(hDC, MapPoint[i].x, MapPoint[i].y, NULL);
	//	LineTo(hDC, MapPoint[i + 1].x, MapPoint[i + 1].y);
	//}
	//MoveToEx(hDC, MapPoint[3].x, MapPoint[3].y, NULL);
	//LineTo(hDC, MapPoint[0].x, MapPoint[0].y);
	//SelectObject(hDC, OldPen);
	//DeleteObject(MyPen);
}

void cMap::DrawBG(HDC hDC, HWND hWnd)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(23, 48, 45));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	SelectObject(hDC, GetStockObject(NULL_PEN));
	Rectangle(hDC, Camera.left, Camera.top,
		Camera.right + 10, Camera.bottom + 10);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);

}

void cMap::DrawFloor(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	g_cimgMapFloor.Draw(hDC, GAME_WIDTH / 2 - 1024, GAME_HEIGHT / 2 - 522, 2048, 1044); 
 //   HBITMAP hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_FLOOR));
	//HDC MemDC = CreateCompatibleDC(hDC);
	//HBITMAP oldBit = (HBITMAP)SelectObject(MemDC, hBit);

	//// 바닥 크기 2048 x 1044
	//BitBlt(hDC, GAME_WIDTH / 2 - 1024, GAME_HEIGHT / 2 - 522, 2048, 1044, MemDC, 0, 0, SRCCOPY);
	////TransparentBlt(hDC, GAME_WIDTH / 2 - 1024, GAME_HEIGHT / 2 - 522, 2048, 1044, MemDC, 0, 0, 1024, 522, RGB(255, 255, 255));
	//SelectObject(MemDC, oldBit);
	//DeleteObject(hBit);
	//DeleteDC(MemDC);
	
}

void cMap::DrawPlate(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	//// 429 x 236
	//HBITMAP hBit1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_DECAL1));
	//HDC MemDC1 = CreateCompatibleDC(hDC);
	//HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);

	//// 202 x 143
	//HBITMAP hBit2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_DECAL2));
	//HDC MemDC2 = CreateCompatibleDC(hDC);
	//HBITMAP oldBit2 = (HBITMAP)SelectObject(MemDC2, hBit2);

	//// 452 x 238
	// HBITMAP hBit3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_DECAL8));
	// HDC MemDC3 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit3 = (HBITMAP)SelectObject(MemDC3, hBit3);

	//// 354 x 268
	// HBITMAP hBit4 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_DECAL10));
	// HDC MemDC4 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit4 = (HBITMAP)SelectObject(MemDC4, hBit4);

	//// 350 x 260
	// HBITMAP hBit5 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_DECAL11));
	// HDC MemDC5 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit5 = (HBITMAP)SelectObject(MemDC5, hBit5);

	//BitBlt(hDC, GAME_WIDTH / 2 + 150, GAME_HEIGHT / 2 - 192, 429, 236, MemDC1, 0, 0, SRCCOPY);
	//BitBlt(hDC, GAME_WIDTH / 2 + 602, GAME_HEIGHT / 2 - 102, 202, 143, MemDC2, 0, 0, SRCCOPY);
	//BitBlt(hDC, GAME_WIDTH / 2 - 402, GAME_HEIGHT / 2 + 102, 202, 143, MemDC2, 0, 0, SRCCOPY);
	//BitBlt(hDC, GAME_WIDTH / 2 + 252, GAME_HEIGHT / 2 + 102, 202, 143, MemDC2, 0, 0, SRCCOPY);
	//BitBlt(hDC, GAME_WIDTH / 2 - 220, GAME_HEIGHT / 2 - 430, 452, 238, MemDC3, 0, 0, SRCCOPY);
	//BitBlt(hDC, GAME_WIDTH / 2 - 187, GAME_HEIGHT / 2 - 4, 354, 268, MemDC4, 0, 0, SRCCOPY);
	//BitBlt(hDC, GAME_WIDTH / 2 - 687, GAME_HEIGHT / 2 - 204, 350, 260, MemDC5, 0, 0, SRCCOPY);

	//SelectObject(MemDC1, oldBit1);
	//DeleteObject(hBit1);
	//DeleteDC(MemDC1);

	//SelectObject(MemDC2, oldBit2);
	//DeleteObject(hBit2);
	//DeleteDC(MemDC2);

	//SelectObject(MemDC3, oldBit3);
	//DeleteObject(hBit3);
	//DeleteDC(MemDC3);

	//SelectObject(MemDC4, oldBit4);
	//DeleteObject(hBit4);
	//DeleteDC(MemDC4);

	//SelectObject(MemDC5, oldBit5);
	//DeleteObject(hBit5);
	//DeleteDC(MemDC5);

	g_cimgMapDecal1.Draw(hDC, GAME_WIDTH / 2 + 602, GAME_HEIGHT / 2 - 102, 202, 143);
	g_cimgMapDecal2.Draw(hDC, GAME_WIDTH / 2 + 602, GAME_HEIGHT / 2 - 102, 202, 143);
	g_cimgMapDecal2.Draw(hDC, GAME_WIDTH / 2 - 402, GAME_HEIGHT / 2 + 102, 202, 143);
	g_cimgMapDecal2.Draw(hDC, GAME_WIDTH / 2 + 252, GAME_HEIGHT / 2 + 102, 202, 143);
	g_cimgMapDecal8.Draw(hDC, GAME_WIDTH / 2 - 220, GAME_HEIGHT / 2 - 430, 452, 238);
	g_cimgMapDecal10.Draw(hDC, GAME_WIDTH / 2 - 187, GAME_HEIGHT / 2 - 4, 354, 268);
	g_cimgMapDecal11.Draw(hDC, GAME_WIDTH / 2 - 687, GAME_HEIGHT / 2 - 204, 350, 260);
}

void cMap::DrawObj(HDC hDC, HWND hWnd, HINSTANCE g_hInst, OBJ obj)
{
	//// 57 x 90
	// HBITMAP hBit1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_OBJ1));
	// HDC MemDC1 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);

	//// 57 x 49
	// HBITMAP hBit2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_OBJDEAD1));
	// HDC MemDC2 = CreateCompatibleDC(hDC);
	// HBITMAP oldBit2 = (HBITMAP)SelectObject(MemDC2, hBit2);

	//if (obj.stat == OBJ_ACTIVE) {
	//	obj.area.right = obj.area.left + 57;
	//	obj.area.bottom = obj.area.top + 90;
	//	TransparentBlt(hDC, obj.area.left, obj.area.top, 57, 90, MemDC1,
	//		0, 0, 57, 90, RGB(24, 52, 71));
	//}
	//else {
	//	obj.area.right = obj.area.left + 57;
	//	obj.area.bottom = obj.area.top + 49;
	//	TransparentBlt(hDC, obj.area.left, obj.area.top+41, 57, 49, MemDC2,
	//		0, 0, 57, 49, RGB(24, 52, 71));
	//}
	////HPEN hPen, oldPen;
	////hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	////oldPen = (HPEN)SelectObject(hDC, hPen);
	////Rectangle(hDC, obj.area.left, obj.area.top, obj.area.right, obj.area.bottom);
	////SelectObject(hDC, oldPen);
	////DeleteObject(hPen);

	//SelectObject(MemDC1, oldBit1);
	//DeleteObject(hBit1);
	//DeleteDC(MemDC1);

	//SelectObject(MemDC2, oldBit2);
	//DeleteObject(hBit2);
	//DeleteDC(MemDC2);

	if (obj.stat == OBJ_ACTIVE) {
		obj.area.right = obj.area.left + 57;
		obj.area.bottom = obj.area.top + 90;
		g_cimgMapObj1.Draw(hDC, obj.area.left, obj.area.top, 57, 90);
	}
	else {
		obj.area.right = obj.area.left + 57;
		obj.area.bottom = obj.area.top + 49;
		g_cimgMapObjDead1.Draw(hDC, obj.area.left, obj.area.top+41, 57, 49);
	}
}
