#ifndef _PSPARTICLE2F_H
#define _PSPARTICLE2F_H

#include <iostream>
#include "psvector2f.h"
#include "pscolor.h"

using namespace std;

class PsParticle2f{
public:
	// 默认构造函数
	PsParticle2f();
	// 用户自定义的初始化函数
	void init(float mass, float size, PsColor color, PsVector2f velocity, PsVector2f position, 
		float angularVelocity, float angle, float lifetime, float age);
	// 析构函数
	virtual ~PsParticle2f();
	// 粒子变老
	virtual void aging(float timeInterval);
	// 粒子是否还活着
	virtual bool isAlive();
	// 根据当前位置实时计算粒子的加速度
	void computeAcceleration();
	// 计算粒子的角速度
	virtual void computeAngularVelocity();
	// 计算粒子的速度、角速度、位置和角度
	void move(float timeInterval);
	// 打印粒子信息
	virtual void printInfo();

	// 重载输出流
	friend ostream &operator<<(ostream &os, const PsParticle2f &psParticle2f);

protected:
	// 粒子的质量
	float mass;
	// 粒子的大小（半径）
	float size;
	// 粒子的颜色
	PsColor color;
	// 粒子的加速度
	PsVector2f acceleration;
	// 粒子的速度
	PsVector2f velocity;
	// 粒子的位置
	PsVector2f position;
	// 粒子的角速度
	float angularVelocity;
	// 粒子的角度
	float angle;
	// 粒子的生命周期
	float lifetime;
	// 粒子的年龄
	float age;
};

#endif