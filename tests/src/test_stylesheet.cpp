#include "JuceHeader.h"
#include "gtest/gtest.h"

using namespace juce;


/** Test basic stylesheet parsing and properties extraction. */
TEST(stylesheet, parse)
{
    vitro::Stylesheet stylesheet{};

    stylesheet.populateFromString(R"(
        {
            property: global;
        }

        tag {
            property: tag;
        }

        .class {
            property: class;
        }

        #id {
            property: id;
        }

        [attr="value"] {
            property: attribute;
        }
    )");

    ValueTree tree("tag");

    const auto valGlobal{ stylesheet.getProperty("property", "", {}, "", tree) };
    ASSERT_EQ(valGlobal.toString(), "global");

    const auto valTag{ stylesheet.getProperty("property", "tag", {}, "", tree) };
    ASSERT_EQ(valTag.toString(), "tag");

    const auto valClass{ stylesheet.getProperty("property", "", {"class"}, "", tree) };
    ASSERT_EQ(valClass.toString(), "class");

    const auto valId{ stylesheet.getProperty("property", "", {}, "id", tree) };
    ASSERT_EQ(valId.toString(), "id");

    tree.setProperty("attr", "value", nullptr);
    const auto valAttr{ stylesheet.getProperty("property", "", {}, "", tree) };
    ASSERT_EQ(valAttr.toString(), "attribute");
}

TEST(stylesheet, attributes)
{
    vitro::Stylesheet stylesheet{};

    stylesheet.populateFromString(R"(
        [attr="value"] {
            property: attribute;
        }
    )");

    ValueTree tree("tag");
    tree.setProperty("attr", "value", nullptr);
    const auto valAttr{ stylesheet.getProperty("property", "", {}, "", tree) };
    ASSERT_EQ(valAttr.toString(), String("attribute"));
}

TEST(stylesheet, macros)
{
    vitro::Stylesheet stylesheet{};

    stylesheet.populateFromString(R"(
        $macro1 : 1;
        $macro2 : 2;

        tag1 {
            value : $macro1;
        }

        tag2 {
            value : $macro2;
        }
    )");

    ValueTree tree("tag");

    const auto val1{ stylesheet.getProperty("value", "tag1", {}, "", tree) };
    ASSERT_EQ((int)val1, 1);

    const auto val2{ stylesheet.getProperty("value", "tag2", {}, "", tree) };
    ASSERT_EQ((int)val2, 2);
}
