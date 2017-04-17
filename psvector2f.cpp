#include "psvector2f.h"

PsVector2f::PsVector2f(){
	x = 0.0f;
	y = 0.0f;
}

PsVector2f::PsVector2f(float x, float y){
	this->x = x;
	this->y = y;
}

PsVector2f::~PsVector2f(){}

// 输出向量信息
void PsVector2f::printInfo(){
	cout << "PsVector2f: x = " << x << "; y = " << y << endl;
}

// 矢量加法
PsVector2f PsVector2f::operator+(PsVector2f v){
	return PsVector2f(x + v.x, y + v.y);
}

// 矢量减法
PsVector2f PsVector2f::operator-(PsVector2f v){
	return PsVector2f(x - v.x, y - v.y);
}

// 数乘
PsVector2f PsVector2f::operator*(float f){
	return PsVector2f(x * f, y * f);
}

// 数除
PsVector2f PsVector2f::operator/(float f){
	return PsVector2f(x / f, y / f);
}

// 向量点积
float PsVector2f::dotMul(PsVector2f v) const{
	return (x * v.x + y * v.y);
}

// 获取分量中的最大值
float PsVector2f::getMax(){
	return (x > y ? x : y);
}

// 获取分量中的最小值
float PsVector2f::getMin(){
	return (x > y ? y : x);
}

// 获取向量长度
float PsVector2f::getLength(){
	return sqrt(x * x + y * y);
}

// 向量单位化
PsVector2f PsVector2f::normalize(){
	float length = getLength();
	return PsVector2f(x / length, y / length);
}

// 求两点之间的距离
float PsVector2f::getDist(PsVector2f v){
	float distSquare = (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
	return sqrt(distSquare);
}

// 获取反向向量
PsVector2f PsVector2f::negate(){
	return PsVector2f(-x, -y);
}

// 获取零向量
PsVector2f PsVector2f::zero(){
	return PsVector2f(0.0f, 0.0f);
}

// 重载输出流
ostream &operator<<(ostream &os, const PsVector2f &psVector2f){
	os << "(" << psVector2f.x << ", " << psVector2f.y << ")";
	return os;
}