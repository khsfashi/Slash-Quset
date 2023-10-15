#pragma once
#include "Manager.h"

//벡터 구조체 정의
//선분 교차를 구현하기 위해선 벡터가 필요하나 stl은 안 배워서 직접 구현함
struct vector2 {
	double x, y;
	//생성자
	vector2(double _x, double _y) {
		x = _x, y = _y;
	}
	//외적
	double cross(const vector2& other) const {
		return x * other.y - y * other.x;
	}

	/* 연산자 오버로딩을 통해 실제 벡터의 연산을 구현합니다. */

	//벡터의 실수배
	vector2 operator * (double r) const {
		return vector2(x * r, y * r);
	}
	//벡터의 덧셈
	vector2 operator + (vector2 other) const {
		return vector2(x + other.x, y + other.y);
	}
	//벡터의 뺄셈
	vector2 operator - (vector2 other) const {
		return vector2(x - other.x, y - other.y);
	}
	//두 벡터의 비교
	bool operator == (vector2 other) const {
		return x == other.x && y == other.y;
	}
	bool operator < (vector2 other) const {
		return ((x < other.x) && (y < other.y));
	}
};

void swap(vector2* a, vector2* b);	//벡터 스왑하는 함수
double ccw(vector2 a, vector2 b);	//원점기준 벡터위치 함수
double ccw(vector2 p, vector2 a, vector2 b);	//p기준 벡터위치 함수
bool sementIntersects(vector2 a, vector2 b, vector2 c, vector2 d);	//선 겹치는거 확인하는 함수