#include "psparticle2f.h"

// 默认构造函数
PsParticle2f::PsParticle2f(){
	init(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(0.0f, 0.0f), PsVector2f(0.0f, 0.0f), 
		0.0f, 0.0f, 10.0f, 0.0f);
}

// 用户自定义的初始化函数
void PsParticle2f::init(float mass, float size, PsColor color, PsVector2f velocity, PsVector2f position,
	float angularVelocity, float angle, float lifetime, float age){
	this->mass = mass;
	this->size = size;
	this->color = color;
	this->velocity = velocity;
	this->position = position;
	this->angularVelocity = angularVelocity;
	this->angle = angle;
	this->lifetime = lifetime;
	this->age = age;

	acceleration = PsVector2f(0.0f, 0.0f);
}

// 析构函数
PsParticle2f::~PsParticle2f(){

}

// 粒子变老
inline void PsParticle2f::aging(float timeInterval){
	age += timeInterval;
}

// 粒子是否还活着
bool PsParticle2f::isAlive(){
	return (age <= lifetime);
}

// 根据当前位置实时计算粒子的加速度 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!待改进
void PsParticle2f::computeAcceleration(){
	acceleration = PsVector2f(0.0f, -1.0f);
}

// 计算粒子的角速度
void PsParticle2f::computeAngularVelocity(){

}

// 计算粒子的速度、角速度、位置和角度
void PsParticle2f::move(float timeInterval){
	// 计算粒子的速度
	PsVector2f lastVelocity = velocity;
	velocity = velocity + acceleration * timeInterval;

	// 计算粒子的角速度
	float lastAngularVelocity = angularVelocity;
	computeAngularVelocity();

	// 计算粒子的位置
	position = position + (lastVelocity + velocity) * 0.5f * timeInterval;

	// 计算粒子的角度
	angle = angle + (lastAngularVelocity + angularVelocity) * 0.5f * timeInterval;
}

// 打印粒子信息
void PsParticle2f::printInfo(){
	cout << "PsParticle2f: mass = " << mass << "; size = " << size << "; color = " << color
		<< "; acceleration = " << acceleration << "; velocity = " << velocity << "; position = "
		<< position << "; angularVelocity = " << angularVelocity << "; angle = " << angle
		<< "; lifetime = " << lifetime << "; age = " << age << endl;
}

// 重载输出流
ostream &operator<<(ostream &os, const PsParticle2f &psParticle2f){
	os << "(mass = " << psParticle2f.mass << "; size = " << psParticle2f.size << "; color = " 
		<< psParticle2f.color << "; acceleration = " << psParticle2f.acceleration << "; velocity = " 
		<< psParticle2f.velocity << "; position = " << psParticle2f.position << "; angularVelocity = " 
		<< psParticle2f.angularVelocity << "; angle = " << psParticle2f.angle << "; lifetime = " 
		<< psParticle2f.lifetime << "; age = " << psParticle2f.age << ")";
	return os;
}