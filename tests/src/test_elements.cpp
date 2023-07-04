#include "JuceHeader.h"
#include "gtest/gtest.h"

using namespace juce;

TEST(elements, layout_tree)
{
    Identifier tag_root("root");
    Identifier tag_levelA("levelA");
    Identifier tag_levelB("levelB");

    vitro::Context context{};

    auto root = std::make_unique<vitro::LayoutElement>(tag_root, context);
    auto levelA = std::make_unique<vitro::Element>(tag_levelA, context);
    auto levelB = std::make_unique<vitro::LayoutElement>(tag_levelB, context);

    ASSERT_EQ(root->getTag(), tag_root);
    ASSERT_EQ(levelA->getTag(), tag_levelA);
    ASSERT_EQ(levelB->getTag(), tag_levelB);

    auto* levelBPtr = levelB.get();
    levelA->addChildElement(levelB.release());

    // Root layout node is not accessible yet from levelB
    ASSERT_EQ(levelBPtr->getParentLayoutElement(), nullptr);

    auto* levelAPtr = levelA.get();
    root->addChildElement(levelA.release());

    // Root layout node should be accessible not from levelB
    ASSERT_EQ(levelBPtr->getParentLayoutElement(), root.get());
}

TEST(elements, layout_style)
{
    Identifier tag_hbox("hbox");
    Identifier tag_a("a");
    Identifier tag_b("b");

    vitro::Context context{};

    context.getStylesheet().populateFromString(R"(
        hbox {
            flex-direction: row;
            flex-grow: 1;
        }

        a {
            width: 25%;
            flex-grow: 1;
        }

        b {
            width: 75%;
            flex-grow: 1;
        }
    )");

    auto root = std::make_unique<vitro::LayoutElement>(tag_hbox, context);
    root->setAttribute("id", "id_root");

    auto a = std::make_unique<vitro::LayoutElement>(tag_a, context);
    a->setAttribute("id", "id_a");
    auto* aPtr = a.get();
    root->addChildElement(a.release());

    auto b = std::make_unique<vitro::LayoutElement>(tag_b, context);
    b->setAttribute("id", "id_b");
    auto* bPtr = b.get();
    root->addChildElement(b.release());

    ASSERT_EQ(root->getElementById("id_root"), dynamic_cast<vitro::Element*>(root.get()));
    ASSERT_EQ(root->getElementById("id_a"), dynamic_cast<vitro::Element*>(aPtr));
    ASSERT_EQ(root->getElementById("id_b"), dynamic_cast<vitro::Element*>(bPtr));

    // Capture all the style properties of all the elements
    root->updateStyleProperties();
    aPtr->updateStyleProperties();
    bPtr->updateStyleProperties();

    ASSERT_EQ(aPtr->getStyleProperty("width").toString(), "25%");
    ASSERT_EQ(bPtr->getStyleProperty("width").toString(), "75%");

    // Apply style properties to the layout
    root->updateLayout();

    const float width{ 100.0f };
    const float height{ 100.0f };

    // Recalculate elements layout boxes
    root->recalculateLayout(width, height);

    auto rootBounds{ root->getLayoutElementBounds() };
    auto aBounds{ aPtr->getLayoutElementBounds() };
    auto bBounds{ bPtr->getLayoutElementBounds() };

    ASSERT_EQ(rootBounds.getX(), 0.0f);
    ASSERT_EQ(rootBounds.getY(), 0.0f);
    ASSERT_EQ(rootBounds.getWidth(), width);
    ASSERT_EQ(rootBounds.getHeight(), height);

    ASSERT_EQ(aBounds.getX(), 0.0f);
    ASSERT_EQ(aBounds.getY(), 0.0f);
    ASSERT_EQ(aBounds.getWidth(), width * 0.25f);
    ASSERT_EQ(aBounds.getHeight(), height);

    ASSERT_EQ(bBounds.getX(), width * 0.25f);
    ASSERT_EQ(bBounds.getY(), 0.0f);
    ASSERT_EQ(bBounds.getWidth(), width * 0.75f);
    ASSERT_EQ(bBounds.getHeight(), height);
}
