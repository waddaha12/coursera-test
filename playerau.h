#pragma once
#include <JuceHeader.h>

// PlayerAudio: handles loading, playback, gain, position, and looping.
class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFile(const juce::File& file);
    void play();
    void stop();
    void restart();

    void setGain(float gain);
    double getPosition() const;
    void setPosition(double pos);
    double getLength() const;

    // Loop control
    void setLooping(bool shouldLoop);
    bool isLooping() const;

private:
    juce::AudioFormatManager formatManager;

    // We keep readerSource as a PositionableAudioSource unique_ptr (AudioFormatReaderSource derives from that)
    std::unique_ptr<juce::PositionableAudioSource> readerSource;

    // LoopingAudioSource wraps the readerSource to provide looping behavior.
    std::unique_ptr<juce::LoopingAudioSource> loopingSource;

    juce::AudioTransportSource transportSource;
    bool loopingEnabled { false };
};