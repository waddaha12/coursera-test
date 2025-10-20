#include <JuceHeader.h>
#include "MainComponent.h"

class AudioApp : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Enhanced Audio Player"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    void initialise(const juce::String&) override
    {
        mainWindow.reset(new MainWindow("Enhanced Audio Player", new MainComponent(), *this));
    }

    void shutdown() override { mainWindow = nullptr; }

private:
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name, juce::Component* c, JUCEApplication& a)
            : DocumentWindow(name, juce::Colours::darkgrey, DocumentWindow::allButtons), app(a)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(c, true);
            centreWithSize(getWidth(), getHeight());
            setVisible(true);
        }

        void closeButtonPressed() override { app.systemRequestedQuit(); }

    private:
        JUCEApplication& app;
    };

    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(AudioApp)