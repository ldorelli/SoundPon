#include <note.h>



sp::Note::Note(int note, int octave)
{
		this->octave = octave;
		this->note = note;
}

const double sp::Note::frequencyTable[10][21] =
	
	{
		{ 	// Oitava 0
			16.361, 17.324, 0, // C
			18.354, 19.445, 17.324, // D
			20.601, 19.445, 21.827, // E
			21.827, 20.601, 23.124 , // F
			24.499, 25.956, 23.124 , // G
			27.5, 29.135, 25.956 , // A
			30.868, 32.703, 29.135 
		}, // B
	
		// Oitava 1
		{
			30.868, 32.703, 34.648, // C
			36.708, 38.891, 34.648, // D
			41.203, 43.654, 38.891, // E
			43.654, 46.249, 41.203, // F
			48.999, 46.249, 51.913, // G
			55, 58.27, 51.913, // A
			61.735, 65.406, 58.27	// B
		},
		// Oitava 2
		{
			65.406, 69.296, 61.735, // C
			73.416, 77.782, 69.296, // D
			82.407, 87.307, 77.782, // E
			87.307, 82.407, 92.499, // F
			97.999, 103.826, 92.499, // G
			110, 116.541, 103.826, // A
			123.471, 130.813, 116.541 // B
		},
		// Oitava 3
		{
			130.813, 138.591, 123.471, // C
			146.832, 155.563, 138.591, // D
			164.814, 174.614, 155.563, // E
			174.614, 184.997, 164.814, // F
			195.998, 207.652, 184.997, // G
			220, 233.082, 207.652, // A
			246.942, 261.626, 246.942 // B
		},
		// Oitava 4
		{
			261.626, 277.183, 246.942, // C
			293.665, 311.127, 277.183, // D
			329.628, 349.228, 311.127, // E
			349.228, 369.994, 329.628, // F
			391.995, 415.305, 369.994, // G
			440, 466.164, 415.305, // A
			493.883, 523.251, 466.164 // B
		},
		// Oitava 5
		{
			523.251, 554.365, 493.883, // C
			587.33, 622.254, 554.365, // D
			659.255, 698.456, 622.254, // E
			698.456, 739.989, 659.255, // F
			783.991, 830.609, 739.989, // G
			880, 932.328, 830.609, // A
			987.767, 1046.502, 932.328 // B
		},
		// Oitava 6
		{
			1046.502, 1108.731, 987.767, // C
			1174.659, 1244.508, 1108.731, // D
			1318.51, 1396.913, 1244.508, // E
			1396.913, 1479.978, 1318.51, // F
			1567.982, 1661.219, 1479.978, // G
			1760, 1864.655, 1661.219, // A
			1975.533, 2093.005, 1864.655 // B
		}, 
		// Oitava 7
		{
			2093.005, 2217.461, 1975.533, // C
			2349.318, 2489.016, 2217.461, // D
			2637.021, 2793.826, 2489.016, // E
			2793.826, 2959.955, 2637.021, // F
			3135.964, 3322.438, 2959.955, // G
			3520, 3729.31, 3322.438, // A
			3951.066, 4186.009, 3729.31 // B
		},
		// Oitava 8
		{
			4186.009, 4434.922, 3951.066, // C
			4698.636, 4978.032, 4434.922, // D
			5274.042, 5587.652, 4978.032, // E
			5587.652, 5919.91, 5274.042, // F
			6271.928, 6644.876, 5919.91, // G
			7040, 7458.62, 6644.876, // A
			7902.132, 8372.018, 7458.62 // B
		}, 
		// Oitava 9
		{
			8372.018, 8869.844, 7902.132, // C
			9397.272, 9956.064, 8869.844, // D
			10548.084, 11175.304, 9956.064, // E
			11175.304, 11839.82, 10548.084, // F
			12543.856, 13289.752, 11839.82, // G
			14080, 14917.24, 13289.752, // A
			15804.264, 0, 14917.24 // B

		}

	};

