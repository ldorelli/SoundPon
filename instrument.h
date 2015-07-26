#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <note.h>
#include <functional>
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>

namespace sp {

enum NoteState {
	PRESS, SUSTAIN, RELEASE
};

struct PressedNote {
	double volume; 
	double currVolume;
	double frequency; 
	double time;  
	bool done;
	NoteState state;

	PressedNote(double frequency, double time, double volume, NoteState state) :
		frequency(frequency), time(time), volume(volume), state(state), currVolume(0.0), done(false) {}
};


/*
 *  An instrument class that generates a bunch of notes when asked.
 */
class Instrument {
protected:
	std::vector <double> harmonics;
	std::vector <PressedNote> notesOn;

	// Attack and decay times
	double decayTime;
	double attackTime;

	/**
	 *	Returns the current amplitude and advances time for that note.
	 */
	virtual double attack(sp::PressedNote& note, double timeStep) = 0;
	virtual double sustain(sp::PressedNote& note, double timeStep) = 0;
	virtual double decay(sp::PressedNote& note, double timeStep) = 0;

public:

	Instrument();
	~Instrument();
	/**
	 *	Adds a note to the list of notes being pressed.
	 *	@param frequency The frequency of the note
	 *	@param volume The intensity of the note
	 *	@return The index of the newly generated note within the instrument.
	 */
	virtual int pressNote (double frequency, double volume);

	/**
	 *	Releases a note.
	 *  @param noteIndex The index of the node that was being pressed.
	 */
	virtual void releaseNote(int noteIndex);
	
	/*
	 * Returns the next wave amplitude
	 * @param timeStep The aumont of time elapsed o nthis iteration.
	 * @return Next wave amplitude generated [-1, 1]
	 */
	virtual double nextAmplitude (double timeStep);
};


// // An instrument that updates every 0.01 seconds 
// class Instrument 
// {
// 	// Instrument harmonics
// 	std::vector<double>				harmonics;

// 	// Functions of the Envelope 
// 	// (receives the Amplitude and Time, returns adjusted)
// 	std::function<double(double, double)> 	attack;
// 	std::function<double(double, double)> 	sustain;
// 	std::function<double(double, double)> 	decay;

// 	// Parameters of the envelope
// 	double attackTime;
// 	double decayTime;

// 	//  The note and when it started 
// 	std::vector<PressedNote> notesON;

// 	// Sampling parameters
// 	int channelsQty;
// 	int sampleRate;
// 	// The time it takes to generate new samples
// 	double updateTime; 
// 	const double maxVolume = 32768;
// 	// Volume [0,1]
// 	double volume;

// 	double timePerSample;

// 	virtual bool onGetData(Chunk& data);
// 	void onSeek(sf::Time timeOffset);

// 	void updateNote(PressedNote& note);
// 	double getAmplitude (int noteId);

// public:
// 	/**
// 	 *	Creates a new instrument.
// 	 *	@param channelsQty Number of channels
// 	 *	@param sampleRate The sample rate of the instrument
// 	 *	@param volume The volume [0,1]
// 	 *	@param updateTime The time between samples
// 	 */
// 	Instrument(int channelsQty, int sampleRate, double volume, double updateTime);
// 	~Instrument();

// 	void addHarmonic(double h);
	

// 	int  pressNote(double freq, double volume);
// 	void releaseNote(int idx);


// 	// double getAmplitude(double note, double t, double mpl, 
// 	// 	double volume, double holdDuration);
// };

}

#endif