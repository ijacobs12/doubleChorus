/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define PI 3.14159265395
//==============================================================================
A_chorus_linesAudioProcessor::A_chorus_linesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

A_chorus_linesAudioProcessor::~A_chorus_linesAudioProcessor()
{
}

//==============================================================================
const String A_chorus_linesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool A_chorus_linesAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool A_chorus_linesAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool A_chorus_linesAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double A_chorus_linesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int A_chorus_linesAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int A_chorus_linesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void A_chorus_linesAudioProcessor::setCurrentProgram (int index)
{
}

const String A_chorus_linesAudioProcessor::getProgramName (int index)
{
    return {};
}

void A_chorus_linesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void A_chorus_linesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    osc1.setFrequency(1);
    osc1.setSampleRate(sampleRate);
    osc1.setPhaseOffset(0);
    
    osc2.setFrequency(1);
    osc2.setSampleRate(sampleRate);
    osc2.setPhaseOffset(PI/2);
    
    osc3.setFrequency(1);
    osc3.setSampleRate(sampleRate);
    osc3.setPhaseOffset(PI);
    
    osc4.setFrequency(1);
    osc4.setSampleRate(sampleRate);
    osc4.setPhaseOffset(3*PI/2);
    
    leftBuffer.setBufferSize(4410);
    rightBuffer.setBufferSize(4410);
    
    
    leftDelayTime = get_Parameter(((widthParam*.004)+.005)*sampleRate);
    rightDelayTime = get_Parameter(((widthParam*.003)+.005)*sampleRate);
    
    set_Parameter(mixParam, .5);
    set_Parameter(widthParam, .25);
    set_Parameter(rateParam, .1);
    
}

float A_chorus_linesAudioProcessor::get_Parameter(int index)
{
    switch (index) {
        case mixParam: return parameters[0];
        case widthParam: return parameters[1];
        case rateParam: return parameters[2];
        default: return 0.0f;
    }
}

void A_chorus_linesAudioProcessor::set_Parameter(int index, float newValue)
{
    switch (index) {
        case mixParam: parameters[0] = newValue; break;
        case widthParam: parameters[1] = newValue; break;
        case rateParam:  parameters[2] = newValue; break;
        default: break;
    }
}
void A_chorus_linesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A_chorus_linesAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void A_chorus_linesAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (buffer.getNumChannels() == 2)
    {
    for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            osc1.setFrequency(get_Parameter(rateParam));
            float nextSample = osc1.nextSample()+1;
            float leftMod = nextSample*100*get_Parameter(widthParam);
            float rightMod = nextSample*100*get_Parameter(widthParam);
            
            leftDelayTime = 200 + leftMod; //200 * delayparam?
            rightDelayTime = 200 + rightMod;
            
            float l_xn = buffer.getReadPointer(0)[i];
            float r_xn = buffer.getReadPointer(1)[i];
            
            float l_yn = leftBuffer.getSample(leftDelayTime);
            float r_yn = rightBuffer.getSample(rightDelayTime);
            
            float l_combined = l_xn + r_yn*.5;
            float r_combined = r_xn + l_yn*.5; //* feedbackParam?
            leftBuffer.addSample(l_combined);
            rightBuffer.addSample(r_combined);
            buffer.getWritePointer(0)[i] =
                l_xn*(1-get_Parameter(mixParam)) + l_yn*get_Parameter(mixParam);
            buffer.getWritePointer(1)[i] =
                r_xn*(1-get_Parameter(mixParam)) + r_yn*get_Parameter(mixParam);
        
        
        }
    }
    else
    {
        buffer.getWritePointer(0); //audio passes through in mono
    }
}

//==============================================================================
bool A_chorus_linesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* A_chorus_linesAudioProcessor::createEditor()
{
    return new A_chorus_linesAudioProcessorEditor (*this);
}

//==============================================================================
void A_chorus_linesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void A_chorus_linesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A_chorus_linesAudioProcessor();
}
