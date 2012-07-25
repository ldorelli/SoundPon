#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <note.h>
#include <chord.h>
#include <vector>

namespace sp {

class Instrument
{
	double		 attackTime;
	double	 	 decayTime;
	double 		 sustainLvl;
	double 		 releaseTime;	
	std::vector<double>		harmonics;

public:
	Instrument(double attackTime, 
		double decayTime, double sustainLvl, 
		double releaseTime);

	~Instrument();

	void addHarmonic(double h);

	double getADRduration(); 

	double getAmplitude(double note, double t0, double t, 
		double mpl, double volume, double holdDuration);
};

}

#endif