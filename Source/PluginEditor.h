#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class BrainwaveVSTAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit BrainwaveVSTAudioProcessorEditor (BrainwaveVSTAudioProcessor&);
    ~BrainwaveVSTAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BrainwaveVSTAudioProcessor& audioProcessor;
    juce::Slider frequencySlider;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> frequencyAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrainwaveVSTAudioProcessorEditor)
};

