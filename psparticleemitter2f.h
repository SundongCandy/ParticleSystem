#ifndef _PSPARTICLEEMITTER2F_H
#define _PSPARTICLEEMITTER2F_H

#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>

#include "psparticle2f.h"
#include "psvector2f.h"

using namespace std;

class PsParticleEmitter2f
{
public:
	PsParticleEmitter2f(
		int maxNumber,
		PsVector2f emitPosition,
		PsVector2f emitPositionRange,
		float emitSpeed,
		float emitMass,
		float emitMassRange,
		float emitSize,
		float emitSizeRange,
		PsColor emitColor,
		PsVector2f emitVelocity,
		PsVector2f emitVelocityRange,
		float emitAngularVelocity,
		float emitAngularVelocityRange,
		float emitAngle,
		float emitAngleRange,
		float emitLifetime,
		float emitLifetimeRange,
		float emitterLifetime,
		float zoom = 20.0f
		);
	virtual ~PsParticleEmitter2f();
	// 初始化maxNumber个粒子
	virtual void initializeParticles();

	// 生成满足均匀分布的浮点数
	float generateUniformDistribution(float base, float radius);
	// 获取最大的渲染参数：所有微粒的顶点数目和，三角形数目和
	void getMaxRenderParameter(int *maxVertexNumber, int *maxtriangleNumber);
	// 获取当前的渲染参数：存活的微粒的顶点数目和，三角形数目和
	void getCurrentRenderParameter(int *currentVertexNumber, int *currentTriangleNumber);

	// 粒子系统运行
	void run(float timeInterval);
	
	// 将获取的用于绘制的数据数组作为数组的一部分
	void getRenderDataasPart(float **vertices, int *verticesBegin, 
		unsigned int **indices, int *indicesBegin, bool hasTexture);



protected:
	// 粒子池：存活粒子、死亡（未激活）粒子
	list<PsParticle2f *> *livingParticles, *deadParticles;
	// 最大粒子数目
	int maxNumber;
	// 发射位置
	PsVector2f emitPosition;
	// 以发射位置为中心的发射范围
	PsVector2f emitPositionRange;
	// 发射粒子的速度：个/秒
	float emitSpeed;

	// 发射粒子的质量及其变动范围
	float emitMass, emitMassRange;
	// 发射粒子的大小（半径）及其变动范围
	float emitSize, emitSizeRange;
	// 发射粒子的颜色
	PsColor emitColor;
	// 发射粒子的初速度及其变动范围
	PsVector2f emitVelocity, emitVelocityRange;
	// 发射粒子的初始角速度及其变动范围
	float emitAngularVelocity, emitAngularVelocityRange;
	// 发射粒子的初始角度及其变动范围
	float emitAngle, emitAngleRange;
	// 发射粒子的生命周期及其变动范围
	float emitLifetime, emitLifetimeRange;
	// 发射器的生命周期
	float emitterLifetime;

	// 尺寸缩放
	float zoom;

	// 发射器的年龄
	float age;
	// 已经发射的时间
	float totalEmitTime;
	// 已经发射的粒子数目
	int totalEmitedParticleNumber;

	int vertexNumberPerParticle;
	int triangleNumberPerParticle;
};

#endif