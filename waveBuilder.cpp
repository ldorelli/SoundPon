#include <waveBuilder.h>


sp::BasicWaveBuilder::BasicWaveBuilder(int channelsQty, 
	int seconds, int sampleRate, int bitsPerSample)
{
	/* Cria um vetor com todas as amostras */
	if(bitsPerSample == 8) {
		maxVolume = 128;
		data8 = std::vector<unsigned char> (seconds * sampleRate * channelsQty, 128);
	} else if(bitsPerSample == 16) {
		maxVolume = (1<<15);
		data16 = std::vector<short> (seconds * sampleRate * channelsQty, 0);
	} else {
		maxVolume = (1<<30);
	 	data32 = std::vector<int> (seconds * sampleRate * channelsQty, 0);	
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
	
	if(bitsPerSample == 8) dataSize = data8.size();
	else if(bitsPerSample == 16) dataSize = data16.size();
	else dataSize = data32.size();
	return std::min( dataSize-1, (int) (t/timePerSample) );
}

void sp::BasicWaveBuilder::writeToWave(std::string fileName) {
	WaveFile file(fileName, channelsQty, bitsPerSample, sampleRate);
	
	if(bitsPerSample == 8)
		file.writeData(data8);
	else if(bitsPerSample == 16)
		file.writeData(data16);
	//else file.writeData(data32);
	file.close();
}

using namespace std;
void sp::BasicWaveBuilder::addNote(sp::Note note, double t, double duration, double volume, int channel)
{
	channel--;
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t + duration) - 1;
	//cout << t << " " << j * timePerSample + t << " " << duration << endl;

	for( ; i < j; i++) {
		if(bitsPerSample == 8) {
			data8[channelsQty*i+channel] = 
				data8[channelsQty*i+channel] + 
				Chord::discretizeSingleNote(note, timePerSample*i, multiplier, volume * 256);
		} else if(bitsPerSample == 16) {
			//std::cout << (t+timePerSample*i) << std::endl;
			data16[channelsQty*i+channel] = 
				data16[channelsQty*i+channel] + 
				Chord::discretizeSingleNote(note, timePerSample*i, multiplier, volume * (1<<15));
			//std::cout << data16[channelsQty*i+channel] << std::endl;
		} else {
			data32[channelsQty*i+channel] = 
				data32[channelsQty*i+channel] +  
				Chord::discretizeSingleNote(note, t+timePerSample*i, multiplier, volume * (1<<30));
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
//	cout << t << " " << j * timePerSample  << " " << duration << endl;
	duration = duration - tf;

	for(; i < j; i++) {
		if(bitsPerSample == 8) {
			data8[channelsQty*i+channel] = 
				data8[channelsQty*i+channel] + 
				256 * Chord::discretizeSingleNote(note, timePerSample * i, multiplier, volume);
		} else if(bitsPerSample == 16) {

			short noteToAdd = 
				(1<<15) * instr.getNoteValue(note, t, timePerSample * i, multiplier, 
						volume, duration);
			data16[channelsQty*i+channel]  = data16[channelsQty*i+channel] + noteToAdd;
			//data16[channelsQty*i+channel] 
			//	= data16[channelsQty*i+channel]/tot * tot +
			//		noteToAdd/tot * tot;
		} else {
			data32[channelsQty*i+channel] = 
				data32[channelsQty*i+channel] +  
				Chord::discretizeSingleNote(note, t + timePerSample * i, multiplier, volume * (1<<30));
		}
	}

}

void sp::BasicWaveBuilder::setWave(WaveForm *wf, double t, double duration)
{
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t+duration);
	for( ; i <= j; i++) {
		if(bitsPerSample == 8) {
			data8[i] = (*wf)(i);
		} else if(bitsPerSample == 16) {
			data16[i] = (*wf) (i);
		} else {
			data32[i] = (*wf) (i);
		}
	}
}

