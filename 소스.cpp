#include "Manager.h"
#include "cGameMain.h"
#include "cPlayer.h"
#include "cMap.h"
#include "cInGame.h"
#include "cMonster.h"
#include "cObj.h"

std::uniform_int_distribution<int> SoundRandom(0, 1);

CImage g_cimgMapFloor;
CImage g_cimgMapDecal1;
CImage g_cimgMapDecal2;
CImage g_cimgMapDecal8;
CImage g_cimgMapDecal10;
CImage g_cimgMapDecal11;
CImage g_cimgMapObj1;
CImage g_cimgMapObjDead1;

CImage g_cimgPlayerLeft;
CImage g_cimgPlayerRight;
CImage g_cimgPlayerLeftHit;
CImage g_cimgPlayerRightHit;

CImage g_cimgHeartFull;
CImage g_cimgHeartBlank;
CImage g_cimgError;
CImage g_cimgPlayerDeadLeft;
CImage g_cimgPlayerDeadRight;
CImage g_cimgPlayerDeadBG;

CImage g_cimgEnemyLeft1;
CImage g_cimgEnemyRight1;
CImage g_cimgEnemyDead1;

CImage g_cimgEnemyLeft2;
CImage g_cimgEnemyRight2;
CImage g_cimgEnemyDead2;

CImage g_cimgEnemyLeft3;
CImage g_cimgEnemyAttackL3;
CImage g_cimgEnemyRight3;
CImage g_cimgEnemyAttackR3;
CImage g_cimgEnemyDead3;
CImage g_cimgBullet;

CImage g_cimgEnemyLeft4;
CImage g_cimgEnemyAttackL4;
CImage g_cimgEnemyRight4;
CImage g_cimgEnemyAttackR4;
CImage g_cimgEnemyDead4;

CImage g_cimgBossPatternR;
CImage g_cimgBossPatternL;
CImage g_cimgBossAttackR;
CImage g_cimgBossAttackL;
CImage g_cimgBossRight;
CImage g_cimgBossLeft;
CImage g_cimgBossDeadR;
CImage g_cimgBossDeadL;

CImage g_cimgOBJ1;
CImage g_cimgOBJ2;
CImage g_cimgOBJ3;
CImage g_cimgHelmet;


HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Window Class Name");
LPCTSTR lpszWindowName = TEXT("Slash Quest");

void GameLoop();
void DrawByDoubleBuffering(HWND hWnd, HDC hDC);
void DrawByDC(HWND hWnd, HDC hDC);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	// 윈도우 생성
	RECT rt = { 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	//    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_CAPTION | WS_SYSMENU , CW_USEDEFAULT, CW_USEDEFAULT,
	// rt.right - rt.left, rt.bottom - rt.top, NULL, (HMENU)NULL, hInstance, NULL);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_CAPTION | WS_SYSMENU,
		(GetSystemMetrics(SM_CXSCREEN) / 2) - (CLIENT_WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (CLIENT_HEIGHT / 2) - 30,
		rt.right - rt.left, rt.bottom - rt.top, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow); // nCmdShow, SW_SHOWMAXIMIZED : 전체화면
	UpdateWindow(hWnd);

	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	//while (WM_QUIT != Message.message) {
	//   if (PeekMessage(&Message, NULL, 0, 0, PM_NOREMOVE)) {
	//      GetMessage(&Message, NULL, 0, 0);
	//      TranslateMessage(&Message);
	//      DispatchMessage(&Message);
	//   }
	//   else {
	//      // 게임루프
	//      GameLoop()
	//   }
	//}


 //출처: https://microsoft.tistory.com/85 [::: 책 읽는 프로그래머 :::]
	return Message.wParam;
}

void UpdateFPS(HDC hDC);

MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

// 소리
DWORD dwID[MAX_SOUND_SIZE];

cGameMain GMain;
cMap Map;
cPlayer Player;
cInGame InGame;
cMonster Monster;