sp::Note sp::Note::operator+ (int b) const {
	Note answ;

	if(b > 0) {
		answ.note = (note + b)%21;
		answ.octave = octave + (note+b)/21;
	} else {
		answ.note = (note + b + 21)%21;
		if(b > note) answ.octave = octave-1;
		else answ.octave = octave;
	}
	return answ;
}

double sp::Note::getFrequency()
{
	return sp::Note::frequencyTable[octave][note];
}


const  sp::Note sp::Note::C0 = sp::Note(C,  0);
const sp::Note sp::Note::Cb0 = sp::Note(Cb, 0);
const sp::Note sp::Note::Cf0 = sp::Note(Cf, 0);
const  sp::Note sp::Note::D0 = sp::Note(D,  0);
const sp::Note sp::Note::Db0 = sp::Note(Db, 0);
const sp::Note sp::Note::Df0 = sp::Note(Df, 0);
const  sp::Note sp::Note::E0 = sp::Note(E,  0);
const sp::Note sp::Note::Eb0 = sp::Note(Eb, 0);
const sp::Note sp::Note::Ef0 = sp::Note(Ef, 0);
const  sp::Note sp::Note::F0 = sp::Note(F,  0);
const sp::Note sp::Note::Fb0 = sp::Note(Fb, 0);
const sp::Note sp::Note::Ff0 = sp::Note(Ff, 0);
const  sp::Note sp::Note::G0 = sp::Note(G,  0);
const sp::Note sp::Note::Gb0 = sp::Note(Gb, 0);
const sp::Note sp::Note::Gf0 = sp::Note(Gf, 0);
const  sp::Note sp::Note::A0 = sp::Note(A,  0);
const sp::Note sp::Note::Ab0 = sp::Note(Ab, 0);
const sp::Note sp::Note::Af0 = sp::Note(Af, 0);
const  sp::Note sp::Note::B0 = sp::Note(B,  0);
const sp::Note sp::Note::Bb0 = sp::Note(Bb, 0);
const sp::Note sp::Note::Bf0 = sp::Note(Bf, 0);

const  sp::Note sp::Note::C1 = sp::Note(C,  1);
const sp::Note sp::Note::Cb1 = sp::Note(Cb, 1);
const sp::Note sp::Note::Cf1 = sp::Note(Cf, 1);
const  sp::Note sp::Note::D1 = sp::Note(D,  1);
const sp::Note sp::Note::Db1 = sp::Note(Db, 1);
const sp::Note sp::Note::Df1 = sp::Note(Df, 1);
const  sp::Note sp::Note::E1 = sp::Note(E,  1);
const sp::Note sp::Note::Eb1 = sp::Note(Eb, 1);
const sp::Note sp::Note::Ef1 = sp::Note(Ef, 1);
const  sp::Note sp::Note::F1 = sp::Note(F,  1);
const sp::Note sp::Note::Fb1 = sp::Note(Fb, 1);
const sp::Note sp::Note::Ff1 = sp::Note(Ff, 1);
const  sp::Note sp::Note::G1 = sp::Note(G,  1);
const sp::Note sp::Note::Gb1 = sp::Note(Gb, 1);
const sp::Note sp::Note::Gf1 = sp::Note(Gf, 1);
const  sp::Note sp::Note::A1 = sp::Note(A,  1);
const sp::Note sp::Note::Ab1 = sp::Note(Ab, 1);
const sp::Note sp::Note::Af1 = sp::Note(Af, 1);
const  sp::Note sp::Note::B1 = sp::Note(B,  1);
const sp::Note sp::Note::Bb1 = sp::Note(Bb, 1);
const sp::Note sp::Note::Bf1 = sp::Note(Bf, 1);

