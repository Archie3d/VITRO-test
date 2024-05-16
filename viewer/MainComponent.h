//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#pragma once

#include <JuceHeader.h>
#include "FilesWatcher.h"

class MainComponent : public juce::Component,
                      private juce::AsyncUpdater,
                      private juce::KeyListener,
                      private vitro::ViewContainer::Listener, 
                      private vitro::Loader::Listener,
                      private FilesWatcher::Listener
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

    // vitro::ViewContainer::Listener
    void onContextCreated(vitro::Context* ctx) override;

    // vitro::Loader::Listener
    void onResourceLoaded(const juce::String& location, const juce::File& file) override;

    // FilesWatcher::Listener
    void onWatchedFilesChanged() override;

    vitro::ViewContainer viewContainer{};
    std::unique_ptr<FilesWatcher> filesWatcher{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
