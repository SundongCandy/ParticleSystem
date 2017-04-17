#ifndef _PSPARTICLE2F_H
#define _PSPARTICLE2F_H

#include <iostream>
#include "psvector2f.h"
#include "pscolor.h"

using namespace std;

class PsParticle2f{
public:
	// Ĭ�Ϲ��캯��
	PsParticle2f();
	// �û��Զ���ĳ�ʼ������
	void init(float mass, float size, PsColor color, PsVector2f velocity, PsVector2f position, 
		float angularVelocity, float angle, float lifetime, float age);
	// ��������
	virtual ~PsParticle2f();
	// ���ӱ���
	virtual void aging(float timeInterval);
	// �����Ƿ񻹻���
	virtual bool isAlive();
	// ���ݵ�ǰλ��ʵʱ�������ӵļ��ٶ�
	void computeAcceleration();
	// �������ӵĽ��ٶ�
	virtual void computeAngularVelocity();
	// �������ӵ��ٶȡ����ٶȡ�λ�úͽǶ�
	void move(float timeInterval);
	// ��ӡ������Ϣ
	virtual void printInfo();

	// ���������
	friend ostream &operator<<(ostream &os, const PsParticle2f &psParticle2f);

protected:
	// ���ӵ�����
	float mass;
	// ���ӵĴ�С���뾶��
	float size;
	// ���ӵ���ɫ
	PsColor color;
	// ���ӵļ��ٶ�
	PsVector2f acceleration;
	// ���ӵ��ٶ�
	PsVector2f velocity;
	// ���ӵ�λ��
	PsVector2f position;
	// ���ӵĽ��ٶ�
	float angularVelocity;
	// ���ӵĽǶ�
	float angle;
	// ���ӵ���������
	float lifetime;
	// ���ӵ�����
	float age;
};

#endif