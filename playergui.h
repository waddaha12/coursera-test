#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
                  public juce::Button::Listener,
                  public juce::Slider::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void resized() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

private:
    PlayerAudio playerAudio;

    juce::TextButton loadButton{ "Load" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton restartButton{ "Restart" };

    // NEW: Loop toggle button
    juce::ToggleButton loopToggle{ "Loop" };

    juce::Slider volumeSlider;

    std::unique_ptr<juce::FileChooser> chooser;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
};