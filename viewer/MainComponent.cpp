//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#include "MainComponent.h"

MainComponent::MainComponent()
{
    viewContainer.setLocalDirectory(File::getSpecialLocation(File::currentApplicationFile).getParentDirectory());
    addAndMakeVisible(viewContainer);

    reload();
    triggerAsyncUpdate();

    setSize (600, 400);
}

MainComponent::~MainComponent() = default;

void MainComponent::reload()
{
    viewContainer.loadFromResource("view.xml", "style.css", "script.js");

    // Need to call resized so that the new view gets adjusted to the container
    resized();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
}

void MainComponent::resized()
{
    viewContainer.setBounds(getLocalBounds());
}

void MainComponent::handleAsyncUpdate()
{
    getTopLevelComponent()->addKeyListener(this);
}

bool MainComponent::keyPressed(const KeyPress& key, Component*)
{
    // Capture Ctrl-R to refresh the UI
    if (key.getModifiers().isCommandDown() && key.isKeyCode(82)) {
        reload();
        return true;
    }

    return false;

}
