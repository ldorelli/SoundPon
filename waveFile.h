#ifndef WAVE_FILE
#define WAVE_FILE

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace sp {

#define byte(x) ((const char*) &x)

class WaveFile {
private:
	std::fstream file;
	std::string fileName;
	unsigned long sz;
	unsigned long bitsPerSample;
	int sampleRate;
	short channels;


	void writeInteger(int c);

	void writeShort(short c);

	void writeFormat();

public:

	WaveFile(std::string fileName, short channels, int bitsPerSample, int sampleRate);

	void writeData(std::vector<unsigned char> data);

	void writeData(std::vector<short> data);


	void close();

	~WaveFile();
};

}

#endif