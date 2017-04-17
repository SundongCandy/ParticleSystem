#ifndef _PSVECTOR2F_H
#define _PSVECTOR2F_H

#include <iostream>
#include <cmath>
using namespace std;

class PsVector2f{
public:
	PsVector2f();
	PsVector2f(float x, float y);
	~PsVector2f();
	// ���������Ϣ
	void printInfo();
	// ʸ���ӷ�
	PsVector2f operator+(PsVector2f v);
	// ʸ������
	PsVector2f operator-(PsVector2f v);
	// ����
	PsVector2f operator*(float f);
	// ����
	PsVector2f operator/(float f);
	// �������
	float dotMul(PsVector2f v) const;
	// ��ȡ�����е����ֵ
	float getMax();
	// ��ȡ�����е���Сֵ
	float getMin();
	// ��ȡ��������
	float getLength();
	// ������λ��
	PsVector2f normalize();
	// ������֮��ľ���
	float getDist(PsVector2f v);
	// ��ȡ��������
	PsVector2f negate();

	// ��ȡ������
	static PsVector2f zero();

	// ���������
	friend ostream &operator<<(ostream &os, const PsVector2f &psVector2f);
	float x;
	float y;
};

#endif