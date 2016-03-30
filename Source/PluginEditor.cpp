#include "PluginProcessor.h"
#include "MainEditorWindow.h"

#include "PluginEditor.h"

//==============================================================================
AlkamistSidechainCompressorAudioProcessorEditor::AlkamistSidechainCompressorAudioProcessorEditor (AlkamistSidechainCompressorAudioProcessor& owner)
    : AudioProcessorEditor (owner),
      mParentProcessor (owner)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (184, 296);

    addAndMakeVisible (mMainEditorWindow = new MainEditorWindow (mParentProcessor));
}

AlkamistSidechainCompressorAudioProcessorEditor::~AlkamistSidechainCompressorAudioProcessorEditor()
{
    mMainEditorWindow = nullptr;
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void AlkamistSidechainCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
