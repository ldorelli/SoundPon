#ifndef SINOID_H
#define SINOID_H

#include <instrument.h>

namespace sp {

class Sinoid: public Instrument {
protected:
	const double PI = acos(-1);
	/**
	 *	Returns the current amplitude and advances time for that note.
	 */
	double sustain(sp::PressedNote& note, double timeStep);
	double attack(sp::PressedNote& note, double timeStep) {};
	double decay(sp::PressedNote& note, double timeStep) {};

public:
	void releaseNote(int idx);
	int pressNote (double frequency, double volume);
	Sinoid();
};

}
#endif