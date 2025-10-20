#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(restartButton);
    addAndMakeVisible(volumeSlider);

    loadButton.addListener(this);
    playButton.addListener(this);
    stopButton.addListener(this);
    restartButton.addListener(this);
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
    auto area = getLocalBounds().reduced(10);
    loadButton.setBounds(area.removeFromTop(30));
    playButton.setBounds(area.removeFromTop(30));
    stopButton.setBounds(area.removeFromTop(30));
    restartButton.setBounds(area.removeFromTop(30));
    volumeSlider.setBounds(area.removeFromTop(40));
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
                    playerAudio.loadFile(file);
            });
    }
    else if (button == &playButton)
        playerAudio.play();
    else if (button == &stopButton)
        playerAudio.stop();
    else if (button == &restartButton)
        playerAudio.restart();
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain(slider->getValue());
}