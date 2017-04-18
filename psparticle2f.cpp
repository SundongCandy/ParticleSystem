#include "psparticle2f.h"

// Ĭ�Ϲ��캯��
PsParticle2f::PsParticle2f(){
	// ��ʼ��������Ⱦ������ ��Щ���ݶ���ĳ���ض���΢���ǲ����
	vertexNumber = 3;
	triangleNumber = 1;
	vertices = (float *)malloc(sizeof(float) * vertexNumber * 2);
	vertexColors = (float *)malloc(sizeof(float) * vertexNumber * 3);
	textureCoordinates = (float *)malloc(sizeof(float) * vertexNumber * 2);
	indices = (unsigned int *)malloc(sizeof(unsigned int) * triangleNumber * 3);

	// ��ʼ����������һ���ֲ�������
	init(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(0.0f, -1.0f), PsVector2f(0.0f, 0.0f), 
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
	zoom = 1.0f;

	// ��ʼ��������ɫ�����������������Ϣ
	initData();
	// ��ʼ������¶�������
	refreshVertices();
}

// ��������
PsParticle2f::~PsParticle2f(){
	if (vertices != NULL)
		free(vertices);
	if (vertexColors != NULL)
		free(vertexColors);
	if (textureCoordinates != NULL)
		free(textureCoordinates);
	if (indices != NULL)
		free(indices);
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

// ��ȡ΢���Ķ�����Ŀ�ͻ���΢������Ҫ����������Ŀ
void PsParticle2f::getRenderParameter(int &_vertexNumber, int &_triangleNumber){
	_vertexNumber = vertexNumber;
	_triangleNumber = triangleNumber;
}

// ��ʼ��������ɫ�����������������Ϣ
void PsParticle2f::initData(){
	const float squareRootof3 = 1.732050807569f;
	// ���½�
	vertexColors[0] = color.r; // ��ɫ
	vertexColors[1] = color.g;
	vertexColors[2] = color.b;
	textureCoordinates[0] = 1.0f; // ��������
	textureCoordinates[1] = 0.0f;

	// ���½�
	vertexColors[3] = color.r; // ��ɫ
	vertexColors[4] = color.g;
	vertexColors[5] = color.b;
	textureCoordinates[2] = 0.0f; // ��������
	textureCoordinates[3] = 0.0f;

	// ����
	vertexColors[6] = color.r; // ��ɫ
	vertexColors[7] = color.g;
	vertexColors[8] = color.b;
	textureCoordinates[4] = 0.5f; // ��������
	textureCoordinates[5] = 0.5f * squareRootof3;

	indices[0] = 0; // ������Ϣ
	indices[1] = 1;
	indices[2] = 2;
}

// ��ʼ������¶�������
void PsParticle2f::refreshVertices(){
	const float squareRootof3 = 1.732050807569f;
	
	// ���½�
	vertices[0] = (position.x + 0.5f * squareRootof3 * size) / zoom;
	vertices[1] = (position.y - 0.5f * size) / zoom;
	
	// ���½�
	vertices[2] = (position.x - 0.5f * squareRootof3 * size) / zoom;
	vertices[3] = (position.y - 0.5f * size) / zoom;
	
	// ����
	vertices[4] = (position.x) / zoom;
	vertices[5] = (position.y + size) / zoom;
}

// ��ӡ���ڻ�����Ⱦ��������Ϣ
void PsParticle2f::printRenderData(){
	cout << "vertexNumber = " << vertexNumber << ", triangleNumber = " << triangleNumber << endl;

	cout << "vertices: " << endl;
	for (int i = 0; i < vertexNumber; ++i){
		// λ��
		cout << vertices[i * 2] << " ";
		cout << vertices[i * 2 + 1] << " ";
		cout << "0 ";

		//  ��ɫ
		cout << vertexColors[i * 3] << " ";
		cout << vertexColors[i * 3 + 1] << " ";
		cout << vertexColors[i * 3 + 2] << " ";

		// ��������
		cout << textureCoordinates[2 * i] << " ";
		cout << textureCoordinates[2 * i + 1];

		cout << endl;
	}
	cout << "indices: " << endl;
	for (int i = 0; i < triangleNumber; ++i){
		cout << indices[i * 3] << " ";
		cout << indices[i * 3 + 1] << " ";
		cout << indices[i * 3 + 2];
		cout << endl;
	}
}

// ��ȡ���ڻ��Ƶ���������
void PsParticle2f::getRenderData(float **_vertices, unsigned int **_indices, bool hasTexture){
	if (hasTexture){
		*_vertices = (float *)malloc(sizeof(float) * 8 * vertexNumber);
		*_indices = (unsigned int *)malloc(sizeof(unsigned int) * 3 * triangleNumber);

		for (int i = 0; i < vertexNumber; ++i){
			// λ��
			(*_vertices)[i * 8] = vertices[2 * i];
			(*_vertices)[i * 8 + 1] = vertices[2 * i + 1];
			(*_vertices)[i * 8 + 2] = 0.0f;
			// ��ɫ
			(*_vertices)[i * 8 + 3] = vertexColors[3 * i];
			(*_vertices)[i * 8 + 4] = vertexColors[3 * i + 1];
			(*_vertices)[i * 8 + 5] = vertexColors[3 * i + 2];
			// ��������
			(*_vertices)[i * 8 + 6] = textureCoordinates[2 * i];
			(*_vertices)[i * 8 + 7] = textureCoordinates[2 * i + 1];
		}
		for (int i = 0; i < triangleNumber; ++i){
			(*_indices)[i * 3] = indices[i * 3];
			(*_indices)[i * 3 + 1] = indices[i * 3 + 1];
			(*_indices)[i * 3 + 2] = indices[i * 3 + 2];
		}
	}
	else{

	}
}

// ����ȡ�����ڻ��Ƶ�����������Ϊ�����һ����
void PsParticle2f::getRenderDataasPart(float **_vertices, int *_verticesBegin, unsigned int **_indices, int *_indicesBegin, bool hasTexture){
	int indexElementsBegin = *_verticesBegin / 8; 
	if (hasTexture){
		for (int i = 0; i < vertexNumber; ++i){
			// λ��
			(*_vertices)[*_verticesBegin + i * 8] = vertices[2 * i];
			(*_vertices)[*_verticesBegin + i * 8 + 1] = vertices[2 * i + 1];
			(*_vertices)[*_verticesBegin + i * 8 + 2] = 0.0f;
			// ��ɫ
			(*_vertices)[*_verticesBegin + i * 8 + 3] = vertexColors[3 * i];
			(*_vertices)[*_verticesBegin + i * 8 + 4] = vertexColors[3 * i + 1];
			(*_vertices)[*_verticesBegin + i * 8 + 5] = vertexColors[3 * i + 2];
			// ��������
			(*_vertices)[*_verticesBegin + i * 8 + 6] = textureCoordinates[2 * i];
			(*_vertices)[*_verticesBegin + i * 8 + 7] = textureCoordinates[2 * i + 1];
		}
		*_verticesBegin = *_verticesBegin + 8 * vertexNumber;
		for (int i = 0; i < triangleNumber; ++i){
			(*_indices)[*_indicesBegin + i * 3] = indices[i * 3] + indexElementsBegin;
			(*_indices)[*_indicesBegin + i * 3 + 1] = indices[i * 3 + 1] + indexElementsBegin;
			(*_indices)[*_indicesBegin + i * 3 + 2] = indices[i * 3 + 2] + indexElementsBegin;
		}
		*_indicesBegin = *_indicesBegin + 3 * triangleNumber;
	}
	else{

	}
}

void PsParticle2f::setZoom(float zoom){
	this->zoom = zoom;
}