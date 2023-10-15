#pragma once
#include "Manager.h"

//���� ����ü ����
//���� ������ �����ϱ� ���ؼ� ���Ͱ� �ʿ��ϳ� stl�� �� ����� ���� ������
struct vector2 {
	double x, y;
	//������
	vector2(double _x, double _y) {
		x = _x, y = _y;
	}
	//����
	double cross(const vector2& other) const {
		return x * other.y - y * other.x;
	}

	/* ������ �����ε��� ���� ���� ������ ������ �����մϴ�. */

	//������ �Ǽ���
	vector2 operator * (double r) const {
		return vector2(x * r, y * r);
	}
	//������ ����
	vector2 operator + (vector2 other) const {
		return vector2(x + other.x, y + other.y);
	}
	//������ ����
	vector2 operator - (vector2 other) const {
		return vector2(x - other.x, y - other.y);
	}
	//�� ������ ��
	bool operator == (vector2 other) const {
		return x == other.x && y == other.y;
	}
	bool operator < (vector2 other) const {
		return ((x < other.x) && (y < other.y));
	}
};

void swap(vector2* a, vector2* b);	//���� �����ϴ� �Լ�
double ccw(vector2 a, vector2 b);	//�������� ������ġ �Լ�
double ccw(vector2 p, vector2 a, vector2 b);	//p���� ������ġ �Լ�
bool sementIntersects(vector2 a, vector2 b, vector2 c, vector2 d);	//�� ��ġ�°� Ȯ���ϴ� �Լ