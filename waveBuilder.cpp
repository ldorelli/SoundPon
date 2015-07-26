#include <waveBuilder.h>


sp::BasicWaveBuilder::BasicWaveBuilder(int channelsQty, 
	int seconds, int sampleRate, int bitsPerSample, double vol)
{
	/* Cria um vetor com todas as amostras */
	data = std::vector<double> (seconds * sampleRate * channelsQty, 0.0);

	if(bitsPerSample == 8) {
		this->maxVolume = 128.0 * vol;
	} else if(bitsPerSample == 16) {
		this->maxVolume = 32768.0 * vol;
	} else {
		this->maxVolume = (1<<30) * vol;
	}

	this->channelsQty = channelsQty;
	this->sampleRate = sampleRate;
	this->totalTime = seconds;
	timePerSample = (double) 1/sampleRate;
	multiplier = (double) 2 * pi;
	this->bitsPerSample = bitsPerSample;

}

void sp::BasicWaveBuilder::buildSFMLBuffer (sf::SoundBuffer &buf) {
	std::vector <sf::Int16> samples(data.size());
	if (bitsPerSample != 16) {
		throw "Not supported.";
	} else if (bitsPerSample == 16) {
		double minV, maxV;
		minV = maxV = data[0];
		for (int i = 0; i < data.size(); ++i) {
			minV = std::min(minV, data[i]);
			maxV = std::max(maxV, data[i]);
		}
		for (int i = 0; i < data.size(); ++i) {
			data[i] = -1.0 - minV*2/(maxV-minV) + data[i] * 2.0/(maxV-minV);
		}
		for (int i = 0; i < data.size(); ++i) {
			samples[i] = (sf::Int16) (maxVolume * data[i]);
		}
	}
	buf.loadFromSamples(&samples[0], samples.size(), channelsQty, sampleRate);
}



int sp::BasicWaveBuilder::getSampleIndexByTime(double t) {
	int dataSize;
	
	dataSize = data.size();
	return std::min( dataSize-1, (int) (t/timePerSample) );
}

void sp::BasicWaveBuilder::addNote(sp::Note note, double t, double duration, double volume, int channel,
		sp::Instrument instr)
{
	channel--;
	//duration = tf + duration;
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t + duration) - 1;

	for(; i < j; i++) {
		double val = instr.getAmplitude(note.getFrequency(), timePerSample * i - t, 
				multiplier, volume, duration);
		data[channelsQty*i+channel] += val;
	}

}

void sp::BasicWaveBuilder::setWave(WaveForm *wf, double t, double duration)
{
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t+duration);
	for( ; i <= j; i++) 
		data[i] = (*wf)(i);
}

void sp::BasicWaveBuilder::writeToWave(std::string fileName) {
	WaveFile file(fileName, channelsQty, bitsPerSample, sampleRate);
	
	if(bitsPerSample == 8) {
		std::vector<unsigned char> data8 = 
			std::vector<unsigned char> (data.size());
		for(int i = 0; i < data.size(); i++) {
			data8[i] = (unsigned char) data[i];
		}
		file.writeData(data8);
	}
	else if(bitsPerSample == 16) {
		std::vector<short> data16 = 
			std::vector<short> (data.size());
		for(int i = 0; i < data.size(); i++) {
			data16[i] = (short) data[i];
		}
		file.writeData(data16);
	} else {
		std::vector<int> data32 = 
			std::vector<int> (data.size());
		for(int i = 0; i < data.size(); i++) {
			data32[i] = (int) data[i];	
		}
		//file.writeData(data32);
	}
}