RECT Camera;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	POINT temp;
	static int cnt = 0;
	static bool bTemp = FALSE;
	RECT rtTemp;
	HDC hDC;

	switch (iMessage)
	{
	case WM_CREATE:
		// 카메라
		Camera.left = Player.GetPlayerPoint().x - CLIENT_WIDTH / 2;
		Camera.top = Player.GetPlayerPoint().y - CLIENT_HEIGHT / 2;
		Camera.right = Camera.left + CLIENT_WIDTH;
		Camera.bottom = Camera.top + CLIENT_HEIGHT;

		// cimage
		g_cimgMapFloor.Load(TEXT("SlashQuestBmp/Floor.png"));
		g_cimgMapDecal1.Load(TEXT("SlashQuestBmp/BG_decal_01.png"));
		g_cimgMapDecal2.Load(TEXT("SlashQuestBmp/BG_decal_02.png"));
		g_cimgMapDecal8.Load(TEXT("SlashQuestBmp/BG_decal_08.png"));
		g_cimgMapDecal10.Load(TEXT("SlashQuestBmp/BG_decal_10.png"));
		g_cimgMapDecal11.Load(TEXT("SlashQuestBmp/BG_decal_11.png"));
		g_cimgMapObj1.Load(TEXT("SlashQuestBmp/cebola01.png"));
		g_cimgMapObjDead1.Load(TEXT("SlashQuestBmp/cebola02.png"));

		g_cimgPlayerLeft.Load(TEXT("SlashQuestBmp/Player2.png"));
		g_cimgPlayerRight.Load(TEXT("SlashQuestBmp/Player.png"));
		g_cimgPlayerLeftHit.Load(TEXT("SlashQuestBmp/Player2_Hit.png"));
		g_cimgPlayerRightHit.Load(TEXT("SlashQuestBmp/Player_Hit.png"));

		g_cimgHeartFull.Load(TEXT("SlashQuestBmp/Heart_Full.png"));
		g_cimgHeartBlank.Load(TEXT("SlashQuestBmp/Heart_Empty.png"));
		g_cimgError.Load(TEXT("SlashQuestBmp/Error.png"));
		g_cimgPlayerDeadLeft.Load(TEXT("SlashQuestBmp/Player_dead.png"));
		g_cimgPlayerDeadRight.Load(TEXT("SlashQuestBmp/Player_dead_reverse.png"));
		g_cimgPlayerDeadBG.Load(TEXT("SlashQuestBmp/Player_dead_bg.png"));

		g_cimgEnemyLeft1.Load(TEXT("SlashQuestBmp/enemy1.png"));
		g_cimgEnemyRight1.Load(TEXT("SlashQuestBmp/enemy1_reverse.png"));
		g_cimgEnemyDead1.Load(TEXT("SlashQuestBmp/enemy1_dead.png"));

		g_cimgEnemyLeft2.Load(TEXT("SlashQuestBmp/enemy2.png"));
		g_cimgEnemyRight2.Load(TEXT("SlashQuestBmp/enemy2_reverse.png"));
		g_cimgEnemyDead2.Load(TEXT("SlashQuestBmp/enemy2_dead.png"));

		g_cimgEnemyLeft3.Load(TEXT("SlashQuestBmp/enemy3_stand.png"));
		g_cimgEnemyAttackL3.Load(TEXT("SlashQuestBmp/enemy3_attack.png"));
		g_cimgEnemyRight3.Load(TEXT("SlashQuestBmp/enemy3_stand_reverse.png"));
		g_cimgEnemyAttackR3.Load(TEXT("SlashQuestBmp/enemy3_attack_reverse.png"));
		g_cimgEnemyDead3.Load(TEXT("SlashQuestBmp/enemy3_dead.png"));
		g_cimgBullet.Load(TEXT("SlashQuestBmp/bullet.png"));

		g_cimgEnemyLeft4.Load(TEXT("SlashQuestBmp/enemy4_stand.png"));
		g_cimgEnemyAttackL4.Load(TEXT("SlashQuestBmp/enemy4_attack.png"));
		g_cimgEnemyRight4.Load(TEXT("SlashQuestBmp/enemy4_stand_reverse.png"));
		g_cimgEnemyAttackR4.Load(TEXT("SlashQuestBmp/enemy4_attack_reverse.png"));
		g_cimgEnemyDead4.Load(TEXT("SlashQuestBmp/enemy4_dead.png"));

		g_cimgBossPatternR.Load(TEXT("SlashQuestBmp/boss_pattern2_reverse.png"));
		g_cimgBossPatternL.Load(TEXT("SlashQuestBmp/boss_pattern2.png"));
		g_cimgBossAttackR.Load(TEXT("SlashQuestBmp/boss_attack1_reverse.png"));
		g_cimgBossAttackL.Load(TEXT("SlashQuestBmp/boss_attack1.png"));
		g_cimgBossRight.Load(TEXT("SlashQuestBmp/boss_stand_reverse.png"));
		g_cimgBossLeft.Load(TEXT("SlashQuestBmp/boss_stand.png"));
		g_cimgBossDeadR.Load(TEXT("SlashQuestBmp/boss_dead_reverse.png"));
		g_cimgBossDeadL.Load(TEXT("SlashQuestBmp/boss_dead.png"));

		g_cimgOBJ1.Load(TEXT("SlashQuestBmp/pedra01.png"));
		g_cimgOBJ2.Load(TEXT("SlashQuestBmp/pedra02.png"));
		g_cimgOBJ3.Load(TEXT("SlashQuestBmp/pedra03.png"));
		g_cimgHelmet.Load(TEXT("SlashQuestBmp/Helmet.png"));

		// 콘솔
		//AllocConsole();                 // Allocate console window
		//freopen("CONOUT$", "a", stderr); // Redirect stderr to console
		//freopen("CONOUT$", "a", stdout); // Redirect stdout also
		//freopen("CONIN$", "r", stdin);
		//SetConsoleTitleA("Test v.1.0");

		// 타이머
		SetTimer(hWnd, 1, 1000 / 144, NULL); // 로고 타이머

		// 소리
		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Marimba - mpeg.mp3");
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[0] = mciOpen.wDeviceID;
		mciSendCommand(dwID[0], MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Theremin - mpeg.mp3");
		mciSendCommand(1, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[1] = mciOpen.wDeviceID;
		mciSendCommand(dwID[1], MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/ddiring.mp3");
		mciSendCommand(2, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[2] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Sword slice.mp3");
		mciSendCommand(3, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[3] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Error_Effects.mp3");
		mciSendCommand(4, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[4] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Fall_Effects.mp3");
		mciSendCommand(5, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[5] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/PlayerDamaged.mp3");
		mciSendCommand(6, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[6] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Enemy1 Cut.mp3");
		mciSendCommand(7, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[7] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Enemy2 Cut.mp3");
		mciSendCommand(8, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[8] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Bunny Killed.mp3");
		mciSendCommand(9, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[9] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Clear.mp3");
		mciSendCommand(10, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[10] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/DeadEnd.mp3");
		mciSendCommand(11, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[11] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("waveaudio");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Rock hit 1.wav");
		mciSendCommand(12, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[12] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("waveaudio");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Rock hit 5.wav");
		mciSendCommand(13, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[13] = mciOpen.wDeviceID;

		mciOpen.lpstrDeviceType = TEXT("mpegvideo");
		mciOpen.lpstrElementName = TEXT("SlashQuestSound/Heavy stomp sound effect.mp3");
		mciSendCommand(14, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpen);
		dwID[14] = mciOpen.wDeviceID;
		// 멈춤
		//    mciSendCommand(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay); 
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			for (int i = 0; i < OBJMAX; ++i) {
				if (Player.interRect
				(Map.GetObjRect(i).left,
					Map.GetObjRect(i).top,
					Map.GetObjRect(i).right,
					Map.GetObjRect(i).bottom) == TRUE &&
					Map.GetObjStat(i) != OBJ_DEAD) {
					Map.SetObjStat(i, OBJ_DEAD);

					mciSendCommand(dwID[3], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					mciSendCommand(dwID[3], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				}
			}
			if (GMain.GetDoneAnime() == true &&
				InGame.GetStage() == CURR_NULL) {
				if (cnt < 100) {
					cnt++;
				}
				else {
					mciSendCommand(dwID[2], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
					// 첫 시작 초기화
					InGame.SetStage(CURR_STAGE1);
					InGame.InitStage1(Player.GetPlayerPoint());
				}
			}
			// 메인 끝날시 작동
			if (GMain.GetDoneAnime() == true &&
				InGame.GetStage() != CURR_NULL && InGame.GetStage() != CURR_STAGECHANGE &&
				((Player.GetIsExitMap() == false) && (Player.GetPlayerLife() != 0)) &&
				(InGame.GetStage() != CURR_PREPARE_GAMEEND) && (InGame.GetStage() != CURR_GAMEEND)) {
				if (((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('a') & 0x8000)) && ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState('d') & 0x8000))) {
					bTemp = Player.MovePlayer(Map);
					Player.Acceleration(0);
					Player.Deceleration(1);
				}
				else if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('a') & 0x8000)) {
					Player.RotateSword(left);
					Player.Acceleration(1);
					Player.Deceleration(0);
					Player.AccelMove(Map);
				}
				else if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState('d') & 0x8000)) {
					Player.RotateSword(right);
					Player.Acceleration(1);
					Player.Deceleration(0);
					Player.AccelMove(Map);
				}
				else {
					Player.Deceleration(1);
					Player.Deceleration(0);
					Player.AccelMove(Map);
				}

				// 적 이동
				int life_tmp1 = Player.GetPlayerLife();
				int mobdead_tmp1 = InGame.GetCurrMobNum();

				InGame.SpawnManage(Player.GetPlayerPoint());
				InGame.MoveMonster(Player);
				InGame.checkObj(Player);


				int life_tmp2 = Player.GetPlayerLife();
				int mobdead_tmp2 = InGame.GetCurrMobNum();

				if (mobdead_tmp1 != mobdead_tmp2) {
					if (SoundRandom(dre) == 1) {
						mciSendCommand(dwID[7], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						mciSendCommand(dwID[7], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
					}
					else {
						mciSendCommand(dwID[8], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						mciSendCommand(dwID[8], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
					}

				}

				if (life_tmp2 != life_tmp1) {
					mciSendCommand(dwID[6], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					mciSendCommand(dwID[6], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				}
				if (life_tmp2 == 0) {
					Player.DyingPlayer();
					mciSendCommand(dwID[0], MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
					mciSendCommand(dwID[1], MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);

				}
				//Monster.calculAngle(Player.GetPlayerPoint());
				//Monster.MoveMonster();
				//RECT mobrect = Monster.GetMonsterRect();
				//if (Player.interRect(mobrect.left, mobrect.top, mobrect.right, mobrect.bottom)) {
				//   Monster.turnDie();
				//}
				//if (Monster.returnDie() == false) {
				//   if (IntersectRect(&rtTemp, &Player.GetPlayerRect(), &Monster.GetMonsterRect())) {
				//      Player.damaged(Monster.GetMonsterRadian());
				//   }
				//}
			}
			//플레이어 추락
			if (Player.GetIsExitMap() == TRUE) {
				mciSendCommand(dwID[0], MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				mciSendCommand(dwID[1], MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				if (Player.player_stat == PLAYER_ACTIVE) {
					Player.player_stat = PLAYER_FALL_START;
					mciSendCommand(dwID[4], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					mciSendCommand(dwID[4], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				}
				if (Player.DropPlayer() >= 50 && Player.player_stat == PLAYER_FALL_START) {
					Player.player_stat = PLAYER_FALLING;
					mciSendCommand(dwID[5], MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					mciSendCommand(dwID[5], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
				}
			}

			// 플레이어 체력이 0이면?
			if (Player.GetPlayerLife() == 0 && (InGame.GetStage() != CURR_DEAD &&
				InGame.GetStage() != CURR_DEADEND)) {
				InGame.SetStage(CURR_DEAD);
				if (InGame.GetGameEndState() == GAME_ACTIVE)
					InGame.SetGameEndState(GAME_PRE_END);
			}

			if (InGame.GetStage() == CURR_DEAD) {
				mciSendCommand(dwID[11], MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
			}

			// BG_MOVE 배경 움직이기(카메라 이동)
			if (Player.GetPlayerLife() != 0) {
				InGame.ShakeCamera();
				//Camera.left = Player.GetPlayerPoint().x - CLIENT_WIDTH / 2;
				//Camera.top = Player.GetPlayerPoint().y - CLIENT_HEIGHT / 2;
				//Camera.right = Camera.left + CLIENT_WIDTH;
				//Camera.bottom = Camera.top + CLIENT_HEIGHT;
			}

			printf(("%d \n"), Map.IsCollideMap(Player.GetPlayerPoint()));
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			if (GMain.GetIsSpace() == FALSE) {
				GMain.SetIsSpace(TRUE);
			}
			break;
			// 체력회복 치트
		case VK_CONTROL:
			Player.SetPlayerLife(5);
			break;
			// 모든 몹 처치 치트
		case VK_DELETE:
			if (InGame.GetStage() == CURR_STAGE1 || InGame.GetStage() == CURR_STAGE2 || InGame.GetStage() == CURR_STAGE3 || InGame.GetStage() == CURR_STAGE4) {
				InGame.active_kill_cheat = TRUE;
				InGame.MoveMonster(Player);
				InGame.SetCurrMobNum(0);
			}
			break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			CloseWindow(hWnd);
			break;
		case VK_END:
			Player.is_active_invincible_cheat = !Player.is_active_invincible_cheat;
			Player.SetInvincibleCheat(Player.is_active_invincible_cheat);
			break;
		case VK_NUMPAD1:
			break;
		case VK_NUMPAD2:
			break;
		case VK_NUMPAD3:
			break;
		case VK_NUMPAD4:
			break;
		case VK_NUMPAD5:
			break;
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		DrawByDoubleBuffering(hWnd, hDC);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		for (int i = 0; i < MAX_SOUND_SIZE; ++i) {
			if (dwID[i] > 0) {
				mciSendCommand(i, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
			}
		}
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void UpdateFPS(HDC hDC)
{
	TCHAR pFPS[256] = { 0, };
	static DWORD frameCount = 0;            //프레임 카운트수
	static float timeElapsed = 0.0f;            //흐른 시간
	static DWORD lastTime = timeGetTime();   //마지막 시간(temp변수)


	DWORD curTime = timeGetTime();      //현재 시간
	float timeDelta = (curTime - lastTime) * 0.001f;        //timeDelta(1번생성후 흐른 시간) 1초단위로 바꿔준다.

	timeElapsed += timeDelta;

	frameCount++;

	float fps = (float)frameCount / timeElapsed;
	char fps_character[100];

	sprintf_s(fps_character, "FPS : %.3f", fps);
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fps_character, strlen(fps_character), (LPWSTR)pFPS, 256);

	//wsprintf(pFPS, TEXT("게임속도 FPS: %s"), fps_character);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, NULL);
	TextOut(hDC, Camera.left + 10, Camera.top + 10, pFPS, lstrlen(pFPS));
	if (timeElapsed >= 1.0f)         //흐른시간이 1초이상이면 내가 하고싶은것 처리
	{
		fps = (float)frameCount / timeElapsed;

		frameCount = 0;
		timeElapsed = 0.0f;

	}
	else
	{
		//Sleep(0.002f * 1000);   // 1fps 

  //Sleep(0.8f * 1000);   // 1fps 
  //Sleep( 0.2f*1000 );   // 10fps 
  //Sleep( 0.05f*1000 );   // 20fps 
  //Sleep( 0.02f*1000 );   // 50fps 
  //Sleep( 0.002f*1000 );   // 100fps   
	}


	lastTime = curTime;
}

void DrawByDoubleBuffering(HWND hWnd, HDC hDC)
{
	HDC hMemDC;
	RECT windowRect;
	HBITMAP bitmap, old_bitmap;

	GetClientRect(hWnd, &windowRect);

	hMemDC = CreateCompatibleDC(hDC);
	bitmap = CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	old_bitmap = (HBITMAP)SelectObject(hMemDC, bitmap);

	PatBlt(hMemDC, 0, 0, GAME_WIDTH, GAME_HEIGHT, WHITENESS);

	DrawByDC(hWnd, hMemDC);

	BitBlt(hDC, 0, 0, windowRect.right, windowRect.bottom,
		hMemDC, Camera.left, Camera.top, SRCCOPY);
	SelectObject(hMemDC, old_bitmap);
	DeleteObject(bitmap);
	DeleteDC(hMemDC);
}

void DrawByDC(HWND hWnd, HDC hDC)
{


	if (InGame.GetGameEndState() == GAME_ACTIVE) {
		// 뒤지는 중 아니면 출력
		Map.DrawMap(hDC, hWnd, g_hInst);
		if (GMain.GetDoneAnime() == FALSE) {
			// 스페이스 안누르면 출력
			GMain.DrawMenu(hDC, hWnd, g_hInst);
		}
		InGame.DrawMob(hDC, g_hInst);
		InGame.DrawObj(hDC);
		InGame.DrawStage(hDC, hWnd, g_hInst);
		Player.DrawLife(hDC, hWnd, g_hInst);
		Player.DrawPlayer(hDC, hWnd, g_hInst);
	}

	if (InGame.GetGameEndState() == GAME_PRE_END) {
		if (InGame.GetStage() == CURR_DEAD || InGame.GetStage() == CURR_DEADEND) {
			// 뒤지는 중일때 출력
			Map.DrawMap(hDC, hWnd, g_hInst);
			Player.DrawPlayer(hDC, hWnd, g_hInst);
			InGame.DrawStage(hDC, hWnd, g_hInst);
		}
		else if (InGame.GetStage() == CURR_PREPARE_GAMEEND || InGame.GetStage() == CURR_GAMEEND) {
			Map.DrawMap(hDC, hWnd, g_hInst);
			Player.DrawPlayer(hDC, hWnd, g_hInst);
			InGame.DrawStage(hDC, hWnd, g_hInst);
		}
	}
	else if (InGame.GetGameEndState() == GAME_END) {
		if (InGame.GetStage() == CURR_DEAD || InGame.GetStage() == CURR_DEADEND) {
			// 뒤지는 중일때 출력
			InGame.DrawStage(hDC, hWnd, g_hInst);
		}
		else if (InGame.GetStage() == CURR_PREPARE_GAMEEND || InGame.GetStage() == CURR_GAMEEND) {
			InGame.DrawStage(hDC, hWnd, g_hInst);
		}
	}
	else {
		UpdateFPS(hDC);
	}

}