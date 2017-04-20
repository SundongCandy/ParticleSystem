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
	// 用户自定义的构造函数
	PsParticle2f(float mass, float size, PsColor color, PsVector2f velocity, PsVector2f position,
		float angularVelocity, float angle, float lifetime, float age, float zoom = 20.0f);
	// 用户自定义的初始化函数
	void init(float mass, float size, PsColor color, PsVector2f velocity, PsVector2f position, 
		float angularVelocity, float angle, float lifetime, float age, float zoom = 20.0f);
	// 析构函数
	virtual ~PsParticle2f();
	// 粒子变老
	virtual void aging(float timeInterval);
	// 粒子是否还活着
	virtual bool isAlive();
	// 根据当前位置实时计算粒子的加速度
	void computeAcceleration();
	// 计算粒子的角速度
	void computeAngularVelocity();
	// 计算粒子的速度、角速度、位置和角度
	void move(float timeInterval);
	// 打印粒子信息
	virtual void printInfo();

	// 重载输出流
	friend ostream &operator<<(ostream &os, const PsParticle2f &psParticle2f);

	// 获取微粒的顶点数目和绘制微粒所需要的三角形数目
	void getRenderParameter(int &_vertexNumber, int &_triangleNumber);
	
	// 初始化或更新顶点坐标
	virtual void refreshVertices();
	// 打印用于绘制渲染的数据信息
	void printRenderData();
	// 获取用于绘制的数据数组
	void getRenderData(float **_vertices, unsigned int **_indices, bool hasTexture);
	// 将获取的用于绘制的数据数组作为数组的一部分
	void getRenderDataasPart(float **_vertices, int *_verticesBegin, unsigned int **_indices, int *_indicesBegin, bool hasTexture);

	// 重新设置粒子尺寸
	void resetSize(float size);

	// 获取绘制微粒所需要的三角形数目
	int getTriangelNumber();
	// 获取微粒的顶点数目
	int getVertexNumber();

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
	// 尺寸缩放
	float zoom;

	// 微粒的顶点数目
	int vertexNumber;
	// 微粒的顶点坐标
	float *vertices;
	// 微粒的顶点颜色
	float *vertexColors;
	// 微粒的纹理坐标
	float *textureCoordinates;
	// 绘制微粒所需要的三角形数目
	int triangleNumber;
	// 绘制微粒的所有三角形的顶点索引
	unsigned int *indices;
	

	// 申请存储渲染绘制用的数据的空间，在类构建时调用一次
	virtual void applyMemory();
	// 初始化顶点颜色、纹理坐标和索引信息
	virtual void initData();
};

#endif