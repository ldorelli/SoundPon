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
	Instrument s(0.1, 0.05, 0.5, 0.05);
	s.addHarmonic(2);
	s.addHarmonic(3);
	s.addHarmonic(4);
	s.addHarmonic(5);
	s.addHarmonic(6);

	string fileName = "storms.wav";
	int discpl = 8;
	double dur = 0.3;
	BasicWaveBuilder wb(2, 15, 22050, 16);
	// DO RE MI FA :D
	//wb.addNote(sp::Note::D5, 0.00, 0.20, 1.0, 2, s);
	
	wb.addNote(sp::Note::D3, 0.00, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::F3, 0.20, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::D4, 0.40, 0.40, 1.0, 2, s);

	
	// --
	wb.addNote(sp::Note::D3, 1.10, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::F3, 1.30, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::D4, 1.50, 0.40, 1.0, 2, s);
	// --, s
	wb.addNote(sp::Note::E4, 2.20, 0.40, 1.0, 2, s);
	wb.addNote(sp::Note::F4, 2.60, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::E4, 2.80, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::F4, 3.00, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::E4, 3.20, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::C4, 3.40, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::A3, 3.60, 0.40, 1.0, 2, s);

	wb.addNote(sp::Note::A3, 4.20, 0.40, 1.0, 2, s);
	wb.addNote(sp::Note::D3, 4.60, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::D3, 4.80, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::F3, 5.00, 0.40, 1.0, 2, s);
	wb.addNote(sp::Note::A3, 5.40, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::A3, 5.60, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::D3, 5.80, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::F3, 6.00, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::G3, 6.20, 0.20, 1.0, 2, s);
	wb.addNote(sp::Note::E3, 6.40, 0.20, 1.0, 2, s); 
	
	Instrument t(0.1, 0.05, 1.0, 0.02);
	
	t.addHarmonic(5);

	// -- CH 1
	wb.addNote(sp::Note::D3+1,    0, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::F3+1, 0.20, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::D4+1, 0.40, 0.40, 0.5, 1, t);
	// --+1
	wb.addNote(sp::Note::D3+1, 1.10, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::F3+1, 1.30, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::D4+1, 1.50, 0.40, 0.5, 1, t);
	// --+1
	wb.addNote(sp::Note::E4+1, 2.20, 0.40, 0.5, 1, t);
	wb.addNote(sp::Note::F4+1, 2.60, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::E4+1, 2.80, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::F4+1, 3.00, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::E4+1, 3.20, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::C4+1, 3.40, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::A3+1, 3.60, 0.40, 0.5, 1, t);
	wb.addNote(sp::Note::A3+1, 4.20, 0.40, 0.5, 1, t);
	wb.addNote(sp::Note::D3+1, 4.60, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::D3+1, 4.80, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::F3+1, 5.00, 0.40, 0.5, 1, t);
	wb.addNote(sp::Note::A3+1, 5.40, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::A3+1, 5.60, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::D3+1, 5.80, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::F3+1, 6.00, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::G3+1, 6.20, 0.20, 0.5, 1, t);
	wb.addNote(sp::Note::E3+1, 6.40, 0.20, 0.5, 1, t);
		
	wb.writeToWave(fileName);


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
