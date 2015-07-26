#ifndef SYNTHETIZER_H
#define SYNTHETIZER_H

#include <note.h>
#include <functional>
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>
#include <instrument.h>
#include <memory>

namespace sp {

// An instrument that updates every 0.01 seconds 
class Synthetizer : public sf::SoundStream
{
	// The instrument to use to synthetize
	std::shared_ptr<sp::Instrument> instrument;
	// Sampling parameters
	int channelsQty;
	int sampleRate;
	// The time it takes to generate new samples
	double updateTime; 
	const double maxVolume = 32768;
	// Volume [0,1]
	double volume;
	double timePerSample;

	virtual bool onGetData(Chunk& res);
	void onSeek(sf::Time timeOffset);
	
	// Sound data
	std::vector<sf::Int16> data;

public:
	/**
	 *	Creates a new Synthetizer.
	 *	@param channelsQty Number of channels
	 *	@param sampleRate The sample rate of the Synthetizer
	 *	@param volume The volume [0,1]
	 *	@param updateTime The time between samples
	 */
	Synthetizer(int channelsQty, int sampleRate, double volume, double updateTime);
	~Synthetizer();

	void setInstrument(std::shared_ptr<sp::Instrument> instrument);
};

}

#endif