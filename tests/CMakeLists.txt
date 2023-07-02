set(TARGET vitro-tests)

enable_testing()

juce_add_console_app(${TARGET}
    PRODUCT_NAME "VITRO-Tests"
    VERSION      "1.0.0"
    COMPANY_NAME "Arthur Benilov"
)

target_link_libraries(${TARGET}
    PRIVATE
        juce::juce_core
        juce::juce_data_structures
        juce::juce_gui_basics
        juce::juce_gui_extra

        juce::vitro
    PUBLIC
        juce::juce_recommended_config_flags
)

juce_generate_juce_header(${TARGET})

file(GLOB_RECURSE src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(${TARGET} PRIVATE ${src})

target_link_libraries(${TARGET} PRIVATE GTest::gtest)

get_property(sources TARGET ${TARGET} PROPERTY SOURCES)

gtest_discover_tests(${TARGET})

#gtest_add_tests(TARGET ${TARGET}
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/test_stylesheet.cpp
#)
