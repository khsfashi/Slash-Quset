#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <math.h> 
#include <random>
#include <atlimage.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//#include "Include.h"
#include "resource.h"
#include "Digitalv.h"

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Msimg32.lib")

#define CLIENT_WIDTH 1280 // Ŭ���̾�Ʈ �ʺ�
#define CLIENT_HEIGHT 720 // Ŭ���̾�Ʈ ����
#define PI 3.14159265358979323846 // ����

#define GAME_WIDTH 2560 // ���� �ʺ� (Ŭ�� * 2)
#define GAME_HEIGHT 1440 // ���� ���� (Ŭ�� * 2)

#define MAX_SOUND_SIZE 15 // �Ҹ� �ִ� ����

//#define GAME_WIDTH 3840 // ���� �ʺ� (Ŭ�� * 3)
//#define GAME_HEIGHT 2160 // ���� ���� (Ŭ�� * 3)

enum CURR_STAGE {CURR_NULL, CURR_STAGE1, CURR_STAGE2, CURR_STAGE3, CURR_STAGE4, CURR_STAGE5, CURR_STAGECHANGE, CURR_DEAD, CURR_DEADEND, CURR_PREPARE_GAMEEND, CURR_GAMEEND };
enum OBJ_STAT { OBJ_NULL, OBJ_SPAWNING, OBJ_ACTIVE, OBJ_DYING, OBJ_DEAD };
enum COMBAT_RESULT { COMBAT_WIN, COMBAT_LOSE, COMBAT_RUN, COMBAT_END };

static std::random_device rd;
static std::default_random_engine dre(rd());