#include "Parameters.h"

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    auto* param = apvts.getParameter(gainParamId.getParamID());
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
}

juce::AudioProcessorValueTreeState::ParameterLayout
Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                           gainParamId,
                                                           "OutputGain",
                                                           juce::NormalisableRange<float> { -36.0f, 12.0f },
                                                           0.0f));
   
    return layout;
}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    double duration = 0.02;
    gainSmoother.reset(sampleRate, duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
}

void Parameters::update() noexcept
{
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
}

void Parameters::smoothen() noexcept
{
    gain = gainSmoother.getNextValue();
}
