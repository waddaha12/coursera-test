#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(restartButton);
    addAndMakeVisible(loopToggle);      // make loop toggle visible
    addAndMakeVisible(volumeSlider);

    loadButton.addListener(this);
    playButton.addListener(this);
    stopButton.addListener(this);
    restartButton.addListener(this);
    loopToggle.addListener(this);       // listen for loop toggle changes
    volumeSlider.addListener(this);

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

void PlayerGUI::resized()
{
    auto area = getLocalBounds().reduced(8);

    auto top = area.removeFromTop(30);
    loadButton.setBounds(top.removeFromLeft(100).reduced(2));
    playButton.setBounds(top.removeFromLeft(100).reduced(2));
    stopButton.setBounds(top.removeFromLeft(100).reduced(2));
    restartButton.setBounds(top.removeFromLeft(100).reduced(2));
    loopToggle.setBounds(top.removeFromLeft(80).reduced(2));

    volumeSlider.setBounds(area.removeFromTop(40).reduced(2));
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        chooser = std::make_unique<juce::FileChooser>("Select an audio file...");
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    bool ok = playerAudio.loadFile(file);
                    // optional: you can update UI (enable play button) based on ok
                }
            });
    }
    else if (button == &playButton)
    {
        playerAudio.play();
    }
    else if (button == &stopButton)
    {
        playerAudio.stop();
    }
    else if (button == &restartButton)
    {
        playerAudio.restart();
    }
    else if (button == &loopToggle)
    {
        bool shouldLoop = loopToggle.getToggleState();
        playerAudio.setLooping(shouldLoop);
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain(slider->getValue());
}