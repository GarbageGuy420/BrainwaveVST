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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrainwaveVSTAudioProcessorEditor)
};