const  sp::Note sp::Note::C2 = sp::Note(C,  2);
const sp::Note sp::Note::Cb2 = sp::Note(Cb, 2);
const sp::Note sp::Note::Cf2 = sp::Note(Cf, 2);
const  sp::Note sp::Note::D2 = sp::Note(D,  2);
const sp::Note sp::Note::Db2 = sp::Note(Db, 2);
const sp::Note sp::Note::Df2 = sp::Note(Df, 2);
const  sp::Note sp::Note::E2 = sp::Note(E,  2);
const sp::Note sp::Note::Eb2 = sp::Note(Eb, 2);
const sp::Note sp::Note::Ef2 = sp::Note(Ef, 2);
const  sp::Note sp::Note::F2 = sp::Note(F,  2);
const sp::Note sp::Note::Fb2 = sp::Note(Fb, 2);
const sp::Note sp::Note::Ff2 = sp::Note(Ff, 2);
const  sp::Note sp::Note::G2 = sp::Note(G,  2);
const sp::Note sp::Note::Gb2 = sp::Note(Gb, 2);
const sp::Note sp::Note::Gf2 = sp::Note(Gf, 2);
const  sp::Note sp::Note::A2 = sp::Note(A,  2);
const sp::Note sp::Note::Ab2 = sp::Note(Ab, 2);
const sp::Note sp::Note::Af2 = sp::Note(Af, 2);
const  sp::Note sp::Note::B2 = sp::Note(B,  2);
const sp::Note sp::Note::Bb2 = sp::Note(Bb, 2);
const sp::Note sp::Note::Bf2 = sp::Note(Bf, 2);

const  sp::Note sp::Note::C3 = sp::Note(C,  3);
const sp::Note sp::Note::Cb3 = sp::Note(Cb, 3);
const sp::Note sp::Note::Cf3 = sp::Note(Cf, 3);
const  sp::Note sp::Note::D3 = sp::Note(D,  3);
const sp::Note sp::Note::Db3 = sp::Note(Db, 3);
const sp::Note sp::Note::Df3 = sp::Note(Df, 3);
const  sp::Note sp::Note::E3 = sp::Note(E,  3);
const sp::Note sp::Note::Eb3 = sp::Note(Eb, 3);
const sp::Note sp::Note::Ef3 = sp::Note(Ef, 3);
const  sp::Note sp::Note::F3 = sp::Note(F,  3);
const sp::Note sp::Note::Fb3 = sp::Note(Fb, 3);
const sp::Note sp::Note::Ff3 = sp::Note(Ff, 3);
const  sp::Note sp::Note::G3 = sp::Note(G,  3);
const sp::Note sp::Note::Gb3 = sp::Note(Gb, 3);
const sp::Note sp::Note::Gf3 = sp::Note(Gf, 3);
const  sp::Note sp::Note::A3 = sp::Note(A,  3);
const sp::Note sp::Note::Ab3 = sp::Note(Ab, 3);
const sp::Note sp::Note::Af3 = sp::Note(Af, 3);
const  sp::Note sp::Note::B3 = sp::Note(B,  3);
const sp::Note sp::Note::Bb3 = sp::Note(Bb, 3);
const sp::Note sp::Note::Bf3 = sp::Note(Bf, 3);

const  sp::Note sp::Note::C4 = sp::Note(C,  4);
const sp::Note sp::Note::Cb4 = sp::Note(Cb, 4);
const sp::Note sp::Note::Cf4 = sp::Note(Cf, 4);
const  sp::Note sp::Note::D4 = sp::Note(D,  4);
const sp::Note sp::Note::Db4 = sp::Note(Db, 4);
const sp::Note sp::Note::Df4 = sp::Note(Df, 4);
const  sp::Note sp::Note::E4 = sp::Note(E,  4);
const sp::Note sp::Note::Eb4 = sp::Note(Eb, 4);
const sp::Note sp::Note::Ef4 = sp::Note(Ef, 4);
const  sp::Note sp::Note::F4 = sp::Note(F,  4);
const sp::Note sp::Note::Fb4 = sp::Note(Fb, 4);
const sp::Note sp::Note::Ff4 = sp::Note(Ff, 4);
const  sp::Note sp::Note::G4 = sp::Note(G,  4);
const sp::Note sp::Note::Gb4 = sp::Note(Gb, 4);
const sp::Note sp::Note::Gf4 = sp::Note(Gf, 4);
const  sp::Note sp::Note::A4 = sp::Note(A,  4);
const sp::Note sp::Note::Ab4 = sp::Note(Ab, 4);
const sp::Note sp::Note::Af4 = sp::Note(Af, 4);
const  sp::Note sp::Note::B4 = sp::Note(B,  4);
const sp::Note sp::Note::Bb4 = sp::Note(Bb, 4);
const sp::Note sp::Note::Bf4 = sp::Note(Bf, 4);

