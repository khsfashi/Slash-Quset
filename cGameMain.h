#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

#include "Manager.h"

class cGameMain {
private: // cGameMain Ŭ���� ���ο����� ���� ����
	bool IsSpace; // �����̽��� �����°�?
	bool DoneAnime; // �ִϸ��̼��� �����°�?
public:
	cGameMain();
	~cGameMain();
public:
	const bool& GetIsSpace();
	void SetIsSpace(bool val);
	const bool& GetDoneAnime();
	void SetDoneAnime(bool val);
public: // �ܺο����� ���� ����
	void DrawMenu(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawLogo(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawFont(HDC hDC, HWND hWnd);
	void DrawAlphaBlend(HDC hDC, HWND hWnd);
};

#endif // !__MAINGAME_H__