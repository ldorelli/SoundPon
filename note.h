#ifndef NOTES_H
#define NOTES_H

#include <vector>
#include <utility>

namespace sp {

enum Note_ { 
		
		C, Cf, Cb, 
		D, Df, Db, 
		E, Ef, Eb, 
		F, Ff, Fb, 
		G, Gf, Gb,
		A, Af, Ab, 
		B, Bf, Bb, 
	}	;

class Note {
private:
	int		octave;
	Note_ 	note;

	Note(){}

public:

	static const double frequencyTable[10][21];

	Note(Note_ note, int octave);

	Note operator+ (const Note &b) const;
};

}

#endif