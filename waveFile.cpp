#include <waveFile.h>

void sp::WaveFile::writeInteger(int c) {
	file.write( byte(c), 1);
	file.write( byte(c)+1, 1);
	file.write( byte(c)+2, 1);
	file.write( byte(c)+3, 1);
} 

void sp::WaveFile::writeShort(short c) {
	file.write( byte(c), 1);
	file.write( byte(c)+1, 1);	
} 

void sp::WaveFile::writeFormat() {
	
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

sp::WaveFile::WaveFile(std::string fileName, short channels, int bitsPerSample, int sampleRate) {
	this->fileName = fileName;
	// Parametros passados na criação
	this->channels = channels;
	this->sampleRate = sampleRate;
	this->bitsPerSample = bitsPerSample;
	// Tenta abrir o arquivo para escrita
	file.open(fileName.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
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

void sp::WaveFile::writeData(std::vector<unsigned char> data)
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

void sp::WaveFile::writeData(std::vector<short> data)
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

void sp::WaveFile::close() {
	file.close();
}

sp::WaveFile::~WaveFile() {
	file.close();
}