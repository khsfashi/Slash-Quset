#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <math.h> 
#include <random>
#include <atlimage.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//#include "Include.h"
#include "resource.h"
#include "Digitalv.h"

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Msimg32.lib")

#define CLIENT_WIDTH 1280 // 클라이언트 너비
#define CLIENT_HEIGHT 720 // 클라이언트 높이
#define PI 3.14159265358979323846 // 파이

#define GAME_WIDTH 2560 // 게임 너비 (클라 * 2)
#define GAME_HEIGHT 1440 // 게임 높이 (클라 * 2)

#define MAX_SOUND_SIZE 15 // 소리 최대 저장

//#define GAME_WIDTH 3840 // 게임 너비 (클라 * 3)
//#define GAME_HEIGHT 2160 // 게임 높이 (클라 * 3)

enum CURR_STAGE {CURR_NULL, CURR_STAGE1, CURR_STAGE2, CURR_STAGE3, CURR_STAGE4, CURR_STAGE5, CURR_STAGECHANGE, CURR_DEAD, CURR_DEADEND, CURR_PREPARE_GAMEEND, CURR_GAMEEND };
enum OBJ_STAT { OBJ_NULL, OBJ_SPAWNING, OBJ_ACTIVE, OBJ_DYING, OBJ_DEAD };
enum COMBAT_RESULT { COMBAT_WIN, COMBAT_LOSE, COMBAT_RUN, COMBAT_END };

static std::random_device rd;
static std::default_random_engine dre(rd());