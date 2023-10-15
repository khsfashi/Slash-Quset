#include "cGameMain.h"

extern RECT Camera;

cGameMain::cGameMain()
{
	IsSpace = FALSE;
	DoneAnime = FALSE;
}

cGameMain::~cGameMain()
{
}

const bool& cGameMain::GetIsSpace()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return IsSpace;
}

void cGameMain::SetIsSpace(bool val)
{
	IsSpace = val;
}

const bool& cGameMain::GetDoneAnime()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return DoneAnime;
}

void cGameMain::SetDoneAnime(bool val)
{
	DoneAnime = val;
}

void cGameMain::DrawMenu(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	DrawAlphaBlend(hDC, hWnd);
	DrawLogo(hDC, hWnd, g_hInst);
	DrawFont(hDC, hWnd);
}

void cGameMain::DrawLogo(HDC hDC, HWND hWnd, HINSTANCE g_hInst)
{
	static int angle = 0;
	static int size = 0;
	static double rad = 0;


	const int MidX = (GAME_WIDTH) / 2;
	const int MidY = (GAME_HEIGHT) / 2;

	POINT LogoP = { 755 / 2, 193 / 2 };

	static HBITMAP hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_LOGO));
	static HDC MemDC = CreateCompatibleDC(hDC);
	static HBITMAP oldBit = (HBITMAP)SelectObject(MemDC, hBit);

	rad = angle * PI / 180;

	static int i = 0;

	// 로고 크기 755 x 193
	if (GetIsSpace() == FALSE) {
		TransparentBlt(hDC, MidX - LogoP.x, 550 - LogoP.y + (int)(50 * sin(rad)), 755, 193, MemDC, 0, 0, 755, 193, RGB(0, 0, 0));
		angle += 5;
		angle = angle % 360;
	}
	else if (GetDoneAnime() == FALSE){
		const POINT SpacedPoint = { MidX - LogoP.x,  550 - LogoP.y + (int)(50 * sin(rad)) };
		TransparentBlt(hDC, MidX - LogoP.x, SpacedPoint.y - i, 755, 193, MemDC, 0, 0, 755, 193, RGB(0, 0, 0));
		i += 40;
	}

	if (i > 600) {
		SelectObject(MemDC, oldBit);
		DeleteObject(hBit);
		DeleteDC(MemDC);
	}
}

void cGameMain::DrawFont(HDC hDC, HWND hWnd) {
	static int i = 0;
	BLENDFUNCTION _bf;
	_bf.BlendOp = AC_SRC_OVER;
	_bf.BlendFlags = 0;
	_bf.SourceConstantAlpha = i;
	_bf.AlphaFormat = 0;

	static int angle = 0;
	static double rad = 0;

	if (GetIsSpace() == FALSE) {
		rad = angle * PI / 180;
		i = abs((int)(255 * sin(rad)));
		angle += 6;
		angle = angle % 360;
	}
	else if (GetIsSpace() == TRUE && angle % 180 > 0) {
		angle -= 6;
		rad = angle * PI / 180;
		i = abs((int)(255 * sin(rad)));
	}

	const int sz = 400;
	RECT PrintRect = { 0 - 10, 1150 - 300, GAME_WIDTH + 10, 1150 - 150 };

	static HBITMAP hBit1 = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);
	BitBlt(MemDC1, 0, 0, GAME_WIDTH, GAME_HEIGHT, hDC, 0, 0, SRCCOPY);

	static HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("Pirata One"));
	static HFONT oldFont = (HFONT)SelectObject(MemDC1, myFont);

	SetBkMode(MemDC1, TRANSPARENT);
	TCHAR str[] = TEXT("Press SpaceBar");
	SetTextColor(MemDC1, RGB(180, 180, 180));
	DrawText(MemDC1, str, lstrlen(str), &PrintRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	GdiAlphaBlend(hDC, Camera.left + sz, Camera.top+sz, CLIENT_WIDTH- sz, CLIENT_HEIGHT-sz, MemDC1, Camera.left+sz, Camera.top+sz, CLIENT_WIDTH-sz, CLIENT_HEIGHT-sz, _bf);

	if (GetIsSpace() == TRUE && angle % 180 == 0) {
		SelectObject(MemDC1, oldFont);
		DeleteObject(myFont);

		SelectObject(MemDC1, oldBit1);
		DeleteObject(hBit1);
		DeleteDC(MemDC1);
	}
}

void cGameMain::DrawAlphaBlend(HDC hDC, HWND hWnd)
{
	static int i = 99;

	BLENDFUNCTION _bf;
	_bf.BlendOp = AC_SRC_OVER;
	_bf.BlendFlags = 0;
	_bf.SourceConstantAlpha = i;
	_bf.AlphaFormat = 0;

	static HBITMAP hBit1 = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	static HDC MemDC1 = CreateCompatibleDC(hDC);
	static HBITMAP oldBit1 = (HBITMAP)SelectObject(MemDC1, hBit1);

	if (GetIsSpace() == TRUE && i >= 0 && GetDoneAnime() == FALSE) {
		i -= 3;
		if (i < 0) {
			SetDoneAnime(TRUE);
			SelectObject(MemDC1, oldBit1);
			DeleteObject(hBit1);
			DeleteDC(MemDC1);
			return;
		}
	}

	RECT window = { 0, 0, GAME_WIDTH, GAME_HEIGHT};
	//GetClientRect(hWnd, &window);
	//const int MidX = (window.left + window.right) / 2;
	//const int MidY = (window.top + window.bottom) / 2;

	FillRect(MemDC1, &window, (HBRUSH)GetStockObject(LTGRAY_BRUSH));

	GdiAlphaBlend(hDC, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, MemDC1, Camera.left, Camera.top, CLIENT_WIDTH, CLIENT_HEIGHT, _bf);

}

