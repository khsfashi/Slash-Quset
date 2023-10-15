#include "cMonster.h"

#define MOB_SPEED 4

extern CImage g_cimgEnemyLeft1;
extern CImage g_cimgEnemyRight1;
extern CImage g_cimgEnemyDead1;

extern CImage g_cimgEnemyLeft2;
extern CImage g_cimgEnemyRight2;
extern CImage g_cimgEnemyDead2;

extern CImage g_cimgEnemyLeft3;
extern CImage g_cimgEnemyAttackL3;
extern CImage g_cimgEnemyRight3;
extern CImage g_cimgEnemyAttackR3;
extern CImage g_cimgEnemyDead3;
extern CImage g_cimgBullet;

extern CImage g_cimgEnemyLeft4;
extern CImage g_cimgEnemyAttackL4;
extern CImage g_cimgEnemyRight4;
extern CImage g_cimgEnemyAttackR4;
extern CImage g_cimgEnemyDead4;

extern CImage g_cimgBossPatternR;
extern CImage g_cimgBossPatternL;
extern CImage g_cimgBossAttackR;
extern CImage g_cimgBossAttackL;
extern CImage g_cimgBossRight;
extern CImage g_cimgBossLeft;
extern CImage g_cimgBossDeadR;
extern CImage g_cimgBossDeadL;

std::uniform_int_distribution<int> MobSpawnRangeX(-800, 800);
std::uniform_int_distribution<int> MobSpawnRangeY(-500, 500);
std::uniform_int_distribution<int> MobSpawnTimer(100, 500);
std::uniform_int_distribution<int> MobSpawnTimer2(300, 700);

cMonster::cMonster() {
	mp.x = GAME_WIDTH / 4;
	mp.y = GAME_HEIGHT / 4;
	M_angle = 0;
	chargeRad = 0;
	isDie = false;
	isSummon = true;
	monsterKind = 2;
	deathCnt = 0;
	patternCnt = 0;
	SpawnCnt = 0;
	MaxSpawnCnt = 0;
	size = { 0,0 };
	die_Size = { 0,0 };
	isAttack = false;
	isRage = false;
	for (int i = 0; i < BULLET; ++i) {
		bullet[i].bp.x = mp.x;
		bullet[i].bp.y = mp.y - 100;
		bullet[i].isShoot = false;
		bullet[i].rad = 0;
	}

	MonsterRect.left = mp.x - (size.x / 4);
	MonsterRect.top = mp.y - (size.y / 2);
	MonsterRect.right = MonsterRect.left + (size.x / 2);
	MonsterRect.bottom = MonsterRect.top + (size.y / 2);
	objNum = -1;
	removeObj = 0;
	hp = 100;
}

cMonster::~cMonster() {

}

