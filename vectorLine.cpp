#define EPSILON 0.0001
#include "vectorLine.h"


//���� �����Լ�
void swap(vector2 * a, vector2 * b) {
	vector2 temp = *a;
	*a = *b;
	*b = *a;
}

//������ ��ġ�� ��ȯ�ϱ� ���� �Լ�
//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
//�������� ���ϰ��� �̿��Ͽ� p�� �������� ���� ��ġ�� ��ȯ�ϴ� �Լ�
//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

//������ ���� ���θ� ��ȯ�ϴ� �Լ�
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
	//�� ������ �� ������ ���� �ְų� ������ ��ġ�� ���
	if (ab == 0.0 && cd == 0.0) {
		if (b < a) swap(&a, &b);
		if (d < c) swap(&c, &d);
		return !((b < c) || (d < a));
	}
	return ab <= 0 && cd <= 0;
}