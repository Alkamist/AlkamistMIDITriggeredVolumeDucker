/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.1.0

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
    holdLevelSlider->setRange (-30, 0, 0.01);
    holdLevelSlider->setSliderStyle (Slider::LinearVertical);
    holdLevelSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    holdLevelSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    holdLevelSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    holdLevelSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    holdLevelSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    holdLevelSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    holdLevelSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    holdLevelSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    holdLevelSlider->addListener (this);

    addAndMakeVisible (attackTimeSlider = new Slider ("Attack Time Slider"));
    attackTimeSlider->setRange (0.1, 200, 0.1);
    attackTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTimeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    attackTimeSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    attackTimeSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    attackTimeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    attackTimeSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    attackTimeSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    attackTimeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    attackTimeSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    attackTimeSlider->addListener (this);

    addAndMakeVisible (releaseTimeSlider = new Slider ("Release Time Slider"));
    releaseTimeSlider->setRange (0.1, 200, 0.1);
    releaseTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTimeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    releaseTimeSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    releaseTimeSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    releaseTimeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    releaseTimeSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    releaseTimeSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    releaseTimeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    releaseTimeSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    releaseTimeSlider->addListener (this);

    addAndMakeVisible (holdLevelLabel = new Label ("Hold Level Label",
                                                   TRANS("Gain\n"
                                                   "Reduction \n"
                                                   "(dB)")));
    holdLevelLabel->setFont (Font (15.00f, Font::plain));
    holdLevelLabel->setJustificationType (Justification::centred);
    holdLevelLabel->setEditable (false, false, false);
    holdLevelLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    holdLevelLabel->setColour (TextEditor::textColourId, Colours::black);
    holdLevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackTimeLabel = new Label ("Attack Time Label",
                                                    TRANS("Attack\n"
                                                    "Time \n"
                                                    "(ms)")));
    attackTimeLabel->setFont (Font (15.00f, Font::plain));
    attackTimeLabel->setJustificationType (Justification::centred);
    attackTimeLabel->setEditable (false, false, false);
    attackTimeLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    attackTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    attackTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseTimeLabel = new Label ("Release Time Label",
                                                     TRANS("Release \n"
                                                     "Time \n"
                                                     "(ms)")));
    releaseTimeLabel->setFont (Font (15.00f, Font::plain));
    releaseTimeLabel->setJustificationType (Justification::centred);
    releaseTimeLabel->setEditable (false, false, false);
    releaseTimeLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    releaseTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    setAllSliderRanges();
    //[/UserPreSize]

    setSize (184, 296);


    //[Constructor] You can add your own custom stuff here..

    holdLevelSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    holdLevelSlider->setDoubleClickReturnValue(true, 0.0);

    attackTimeSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    attackTimeSlider->setDoubleClickReturnValue(true, 0.1);

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
    releaseTimeSlider = nullptr;
    holdLevelLabel = nullptr;
    attackTimeLabel = nullptr;
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

    holdLevelSlider->setBounds (8, 56, 80, 240);
    attackTimeSlider->setBounds (96, 56, 80, 96);
    releaseTimeSlider->setBounds (96, 200, 80, 96);
    holdLevelLabel->setBounds (0, 0, 96, 48);
    attackTimeLabel->setBounds (96, 0, 80, 48);
    releaseTimeLabel->setBounds (96, 144, 80, 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainEditorWindow::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    setNormalizedValueFromSlider (sliderThatWasMoved);
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
    setSliderRange (releaseTimeSlider);
}

void MainEditorWindow::setNormalizedValueFromSlider(Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        parameter->setNormalizedValue ((float) slider->getValue());
    }
}

void MainEditorWindow::updateSliderValue(Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        float unNormalizedParameterValue = parameter->getUnNormalizedUnSmoothedValue();

        slider->setValue (unNormalizedParameterValue);
    }
}

void MainEditorWindow::updateAllSliderValues()
{
    updateSliderValue (holdLevelSlider);
    updateSliderValue (attackTimeSlider);
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
                 fixedSize="1" initialWidth="184" initialHeight="296">
  <BACKGROUND backgroundColour="ff323232"/>
  <SLIDER name="Hold Level Slider" id="840f7ca9f9570c56" memberName="holdLevelSlider"
          virtualName="" explicitFocusOrder="0" pos="8 56 80 240" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="-30" max="0" int="0.01" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Attack Time Slider" id="21744834f18397a5" memberName="attackTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="96 56 80 96" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0.10000000000000001" max="200" int="0.10000000000000001"
          style="RotaryVerticalDrag" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Release Time Slider" id="9a3aaeae16ed6240" memberName="releaseTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="96 200 80 96" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0.10000000000000001" max="200" int="0.10000000000000001"
          style="RotaryVerticalDrag" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Hold Level Label" id="5e33c499a463e95f" memberName="holdLevelLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 96 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain&#10;Reduction &#10;(dB)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Attack Time Label" id="e19faf81366d6dbe" memberName="attackTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="96 0 80 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack&#10;Time &#10;(ms)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Release Time Label" id="c8bb41d45518e62c" memberName="releaseTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="96 144 80 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Release &#10;Time &#10;(ms)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
