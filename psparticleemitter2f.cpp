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
	// 最大粒子数目
	this->maxNumber = maxNumber;
	// 发射位置
	this->emitPosition = emitPosition;
	// 以发射位置为中心的发射范围
	this->emitPositionRange = emitPositionRange;
	// 发射粒子的速度：个/秒
	this->emitSpeed = emitSpeed;

	// 发射粒子的质量及其变动范围
	this->emitMass = emitMass;
	this->emitMassRange = emitMassRange;
	// 发射粒子的大小（半径）及其变动范围
	this->emitSize = emitSize;
	this->emitSizeRange = emitSizeRange;
	// 发射粒子的颜色
	this->emitColor = emitColor;
	// 发射粒子的初速度及其变动范围
	this->emitVelocity = emitVelocity;
	this->emitVelocityRange = emitVelocityRange;
	// 发射粒子的初始角速度及其变动范围
	this->emitAngularVelocity = emitAngularVelocity;
	this->emitAngularVelocityRange = emitAngularVelocityRange;
	// 发射粒子的初始角度及其变动范围
	this->emitAngle = emitAngle;
	this->emitAngleRange = emitAngleRange;
	// 发射粒子的生命周期及其变动范围
	this->emitLifetime = emitLifetime;
	this->emitLifetimeRange = emitLifetimeRange;
	// 发射器的生命周期
	this->emitterLifetime = emitterLifetime;

	// 尺寸缩放
	this->zoom = zoom;

	// 初始化发射器的年龄
	age = 0.0f;
	// 已经发射的时间
	totalEmitTime = 0.0f;
	// 初始化已经发射的粒子数目
	totalEmitedParticleNumber = 0;

	// 初始化粒子池队列
	livingParticles = new list < PsParticle2f * >;
	deadParticles = new list < PsParticle2f * > ;

	// 设置随机数生成种子
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

// 初始化maxNumber个粒子
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

// 生成满足均匀分布的浮点数
float PsParticleEmitter2f::generateUniformDistribution(float base, float radius){
	float probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float result = base - radius + 2.0f * radius * probability;

	return result;
}

// 获取最大的渲染参数：所有微粒的顶点数目和，三角形数目和
void PsParticleEmitter2f::getMaxRenderParameter(int *maxVertexNumber, int *maxtriangleNumber){
	*maxVertexNumber = maxNumber * vertexNumberPerParticle;
	*maxtriangleNumber = maxNumber *triangleNumberPerParticle;
}

// 获取当前的渲染参数：存活的微粒的顶点数目和，三角形数目和
void PsParticleEmitter2f::getCurrentRenderParameter(int *currentVertexNumber, int *currentTriangleNumber){
	int currentParticleNumber = livingParticles->size();
	*currentVertexNumber = currentParticleNumber * vertexNumberPerParticle;
	*currentTriangleNumber = currentParticleNumber * triangleNumberPerParticle;
}

// 粒子系统运行
void PsParticleEmitter2f::run(float timeInterval){
	/*PsParticle2f *tempPsParticle2f;
	list<PsParticle2f *>::iterator it;
	for (it = livingParticles->begin(); it != livingParticles->end(); ++it){
		tempPsParticle2f = *it;
		// 微粒变老
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
		// 微粒变老
		tempPsParticle2f->aging(timeInterval);
		// 微粒还活着
		if (tempPsParticle2f->isAlive()){
			//cout << "----------begin: " << endl << *tempPsParticle2f << endl;
			tempPsParticle2f->computeAcceleration();
			tempPsParticle2f->move(timeInterval);
			tempPsParticle2f->refreshVertices();
			//cout << "----------end: " << endl << *tempPsParticle2f << endl;

			it++;
		}
		// 微粒死亡，初始化粒子，放入死亡（未激活）粒子池中
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

// 将获取的用于绘制的数据数组作为数组的一部分
void PsParticleEmitter2f::getRenderDataasPart(float **vertices, int *verticesBegin,
	unsigned int **indices, int *indicesBegin, bool hasTexture){
	list<PsParticle2f *>::iterator it;
	PsParticle2f *tempPsParticle2f;

	for (it = livingParticles->begin(); it != livingParticles->end(); ++it){
		tempPsParticle2f = *it;
		
		tempPsParticle2f->getRenderDataasPart(vertices, verticesBegin, indices, indicesBegin, hasTexture);
	}
}