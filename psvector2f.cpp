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

// ���������Ϣ
void PsVector2f::printInfo(){
	cout << "PsVector2f: x = " << x << "; y = " << y << endl;
}

// ʸ���ӷ�
PsVector2f PsVector2f::operator+(PsVector2f v){
	return PsVector2f(x + v.x, y + v.y);
}

// ʸ������
PsVector2f PsVector2f::operator-(PsVector2f v){
	return PsVector2f(x - v.x, y - v.y);
}

// ����
PsVector2f PsVector2f::operator*(float f){
	return PsVector2f(x * f, y * f);
}

// ����
PsVector2f PsVector2f::operator/(float f){
	return PsVector2f(x / f, y / f);
}

// �������
float PsVector2f::dotMul(PsVector2f v) const{
	return (x * v.x + y * v.y);
}

// ��ȡ�����е����ֵ
float PsVector2f::getMax(){
	return (x > y ? x : y);
}

// ��ȡ�����е���Сֵ
float PsVector2f::getMin(){
	return (x > y ? y : x);
}

// ��ȡ��������
float PsVector2f::getLength(){
	return sqrt(x * x + y * y);
}

// ������λ��
PsVector2f PsVector2f::normalize(){
	float length = getLength();
	return PsVector2f(x / length, y / length);
}

// ������֮��ľ���
float PsVector2f::getDist(PsVector2f v){
	float distSquare = (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
	return sqrt(distSquare);
}

// ��ȡ��������
PsVector2f PsVector2f::negate(){
	return PsVector2f(-x, -y);
}

// ��ȡ������
PsVector2f PsVector2f::zero(){
	return PsVector2f(0.0f, 0.0f);
}

// ���������
ostream &operator<<(ostream &os, const PsVector2f &psVector2f){
	os << "(" << psVector2f.x << ", " << psVector2f.y << ")";
	return os;
}