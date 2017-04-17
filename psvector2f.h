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
	// 输出向量信息
	void printInfo();
	// 矢量加法
	PsVector2f operator+(PsVector2f v);
	// 矢量减法
	PsVector2f operator-(PsVector2f v);
	// 数乘
	PsVector2f operator*(float f);
	// 数除
	PsVector2f operator/(float f);
	// 向量点积
	float dotMul(PsVector2f v) const;
	// 获取分量中的最大值
	float getMax();
	// 获取分量中的最小值
	float getMin();
	// 获取向量长度
	float getLength();
	// 向量单位化
	PsVector2f normalize();
	// 求两点之间的距离
	float getDist(PsVector2f v);
	// 获取反向向量
	PsVector2f negate();

	// 获取零向量
	static PsVector2f zero();

	// 重载输出流
	friend ostream &operator<<(ostream &os, const PsVector2f &psVector2f);
	float x;
	float y;
};

#endif