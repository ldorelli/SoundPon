#include <instrument.h>
#include <cmath>

sp::Instrument::Instrument() {}

sp::Instrument::~Instrument() {
	notesOn.clear();
}

int sp::Instrument::pressNote (double frequency, double volume) {
	int sz = notesOn.size();
	notesOn.push_back(sp::PressedNote(frequency, 0.0, volume, sp::PRESS));
	return sz;
}

void sp::Instrument::releaseNote (int noteIndex) {
	notesOn[noteIndex].state = sp::RELEASE;
}

double sp::Instrument::nextAmplitude (double timeStep) {
	double res = 0.0;
	for (auto it = notesOn.begin(); it != notesOn.end(); ) {
		PressedNote& note = *it;
		switch (note.state) {
			case sp::PRESS:
				res += attack(note, timeStep);
				break;
			case sp::SUSTAIN:
				res += sustain(note, timeStep);
				break;	
			case sp::RELEASE:
				res += decay(note, timeStep);
				break;
		}
		if (note.done) { 
			it = notesOn.erase(it);
		} else {
			++it;
		}
	}
	return res;
}


// sp::Instrument::Instrument(int channelCount, int sampleRate, double volume, double updateTime)
// {
// 	this->channelsQty = channelCount;
// 	this->sampleRate = sampleRate;
// 	this->updateTime = updateTime;
// 	this->volume = volume;
// 	this->timePerSample = 1.0/(double)sampleRate;
// 	harmonics.push_back(1);
// 	data = std::vector<sf::Int16> (updateTime * sampleRate, 0.0);
// 	initialize(channelCount, sampleRate);
// }

// void sp::Instrument::addHarmonic(double h) {
// 	harmonics.push_back(h);
// }

// bool sp::Instrument::onGetData(Chunk& data) {
// 	return true;
// }

// void sp::Instrument::onSeek(sf::Time timeOffset) {
// }


// int sp::Instrument::pressNote(double freq, double volume) {
// 	int sz = notesON.size();
// 	notesON.push_back(PressedNote(freq, 0.0, volume, sp::PRESS));
// 	return sz;
// }

// void sp::Instrument::updateNote(sp::PressedNote& note) {
// 	if (note.state == sp::PRESS and note.time >= attackTime) {
// 		 note.time = 0, note.state = sp::SUSTAIN;
// 	}
// 	note.time += timePerSample;
// }

// double sp::Instrument::getAmplitude (int noteId) {
// 	sp::PressedNote &note = notesON[noteId];
// 	double res;
// 	switch (note.state) {
// 		case sp::PRESS:
// 			res = attack(note.frequency, note.time);
// 			break;
// 		case sp::SUSTAIN:
// 			res = sustain(note.frequency, note.time);
// 			break;
// 		case sp::RELEASE:
// 			res = decay(note.frequency, note.time);
// 			break;
// 	}
// 	updateNote(note);
// 	return res * note.volume;
// }


// // double sp::Instrument::getAmplitude(double freq, double t,
// // 	double mpl, double volume, double holdDuration)
// // {
// // 	freq *= mpl;
// //   	double res = 0.0;
// // 	for(int i = 0; i < harmonics.size(); i++)
// // 		res += sin(t * harmonics[i] * freq);
// // 	return res;
// // }

// sp::Instrument::~Instrument() {
// 	harmonics.clear();
// }