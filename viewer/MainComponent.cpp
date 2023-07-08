//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#include "MainComponent.h"

MainComponent::MainComponent()
    : context{},
      view{ std::make_shared<vitro::View>(context) }
{
    context.getLoader().setLocalDirectory(File::getSpecialLocation(File::currentApplicationFile).getParentDirectory());

    addAndMakeVisible(view.get());

    reload();
    triggerAsyncUpdate();

    setSize (600, 400);
}

MainComponent::~MainComponent() = default;

void MainComponent::reload()
{
    context.reset();

    const auto& loader{ context.getLoader() };

    auto styleImporter = [&](const String& location) -> String {
        return loader.loadText(location);
    };

    auto& stylesheet{ context.getStylesheet() };

    stylesheet.clear();
    stylesheet.populateFromString(loader.loadText("style.css"), styleImporter);

    String script{ loader.loadText("script.js") };

    if (script.isNotEmpty()) {
        context.eval(script, "script.js");
        context.dumpError();
    }

    // This will remove all current children in the view
    view->populateFromXmlResource("index.xml");
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
