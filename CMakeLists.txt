cmake_minimum_required(VERSION 3.15)
project(Synth VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

set(EXTERNALS
    "${PROJECT_SOURCE_DIR}/ext")
add_subdirectory(${EXTERNALS}/JUCE)                  

set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")
set(BUILD_SHARED_LIBS OFF)

set(BUILD_DIR
    "${PROJECT_SOURCE_DIR}/build/")
set(SOURCES_DIR        
    "${PROJECT_SOURCE_DIR}/src/")
set(INCLUDES_DIR
    "${PROJECT_SOURCE_DIR}/src/")
set(SOURCES
    ${SOURCES_DIR}/SynthEditor.cpp
    ${SOURCES_DIR}/SynthAudioProcessor.cpp
    # MODULES
    ${SOURCES_DIR}/Synth/Modules/Module.cpp
    ${SOURCES_DIR}/Synth/Modules/ADSR.cpp
    ${SOURCES_DIR}/Synth/Modules/VCA.cpp
    ${SOURCES_DIR}/Synth/Modules/VCO.cpp
    ${SOURCES_DIR}/Synth/Modules/LFO.cpp
    ${SOURCES_DIR}/Synth/Modules/Mixer.cpp
    ${SOURCES_DIR}/Synth/Modules/LadderFilter.cpp
    ${SOURCES_DIR}/Synth/Modules/WaveFunctions.cpp
    # UI
    ${SOURCES_DIR}/Synth/UI/CLookAndFeel.cpp
    ${SOURCES_DIR}/Synth/UI/UI_func.cpp
    ${SOURCES_DIR}/Synth/UI/VCA_section.cpp
    ${SOURCES_DIR}/Synth/UI/ADSR_section.cpp
    ${SOURCES_DIR}/Synth/UI/VCO_section.cpp
    ${SOURCES_DIR}/Synth/UI/MIX_section.cpp
    ${SOURCES_DIR}/Synth/UI/VCF_section.cpp
    ${SOURCES_DIR}/Synth/UI/LFO_section.cpp

    ${SOURCES_DIR}/Synth/SynthVoice.cpp
    ${SOURCES_DIR}/Synth/SynthSound.cpp
)

juce_add_plugin(Synth
    # VERSION ...                               # Set this if the plugin version is different to the project version
    ICON_BIG "assets/buttonSqrGreen.png"                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    ICON_SMALL "assets/buttonSqrGreen.png"
    # COMPANY_NAME ...                          # Specify the name of the plugin's author
    IS_SYNTH TRUE                      # Is this a synth or an effect?
    NEEDS_MIDI_INPUT TRUE              # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE PolF               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "Synth")        # The name of the final executable, which can differ from the target name


juce_generate_juce_header(Synth)

# `target_sources` adds source files to a target. We pass the target that needs the sources as the
# first argument, then a visibility parameter for the sources which should normally be PRIVATE.
# Finally, we supply a list of source files that will be built into the target. This is a standard
# CMake command.

target_sources(Synth
    PRIVATE ${SOURCES})

target_include_directories(Synth
    PUBLIC ${INCLUDES}
    PUBLIC ${INCLUDES}/Synth/
    PUBLIC ${INCLUDES}/Synth/Modules)

target_compile_definitions(Synth
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

# juce_add_binary_data(AudioPluginData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

target_link_libraries(Synth
    PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

#Copying application to bin directory
#add_custom_command(TARGET Synth POST_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy
#    $<TARGET_FILE:Synth>
#    ${OUTPUT_DIR})

#install(TARGETS Synth DESTINATION ${OUTPUT_DIR})