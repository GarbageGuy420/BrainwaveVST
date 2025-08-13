#include "PluginEditor.h"

BrainwaveVSTAudioProcessorEditor::BrainwaveVSTAudioProcessorEditor (BrainwaveVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

BrainwaveVSTAudioProcessorEditor::~BrainwaveVSTAudioProcessorEditor() = default;

void BrainwaveVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("BrainwaveVST", getLocalBounds(), juce::Justification::centred, 1);
}

void BrainwaveVSTAudioProcessorEditor::resized()
{
}

