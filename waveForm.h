#ifndef WAVEFORM_H
#define WAVEFORM_H
#include <iostream>
#include <cmath>

class WaveForm
{
public:
	virtual double operator () (int t)  = 0;
};

class sineWave : public WaveForm {
public:
	double operator () (int t) {
		return 32700 * sin( (double) t);
	}
};

#endif 