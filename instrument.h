#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <note.h>
#include <chord.h>

namespace sp {

class Instrument
{
	double		 attackTime;
	double	 	 decayTime;
	double 		 sustainLvl;
	double 		 releaseTime;	
	int 		 harmonicsProduced;

public:
	Instrument(double attackTime, 
		double decayTime, double sustainLvl, 
		double releaseTime, int harmonicsProduced);

	~Instrument();

	double dicretizeChord(sp::Note note, double t0, double duration, double volume);


	/*
		Discretize a note based on the start time of its pressing, the
		duration (time while pressed) and the volume 
		(relative volume or absolute, doesn't matter)
	*/
	double discretizeNote(sp::Chord chord, double t0, double duration, double volume);
};

}

#endif