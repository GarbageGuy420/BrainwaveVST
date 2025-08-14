#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <vector>

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
    , apvts(*this, nullptr, "Parameters", createParameterLayout())
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

void BrainwaveVSTAudioProcessor::prepareToPlay (double sampleRate, int)
{
    oscillator.prepare(sampleRate);
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
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    buffer.clear();

    auto gain = apvts.getRawParameterValue("GAIN")->load();
    auto freq = apvts.getRawParameterValue("FREQ")->load();
    oscillator.setFrequency(freq);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        auto value = oscillator.getNextSample() * gain;
        for (int channel = 0; channel < totalNumOutputChannels; ++channel)
            buffer.setSample(channel, sample, value);
    }
}

bool BrainwaveVSTAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* BrainwaveVSTAudioProcessor::createEditor()
{
    return new BrainwaveVSTAudioProcessorEditor (*this);
}

void BrainwaveVSTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary(*xml, destData);
}

void BrainwaveVSTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout BrainwaveVSTAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FREQ", "Frequency",
        juce::NormalisableRange<float>(20.f, 2000.f, 0.01f, 0.5f), 440.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "GAIN", "Gain",
        juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.5f));

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BrainwaveVSTAudioProcessor();
}

