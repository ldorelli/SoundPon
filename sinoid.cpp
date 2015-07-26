#include <sinoid.h>

sp::Sinoid::Sinoid() {
	harmonics.push_back(1);
	harmonics.push_back(2);
	harmonics.push_back(3);
}

double sp::Sinoid::sustain(sp::PressedNote& note, double timeStep) {
	double res = 0.0;
	for (int harmonic : harmonics) {
		res += sin(PI * note.time * note.frequency * (double) harmonic);
	}
	note.time += timeStep;
	// std::cout << note.frequency << " " << note.time << " " << res << std::endl;
	return (res * note.volume)/(harmonics.size() * notesOn.size());
}

void sp::Sinoid::releaseNote(int noteIndex) {
	notesOn[noteIndex].done = true;
}

int sp::Sinoid::pressNote (double frequency, double volume) {
	int sz = notesOn.size();
	notesOn.push_back(sp::PressedNote(frequency, 0.0, volume, sp::SUSTAIN));
	return sz;
}



