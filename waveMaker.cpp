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

using namespace std;

typedef long long int LL;
typedef pair<int,int> pii;

#define F first
#define S second
#define pb push_back
#define mp make_pair
#define byte(x) ((const char*) &x)

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

	void writeData(vector<char> data)
	{
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
			if(bitsPerSample == 8)
				file.write(&data[i], 1);
		}
	}

	void close() {
		file.close();
	}

	~WaveFile() {
		file.close();
	}
};

int main (void)
{
	string fileName = "mywav.wav";

	int channels = 1;
	int bitsPerSample  = 8;
	int seconds = 15;
	int sampleRate = 22050;

	WaveFile f(fileName, channels, bitsPerSample, sampleRate);
	
	int samplesQty = seconds * sampleRate;

	vector<char> data;

	for(int x = 1; x <= 20; x++) 
		for(int i = 0; i < samplesQty/20; i++) 
			data.pb( (char) 128 + 55 *  ( sin(i/x) + (x%4) * cos(i/x) ) );

	f.writeData(data);
	f.close();

	fstream g("mywav.wav", ios::in);
	unsigned char c;
	g.unsetf(ios_base::skipws);
/*
	while(g >> c) {
		printf("%x ", c);
	}
*/
	return 0;
}
