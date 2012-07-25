#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <string>
#include <list>
#include <fstream>

#include <waveBuilder.h>
#include <instrument.h>

using namespace std;
using namespace sp;

typedef long long int LL;
typedef pair<int,int> pii;


#define pb push_back
#define mp make_pair

int main (void)
{

	string fileName = "storms.wav";
	int discpl = 8;
	double dur = 0.3;
	BasicWaveBuilder wb(2, 7, 44100, 16);
	
	Instrument t(0.025, 0.050, 0.6, 0.025);
	
	t.addHarmonic(2);
	t.addHarmonic(3);
	t.addHarmonic(4);
	t.addHarmonic(5);

	
	//-- CH 1
	// wb.addNote(sp::Note::D4,    0,   1.0, 1.0, 1, t);
	// wb.addNote(sp::Note::G4,    0.1, 1.0, 1.0, 1, t);
	// wb.addNote(sp::Note::B3,    0.2, 1.0, 1.0, 1, t);
//	wb.addNote(sp::Note::G3,    0.0, 1.0, 0.8, 1, t);
//	wb.addChord(ch, 0.0, 1.0, 0.8, 1, t);
	
	wb.addNote(sp::Note::F5, 0.00, 2.00, 0.8, 1, t);
	wb.addNote(sp::Note::D3, 0.00, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::F3, 0.20, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::D4, 0.40, 0.40, 0.8, 1, t);
	
	// --+1
	
	wb.addNote(sp::Note::D3, 1.10, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::F3, 1.30, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::D4, 1.50, 0.40, 0.8, 1, t);
	// --+1
	wb.addNote(sp::Note::E4, 2.20, 0.40, 0.8, 1, t);
	wb.addNote(sp::Note::F4, 2.60, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::E4, 2.80, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::F4, 3.00, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::E4, 3.20, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::C4, 3.40, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::A3, 3.60, 0.40, 0.8, 1, t);
	wb.addNote(sp::Note::A3, 4.20, 0.40, 0.8, 1, t);
	wb.addNote(sp::Note::D3, 4.60, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::D3, 4.80, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::F3, 5.00, 0.40, 0.8, 1, t);
	wb.addNote(sp::Note::A3, 5.40, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::A3, 5.60, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::D3, 5.80, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::F3, 6.00, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::G3, 6.20, 0.20, 0.8, 1, t);
	wb.addNote(sp::Note::E3, 6.40, 0.20, 0.8, 1, t);

	wb.writeToWave(fileName);
/*
	sineWave s;
	wb.setWave(&s, 0, 15);
*/
	
/*
	fstream g("mywav.wav", ios::in);
	unsigned char c;
	g.unsetf(ios_base::skipws);

	while(g >> c) {
		printf("%x ", c);
	}
*/
	return 0;
}
