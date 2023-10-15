#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

#include "Manager.h"

class cGameMain {
private: // cGameMain 클래스 내부에서만 접근 가능
	bool IsSpace; // 스페이스를 눌렀는가?
	bool DoneAnime; // 애니메이션이 끝났는가?
public:
	cGameMain();
	~cGameMain();
public:
	const bool& GetIsSpace();
	void SetIsSpace(bool val);
	const bool& GetDoneAnime();
	void SetDoneAnime(bool val);
public: // 외부에서도 접근 가능
	void DrawMenu(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawLogo(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawFont(HDC hDC, HWND hWnd);
	void DrawAlphaBlend(HDC hDC, HWND hWnd);
};

#endif // !__MAINGAME_H__