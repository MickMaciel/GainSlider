#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"

//==============================================================================

class GainAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GainAudioProcessorEditor (GainAudioProcessor&);
    ~GainAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GainAudioProcessor& audioProcessor;
    
    juce::Slider gainSlider;
    
    juce::AudioProcessorValueTreeState::SliderAttachment attachment
    {
        audioProcessor.apvts, gainParamId.getParamID(), gainSlider
    };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainAudioProcessorEditor)
};
