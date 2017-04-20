#include "psparticleemitter2f.h"

PsParticleEmitter2f::PsParticleEmitter2f(
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
	float zoom
	){
	// ���������Ŀ
	this->maxNumber = maxNumber;
	// ����λ��
	this->emitPosition = emitPosition;
	// �Է���λ��Ϊ���ĵķ��䷶Χ
	this->emitPositionRange = emitPositionRange;
	// �������ӵ��ٶȣ���/��
	this->emitSpeed = emitSpeed;

	// �������ӵ���������䶯��Χ
	this->emitMass = emitMass;
	this->emitMassRange = emitMassRange;
	// �������ӵĴ�С���뾶������䶯��Χ
	this->emitSize = emitSize;
	this->emitSizeRange = emitSizeRange;
	// �������ӵ���ɫ
	this->emitColor = emitColor;
	// �������ӵĳ��ٶȼ���䶯��Χ
	this->emitVelocity = emitVelocity;
	this->emitVelocityRange = emitVelocityRange;
	// �������ӵĳ�ʼ���ٶȼ���䶯��Χ
	this->emitAngularVelocity = emitAngularVelocity;
	this->emitAngularVelocityRange = emitAngularVelocityRange;
	// �������ӵĳ�ʼ�Ƕȼ���䶯��Χ
	this->emitAngle = emitAngle;
	this->emitAngleRange = emitAngleRange;
	// �������ӵ��������ڼ���䶯��Χ
	this->emitLifetime = emitLifetime;
	this->emitLifetimeRange = emitLifetimeRange;
	// ����������������
	this->emitterLifetime = emitterLifetime;

	// �ߴ�����
	this->zoom = zoom;

	// ��ʼ��������������
	age = 0.0f;
	// �Ѿ������ʱ��
	totalEmitTime = 0.0f;
	// ��ʼ���Ѿ������������Ŀ
	totalEmitedParticleNumber = 0;

	// ��ʼ�����ӳض���
	livingParticles = new list < PsParticle2f * >;
	deadParticles = new list < PsParticle2f * > ;

	// �����������������
	srand(static_cast<unsigned>(time(0)));

	initializeParticles();
}

PsParticleEmitter2f::~PsParticleEmitter2f(){
	list<PsParticle2f *>::iterator it;
	for (it = livingParticles->begin(); it != livingParticles->end();){
		it = livingParticles->erase(it);
	}
	for (it = deadParticles->begin(); it != deadParticles->end();){
		it = deadParticles->erase(it);
	}
}

// ��ʼ��maxNumber������
void PsParticleEmitter2f::initializeParticles(){
	PsParticle2f *temp;
	for (int i = 0; i < maxNumber; ++i){
		temp = new PsParticle2f(
			generateUniformDistribution(emitMass, emitMassRange),
			generateUniformDistribution(emitSize, emitSizeRange),
			emitColor,
			PsVector2f(
			generateUniformDistribution(emitVelocity.x, emitVelocityRange.x),
			generateUniformDistribution(emitVelocity.y, emitVelocityRange.y)
			),
			PsVector2f(
			generateUniformDistribution(emitPosition.x, emitPositionRange.x),
			generateUniformDistribution(emitPosition.y, emitPositionRange.y)
			),
			generateUniformDistribution(emitAngularVelocity, emitAngularVelocityRange),
			generateUniformDistribution(emitAngle, emitAngleRange),
			generateUniformDistribution(emitLifetime, emitLifetimeRange),
			0.0f, 
			zoom
			);
		//if (i % 6 == 0)
		//	livingParticles->push_back(temp);
		//else
			deadParticles->push_back(temp);
		//cout << *temp << endl << endl;
	}
	temp = deadParticles->front();
	vertexNumberPerParticle = temp->getVertexNumber();
	triangleNumberPerParticle = temp->getTriangelNumber();
	//cout << "vertexNumberPerParticle = " << vertexNumberPerParticle << ", triangleNumberPerParticle = "
	//	<< triangleNumberPerParticle << endl;
}

// ����������ȷֲ��ĸ�����
float PsParticleEmitter2f::generateUniformDistribution(float base, float radius){
	float probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float result = base - radius + 2.0f * radius * probability;

	return result;
}

