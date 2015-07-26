#ifndef WAVE_BUILDER_H
#define WAVE_BUILDER_H

#include "note.h"
#include "waveForm.h"
#include "waveFile.h"
#include <algorithm>
#include <utility>
#include <instrument.h>
#include <SFML/Audio.hpp>

namespace sp {

const double  	pi = acos(-1);

/*
	Classe que possui funções para incluir perturbações 
		em uma onda
*/
class BasicWaveBuilder {

protected:

	/* 
		The data and the aumont of notes played on an interval. 
		This is used to take the arithmetic mean and prevent
		problems of overflow. 
	*/
	std::vector<double> 	data;


	int 			channelsQty;
	int 			sampleRate;
	double			multiplier;
	double			totalTime;
	double 			timePerSample;
	int 			bitsPerSample;
	double	 			maxVolume;

public:

	BasicWaveBuilder(int channelsQty, int seconds, int sampleRate, int bitsPerSample, double volume);

	virtual int getSampleIndexByTime(double t);

	void buildSFMLBuffer (sf::SoundBuffer &buf);

	void writeToWave(std::string fileName);
	
	virtual void addNote(sp::Note note, double t, double duration, double volume, int channel,
		sp::Instrument instr);

	virtual void setWave(WaveForm *wf, double t, double duration);

};

}

#endif