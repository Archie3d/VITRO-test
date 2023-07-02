//
//  Copyright (C) 2022 Arthur Benilov <arthur.benilov@gmail.com>
//

#include "MainComponent.h"

MainComponent::MainComponent()
    : label({}, "This is a text label"),
      button("Text button")
{
    setSize (600, 400);

    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
    addAndMakeVisible(button);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
}

void MainComponent::resized()
{
    auto bounds {getLocalBounds()};

    button.setBounds(bounds.removeFromBottom(80).reduced(20));
    label.setBounds(bounds.removeFromBottom(40));
}
