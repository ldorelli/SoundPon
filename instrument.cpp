#include <instrument.h>
#include <cmath>

sp::Instrument::Instrument(
	double attackTime, 
	double decayTime, double sustainLvl, 
	double releaseTime)
{
	this->attackTime = attackTime;
	this->decayTime = decayTime;
	this->sustainLvl = sustainLvl;
	this->releaseTime = releaseTime;
	this->sustainLvl = sustainLvl;
	harmonics.push_back(1);
}

double sp::Instrument::getADRduration() {
	return attackTime + releaseTime + decayTime;
}

void sp::Instrument::addHarmonic(int h) {
	harmonics.push_back(h);
}

#include <iostream>
using namespace std;
double sp::Instrument::getNoteValue(sp::Note note, double t0, double t, 
	double mpl, double volume, double holdDuration)
{
	//cout << t << " " << t0 << " " << holdDuration <<  endl;
	t = t  - t0;
	t0 = 0;

	double freq = note.getFrequency() * mpl;

/*	
A	   /\
 	  /	 \ _ _ _   S
	 /           \
0	/             \  0
  t0  aT aT+dT	  rT
*/

  /* 
  		pitch = m * time + b 
  		This will multiply the sine wave
  */
  /* Attack phase */

  if(t0 + t < attackTime) {

  		double m, b;
  		m = volume/attackTime;
  		b = - m * t0;
  		double vol = m * t + b;
  		double res = 0.0;

  		for(int i = 0; i < harmonics.size(); i++)
  			res += sin(t * harmonics[i] * freq);
  		
  		return res * vol / harmonics.size();

  } else if(t0 + t < decayTime + attackTime) {
  		
  		double m, b;
  		m = (sustainLvl - volume)/decayTime;
  		b = volume - m * attackTime;
  		
  		double vol = m * t + b;
  		double res = 0.0;
  		
  		for(int i = 0; i < harmonics.size(); i++)
  			res += sin(t * harmonics[i] * freq);

  		return res * vol / harmonics.size();

  } else if(t0 + t < attackTime + decayTime + holdDuration) {
  		
  		double res = 0.0;
  		for(int i = 0; i < harmonics.size(); i++)
  			res += sin(t * harmonics[i] * freq);
  		
  		return sustainLvl * res / harmonics.size();

  } else if(t0 + t <= attackTime + decayTime + holdDuration + releaseTime) {
  		
  		double m, b;
  		
  		m = -sustainLvl/releaseTime;
  		b = -m * (attackTime + decayTime + holdDuration + releaseTime);
  		
  		double vol = m * t + b;
  		double res = 0.0;
  		
  		for(int i = 0; i < harmonics.size(); i++)
  			res += sin(t * harmonics[i] * freq);

  		return res * vol / harmonics.size();
  } else return 0.0;
}

sp::Instrument::~Instrument() {
	harmonics.clear();
}