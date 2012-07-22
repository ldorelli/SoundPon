#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <string>
#include <list>
#include <fstream>

#include "note.h"

using namespace std;

typedef long long int LL;
typedef pair<int,int> pii;


#define pb push_back
#define mp make_pair
#define byte(x) ((const char*) &x)

const double  	pi = acos(-1);

class WaveFile {
private:
	fstream file;
	string fileName;
	unsigned long sz;
	unsigned long bitsPerSample;
	int sampleRate;
	short channels;


	void writeInteger(int c) {
		file.write( byte(c), 1);
		file.write( byte(c)+1, 1);
		file.write( byte(c)+2, 1);
		file.write( byte(c)+3, 1);
	} 

	void writeShort(short c) {
		file.write( byte(c), 1);
		file.write( byte(c)+1, 1);	
	} 

	void writeFormat() {
		
		file.write( "WAVE" , 4);

		// Calcula o novo tamanho do arquivo
		// 4 Bytes do RIFFTYPE "fmt " + 24 Bytes do Format Header + 4 Bytes do "WAVE"

		// FMT = 4 bytes
		file.write( "fmt " , 4); 

		int chunkSize = 16;
		// CHUNK SIZE = 4 bytes
		writeInteger(chunkSize);
		// COMPRESSION CODE = 2 BYTES
		unsigned short compr = 0x0001;
		writeShort(compr);		

		// CANAIS = 2 BYTES
		writeShort(channels);
		
		// SAMPLE RATE = 4 BYTES
		writeInteger(sampleRate);
		
		unsigned short blockAlign = bitsPerSample/8 * channels;
		// BYTE RATE / SECOND = 4 BYTES
		int brate = bitsPerSample/8 * channels * sampleRate;
		writeInteger(brate);
		// BLOCK ALIGN = 2 BYTES
		writeShort(blockAlign);
		// SIGNIFICANT BYTES PER SAMPLE = 2 BYTES
		writeShort(bitsPerSample);
	}

public:

	WaveFile(string fileName, short channels, int bitsPerSample, int sampleRate) {

		this->fileName = fileName;

		// Parametros passados na criação
		this->channels = channels;
		this->sampleRate = sampleRate;
		this->bitsPerSample = bitsPerSample;

		// Tenta abrir o arquivo para escrita
		file.open(fileName.c_str(), ios::out | ios::binary | ios::trunc);
	
		if(!file.is_open()) {
			throw "Could not open file for writing.\n";
		}

		// RIFF - 4 BYTES
		file.write( "RIFF" , 4);
		// TAMANHO DO ARQUIVO - 8 BYTES
		writeInteger(32);
		
		sz = 32;
		writeFormat();
	}

	void writeData(vector<unsigned char> data)
	{
		if(bitsPerSample != 8) {
			throw "Expected 8 bit samples. For 16 bits, use short. For 32 bits, use int.\n";
		}
		sz += data.size() + 8;
		// Atualiza o tamanho do arquivo
		long pos = file.tellp();
		file.seekp(4);

		writeInteger(sz);
		// Volta para a posicao atual
		file.seekp(pos);

		file.write("data", 4);
		// Data size
		writeInteger(data.size());
		// Writes the data
		for(int i = 0; i < data.size(); i++) {
			file.write((char *) &data[i], 1);
		}
	}

	void writeData(vector<short> data)
	{
		if(bitsPerSample != 16) {
			throw "Expected 16 bit samples. For 8 bits, use char. For 32 bits, use int.\n";
		}
		sz += 2 * data.size() + 8;
		// Atualiza o tamanho do arquivo
		long pos = file.tellp();
		file.seekp(4);

		writeInteger(sz);
		// Volta para a posicao atual
		file.seekp(pos);

		file.write("data", 4);
		// Data size
		writeInteger(data.size() * 2);
		// Writes the data
		for(int i = 0; i < data.size(); i++) {
			writeShort(data[i]);
		}
	}


	void close() {
		file.close();
	}

	~WaveFile() {
		file.close();
	}
};



/*
	Classe que possui funções para incluir perturbações 
		em uma onda
*/
class BasicWaveBuilder {
private:
	vector<unsigned char> 	data8;
	vector<short>			data16;
	vector<int>				data32;

	int 			channelsQty;
	int 			sampleRate;
	double			hertzFrequency;
	double			totalTime;
	double 			timePerSample;
	int 			bitsPerSample;

public:

