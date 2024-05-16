//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#include "MainComponent.h"

MainComponent::MainComponent()
{
    viewContainer.setLocalDirectory(File::getSpecialLocation(File::currentApplicationFile).getParentDirectory());
    addAndMakeVisible(viewContainer);

    viewContainer.addListener(this);

    filesWatcher = std::make_unique<FilesWatcher>();
    filesWatcher->addListener(this);

    reload();
    triggerAsyncUpdate();

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    filesWatcher->removeListener(this);
    viewContainer.getContext()->getLoader().removeListener(this);
}

void MainComponent::reload()
{
    filesWatcher->clearWacthedFiles();
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

void MainComponent::onContextCreated(vitro::Context* ctx)
{
    jassert(ctx != nullptr);
    ctx->getLoader().addListener(this);
}

void MainComponent::onResourceLoaded(const juce::String& location, const juce::File& file)
{
    if (file.existsAsFile())
        filesWatcher->addFileToWatch(file);
}

void MainComponent::onWatchedFilesChanged()
{
    reload();
}
