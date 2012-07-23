#include <chord.h>
#include <cmath>
#include <algorithm>
#include <iostream>

sp::Chord::Chord() {
	totalVolume = 0.0;
}

void sp::Chord::addNote(sp::Note n, int I) {
	totalVolume += I;
	notes.push_back( std::make_pair(n, I) );
}

double sp::Chord::discretize(int t, double baseFrequency, double volume) 
{
	/* 
		Calculates the intensity per note from the chord
		Default adding notes (with I=1) will make them all
		have the same weight, hence an arithmetic mean will 
		be calculated.
	*/
	double val = 0.0;
	for(int i = 0; i < notes.size(); i++)
		val += notes[i].second/totalVolume * volume *
			sin(t * baseFrequency * notes[i].first.getFrequency());
	return val;
}

double sp::Chord::discretizeSingleNote(sp::Note note,
 int t, double baseFrequency, double volume)
{
	double mx = 4;

	return volume * ( sin(t * baseFrequency * note.getFrequency())
		+ sin(t * baseFrequency * 2 * note.getFrequency())
		+ sin(t * baseFrequency * 3 * note.getFrequency()) 
		+ sin(t * baseFrequency * 4 * note.getFrequency()) )/mx;
}