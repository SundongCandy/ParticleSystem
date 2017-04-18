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

	// ��ȡ΢���Ķ�����Ŀ�ͻ���΢������Ҫ����������Ŀ
	void getRenderParameter(int &_vertexNumber, int &_triangleNumber);
	// ��ʼ��������ɫ�����������������Ϣ
	virtual void initData();
	// ��ʼ������¶�������
	virtual void refreshVertices();
	// ��ӡ���ڻ�����Ⱦ��������Ϣ
	void printRenderData();
	// ��ȡ���ڻ��Ƶ���������
	void getRenderData(float **_vertices, unsigned int **_indices, bool hasTexture);
	// ����ȡ�����ڻ��Ƶ�����������Ϊ�����һ����
	void getRenderDataasPart(float **_vertices, int *_verticesBegin, unsigned int **_indices, int *_indicesBegin, bool hasTexture);

	// ���óߴ����ű���
	void setZoom(float zoom);
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

	// ΢���Ķ�����Ŀ
	int vertexNumber;
	// ΢���Ķ�������
	float *vertices;
	// ΢���Ķ�����ɫ
	float *vertexColors;
	// ΢������������
	float *textureCoordinates;
	// ����΢������Ҫ����������Ŀ
	int triangleNumber;
	// ����΢�������������εĶ�������
	unsigned int *indices;
	// �ߴ�����
	float zoom;
};

#endif