set(TARGET "viewer")

juce_add_gui_app(${TARGET}
    PRODUCT_NAME "vitro_viewer"
    VERSION "1.0.0"
    COMPANY_NAME "Archie3D"
)

target_link_libraries(${TARGET}
    PRIVATE
        juce::juce_core
        juce::juce_data_structures
        juce::juce_audio_basics
        juce::juce_audio_utils
        juce::juce_audio_plugin_client
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_opengl

        juce::vitro
    PUBLIC
        juce::juce_recommended_config_flags
)

juce_generate_juce_header(${TARGET})

set(src
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FilesWatcher.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FilesWatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainComponent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainComponent.cpp
)

target_sources(${TARGET} PRIVATE ${src})

target_compile_definitions(${TARGET}
    PUBLIC
        JUCE_DISPLAY_SPLASH_SCREEN=0
)
