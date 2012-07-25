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
	std::vector<int>		harmonics;

public:
	Instrument(double attackTime, 
		double decayTime, double sustainLvl, 
		double releaseTime);

	~Instrument();

	void addHarmonic(int h);

	double getADRduration(); 

	double getNoteValue(sp::Note note, double t0, double t, 
		double mpl, double volume, double holdDuration);


	/*
		Discretize a note based on the start time of its pressing, the
		duration (time while pressed) and the volume 
		(relative volume or absolute, doesn't matter)
	*/
	double discretizeChord(sp::Chord chord, double t0, double duration, double volume);
};

}

#endif