#include <waveBuilder.h>


sp::BasicWaveBuilder::BasicWaveBuilder(int channelsQty, 
	int seconds, int sampleRate, int bitsPerSample)
{
	/* Cria um vetor com todas as amostras */
	if(bitsPerSample == 8) {
		maxVolume = 128;
		data = std::vector< std::pair<double,int> > (seconds * sampleRate * channelsQty, 
			std::make_pair(128, 0) );
	} else if(bitsPerSample == 16) {
		maxVolume = (1<<15);
		data = std::vector< std::pair<double, int> > (seconds * sampleRate * channelsQty, 
			std::make_pair(0, 0));
	} else {
		maxVolume = (1<<30);
	 	data = std::vector< std::pair<double, int> >  (seconds * sampleRate * channelsQty, 
	 		std::make_pair(0, 0));	
	}
	this->channelsQty = channelsQty;
	this->sampleRate = sampleRate;
	this->totalTime = seconds;
	timePerSample = (double) 1/sampleRate;
	multiplier = (double) 2 * pi;
	this->bitsPerSample = bitsPerSample;

}

int sp::BasicWaveBuilder::getSampleIndexByTime(double t) {
	int dataSize;
	
	dataSize = data.size();
	return std::min( dataSize-1, (int) (t/timePerSample) );
}

void sp::BasicWaveBuilder::writeToWave(std::string fileName) {
	WaveFile file(fileName, channelsQty, bitsPerSample, sampleRate);
	
	if(bitsPerSample == 8) {
		std::vector<unsigned char> data8 = 
			std::vector<unsigned char> (data.size());
		for(int i = 0; i < data.size(); i++) {
			if(data[i].second == 0) data8[i] = (unsigned char) data[i].first;
			else data8[i] = (unsigned char) data[i].first/data[i].second;
		}
		file.writeData(data8);
	}
	else if(bitsPerSample == 16) {
		std::vector<short> data16 = 
			std::vector<short> (data.size());
		for(int i = 0; i < data.size(); i++) {
			if(data[i].second == 0) data16[i] = (short) data[i].first;
			else data16[i] = data[i].first/((double) data[i].second);
		}
		file.writeData(data16);
	} else {
		std::vector<int> data32 = 
			std::vector<int> (data.size());
		for(int i = 0; i < data.size(); i++) {
			if(data[i].second == 0) data32[i] = (int) data[i].first;	
			else data32[i] = (short) data[i].first/data[i].second;
		}
		//file.writeData(data32);
	}
}

using namespace std;
void sp::BasicWaveBuilder::addNote(sp::Note note, double t, double duration, double volume, int channel)
{
	channel--;
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t + duration) - 1;


	for( ; i < j; i++) {
		if(bitsPerSample == 8) {
			data[channelsQty*i+channel].first +=
				Chord::discretizeSingleNote(note, timePerSample*i, multiplier, volume * 256);
			data[channelsQty*i+channel].second++;
		} else if(bitsPerSample == 16) {
			//std::cout << (t+timePerSample*i) << std::endl;
			data[channelsQty*i+channel].first +=
				(1<<15) * Chord::discretizeSingleNote(note, timePerSample*i, multiplier, volume);
			data[channelsQty*i+channel].second++;
		} else {
			data[channelsQty*i+channel].first +=
				(1<<30) * Chord::discretizeSingleNote(note, timePerSample*i, multiplier, volume);
			data[channelsQty*i+channel].second++;
		}
	}
}

void sp::BasicWaveBuilder::addNote(sp::Note note, double t, double duration, double volume, int channel,
		sp::Instrument instr)
{
	channel--;
	double tf = instr.getADRduration(); 
	//duration = tf + duration;
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t + duration) - 1;
	duration = duration - tf;

	for(; i < j; i++) {
		if(bitsPerSample == 8) {
			data[channelsQty*i+channel].first +=
				256 * instr.getAmplitude(note.getFrequency(), t, 
					timePerSample * i, multiplier, 
						volume, duration);
			data[channelsQty*i+channel].second++;
		} else if(bitsPerSample == 16) {

			data[channelsQty*i+channel].first +=
				(1<<15) * instr.getAmplitude(note.getFrequency(), 
					t, timePerSample * i, multiplier, 
						volume, duration);
			data[channelsQty*i+channel].second++;
		} else {
			data[channelsQty*i+channel].first +=
				(1<<30) * instr.getAmplitude(note.getFrequency(), t, 
					timePerSample * i, multiplier, 
						volume, duration);
			data[channelsQty*i+channel].second++;
		}
	}

}

void sp::BasicWaveBuilder::setWave(WaveForm *wf, double t, double duration)
{
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t+duration);
	for( ; i <= j; i++) 
		data[i].first = (*wf)(i);
}

