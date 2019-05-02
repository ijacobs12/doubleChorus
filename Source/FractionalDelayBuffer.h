/*
  ==============================================================================

    FractionalDelayBuffer.h
    Created: 1 May 2019 11:36:07pm
    Author:  Isaac Jacobs

    practically stolen from
    https://github.com/marcwilhite/StereoChorus/blob/master/Source/FractionalDelayBuffer.h
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>

class FractionalDelayBuffer
{
public:
    FractionalDelayBuffer();
    ~FractionalDelayBuffer();
    
    void clear();
    void setBufferSize(int size);
    void addSample(float sample);
    float getSample(float sampleIndex);
    int getValidIndex(int index);
    float linearInterpolate(float* buffer, int bufferSize, int bufferPosition);
    
private:
    int index;
    int bufferSize;
    float* buffer;
    
    
};
