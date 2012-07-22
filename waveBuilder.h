#ifndef WAVE_BUILDER_H
#define WAVE_BUILDER_H

#include "note.h"
#include "chord.h"
#include "waveForm.h"
#include "waveFile.h"
#include <algorithm>


namespace sp {

const double  	pi = acos(-1);

/*
	Classe que possui funções para incluir perturbações 
		em uma onda
*/
class BasicWaveBuilder {

protected:

	std::vector<unsigned char> 	data8;
	std::vector<short>			data16;
	std::vector<int>				data32;

	int 			channelsQty;
	int 			sampleRate;
	double			hertzFrequency;
	double			totalTime;
	double 			timePerSample;
	int 			bitsPerSample;

public:

	BasicWaveBuilder(int channelsQty, int seconds, int sampleRate, int bitsPerSample);

	virtual int getSampleIndexByTime(double t);

	void writeToWave(std::string fileName);
	/*
		Writes the given Nothe into file
		On offset time t, with duration seconds 
		Volume is between 0 - 1 and is a relative value
		Channel is the channel to add the audio into
	*/
	virtual void addNote(sp::Note note, double t, double duration, double volume, int channel);

	virtual void setWave(WaveForm *wf, double t, double duration);

};

class ASDRWaveBuilder : public BasicWaveBuilder
{
private:	
	double a, s, d, r, h;
public:
	ASDRWaveBuilder(int channelsQty, int seconds, int sampleRate, int bitsPerSample,
					 double a, double s, double d, double h, double r);
	
	/*
		Writes the given Nothe into file
		On offset time t, with duration seconds 
		Volume is between 0 - 1 and is a relative value
		Channel is the channel to add the audio into
	*/

	int getSampleIndexByTime(double t);
	void addNote(sp::Note note, double t, double duration, double volume, int channel);
	
};

}

#endif