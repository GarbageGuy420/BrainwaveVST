#include "PluginEditor.h"

BrainwaveVSTAudioProcessorEditor::BrainwaveVSTAudioProcessorEditor (BrainwaveVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    frequencySlider.setSliderStyle(juce::Slider::Rotary);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(frequencySlider);
    frequencyAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ", frequencySlider);

    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(gainSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);

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
    auto area = getLocalBounds();
    auto halfWidth = area.getWidth() / 2;
    frequencySlider.setBounds(area.removeFromLeft(halfWidth).reduced(40));
    gainSlider.setBounds(area.reduced(40));
}

