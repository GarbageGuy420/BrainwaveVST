#include "PluginProcessor.h"
#include "PluginEditor.h"

BrainwaveVSTAudioProcessor::BrainwaveVSTAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                       .withInput ("Input", juce::AudioChannelSet::stereo(), true)
#endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                       )
#endif
{
}

BrainwaveVSTAudioProcessor::~BrainwaveVSTAudioProcessor() = default;

const juce::String BrainwaveVSTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BrainwaveVSTAudioProcessor::acceptsMidi() const
{
    return JucePlugin_WantsMidiInput;
}

bool BrainwaveVSTAudioProcessor::producesMidi() const
{
    return JucePlugin_ProducesMidiOutput;
}

bool BrainwaveVSTAudioProcessor::isMidiEffect() const
{
    return JucePlugin_IsMidiEffect;
}

double BrainwaveVSTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BrainwaveVSTAudioProcessor::getNumPrograms()
{
    return 1;
}

int BrainwaveVSTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BrainwaveVSTAudioProcessor::setCurrentProgram (int)
{
}

const juce::String BrainwaveVSTAudioProcessor::getProgramName (int)
{
    return {};
}

void BrainwaveVSTAudioProcessor::changeProgramName (int, const juce::String&)
{
}

void BrainwaveVSTAudioProcessor::prepareToPlay (double, int)
{
}

void BrainwaveVSTAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BrainwaveVSTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (! JucePlugin_IsSynth && layouts.getMainInputChannelSet() != layouts.getMainOutputChannelSet())
        return false;

    return true;
#endif
}
#endif

void BrainwaveVSTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
}

bool BrainwaveVSTAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* BrainwaveVSTAudioProcessor::createEditor()
{
    return new BrainwaveVSTAudioProcessorEditor (*this);
}

void BrainwaveVSTAudioProcessor::getStateInformation (juce::MemoryBlock&)
{
}

void BrainwaveVSTAudioProcessor::setStateInformation (const void*, int)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BrainwaveVSTAudioProcessor();
}

