#include <iostream>
#include <synthetizer.h>
#include <sinoid.h>

using namespace std;
using namespace sp;

int main (void)
{
	// Instrument t(2, 44100, 0.8, 0.01);
	// t.addHarmonic(2);
	// t.addHarmonic(3);
	// t.addHarmonic(10);
	// t.addHarmonic(12);
	
	// C Major scale
	sp::Note cMajor[14] = { 
		sp::Note::C4,
		sp::Note::D4,
		sp::Note::E4,
		sp::Note::F4,
		sp::Note::G4,
		sp::Note::A4,
		sp::Note::B4,
		sp::Note::C3,
		sp::Note::D3,
		sp::Note::E3,
		sp::Note::F3,
		sp::Note::G3,
		sp::Note::A3,
		sp::Note::B3,
	};

	sp::Synthetizer synth(2, 44100, 0.8, 1.0/44100.0 * 5000.0);

	shared_ptr<Sinoid> instr (new Sinoid());
	synth.setInstrument(instr);

	synth.play();

	string cmd;
	do {
		cin >> cmd;
		if (cmd == "p") {
			int nr; cin >> nr;
			instr->pressNote(cMajor[nr].getFrequency(), 1.0);
			std::cout << "Playing " << cMajor[nr].getFrequency() << " " << std::endl;
		} else if (cmd == "r") {
			int nr; cin >> nr;
			instr->releaseNote(nr);
		}
	} while (cmd != "x");

	return 0;
}
