//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#include "MainComponent.h"

MainComponent::MainComponent()
{
    reload();
    triggerAsyncUpdate();

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    // The view must be deleted before the context, otherwise JS context will leak.
    view.reset();
}

void MainComponent::reload()
{
    // Delete the current view
    view.reset();
    context.reset();

    context = std::make_unique<vitro::Context>();

    auto& loader{ context->getLoader() };
    loader.setLocalDirectory(File::getSpecialLocation(File::currentApplicationFile).getParentDirectory());

    auto styleImporter = [&](const String& location) -> String {
        return loader.loadText(location);
    };

    auto& stylesheet{ context->getStylesheet() };

    stylesheet.clear();
    stylesheet.populateFromString(loader.loadText("style.css"), styleImporter);

    // Create a new view before evaluating the script
    view = std::dynamic_pointer_cast<vitro::View>(context->getElementsFactory().createElement(vitro::View::tag));
    addAndMakeVisible(view.get());

    String script{ loader.loadText("script.js") };

    if (script.isNotEmpty()) {
        context->eval(script, "script.js");
        context->dumpError();
    }

    // This will remove all current children in the view
    view->populateFromXmlResource("index.xml");
    
    // Need to call resized so that the new view gets adjusted to the container
    resized();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
}

void MainComponent::resized()
{
    view->setBounds(getLocalBounds());
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
