#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AlkamistSidechainCompressorAudioProcessor;
class MainEditorWindow;

class AlkamistSidechainCompressorAudioProcessorEditor  : public AudioProcessorEditor
{
public:

    AlkamistSidechainCompressorAudioProcessorEditor (AlkamistSidechainCompressorAudioProcessor& owner);
    ~AlkamistSidechainCompressorAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:

    AlkamistSidechainCompressorAudioProcessor& mParentProcessor;

    ScopedPointer<MainEditorWindow> mMainEditorWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlkamistSidechainCompressorAudioProcessorEditor)

};


#endif  // PLUGINEDITOR_H_INCLUDED
