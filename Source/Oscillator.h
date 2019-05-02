/*
  ==============================================================================

    Oscillator.h
    Created: 1 May 2019 11:25:05pm
    Author:  Isaac Jacobs

    practically stolen from
    https://github.com/marcwilhite/StereoChorus/blob/master/Source/Oscillator.h
  ==============================================================================
*/

#pragma once
#include <iostream>
#include <math.h>

class Oscillator {
private:
    const double mPI;
    const double twoPI;
    bool isMuted;
    double mFrequency;
    double mPhase;
    double mSampleRate;
    int mOvertoneLimit;
    double mPhaseIncrement;
    void updateIncrement();
public:
    void setFrequency(double frequency);
    void setSampleRate(double sampleRate);
    void generate(double* buffer, int nFrames);
    inline void setMuted(bool muted) { isMuted = muted; }
    float nextSample();
    Oscillator():
    mPI(2*acos(0.0)),
    twoPI(2*mPI),
    isMuted(false),
    mFrequency(440.0),
    mPhase(0.0),
    mSampleRate(44100.0) { updateIncrement(); };
    
    
    
    
};
