#include <instrument.h>

sp::Instrument::Instrument(
	double attackTime, 
	double decayTime, double sustainLvl, 
	double releaseTime, int harmonicsProduced)
{
	this->attackTime = attackTime;
	this->decayTime = decayTime;
	this->sustainLvl = sustainLvl;
	this->releaseTime = releaseTime;
	this->harmonicsProduced = harmonicsProduced;
	this->sustainLvl = sustainLvl;
}