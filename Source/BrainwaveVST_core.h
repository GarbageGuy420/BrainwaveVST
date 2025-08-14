#pragma once

#include <JuceHeader.h>

// Simple sine wave oscillator
class BrainwaveCore {
public:
    void prepare(double sampleRate)
    {
        currentSampleRate = sampleRate;
        phase = 0.0f;
        updateIncrement();
    }

    void setFrequency(float newFrequency)
    {
        frequency = newFrequency;
        updateIncrement();
    }

    float getNextSample()
    {
        auto value = std::sin(phase);
        phase += phaseIncrement;
        if (phase >= juce::MathConstants<float>::twoPi)
            phase -= juce::MathConstants<float>::twoPi;
        return value;
    }

private:
    void updateIncrement()
    {
        phaseIncrement = juce::MathConstants<float>::twoPi * frequency / static_cast<float>(currentSampleRate);
    }

    double currentSampleRate { 44100.0 };
    float frequency { 440.0f };
    float phase { 0.0f };
    float phaseIncrement { 0.0f };
};
