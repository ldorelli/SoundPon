#include <waveBuilder.h>


sp::BasicWaveBuilder::BasicWaveBuilder(int channelsQty, 
	int seconds, int sampleRate, int bitsPerSample)
{
	/* Cria um vetor com todas as amostras */
	if(bitsPerSample == 8)
		data8 = std::vector<unsigned char> (seconds * sampleRate * channelsQty, 128);
	else if(bitsPerSample == 16)
		data16 = std::vector<short> (seconds * sampleRate * channelsQty, 0);
	else data32 = std::vector<int> (seconds * sampleRate * channelsQty, 0);
	this->channelsQty = channelsQty;
	this->sampleRate = sampleRate;
	this->totalTime = seconds;
	timePerSample = (double) 1/sampleRate;
	hertzFrequency = (double) 2 * pi/sampleRate;
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

void sp::BasicWaveBuilder::addNote(sp::Note note, double t, double duration, double volume, int channel)
{
	int i = getSampleIndexByTime(t);
	int j = getSampleIndexByTime(t + duration);
	for( ; i <= j; i++) {
		if(bitsPerSample == 8) {
			data8[channelsQty*i+channel] = 
				data8[channelsQty*i+channel] + 
				Chord::discretizeSingleNote(note, i, hertzFrequency, volume * 256);
		} else if(bitsPerSample == 16) {
			data16[channelsQty*i+channel] = 
				data16[channelsQty*i+channel] + 
				Chord::discretizeSingleNote(note, i, hertzFrequency, volume * (1<<15));
		} else {
			data32[channelsQty*i+channel] = 
				data32[channelsQty*i+channel] +  
				Chord::discretizeSingleNote(note, i, hertzFrequency, volume * (1<<30));
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

sp::ASDRWaveBuilder::ASDRWaveBuilder(int channelsQty, int seconds, int sampleRate, int bitsPerSample,
		double a, double s, double d, double h, double r)
			: BasicWaveBuilder(channelsQty, seconds, sampleRate, bitsPerSample)
{
	this->a = a, this->s = s, this->d = d, this->r = r, this->h = h;
	/* Cria um vetor com todas as amostras */
	if(bitsPerSample == 8)
		data8 = std::vector<unsigned char> ();
	else if(bitsPerSample == 16)
		data16 = std::vector<short> ();
	else data32 = std::vector<int> ();

	this->channelsQty = channelsQty;
	this->sampleRate = sampleRate;
	this->totalTime = seconds;
	timePerSample = (double) 1/sampleRate;
	hertzFrequency = (double) 2 * pi/sampleRate;
	this->bitsPerSample = bitsPerSample;

}

void sp::ASDRWaveBuilder::addNote(
	sp::Note note, double t, double duration, double volume, int channel)
{

	/* 
		t is the relative timestamp from the beg of note.
		During t-a the volume rises to the attack level, linearly	
		during a-d the volume rises to the sustain lvl (s), linearly
		During b-duration the note decays according to a function of s (sustain)
		During duration-duration+release, the volume drops linearly (release)
		The total time thus is a+d+duration+r
		All is multiplied by volume. 
	*/
/*	double noteTimeSpan = a+b+duration+d;

	int start = getSampleIndexByTime(t);
	int peakTime = getSampleIndexByTime(t+a);
	int holdTime = getSampleIndexByTime(t+a+d);
	int releaseStart = getSampleIndexByTime(t+a+d+duration);
	int noteEnding = getSampleIndexByTime(t+a+d+duration+r);

	int i = start;
	int j = noteEnding;

	if(bitsPerSample == 8) {
		if(j > data8.size()) data8.rezise(j+1);
	} else if(bitsPerSample == 16) {
		if(j > data16.size()) data8.rezise(j+1);
	} else {
		if(j > data32.size()) data32.rezise(j+1);
	}

	//Volume = m * t + b 
	double m = volume/peakTime;
	double b = -i * a;

	for( ; i <= peakTime; i++) {
		double vol = m * i + b;
		if(bitsPerSample == 8) {
			data8[channelsQty*i+channel] = 
				data8[channelsQty*i+channel] + 
				Chord::discretizeSingleNote(note, i, hertzFrequency, vol * 256);
		} else if(bitsPerSample == 16) {
			data16[channelsQty*i+channel] = 
				data16[channelsQty*i+channel] + 
				Chord::discretizeSingleNote(note, i, hertzFrequency, vol * (1<<15));
		} else {
			data32[channelsQty*i+channel] = 
				data32[channelsQty*i+channel] +  
				Chord::discretizeSingleNote(note, i, hertzFrequency, vol * (1<<30));
		}
	}
*/
	/* Volume = m * t + b */
	//double m = (sustain - peakTime)/()
}

int sp::ASDRWaveBuilder::getSampleIndexByTime(double t) {
	return (t/timePerSample);
}
