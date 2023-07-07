//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#pragma once

#include <JuceHeader.h>

class MainComponent : public juce::Component,
                      private juce::AsyncUpdater,
                      private juce::KeyListener
{
public:

    MainComponent();
    ~MainComponent() override;

    void reload();

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // juce::AsyncUpdater
    void handleAsyncUpdate() override;

    // juce::KeyListener
    bool keyPressed(const juce::KeyPress& key, juce::Component* source) override;

    vitro::Context context;
    std::shared_ptr<vitro::View> view;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