// ��ȡ������Ⱦ����������΢���Ķ�����Ŀ�ͣ���������Ŀ��
void PsParticleEmitter2f::getMaxRenderParameter(int *maxVertexNumber, int *maxtriangleNumber){
	*maxVertexNumber = maxNumber * vertexNumberPerParticle;
	*maxtriangleNumber = maxNumber *triangleNumberPerParticle;
}

// ��ȡ��ǰ����Ⱦ����������΢���Ķ�����Ŀ�ͣ���������Ŀ��
void PsParticleEmitter2f::getCurrentRenderParameter(int *currentVertexNumber, int *currentTriangleNumber){
	int currentParticleNumber = livingParticles->size();
	*currentVertexNumber = currentParticleNumber * vertexNumberPerParticle;
	*currentTriangleNumber = currentParticleNumber * triangleNumberPerParticle;
}

// ����ϵͳ����
void PsParticleEmitter2f::run(float timeInterval){
	/*PsParticle2f *tempPsParticle2f;
	list<PsParticle2f *>::iterator it;
	for (it = livingParticles->begin(); it != livingParticles->end(); ++it){
		tempPsParticle2f = *it;
		// ΢������
		tempPsParticle2f->aging(timeInterval);
		tempPsParticle2f->computeAcceleration();
		tempPsParticle2f->move(timeInterval);
		tempPsParticle2f->refreshVertices();
	}*/
	PsParticle2f *tempPsParticle2f;
	totalEmitTime += timeInterval;
	int newParticleNumber = static_cast<int>(totalEmitTime * emitSpeed) - totalEmitedParticleNumber;
	if (newParticleNumber > 0){
		for (int i = 0; i < newParticleNumber; ++i){
			if (!deadParticles->empty()){
				tempPsParticle2f = deadParticles->front();
				livingParticles->push_back(tempPsParticle2f);
				deadParticles->pop_front();
				totalEmitedParticleNumber += 1;
				//cout << *tempPsParticle2f << endl;
			}
			else
				break;
		}
	}
	if (totalEmitedParticleNumber > maxNumber){
		totalEmitTime = 0.0f;
		totalEmitedParticleNumber = 0;
	}

	list<PsParticle2f *>::iterator it;
	for (it = livingParticles->begin(); it != livingParticles->end();){
		tempPsParticle2f = *it;
		// ΢������
		tempPsParticle2f->aging(timeInterval);
		// ΢��������
		if (tempPsParticle2f->isAlive()){
			//cout << "----------begin: " << endl << *tempPsParticle2f << endl;
			tempPsParticle2f->computeAcceleration();
			tempPsParticle2f->move(timeInterval);
			tempPsParticle2f->refreshVertices();
			//cout << "----------end: " << endl << *tempPsParticle2f << endl;

			it++;
		}
		// ΢����������ʼ�����ӣ�����������δ������ӳ���
		else{
			it = livingParticles->erase(it);
			tempPsParticle2f->init(
				generateUniformDistribution(emitMass, emitMassRange),
				generateUniformDistribution(emitSize, emitSizeRange),
				emitColor,
				PsVector2f(
				generateUniformDistribution(emitVelocity.x, emitVelocityRange.x),
				generateUniformDistribution(emitVelocity.y, emitVelocityRange.y)
				),
				PsVector2f(
				generateUniformDistribution(emitPosition.x, emitPositionRange.x),
				generateUniformDistribution(emitPosition.y, emitPositionRange.y)
				),
				generateUniformDistribution(emitAngularVelocity, emitAngularVelocityRange),
				generateUniformDistribution(emitAngle, emitAngleRange),
				generateUniformDistribution(emitLifetime, emitLifetimeRange),
				0.0f,
				zoom
				);
			//cout << *tempPsParticle2f << endl;
			deadParticles->push_back(tempPsParticle2f);
		}
	}
}

// ����ȡ�����ڻ��Ƶ�����������Ϊ�����һ����
void PsParticleEmitter2f::getRenderDataasPart(float **vertices, int *verticesBegin,
	unsigned int **indices, int *indicesBegin, bool hasTexture){
	list<PsParticle2f *>::iterator it;
	PsParticle2f *tempPsParticle2f;

	for (it = livingParticles->begin(); it != livingParticles->end(); ++it){
		tempPsParticle2f = *it;
		
		tempPsParticle2f->getRenderDataasPart(vertices, verticesBegin, indices, indicesBegin, hasTexture);
	}
}