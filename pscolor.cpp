#include "pscolor.h"

PsColor::PsColor(){
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	alpha = 1.0f;
}

PsColor::PsColor(float r, float g, float b, float alpha){
	this->r = r;
	this->g = g;
	this->b = b;
	this->alpha = alpha;
}

PsColor::~PsColor(){}

void PsColor::printInfo(){
	cout << "PsColor: r = " << r << "; g = " << g << "; b = " << b << "; alpha = " << alpha << endl;
}

// ÖØÔØÊä³öÁ÷
ostream &operator<<(ostream &os, const PsColor &psColor){
	os << "(" << psColor.r << ", " << psColor.g << ", " << psColor.b << ", " << psColor.alpha << ")";
	return os;
}