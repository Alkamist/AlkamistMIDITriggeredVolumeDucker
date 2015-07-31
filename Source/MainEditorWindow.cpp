/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
#include "FloatParameter.h"
//[/Headers]

#include "MainEditorWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainEditorWindow::MainEditorWindow (AlkamistSidechainCompressorAudioProcessor& inputProcessor)
    : mParentProcessor (&inputProcessor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (holdLevelSlider = new Slider ("Hold Level Slider"));
    holdLevelSlider->setRange (-60, 0, 0.01);
    holdLevelSlider->setSliderStyle (Slider::LinearVertical);
    holdLevelSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    holdLevelSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    holdLevelSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    holdLevelSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    holdLevelSlider->addListener (this);

    addAndMakeVisible (attackTimeSlider = new Slider ("Attack Time Slider"));
    attackTimeSlider->setRange (0.1, 200, 0.1);
    attackTimeSlider->setSliderStyle (Slider::LinearVertical);
    attackTimeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    attackTimeSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    attackTimeSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    attackTimeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    attackTimeSlider->addListener (this);

    addAndMakeVisible (holdTimeSlider = new Slider ("Hold Time Slider"));
    holdTimeSlider->setRange (0.1, 200, 0.1);
    holdTimeSlider->setSliderStyle (Slider::LinearVertical);
    holdTimeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    holdTimeSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    holdTimeSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    holdTimeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    holdTimeSlider->addListener (this);

    addAndMakeVisible (releaseTimeSlider = new Slider ("Release Time Slider"));
    releaseTimeSlider->setRange (0.1, 200, 0.1);
    releaseTimeSlider->setSliderStyle (Slider::LinearVertical);
    releaseTimeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    releaseTimeSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    releaseTimeSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    releaseTimeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    releaseTimeSlider->addListener (this);

    addAndMakeVisible (holdLevelLabel = new Label ("Hold Level Label",
                                                   TRANS("Hold\n"
                                                   "Level (dB)")));
    holdLevelLabel->setFont (Font (15.00f, Font::plain));
    holdLevelLabel->setJustificationType (Justification::centred);
    holdLevelLabel->setEditable (false, false, false);
    holdLevelLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    holdLevelLabel->setColour (TextEditor::textColourId, Colours::black);
    holdLevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackTimeLabel = new Label ("Attack Time Label",
                                                    TRANS("Attack\n"
                                                    "Time (ms)")));
    attackTimeLabel->setFont (Font (15.00f, Font::plain));
    attackTimeLabel->setJustificationType (Justification::centred);
    attackTimeLabel->setEditable (false, false, false);
    attackTimeLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    attackTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    attackTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (holdTimeLabel = new Label ("Hold Time Label",
                                                  TRANS("Hold \n"
                                                  "Time (ms)")));
    holdTimeLabel->setFont (Font (15.00f, Font::plain));
    holdTimeLabel->setJustificationType (Justification::centred);
    holdTimeLabel->setEditable (false, false, false);
    holdTimeLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    holdTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    holdTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseTimeLabel = new Label ("Release Time Label",
                                                     TRANS("Release \n"
                                                     "Time (ms)")));
    releaseTimeLabel->setFont (Font (15.00f, Font::plain));
    releaseTimeLabel->setJustificationType (Justification::centred);
    releaseTimeLabel->setEditable (false, false, false);
    releaseTimeLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    releaseTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    setAllSliderRanges();
    //[/UserPreSize]

    setSize (400, 250);


    //[Constructor] You can add your own custom stuff here..

    holdLevelSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    holdLevelSlider->setDoubleClickReturnValue(true, 0.0);

    attackTimeSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    attackTimeSlider->setDoubleClickReturnValue(true, 0.1);

    holdTimeSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    holdTimeSlider->setDoubleClickReturnValue(true, 0.1);

    releaseTimeSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    releaseTimeSlider->setDoubleClickReturnValue(true, 0.1);

    updateAllSliderValues();

    startTimerHz(60);

    //[/Constructor]
}

