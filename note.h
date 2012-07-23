#ifndef NOTES_H
#define NOTES_H

#include <vector>
#include <utility>

namespace sp {

#define C 0
#define Cf 1
#define Cb 2
#define D 3
#define Df 4
#define Db 5
#define E 6
#define Ef 7
#define Eb 8
#define F 9
#define Ff 10
#define Fb 11
#define G 12
#define Gf 13
#define Gb 14
#define A 15
#define Af 16
#define Ab 17
#define B 18
#define Bf 19
#define Bb 20

class Note {
protected:
	int		octave;
	int 	note;

	Note(){}

	// Auxiliary function

	static int getNoteByIndex(int index);

	static int getIndexByNote(int note);

public:

	static const double frequencyTable[10][21];

	static const Note 

		MiddleC, 
		C0, Cf0, Cb0,
		D0, Df0, Db0,
		E0, Ef0, Eb0,
		F0, Ff0, Fb0,
		G0, Gf0, Gb0,
		A0, Af0, Ab0,
		B0, Bf0, Bb0,

		C1, Cf1, Cb1,
		D1, Df1, Db1,
		E1, Ef1, Eb1,
		F1, Ff1, Fb1,
		G1, Gf1, Gb1,
		A1, Af1, Ab1,
		B1, Bf1, Bb1,

		C2, Cf2, Cb2,
		D2, Df2, Db2,
		E2, Ef2, Eb2,
		F2, Ff2, Fb2,
		G2, Gf2, Gb2,
		A2, Af2, Ab2,
		B2, Bf2, Bb2,

		C3, Cf3, Cb3,
		D3, Df3, Db3,
		E3, Ef3, Eb3,
		F3, Ff3, Fb3,
		G3, Gf3, Gb3,
		A3, Af3, Ab3,
		B3, Bf3, Bb3,

		C4, Cf4, Cb4,
		D4, Df4, Db4,
		E4, Ef4, Eb4,
		F4, Ff4, Fb4,
		G4, Gf4, Gb4,
		A4, Af4, Ab4,
		B4, Bf4, Bb4,

		C5, Cf5, Cb5,
		D5, Df5, Db5,
		E5, Ef5, Eb5,
		F5, Ff5, Fb5,
		G5, Gf5, Gb5,
		A5, Af5, Ab5,
		B5, Bf5, Bb5,

		C6, Cf6, Cb6,
		D6, Df6, Db6,
		E6, Ef6, Eb6,
		F6, Ff6, Fb6,
		G6, Gf6, Gb6,
		A6, Af6, Ab6,
		B6, Bf6, Bb6,

		C7, Cf7, Cb7,
		D7, Df7, Db7,
		E7, Ef7, Eb7,
		F7, Ff7, Fb7,
		G7, Gf7, Gb7,
		A7, Af7, Ab7,
		B7, Bf7, Bb7,

		C8, Cf8, Cb8,
		D8, Df8, Db8,
		E8, Ef8, Eb8,
		F8, Ff8, Fb8,
		G8, Gf8, Gb8,
		A8, Af8, Ab8,
		B8, Bf8, Bb8,

		C9, Cf9, Cb9,
		D9, Df9, Db9,
		E9, Ef9, Eb9,
		F9, Ff9, Fb9,
		G9, Gf9, Gb9,
		A9, Af9, Ab9,
		B9, Bf9, Bb9;




	Note(int note, int octave);

	double getFrequency();

	Note operator+ (int b) const;
};

}

#endif