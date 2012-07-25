#ifndef CHORD_H
#define CHORD_H

#include <vector>
#include <utility>
#include <note.h>


namespace sp {

/* 
	Class that represents a chord
*/
class Chord {
private:

	std::vector< std::pair<sp::Note, double> >		notes;
	double									totalVolume;

public:

	Chord();

	/*
		Adds a note to the chord
	*/	
	void addNote(sp::Note n, double I = 1.0);

	/* 
		Generates the correct wave of the Chord 
		Can be used to represent a single note 
	*/
	double discretize(int t, double baseFrequency, 
		double maxVolume);

	/* 
		Return only the mixed frequency of notes
	*/
	double getMixedFrequency(double t, double baseFrequency);

	static double discretizeSingleNote(
		sp::Note note, double t, double baseFrequency, double volume);
};

}

#endif