MainEditorWindow::~MainEditorWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    holdLevelSlider = nullptr;
    attackTimeSlider = nullptr;
    holdTimeSlider = nullptr;
    releaseTimeSlider = nullptr;
    holdLevelLabel = nullptr;
    attackTimeLabel = nullptr;
    holdTimeLabel = nullptr;
    releaseTimeLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainEditorWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323232));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainEditorWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    holdLevelSlider->setBounds (0, 40, 104, 208);
    attackTimeSlider->setBounds (128, 40, 88, 208);
    holdTimeSlider->setBounds (216, 40, 88, 208);
    releaseTimeSlider->setBounds (304, 40, 88, 208);
    holdLevelLabel->setBounds (0, 0, 104, 32);
    attackTimeLabel->setBounds (128, 0, 88, 32);
    holdTimeLabel->setBounds (216, 0, 88, 32);
    releaseTimeLabel->setBounds (304, 0, 88, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainEditorWindow::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    setNormalizedValueFromSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == holdLevelSlider)
    {
        //[UserSliderCode_holdLevelSlider] -- add your slider handling code here..
        //[/UserSliderCode_holdLevelSlider]
    }
    else if (sliderThatWasMoved == attackTimeSlider)
    {
        //[UserSliderCode_attackTimeSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackTimeSlider]
    }
    else if (sliderThatWasMoved == holdTimeSlider)
    {
        //[UserSliderCode_holdTimeSlider] -- add your slider handling code here..
        //[/UserSliderCode_holdTimeSlider]
    }
    else if (sliderThatWasMoved == releaseTimeSlider)
    {
        //[UserSliderCode_releaseTimeSlider] -- add your slider handling code here..
        //[/UserSliderCode_releaseTimeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainEditorWindow::setSliderRange (Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        double dittoInterval = slider->getInterval();

        slider->setRange (parameter->getMinimum(), parameter->getMaximum(), dittoInterval);
    }
}

void MainEditorWindow::setAllSliderRanges()
{
    setSliderRange (holdLevelSlider);
    setSliderRange (attackTimeSlider);
    setSliderRange (holdTimeSlider);
    setSliderRange (releaseTimeSlider);
}

void MainEditorWindow::setNormalizedValueFromSlider(Slider* slider)
{
    FloatParameter* parameter = getParameterFromSlider(slider);

    parameter->setNormalizedValue (slider->getValue());
}

void MainEditorWindow::updateSliderValue(Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        float unNormalizedParameterValue = parameter->getUnNormalizedValue();

        slider->setValue (unNormalizedParameterValue);
    }
}

void MainEditorWindow::updateAllSliderValues()
{
    updateSliderValue (holdLevelSlider);
    updateSliderValue (attackTimeSlider);
    updateSliderValue (holdTimeSlider);
    updateSliderValue (releaseTimeSlider);
}

void MainEditorWindow::timerCallback()
{
    updateAllSliderValues();
}

void MainEditorWindow::sliderDragStarted (Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider (slider))
    {
        parameter->beginChangeGesture();
    }
}

void MainEditorWindow::sliderDragEnded (Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider (slider))
    {
        parameter->endChangeGesture();
    }
}

FloatParameter* MainEditorWindow::getParameterFromSlider (const Slider* slider) const
{
    if (slider == holdLevelSlider)
        return mParentProcessor->holdLevel;

    if (slider == attackTimeSlider)
        return mParentProcessor->attackTime;

    if (slider == holdTimeSlider)
        return mParentProcessor->holdTime;

    if (slider == releaseTimeSlider)
        return mParentProcessor->releaseTime;

    return nullptr;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainEditorWindow" componentName=""
                 parentClasses="public Component, public Timer" constructorParams="AlkamistSidechainCompressorAudioProcessor&amp; inputProcessor"
                 variableInitialisers="mParentProcessor (&amp;inputProcessor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="250">
  <BACKGROUND backgroundColour="ff323232"/>
  <SLIDER name="Hold Level Slider" id="840f7ca9f9570c56" memberName="holdLevelSlider"
          virtualName="" explicitFocusOrder="0" pos="0 40 104 208" thumbcol="ff909090"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" min="-60" max="0"
          int="0.01" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Attack Time Slider" id="21744834f18397a5" memberName="attackTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="128 40 88 208" thumbcol="ff909090"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" min="0.10000000000000001"
          max="200" int="0.10000000000000001" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Hold Time Slider" id="88e6d901167994f4" memberName="holdTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="216 40 88 208" thumbcol="ff909090"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" min="0.10000000000000001"
          max="200" int="0.10000000000000001" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Release Time Slider" id="9a3aaeae16ed6240" memberName="releaseTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="304 40 88 208" thumbcol="ff909090"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" min="0.10000000000000001"
          max="200" int="0.10000000000000001" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Hold Level Label" id="5e33c499a463e95f" memberName="holdLevelLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 104 32" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Hold&#10;Level (dB)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Attack Time Label" id="e19faf81366d6dbe" memberName="attackTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="128 0 88 32" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack&#10;Time (ms)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Hold Time Label" id="b454a4d7a5c910a1" memberName="holdTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="216 0 88 32" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Hold &#10;Time (ms)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Release Time Label" id="c8bb41d45518e62c" memberName="releaseTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="304 0 88 32" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Release &#10;Time (ms)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