	/**
		channelsQty = quantidade de canais
		lenght = 
	**/
	BasicWaveBuilder(int channelsQty, int seconds, int sampleRate, int bitsPerSample) 
	{
		/* Cria um vetor com todas as amostras */
		if(bitsPerSample == 8)
			data8 = vector<unsigned char> (seconds * sampleRate * channelsQty, 128);
		else if(bitsPerSample == 16)
			data16 = vector<short> (seconds * sampleRate * channelsQty, 0);
		else data32 = vector<int> (seconds * sampleRate * channelsQty, 0);

		this->channelsQty = channelsQty;
		this->sampleRate = sampleRate;
		this->totalTime = seconds;
		timePerSample = (double) 1/sampleRate;
		hertzFrequency = (double) 2 * pi/sampleRate;
		this->bitsPerSample = bitsPerSample;
	}

	int getSampleIndexByTime(double t) {
		int dataSize;
		
		if(bitsPerSample == 8) dataSize = data8.size();
		else if(bitsPerSample == 16) dataSize = data16.size();
		else dataSize = data32.size();

		return min( dataSize-1, (int) (t/timePerSample) );
	}

	void writeToWave(string fileName) {

		WaveFile file(fileName, channelsQty, bitsPerSample, sampleRate);
		
		if(bitsPerSample == 8)
			file.writeData(data8);
		else if(bitsPerSample == 16)
			file.writeData(data16);
		//else file.writeData(data32);

		file.close();
	}

	void addNote(sp::Note_ note, int octave,
				 double t, double duration, double percent)
	{
		int i = getSampleIndexByTime(t);
		int j = getSampleIndexByTime(t + duration);
		
		for( ; i <= j; i++) {
			if(bitsPerSample == 8) {
				data8[i] = data8[i] + percent * 
					sin(i * hertzFrequency * sp::Note::frequencyTable[octave][note]);
			} else if(bitsPerSample == 16) {
				data16[i] = data16[i] + percent * 
					sin(i * hertzFrequency * sp::Note::frequencyTable[octave][note]);
			} else {
				data32[i] = data32[i] + percent * 
					sin(i * hertzFrequency * sp::Note::frequencyTable[octave][note]);
			}
		}
	}

};

int main (void)
{
	string fileName = "mywav.wav";
/*
	int channels = 1;
	int bitsPerSample  = 8;
	int seconds = 15;
	int sampleRate = 22050;

	WaveFile f(fileName, channels, bitsPerSample, sampleRate);
	
	int samplesQty = seconds * sampleRate * channels;

	vector<char> data;

	for(int x = 1; x <= 20; x++) 
		for(int i = 0; i < samplesQty/20; i++) 
			data.pb( (char) 128 + ( 70 * sin(i/x) + 30 * sin(i) ) );

	f.writeData(data);
	f.close();
*/

	int octave = 5;
	BasicWaveBuilder wb(1, 15, 22050, 16);
	// DO RE MI FA :D
	wb.addNote(sp::C, octave, 0, 0.5, 32700);
	wb.addNote(sp::D, octave, 0.5, 0.5, 32700);
	wb.addNote(sp::E, octave, 1, 0.5, 32700);
	wb.addNote(sp::F, octave, 1.5, 0.5, 32700);
	wb.addNote(sp::F, octave, 2.5, 0.5, 32700);
	wb.addNote(sp::F, octave, 3.0, 0.5, 32700);
	wb.addNote(sp::C, octave, 4, 0.5, 32700);
	wb.addNote(sp::D, octave, 4.5, 0.5, 32700);
	wb.addNote(sp::C, octave, 5, 0.5, 32700);
	wb.addNote(sp::D, octave, 5.5, 0.5, 32700);
	wb.addNote(sp::D, octave, 6.5, 0.5, 32700);
	wb.addNote(sp::D, octave, 7, 0.5, 32700);

	wb.addNote(sp::C, octave, 8, 0.5, 32700);
	wb.addNote(sp::G, octave, 8.5, 0.5, 32700);
	wb.addNote(sp::F, octave, 9, 0.5, 32700);
	wb.addNote(sp::E, octave, 9.5, 0.5, 32700);
	wb.addNote(sp::E, octave, 10.5, 0.5, 32700);
	wb.addNote(sp::E, octave, 11, 0.5, 32700);

	wb.addNote(sp::C, octave, 11.5, 0.5, 32700);
	wb.addNote(sp::D, octave, 12, 0.5, 32700);
	wb.addNote(sp::E, octave, 12.5, 0.5, 32700);
	wb.addNote(sp::F, octave, 13, 0.5, 32700);
	wb.addNote(sp::F, octave, 14, 0.5, 32700);
	wb.addNote(sp::F, octave, 14.5, 0.5, 32700);


	wb.writeToWave(fileName);
/*
	fstream g("mywav.wav", ios::in);
	unsigned char c;
	g.unsetf(ios_base::skipws);

	while(g >> c) {
		printf("%x ", c);
	}
*/
	return 0;
}
