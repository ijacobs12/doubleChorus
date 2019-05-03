/*
  ==============================================================================

    Oscillator.cpp
    Created: 1 May 2019 11:25:05pm
    Author:  Isaac Jacobs
        
    practically stolen from
    https://github.com/marcwilhite/StereoChorus/blob/master/Source/Oscillator.cpp
  ==============================================================================
*/

#include "Oscillator.h"

void Oscillator::setFrequency(double frequency)
{
    mFrequency = frequency;
    updateIncrement();
}

void Oscillator::setSampleRate(double sampleRate)
{
    mSampleRate = sampleRate;
    updateIncrement();

}

void Oscillator::setPhaseOffset(double offset)
{
    mPhaseOffset = offset;
}

void Oscillator::updateIncrement()
{
    mPhaseIncrement = mFrequency * twoPI/mSampleRate;
}

void Oscillator::generate(double *buffer, int nFrames)
{
    for (int i =0; i < nFrames; i++)
    {
        buffer[i] = sin(mPhase);
        mPhase += mPhaseIncrement;
        while (mPhase >= twoPI)
        {
            mPhase -= twoPI;
        }
    }
}

float Oscillator::nextSample()
{
    float value = 0.0;
    if(isMuted) return value;
    value = sin(mPhase);
    mPhase += mPhaseIncrement;
    while (mPhase >= twoPI)
    {
        mPhase -= twoPI;
    }
    return value;
}