void cMonster::drawMonster(HDC hDC, HINSTANCE g_hInst) {

	if (isSummon) {
		switch (monsterKind) {
		case 1:
			size.x = 95;
			size.y = 161;
			die_Size.x = 139;
			die_Size.y = 161;
			if (isDie == false) {
				if (M_angle >= 270 || M_angle <= 90) {
					// 적 오른쪽 보기 95 x 161
					g_cimgEnemyRight1.SetTransparentColor(RGB(255, 0, 0));
					g_cimgEnemyRight1.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
				}
				else {
					// 적 왼쪽 보기 95 x 161
					g_cimgEnemyLeft1.SetTransparentColor(RGB(255, 0, 0));
					g_cimgEnemyLeft1.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
				}
			}
			else if (isDie) {
				// 적 뒤짐 139 x 161
				g_cimgEnemyDead1.SetTransparentColor(RGB(255, 0, 0));
				g_cimgEnemyDead1.Draw(hDC, mp.x - (die_Size.x / 4), mp.y - (die_Size.y / 2), die_Size.x / 2, die_Size.y / 2);
			}
			break;
		case 2:
			size.x = 200;
			size.y = 293;
			die_Size.x = 115;
			die_Size.y = 293;
			if (isDie == false) {
				if (M_angle >= 270 || M_angle <= 90) {
					// 적 오른쪽 보기 200 x 293
					g_cimgEnemyRight2.SetTransparentColor(RGB(255, 0, 0));
					g_cimgEnemyRight2.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
				}
				else {
					// 적 왼쪽 보기 200 x 293
					g_cimgEnemyLeft2.SetTransparentColor(RGB(255, 0, 0));
					g_cimgEnemyLeft2.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
				}
			}
			else if (isDie) {
				// 적 뒤짐 115 x 293
				g_cimgEnemyDead2.SetTransparentColor(RGB(255, 0, 0));
				g_cimgEnemyDead2.Draw(hDC, mp.x - (die_Size.x / 4), mp.y - (die_Size.y / 2), die_Size.x / 2, die_Size.y / 2);
			}
			break;
		case 3:
			size.x = 172;
			size.y = 296;
			die_Size.x = 172;
			die_Size.y = 296;
			if (isDie == false) {
				if (isAttack) {
					if (M_angle >= 270 || M_angle <= 90) {
						// 적 오른쪽 보기 172 x 296
						g_cimgEnemyAttackR3.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyAttackR3.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
					else {
						// 적 왼쪽 보기 172 x 296
						g_cimgEnemyAttackL3.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyAttackL3.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
				}
				else {
					// 적 오른쪽 보기 172 x 296
					if (M_angle >= 270 || M_angle <= 90) {
						g_cimgEnemyRight3.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyRight3.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
					else {
						// 적 왼쪽 보기 172 x 296
						g_cimgEnemyLeft3.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyLeft3.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
				}
			}
			else if (isDie) {
				// 적 뒤짐 172 x 296
				g_cimgEnemyDead3.SetTransparentColor(RGB(255, 0, 0));
				g_cimgEnemyDead3.Draw(hDC, mp.x - (die_Size.x / 4), mp.y - (die_Size.y / 2), die_Size.x / 2, die_Size.y / 2);
			}
			break;
		case 4:
			die_Size.x = 135;
			die_Size.y = 181;
			if (isDie == false) {
				if (isAttack) {
					size.x = 177;
					size.y = 186;
					if (M_angle >= 270 || M_angle <= 90) {
						// 적 오른쪽 보기 177 x 186
						g_cimgEnemyAttackR4.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyAttackR4.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
					else {
						// 적 왼쪽 보기 177 x 186
						g_cimgEnemyAttackL4.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyAttackL4.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
				}
				else {
					size.x = 161;
					size.y = 181;
					if (M_angle >= 270 || M_angle <= 90) {
						// 적 오른쪽 보기 161 x 181
						g_cimgEnemyRight4.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyRight4.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
					else {
						// 적 왼쪽 보기 161 x 181
						g_cimgEnemyLeft4.SetTransparentColor(RGB(255, 0, 0));
						g_cimgEnemyLeft4.Draw(hDC, mp.x - (size.x / 4), mp.y - (size.y / 2), size.x / 2, size.y / 2);
					}
				}
			}
			else if (isDie) {
				// 적 뒤짐 135 x 181
				g_cimgEnemyDead4.SetTransparentColor(RGB(255, 0, 0));
				g_cimgEnemyDead4.Draw(hDC, mp.x - (die_Size.x / 4), mp.y - (die_Size.y / 2), die_Size.x / 2, die_Size.y / 2);
			}
			break;
		case 5:
			size.x = 94;
			size.y = 134;
			die_Size.x = 94;
			die_Size.y = 134;
			if (isDie == false) {
				if (isRage) {
					if (M_angle >= 270 || M_angle <= 90) {
						// 적 오른쪽 보기 94 x 134
						g_cimgBossPatternR.SetTransparentColor(RGB(255, 0, 0));
						g_cimgBossPatternR.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
					}
					else {
						// 적 왼쪽 보기 94 x 134
						g_cimgBossPatternL.SetTransparentColor(RGB(255, 0, 0));
						g_cimgBossPatternL.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
					}
				}
				else if (isAttack)
				{
					if (M_angle >= 270 || M_angle <= 90) {
						// 적 오른쪽 보기 94 x 134
						g_cimgBossAttackR.SetTransparentColor(RGB(255, 0, 0));
						g_cimgBossAttackR.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
					}
					else {
						// 적 왼쪽 보기 94 x 134
						g_cimgBossAttackL.SetTransparentColor(RGB(255, 0, 0));
						g_cimgBossAttackL.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
					}
				}
				else {
					// 적 오른쪽 보기 94 x 134
					if (M_angle >= 270 || M_angle <= 90) {
						g_cimgBossRight.SetTransparentColor(RGB(255, 0, 0));
						g_cimgBossRight.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
					}
					else {
						// 적 왼쪽 보기 94 x 134
						g_cimgBossLeft.SetTransparentColor(RGB(255, 0, 0));
						g_cimgBossLeft.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
					}
				}
			}
			else if (isDie) {
				// 적 오른쪽 보기 94 x 134
				if (M_angle >= 270 || M_angle <= 90) {
					g_cimgBossDeadR.SetTransparentColor(RGB(255, 0, 0));
					g_cimgBossDeadR.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
				}
				else {
					// 적 왼쪽 보기 94 x 134
					g_cimgBossDeadL.SetTransparentColor(RGB(255, 0, 0));
					g_cimgBossDeadL.Draw(hDC, mp.x - (size.x / 2), mp.y - size.y, size.x, size.y);
				}
			}
			break;


		default:
			break;
		}
	}
	// 타이머 == CInGame.h 의 MAX_CLEAR_CNT
	if (deathCnt >= 150 && monsterKind != 2) {
		isSummon = false;
		deathCnt = 0;
		isDie = true;
		removeObj = 1;
	}
	else if (deathCnt >= 200 && monsterKind == 2) {
		isSummon = false;
		deathCnt = 0;
		isDie = true;
		removeObj = 1;
	}
	

	for (int i = 0; i < BULLET; ++i) {
		if (bullet[i].isShoot) {
			// 적 총알 55 x 55
			g_cimgBullet.SetTransparentColor(RGB(255, 0, 0));
			g_cimgBullet.Draw(hDC, bullet[i].bp.x, bullet[i].bp.y, 55 / 2, 55 / 2);
		}
	}

	if (monsterKind == 5) {
		MonsterRect.left = mp.x - (size.x / 2);
		MonsterRect.top = mp.y - size.y;
		MonsterRect.right = MonsterRect.left + size.x;
		MonsterRect.bottom = MonsterRect.top + size.y;
	}
	else {
		MonsterRect.left = mp.x - (size.x / 4);
		MonsterRect.top = mp.y - (size.y / 2);
		MonsterRect.right = MonsterRect.left + (size.x / 2);
		MonsterRect.bottom = MonsterRect.top + (size.y / 2);
	}
	for (int i = 0; i < BULLET; ++i) {
		if (bullet[i].isShoot == false) {
			bullet[i].bp.x = mp.x;
			bullet[i].bp.y = mp.y - (size.y / 4);
		}
	}
}

bool cMonster::SpawnMonster(POINT pp)
{
	cMap Map;
	if (isSummon == false && isDie == false) {
		SpawnCnt++;
		if (SpawnCnt >= MaxSpawnCnt) {
			POINT mobp;
			int range1 = MobSpawnRangeX(dre);
			int range2 = MobSpawnRangeY(dre);

			mobp.x = GAME_WIDTH / 2 + range1 + 75;
			mobp.y = GAME_HEIGHT / 2 + range2 + 150;

			double lenVec = sqrt((pp.x - mobp.x) * (pp.x - mobp.x)
				+ (pp.y - mobp.y) * (pp.y - mobp.y));
			if (Map.IsCollideMap(mobp) == TRUE) {
				return false;
			}
			else if (lenVec < 300) {
				return false;
			}
			mp = mobp;

			for (int i = 0; i < BULLET; ++i) {
				bullet[i].bp.x = mp.x - (size.x / 4) + 10;
				bullet[i].bp.y = mp.y - (size.y / 2) + 20;
				bullet[i].isShoot = false;
				bullet[i].rad = 0;
			}
			if (monsterKind == 5) {
				MonsterRect.left = mp.x - (size.x / 2);
				MonsterRect.top = mp.y - size.y;
				MonsterRect.right = MonsterRect.left + size.x;
				MonsterRect.bottom = MonsterRect.top + size.y;
			}
			isSummon = true;
			return true;
		}
	}
	return false;
}

void cMonster::MoveMonster() {
	int speed = MOB_SPEED;
	double rad = M_angle / 180.f * PI;
	switch (monsterKind) {
	case 1:
		if (isDie == false && isSummon == true) {
			mp.x = (LONG)(mp.x + ((speed)* cos(rad)));
			mp.y = (LONG)(mp.y + ((speed)* sin(rad)));
		}

		if (isDie) {
			if (isSummon) {
				deathCnt++;
			}
		}
		break;
	case 2:
		speed = 2;
		if (isDie == false && isSummon == true) {
			mp.x = (LONG)(mp.x + ((speed)* cos(rad)));
			mp.y = (LONG)(mp.y + ((speed)* sin(rad)));
		}

		if (isDie) {
			if (isSummon) {
				deathCnt++;
			}
		}
		break;
	case 3:
		speed = MOB_SPEED + 5;
		for (int i = 0; i < BULLET; ++i) {
			if (bullet[i].isShoot) {
				bullet[i].bp.x = (LONG)(bullet[i].bp.x + ((speed)* cos(bullet[i].rad)));
				bullet[i].bp.y = (LONG)(bullet[i].bp.y + ((speed)* sin(bullet[i].rad)));
				if (bullet[i].bp.x >= GAME_WIDTH || bullet[i].bp.y >= GAME_HEIGHT || bullet[i].bp.x <= 0 || bullet[i].bp.y <= 0) {
					bullet[i].isShoot = false;
					bullet[i].bp.x = mp.x - (size.x / 4);
					bullet[i].bp.y = mp.y - (size.y / 2);
				}
			}
		}
		if (isDie) {
			if (isSummon) {
				deathCnt++;
			}
		}
		break;
	case 4:
		speed = MOB_SPEED / 2;
		if (isAttack) {
			speed = MOB_SPEED + 5;
		}
		if (isDie == false && isSummon == true) {
			if (isAttack) {
				mp.x = (LONG)(mp.x + ((speed)* cos(chargeRad)));
				mp.y = (LONG)(mp.y + ((speed)* sin(chargeRad)));
			}
			else {
				mp.x = (LONG)(mp.x + ((speed)* cos(rad)));
				mp.y = (LONG)(mp.y + ((speed)* sin(rad)));
			}
		}

		if (isDie) {
			if (isSummon) {
				deathCnt++;
			}
		}
		break;
	case 5:
		if (isDie == false && isSummon == true) {
			if (isAttack) {
				if (isRage) {
					speed = MOB_SPEED + 10;
				}
				else {
					speed = MOB_SPEED + 5;
				}
				mp.x = (LONG)(mp.x + ((speed)* cos(chargeRad)));
				mp.y = (LONG)(mp.y + ((speed)* sin(chargeRad)));
			}
		}
		if (isDie) {
			if (isSummon) {
				deathCnt++;
			}
		}
		break;

	default:
		break;
	}
	if (monsterKind == 5) {
		MonsterRect.left = mp.x - (size.x / 2);
		MonsterRect.top = mp.y - size.y;
		MonsterRect.right = MonsterRect.left + size.x;
		MonsterRect.bottom = MonsterRect.top + size.y;
	}
	else {
		MonsterRect.left = mp.x - (size.x / 4);
		MonsterRect.top = mp.y - (size.y / 2);
		MonsterRect.right = MonsterRect.left + (size.x / 2);
		MonsterRect.bottom = MonsterRect.top + (size.y / 2);
	}

}

void cMonster::calculAngle(POINT pp) {
	LONG dx = pp.x - (mp.x);
	LONG dy = pp.y - (mp.y);
	double rad = atan2((double)dx, (double)dy);
	rad = 360 - rad;
	M_angle = rad * 180.f / PI;
	if (M_angle < 0.0) {
		M_angle = 360 + M_angle;
	}
	M_angle = (int)M_angle % 360;
}

void cMonster::turnDie() {
	isDie = true;
	
}

void cMonster::turnShoot(int i) {
	bullet[i].isShoot = false;
	bullet[i].bp.x = mp.x - (size.x / 4) + 10;
	bullet[i].bp.y = mp.y - (size.y / 2) + 20;
}

void cMonster::pointHandle(LONG x, LONG y) {
	mp.x += x;
	mp.y += y;
}

void cMonster::setObjNum(int num) {
	objNum = num;
}
void cMonster::removeObj2Zero() {
	removeObj = 0;
}

void cMonster::bossHit() {
	if (hp > 0) {
		hp--;
		if (hp < 50) {
			isRage = true;
		}
	}
	else {
		turnDie();
	}
}

const int& cMonster::GetMonsterKind() {
	return monsterKind;
}

const POINT& cMonster::GetMonsterPoint() {
	// TODO: 여기에 반환 구문을 삽입합니다.
	POINT temp_Mp;
	if (monsterKind == 5) {
		temp_Mp.x = mp.x - (size.x / 2);
		temp_Mp.y = mp.y - size.y;
	}
	else {
		temp_Mp.x = mp.x - (size.x / 4);
		temp_Mp.y = mp.y - (size.y / 2);
	}
	return temp_Mp;
}

const POINT& cMonster::GetBulletPoint(int i) {
	// TODO: 여기에 반환 구문을 삽입합니다.
	POINT temp = { 0,0 };
	if (bullet[i].isShoot) {
		return bullet[i].bp;
	}
	else return temp;
}

const POINT& cMonster::GetMonstersize() {
	// TODO: 여기에 반환 구문을 삽입합니다.
	return size;
}

const double& cMonster::GetMonsterRadian() {
	// TODO: 여기에 반환 구문을 삽입합니다.
	return M_angle;
}

const double& cMonster::GetBulletRadian(int i) {
	// TODO: 여기에 반환 구문을 삽입합니다.
	return bullet[i].rad;
}

const RECT& cMonster::GetMonsterRect()
{
	if (monsterKind == 5) {
		MonsterRect.left = mp.x - (size.x / 2);
		MonsterRect.top = mp.y - size.y;
		MonsterRect.right = MonsterRect.left + size.x;
		MonsterRect.bottom = MonsterRect.top + size.y;
	}
	else {
		MonsterRect.left = mp.x - (size.x / 4);
		MonsterRect.top = mp.y - (size.y / 2);
		MonsterRect.right = MonsterRect.left + (size.x / 2);
		MonsterRect.bottom = MonsterRect.top + (size.y / 2);
	}
	// TODO: 여기에 반환 구문을 삽입합니다.
	return MonsterRect;
}

const bool& cMonster::GetIsDie()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return isDie;
}

const int& cMonster::GetObjNum() {
	return objNum;
}

const int& cMonster::GetRemoveObj() {
	return removeObj;
}

const int& cMonster::GetBossHp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return hp;
}

void cMonster::SetBossHp(int val)
{
	hp = val;
}

const bool& cMonster::GetIsSummon() {
	return isSummon;
}

void cMonster::monsterPattern() {
	switch (monsterKind) {
	case 3:
		if (isDie == false && isSummon == true) {
			if (isAttack == false) {
				patternCnt++;
				if (patternCnt >= 75) {
					isAttack = true;
					patternCnt = 0;
					for (int i = 0; i < BULLET; ++i) {
						if (bullet[i].isShoot == false) {
							bullet[i].rad = (M_angle - 7) / 180.f * PI;
							//bullet[i].rad = bullet[i].rad - 10;
							bullet[i].isShoot = true;
							break;
						}
					}
				}
			}
			else {
				patternCnt++;
				if (patternCnt >= 15) {
					isAttack = false;
					patternCnt = 0;
				}
			}
		}
		break;
	case 4:
		if (isDie == false && isSummon == true) {
			if (isAttack == false) {
				patternCnt++;
				if (patternCnt >= 75) {
					isAttack = true;
					patternCnt = 0;
					chargeRad = M_angle / 180.f * PI;
				}
			}
			else {
				patternCnt++;
				if (patternCnt >= 25) {
					isAttack = false;
					patternCnt = 0;
				}
			}
		}
		break;
	case 5:
		if (isAttack == false) {
			patternCnt++;
			if (isRage) {
				if (patternCnt >= 40) {
					isAttack = true;
					patternCnt = 0;
					chargeRad = M_angle / 180.f * PI;
				}
			}
			else if (patternCnt >= 100)
			{
				isAttack = true;
				patternCnt = 0;
				chargeRad = M_angle / 180.f * PI;
			}
		}
		else {
			patternCnt++;
			if (isRage) {
				if (patternCnt >= 10)
				{
					isAttack = false;
					patternCnt = 0;
				}
			}
			else if (patternCnt >= 25)
			{
				isAttack = false;
				patternCnt = 0;
			}
		}
		break;

	default:
		break;
	}
}

void cMonster::InitMobSetting(POINT Mobp, int kind)
{
	mp.x = Mobp.x;
	mp.y = Mobp.y;
	M_angle = 0;
	isDie = false;
	isSummon = false;
	monsterKind = kind;
	deathCnt = 0;
	patternCnt = 0;
	SpawnCnt = 0;
	if (kind == 1 || kind == 2 || kind == 5) {
		MaxSpawnCnt = MobSpawnTimer(dre);
	}
	else if (kind == 3 || kind == 4) {
		MaxSpawnCnt = MobSpawnTimer2(dre);
	}
	size = { 0,0 };
	die_Size = { 0,0 };
	isAttack = false;
	for (int i = 0; i < BULLET; ++i) {
		bullet[i].bp.x = mp.x - (size.x / 4);
		bullet[i].bp.y = mp.y - (size.y / 2);
		bullet[i].isShoot = false;
		bullet[i].rad = 0;
	}

	if (monsterKind == 5) {
		hp = 90;
		MonsterRect.left = mp.x - (size.x / 2);
		MonsterRect.top = mp.y - size.y;
		MonsterRect.right = MonsterRect.left + size.x;
		MonsterRect.bottom = MonsterRect.top + size.y;
	}
	else {
		MonsterRect.left = mp.x - (size.x / 4);
		MonsterRect.top = mp.y - (size.y / 2);
		MonsterRect.right = MonsterRect.left + (size.x / 2);
		MonsterRect.bottom = MonsterRect.top + (size.y / 2);
	}
}

bool cMonster::returnDie() {
	if (isSummon) {
		return isDie;
	}
	else {
		return true;
	}
}