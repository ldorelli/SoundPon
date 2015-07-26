#include <synthetizer.h>
#include <cmath>

sp::Synthetizer::Synthetizer(int channelCount, int sampleRate, double volume, double updateTime)
{
	this->channelsQty = channelCount;
	this->sampleRate = sampleRate;
	this->updateTime = updateTime;
	this->volume = volume;
	this->timePerSample = 1.0/(double)sampleRate;
	data = std::vector<sf::Int16> (updateTime/timePerSample + 1, 0.0);
	std::cerr << "Initializing channels:" << channelCount << " sampleRate:" << sampleRate << std::endl;
	initialize(channelCount, sampleRate);
}

void norm (std::vector<double>& v) {
	double A, B;
	A = B = v[0];
	for (int i = 0; i < v.size(); ++i) {
		A = std::min(A, v[i]);
		B = std::max(B, v[i]);
	}
	double b = -1.0 - 2.0*A/(B-A);
	double a = 2.0/(B-A);
	for (int i = 0; i < v.size(); ++i) {
		v[i] = a*v[i] + b;
	}
}

// double t = 0.0;
bool sp::Synthetizer::onGetData(Chunk& res) {

	int samples = updateTime/timePerSample;
	
	for (int i = 0; i < samples; ++i) {
		// data[i] = sin(440*t*M_PI) * maxVolume;
		// t += timePerSample;
		data[i] = instrument->nextAmplitude(timePerSample) * volume * maxVolume;
	}
	res.samples = &data[0];
	res.sampleCount = samples; 
	return true;
}

void sp::Synthetizer::onSeek(sf::Time timeOffset) {
}

void sp::Synthetizer::setInstrument(std::shared_ptr<sp::Instrument> instrument) {
	this->instrument = instrument;
}

sp::Synthetizer::~Synthetizer() {
}