const  sp::Note sp::Note::C5 = sp::Note(C,  5);
const sp::Note sp::Note::Cb5 = sp::Note(Cb, 5);
const sp::Note sp::Note::Cf5 = sp::Note(Cf, 5);
const  sp::Note sp::Note::D5 = sp::Note(D,  5);
const sp::Note sp::Note::Db5 = sp::Note(Db, 5);
const sp::Note sp::Note::Df5 = sp::Note(Df, 5);
const  sp::Note sp::Note::E5 = sp::Note(E,  5);
const sp::Note sp::Note::Eb5 = sp::Note(Eb, 5);
const sp::Note sp::Note::Ef5 = sp::Note(Ef, 5);
const  sp::Note sp::Note::F5 = sp::Note(F,  5);
const sp::Note sp::Note::Fb5 = sp::Note(Fb, 5);
const sp::Note sp::Note::Ff5 = sp::Note(Ff, 5);
const  sp::Note sp::Note::G5 = sp::Note(G,  5);
const sp::Note sp::Note::Gb5 = sp::Note(Gb, 5);
const sp::Note sp::Note::Gf5 = sp::Note(Gf, 5);
const  sp::Note sp::Note::A5 = sp::Note(A,  5);
const sp::Note sp::Note::Ab5 = sp::Note(Ab, 5);
const sp::Note sp::Note::Af5 = sp::Note(Af, 5);
const  sp::Note sp::Note::B5 = sp::Note(B,  5);
const sp::Note sp::Note::Bb5 = sp::Note(Bb, 5);
const sp::Note sp::Note::Bf5 = sp::Note(Bf, 5);

const  sp::Note sp::Note::C6 = sp::Note(C,  6);
const sp::Note sp::Note::Cb6 = sp::Note(Cb, 6);
const sp::Note sp::Note::Cf6 = sp::Note(Cf, 6);
const  sp::Note sp::Note::D6 = sp::Note(D,  6);
const sp::Note sp::Note::Db6 = sp::Note(Db, 6);
const sp::Note sp::Note::Df6 = sp::Note(Df, 6);
const  sp::Note sp::Note::E6 = sp::Note(E,  6);
const sp::Note sp::Note::Eb6 = sp::Note(Eb, 6);
const sp::Note sp::Note::Ef6 = sp::Note(Ef, 6);
const  sp::Note sp::Note::F6 = sp::Note(F,  6);
const sp::Note sp::Note::Fb6 = sp::Note(Fb, 6);
const sp::Note sp::Note::Ff6 = sp::Note(Ff, 6);
const  sp::Note sp::Note::G6 = sp::Note(G,  6);
const sp::Note sp::Note::Gb6 = sp::Note(Gb, 6);
const sp::Note sp::Note::Gf6 = sp::Note(Gf, 6);
const  sp::Note sp::Note::A6 = sp::Note(A,  6);
const sp::Note sp::Note::Ab6 = sp::Note(Ab, 6);
const sp::Note sp::Note::Af6 = sp::Note(Af, 6);
const  sp::Note sp::Note::B6 = sp::Note(B,  6);
const sp::Note sp::Note::Bb6 = sp::Note(Bb, 6);
const sp::Note sp::Note::Bf6 = sp::Note(Bf, 6);

