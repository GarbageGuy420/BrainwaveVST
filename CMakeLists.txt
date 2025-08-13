cmake_minimum_required(VERSION 3.22)
project(BrainwaveVST VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Tell CMake where JUCE is: either pass -DJUCE_DIR=... or keep JUCE next to this folder (../JUCE)
if(DEFINED JUCE_DIR)
  message(STATUS "Using JUCE at: ${JUCE_DIR}")
  add_subdirectory(${JUCE_DIR} ${CMAKE_BINARY_DIR}/JUCE-build)
else()
  message(STATUS "Using JUCE at ../JUCE (sibling folder). You can override with -DJUCE_DIR=...")
  add_subdirectory(../JUCE ${CMAKE_BINARY_DIR}/JUCE-build)
endif()

juce_add_plugin(BrainwaveVST
    COMPANY_NAME "AtlasAudio"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE AtlA
    PLUGIN_CODE BrnW
    FORMATS VST3 Standalone
    PRODUCT_NAME "BrainwaveVST")

juce_generate_juce_header(BrainwaveVST)

# Avoid JUCE's VST2/3 automation warning
add_compile_definitions(JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)

set(SRC
  Source/PluginProcessor.cpp
  Source/PluginEditor.cpp
  Source/BrainwaveVST_core.h
  Source/PluginProcessor.h
  Source/PluginEditor.h
)

target_sources(BrainwaveVST PRIVATE ${SRC})

target_link_libraries(BrainwaveVST PRIVATE
  juce::juce_audio_utils
  juce::juce_dsp
)
