#include "JuceHeader.h"
#include "gtest/gtest.h"

using namespace juce;

int main (int argc, char* argv[])
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}