const  sp::Note sp::Note::C7 = sp::Note(C,  7);
const sp::Note sp::Note::Cb7 = sp::Note(Cb, 7);
const sp::Note sp::Note::Cf7 = sp::Note(Cf, 7);
const  sp::Note sp::Note::D7 = sp::Note(D,  7);
const sp::Note sp::Note::Db7 = sp::Note(Db, 7);
const sp::Note sp::Note::Df7 = sp::Note(Df, 7);
const  sp::Note sp::Note::E7 = sp::Note(E,  7);
const sp::Note sp::Note::Eb7 = sp::Note(Eb, 7);
const sp::Note sp::Note::Ef7 = sp::Note(Ef, 7);
const  sp::Note sp::Note::F7 = sp::Note(F,  7);
const sp::Note sp::Note::Fb7 = sp::Note(Fb, 7);
const sp::Note sp::Note::Ff7 = sp::Note(Ff, 7);
const  sp::Note sp::Note::G7 = sp::Note(G,  7);
const sp::Note sp::Note::Gb7 = sp::Note(Gb, 7);
const sp::Note sp::Note::Gf7 = sp::Note(Gf, 7);
const  sp::Note sp::Note::A7 = sp::Note(A,  7);
const sp::Note sp::Note::Ab7 = sp::Note(Ab, 7);
const sp::Note sp::Note::Af7 = sp::Note(Af, 7);
const  sp::Note sp::Note::B7 = sp::Note(B,  7);
const sp::Note sp::Note::Bb7 = sp::Note(Bb, 7);
const sp::Note sp::Note::Bf7 = sp::Note(Bf, 7);

const  sp::Note sp::Note::C8 = sp::Note(C,  8);
const sp::Note sp::Note::Cb8 = sp::Note(Cb, 8);
const sp::Note sp::Note::Cf8 = sp::Note(Cf, 8);
const  sp::Note sp::Note::D8 = sp::Note(D,  8);
const sp::Note sp::Note::Db8 = sp::Note(Db, 8);
const sp::Note sp::Note::Df8 = sp::Note(Df, 8);
const  sp::Note sp::Note::E8 = sp::Note(E,  8);
const sp::Note sp::Note::Eb8 = sp::Note(Eb, 8);
const sp::Note sp::Note::Ef8 = sp::Note(Ef, 8);
const  sp::Note sp::Note::F8 = sp::Note(F,  8);
const sp::Note sp::Note::Fb8 = sp::Note(Fb, 8);
const sp::Note sp::Note::Ff8 = sp::Note(Ff, 8);
const  sp::Note sp::Note::G8 = sp::Note(G,  8);
const sp::Note sp::Note::Gb8 = sp::Note(Gb, 8);
const sp::Note sp::Note::Gf8 = sp::Note(Gf, 8);
const  sp::Note sp::Note::A8 = sp::Note(A,  8);
const sp::Note sp::Note::Ab8 = sp::Note(Ab, 8);
const sp::Note sp::Note::Af8 = sp::Note(Af, 8);
const  sp::Note sp::Note::B8 = sp::Note(B,  8);
const sp::Note sp::Note::Bb8 = sp::Note(Bb, 8);
const sp::Note sp::Note::Bf8 = sp::Note(Bf, 8);

const  sp::Note sp::Note::C9 = sp::Note(C,  9);
const sp::Note sp::Note::Cb9 = sp::Note(Cb, 9);
const sp::Note sp::Note::Cf9 = sp::Note(Cf, 9);
const  sp::Note sp::Note::D9 = sp::Note(D,  9);
const sp::Note sp::Note::Db9 = sp::Note(Db, 9);
const sp::Note sp::Note::Df9 = sp::Note(Df, 9);
const  sp::Note sp::Note::E9 = sp::Note(E,  9);
const sp::Note sp::Note::Eb9 = sp::Note(Eb, 9);
const sp::Note sp::Note::Ef9 = sp::Note(Ef, 9);
const  sp::Note sp::Note::F9 = sp::Note(F,  9);
const sp::Note sp::Note::Fb9 = sp::Note(Fb, 9);
const sp::Note sp::Note::Ff9 = sp::Note(Ff, 9);
const  sp::Note sp::Note::G9 = sp::Note(G,  9);
const sp::Note sp::Note::Gb9 = sp::Note(Gb, 9);
const sp::Note sp::Note::Gf9 = sp::Note(Gf, 9);
const  sp::Note sp::Note::A9 = sp::Note(A,  9);
const sp::Note sp::Note::Ab9 = sp::Note(Ab, 9);
const sp::Note sp::Note::Af9 = sp::Note(Af, 9);
const  sp::Note sp::Note::B9 = sp::Note(B,  9);
const sp::Note sp::Note::Bb9 = sp::Note(Bb, 9);
const sp::Note sp::Note::Bf9 = sp::Note(Bf, 9);
