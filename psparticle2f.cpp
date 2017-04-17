#include "psparticle2f.h"

// Ĭ�Ϲ��캯��
PsParticle2f::PsParticle2f(){
	init(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(0.0f, 0.0f), PsVector2f(0.0f, 0.0f), 
		0.0f, 0.0f, 10.0f, 0.0f);
}

// �û��Զ���ĳ�ʼ������
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

// ��������
PsParticle2f::~PsParticle2f(){

}

// ���ӱ���
inline void PsParticle2f::aging(float timeInterval){
	age += timeInterval;
}

// �����Ƿ񻹻���
bool PsParticle2f::isAlive(){
	return (age <= lifetime);
}

// ���ݵ�ǰλ��ʵʱ�������ӵļ��ٶ� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!���Ľ�
void PsParticle2f::computeAcceleration(){
	acceleration = PsVector2f(0.0f, -1.0f);
}

// �������ӵĽ��ٶ�
void PsParticle2f::computeAngularVelocity(){

}

// �������ӵ��ٶȡ����ٶȡ�λ�úͽǶ�
void PsParticle2f::move(float timeInterval){
	// �������ӵ��ٶ�
	PsVector2f lastVelocity = velocity;
	velocity = velocity + acceleration * timeInterval;

	// �������ӵĽ��ٶ�
	float lastAngularVelocity = angularVelocity;
	computeAngularVelocity();

	// �������ӵ�λ��
	position = position + (lastVelocity + velocity) * 0.5f * timeInterval;

	// �������ӵĽǶ�
	angle = angle + (lastAngularVelocity + angularVelocity) * 0.5f * timeInterval;
}

// ��ӡ������Ϣ
void PsParticle2f::printInfo(){
	cout << "PsParticle2f: mass = " << mass << "; size = " << size << "; color = " << color
		<< "; acceleration = " << acceleration << "; velocity = " << velocity << "; position = "
		<< position << "; angularVelocity = " << angularVelocity << "; angle = " << angle
		<< "; lifetime = " << lifetime << "; age = " << age << endl;
}

// ���������
ostream &operator<<(ostream &os, const PsParticle2f &psParticle2f){
	os << "(mass = " << psParticle2f.mass << "; size = " << psParticle2f.size << "; color = " 
		<< psParticle2f.color << "; acceleration = " << psParticle2f.acceleration << "; velocity = " 
		<< psParticle2f.velocity << "; position = " << psParticle2f.position << "; angularVelocity = " 
		<< psParticle2f.angularVelocity << "; angle = " << psParticle2f.angle << "; lifetime = " 
		<< psParticle2f.lifetime << "; age = " << psParticle2f.age << ")";
	return os;
}