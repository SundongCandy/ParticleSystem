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
	// ��ʼ��maxNumber������
	virtual void initializeParticles();

	// ����������ȷֲ��ĸ�����
	float generateUniformDistribution(float base, float radius);
	// ��ȡ������Ⱦ����������΢���Ķ�����Ŀ�ͣ���������Ŀ��
	void getMaxRenderParameter(int *maxVertexNumber, int *maxtriangleNumber);
	// ��ȡ��ǰ����Ⱦ����������΢���Ķ�����Ŀ�ͣ���������Ŀ��
	void getCurrentRenderParameter(int *currentVertexNumber, int *currentTriangleNumber);

	// ����ϵͳ����
	void run(float timeInterval);
	
	// ����ȡ�����ڻ��Ƶ�����������Ϊ�����һ����
	void getRenderDataasPart(float **vertices, int *verticesBegin, 
		unsigned int **indices, int *indicesBegin, bool hasTexture);



protected:
	// ���ӳأ�������ӡ�������δ�������
	list<PsParticle2f *> *livingParticles, *deadParticles;
	// ���������Ŀ
	int maxNumber;
	// ����λ��
	PsVector2f emitPosition;
	// �Է���λ��Ϊ���ĵķ��䷶Χ
	PsVector2f emitPositionRange;
	// �������ӵ��ٶȣ���/��
	float emitSpeed;

	// �������ӵ���������䶯��Χ
	float emitMass, emitMassRange;
	// �������ӵĴ�С���뾶������䶯��Χ
	float emitSize, emitSizeRange;
	// �������ӵ���ɫ
	PsColor emitColor;
	// �������ӵĳ��ٶȼ���䶯��Χ
	PsVector2f emitVelocity, emitVelocityRange;
	// �������ӵĳ�ʼ���ٶȼ���䶯��Χ
	float emitAngularVelocity, emitAngularVelocityRange;
	// �������ӵĳ�ʼ�Ƕȼ���䶯��Χ
	float emitAngle, emitAngleRange;
	// �������ӵ��������ڼ���䶯��Χ
	float emitLifetime, emitLifetimeRange;
	// ����������������
	float emitterLifetime;

	// �ߴ�����
	float zoom;

	// ������������
	float age;
	// �Ѿ������ʱ��
	float totalEmitTime;
	// �Ѿ������������Ŀ
	int totalEmitedParticleNumber;

	int vertexNumberPerParticle;
	int triangleNumberPerParticle;
};

#endif