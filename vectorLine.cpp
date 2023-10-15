#define EPSILON 0.0001
#include "vectorLine.h"


//벡터 스왑함수
void swap(vector2 * a, vector2 * b) {
	vector2 temp = *a;
	*a = *b;
	*b = *a;
}

//벡터의 위치를 반환하기 위한 함수
//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
//원점기준 리턴값을 이용하여 p를 기준으로 벡터 위치를 반환하는 함수
//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

//선분의 접촉 여부를 반환하는 함수
bool sementIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	if (a.y == b.y && b.y == c.y && c.y == d.y) {
		if (b.x < a.x) swap(&a, &b);
		if (d.x < c.x) swap(&c, &d);
		return !((b.x < c.x) || (d.x < a.x));
	}
	else if (a.x == b.x && b.x == c.x && c.x == d.x) {
		if (b.y < a.y) swap(&a, &b);
		if (d.y < c.y) swap(&c, &d);
		return !((b.y < c.y) || (d.y < a.y));
	}
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	//두 선분이 한 직선에 위에 있거나 끝점이 겹치는 경우
	if (ab == 0.0 && cd == 0.0) {
		if (b < a) swap(&a, &b);
		if (d < c) swap(&c, &d);
		return !((b < c) || (d < a));
	}
	return ab <= 0 && cd <= 0;
}