#ifndef _PSCOLOR_H
#define _PSCOLOR_H

#include <iostream>
using namespace std;

class PsColor
{
public:
	PsColor();
	PsColor(float r, float g, float b, float alpha = 1.0f);
	~PsColor();
	void printInfo();
	float r;
	float g;
	float b;
	float alpha;

	// жидиЪфГіСї
	friend ostream &operator<<(ostream &os, const PsColor &psColor);
};

#endif