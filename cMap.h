#pragma once
#include "Manager.h"

#ifndef __MAP_H__
#define __MAP_H__

#define OBJMAX 10

typedef struct Object {
	RECT area;
	OBJ_STAT stat;
}OBJ;

class cMap {
private:
	OBJ obj[OBJMAX];
public:
	cMap();
	~cMap();

public:
	bool IsCollideMap(POINT p);
//	bool IsCollideObj(RECT rt);
public:
	const RECT& GetObjRect(int i);
	const OBJ_STAT& GetObjStat(int i);
	void SetObjStat(int i, OBJ_STAT st);
public:
	void DrawMap(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawBG(HDC hDC, HWND hWnd);
	void DrawFloor(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawPlate(HDC hDC, HWND hWnd, HINSTANCE g_hInst);
	void DrawObj(HDC hDC, HWND hWnd, HINSTANCE g_hInst, OBJ obj);
};

#endif // !__MAP_H__