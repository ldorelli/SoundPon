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

using namespace std;
using namespace sp;

typedef long long int LL;
typedef pair<int,int> pii;


#define pb push_back
#define mp make_pair

int main (void)
{
	string fileName = "mywav.wav";
	int discpl = 8;
	double dur = 0.3;
	BasicWaveBuilder wb(2, 15, 22050, 16);
	// DO RE MI FA :D
	/*
	wb.addNote(sp::Note::C5+discpl,    0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::D5+discpl,  0.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::E5+discpl,    1, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl,  1.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl,  2.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl,  3.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::C5+discpl,  4.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::D5+discpl,  4.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::C5+discpl,  5.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::D5+discpl,  5.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::D5+discpl,  6.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::D5+discpl,  7.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::C5+discpl,  8.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::G5+discpl,  8.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl,  9.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::E5+discpl,  9.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::E5+discpl, 10.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::E5+discpl, 11.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::C5+discpl, 11.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::D5+discpl, 12.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::E5+discpl, 12.5, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl, 13.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl, 14.0, 0.5, 0.9, 1);
	wb.addNote(sp::Note::F5+discpl, 14.5, 0.5, 0.9, 1); 
	*/
	// DO RE MI FA (CHANNEL 2)
	/*
	wb.addNote(sp::Note::C5,    0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::D5,  0.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::E5,    1, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5,  1.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5,  2.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5,  3.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::C5,  4.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::D5,  4.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::C5,  5.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::D5,  5.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::D5,  6.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::D5,  7.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::C5,  8.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::G5,  8.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5,  9.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::E5,  9.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::E5, 10.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::E5, 11.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::C5, 11.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::D5, 12.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::E5, 12.5, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5, 13.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5, 14.0, 0.5, 0.9, 2);
	wb.addNote(sp::Note::F5, 14.5, 0.5, 0.9, 2); 
	*/
	dur = 0.3;
	wb.addNote(sp::Note::E5,  0.0, dur, 0.9, 1);
	wb.addNote(sp::Note::D5+1,  0.3, dur, 0.9, 1);
	//--
	wb.addNote(sp::Note::E5,  0.6, dur, 0.9, 1);
	wb.addNote(sp::Note::D5+1, 0.9, dur, 0.9, 1);
	wb.addNote(sp::Note::E5,  1.2, dur, 0.9, 1);
	wb.addNote(sp::Note::B4,  1.5, dur, 0.9, 1);
	wb.addNote(sp::Note::D5,  1.8, dur, 0.9, 1);
	wb.addNote(sp::Note::C5,  2.1, dur, 0.9, 1);
	//--
	wb.addNote(sp::Note::A4,  2.4, dur, 0.9, 1);
	wb.addNote(sp::Note::A2,  2.4, dur, 0.9, 2);
	wb.addNote(sp::Note::A4,  2.7, dur, 0.9, 1);
	wb.addNote(sp::Note::E3,  2.7, dur, 0.9, 2);
	wb.addNote(sp::Note::A3,  3.0, dur, 0.9, 2);
	wb.addNote(sp::Note::C4,  3.3, dur, 0.9, 1);
	wb.addNote(sp::Note::E4,  3.6, dur, 0.9, 1);
	wb.addNote(sp::Note::A4,  3.9, dur, 0.9, 1);
	//--
	wb.addNote(sp::Note::B4,  3.0, dur, 0.9, 1);
	wb.addNote(sp::Note::E2,  3.0, dur, 0.9, 2);
	wb.addNote(sp::Note::B4,  3.3, dur, 0.9, 1);
	wb.addNote(sp::Note::E3,  3.3, dur, 0.9, 2);
	wb.addNote(sp::Note::G3+1,  3.6, dur, 0.9, 2);
/*
	sineWave s;
	wb.setWave(&s, 0, 15);
*/
	wb.writeToWave(fileName);
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
