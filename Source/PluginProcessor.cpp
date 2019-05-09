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
                       ), treeState(*this, nullptr, "PARAMS",
                                    {
                                        std::make_unique<AudioParameterFloat>
                                            ("mix","Mix", NormalisableRange<float>(0.0,1.0), 0.5f),
                                        std::make_unique<AudioParameterFloat>("rate","Rate",NormalisableRange<float>(0.01f, 4.0f, 0, .8), 1.0f),
                                        //0 indicates continuous range, .8 introduces a skew so lower
                                        //frequencies take up more of the knob
                                        std::make_unique<AudioParameterFloat>("width","Width",NormalisableRange<float>(0.2,1.3), 0.5f),
                                        std::make_unique<AudioParameterFloat>("feedback","Feedback",  NormalisableRange<float>(0.2f,0.89f), 0.3f)
                                    }
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
    
    smoothWidth.reset(100); //100 sample ramp
    smoothMix.reset(100);
    smoothWidth.setCurrentAndTargetValue(*treeState.getRawParameterValue("width"));
    
    
    
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
    float freq = *treeState.getRawParameterValue("rate");
    smoothWidth.setTargetValue(*treeState.getRawParameterValue("width"));
    smoothMix.setTargetValue(*treeState.getRawParameterValue("mix"));
    float feedback = *treeState.getRawParameterValue("feedback");
    
    osc1.setFrequency(freq);
    osc2.setFrequency(freq);
    osc3.setFrequency(freq);
    osc4.setFrequency(freq);
    if (buffer.getNumChannels() == 2)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) //we have two channels, iterate through them
            {
            
            float nextSample1 = osc1.nextSample() + 1; // get oscillator values for offset
            float nextSample2 = osc2.nextSample() + 1;
            float nextSample3 = osc3.nextSample() + 1;
            float nextSample4 = osc4.nextSample() + 1;
             
            float width = smoothWidth.getNextValue();
            float mod1 = 440 + nextSample1*100*width;
            float mod2 = 440 + nextSample2*100*width;
            float mod3 = 440 + nextSample3*100*width;
            float mod4 = 440 + nextSample4*100*width;
            
            float l_xn = buffer.getReadPointer(0)[i]; // raw audio
            float r_xn = buffer.getReadPointer(1)[i];
            
            float l_yn1 = leftBuffer.getSample(mod1); // delay line audio
            float l_yn2 = leftBuffer.getSample(mod2);
            float l_yn3 = leftBuffer.getSample(mod3);
            float l_yn4 = leftBuffer.getSample(mod4);
            
            float r_yn1 = rightBuffer.getSample(mod1);
            float r_yn2 = rightBuffer.getSample(mod2);
            float r_yn3 = rightBuffer.getSample(mod3);
            float r_yn4 = rightBuffer.getSample(mod4);
            
            // update delay lines. including all delay lines creates some interference that destroys the classic phasing effect, which is why I only use yn1 and 2.
            float l_combined = (l_xn + (l_yn1)*feedback);
            float r_combined = (r_xn + (r_yn3)*feedback);
            
            rightBuffer.addSample(l_combined);
            leftBuffer.addSample(r_combined);
            
            // write to output buffer. divide by 2 is a hacky normalization that I found by experimentation (trying to get avg. volume of 100% dry to equal avg. vol of 100% wet). makes me sort of uncomfortable because seems like it should be four, but that makes things decidedly too quiet on the wet end. hmm.
                
            float mix = smoothMix.getNextValue();
            buffer.getWritePointer(0)[i] =
                l_xn*(1 - mix) + (r_yn1+r_yn2+r_yn3+r_yn4)*mix/2.1;
            buffer.getWritePointer(1)[i] =
                r_xn*(1 - mix) + (l_yn1+l_yn2+l_yn3+l_yn4)*mix/2.1;
        
                }
            }
    else // channel is mono
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) //we have two channels, iterate through them
        {
            
        float nextSample1 = osc1.nextSample() + 1; // get oscillator values for offset
        float nextSample2 = osc2.nextSample() + 1;
        float nextSample3 = osc3.nextSample() + 1;
        float nextSample4 = osc4.nextSample() + 1;
            
        float width = smoothWidth.getNextValue();
        float mod1 = 440 + nextSample1 * 150 * width;
        float mod2 = 440 + nextSample2 * 150 * width;
        float mod3 = 440 + nextSample3 * 150 * width;
        float mod4 = 440 + nextSample4 * 150 * width;
        float l_xn = buffer.getReadPointer(0)[i]; // raw audio
        
        float l_yn1 = leftBuffer.getSample(mod1); // delay line audio
        float l_yn2 = leftBuffer.getSample(mod2);
        float l_yn3 = leftBuffer.getSample(mod3);
        float l_yn4 = leftBuffer.getSample(mod4);
        
        float l_combined = l_xn + (l_yn1+l_yn2)* feedback/2.;
        
        leftBuffer.addSample(l_combined); // update delay line
        
        // write to output buffer
        float mix = smoothMix.getNextValue();
        buffer.getWritePointer(0)[i] =
        l_xn*(1 - mix) + (l_yn1+l_yn2+l_yn3+l_yn4)* mix/2.1;
            
        }
    }
}

//==============================================================================
bool A_chorus_linesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* A_chorus_linesAudioProcessor::createEditor()
{
    return new A_chorus_linesAudioProcessorEditor (*this, treeState);
    //return new GenericAudioProcessorEditor (this);
}

//==============================================================================
void A_chorus_linesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = treeState.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void A_chorus_linesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr and xmlState -> hasTagName(treeState.state.getType()))
        {
            treeState.replaceState(ValueTree::fromXml(*xmlState));
            smoothWidth.setCurrentAndTargetValue(*treeState.getRawParameterValue("width"));
            smoothMix.setCurrentAndTargetValue(*treeState.getRawParameterValue("mix"));
           
        }

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A_chorus_linesAudioProcessor();
}
