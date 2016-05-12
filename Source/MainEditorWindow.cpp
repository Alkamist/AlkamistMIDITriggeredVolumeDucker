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

    addAndMakeVisible (releaseBottomWeightSlider = new Slider ("Release Bottom Weight Slider"));
    releaseBottomWeightSlider->setRange (0.01, 0.99, 0.01);
    releaseBottomWeightSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseBottomWeightSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    releaseBottomWeightSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    releaseBottomWeightSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    releaseBottomWeightSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    releaseBottomWeightSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    releaseBottomWeightSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    releaseBottomWeightSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    releaseBottomWeightSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    releaseBottomWeightSlider->addListener (this);

    addAndMakeVisible (releaseBottomWeightLabel = new Label ("Release Bottom Weight Label",
                                                             TRANS("Release Bottom Weight")));
    releaseBottomWeightLabel->setFont (Font (15.00f, Font::plain));
    releaseBottomWeightLabel->setJustificationType (Justification::centred);
    releaseBottomWeightLabel->setEditable (false, false, false);
    releaseBottomWeightLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    releaseBottomWeightLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseBottomWeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseTopWeightSlider = new Slider ("Release Top Weight Slider"));
    releaseTopWeightSlider->setRange (0.01, 0.99, 0.01);
    releaseTopWeightSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    releaseTopWeightSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    releaseTopWeightSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    releaseTopWeightSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    releaseTopWeightSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    releaseTopWeightSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    releaseTopWeightSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    releaseTopWeightSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    releaseTopWeightSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    releaseTopWeightSlider->addListener (this);

    addAndMakeVisible (releaseTopWeightLabel = new Label ("Release Top Weight Label",
                                                          TRANS("Release Top Weight")));
    releaseTopWeightLabel->setFont (Font (15.00f, Font::plain));
    releaseTopWeightLabel->setJustificationType (Justification::centred);
    releaseTopWeightLabel->setEditable (false, false, false);
    releaseTopWeightLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    releaseTopWeightLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseTopWeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackBottomWeightSlider = new Slider ("Attack Bottom Weight Slider"));
    attackBottomWeightSlider->setRange (0.01, 0.99, 0.01);
    attackBottomWeightSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    attackBottomWeightSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    attackBottomWeightSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    attackBottomWeightSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    attackBottomWeightSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    attackBottomWeightSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    attackBottomWeightSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    attackBottomWeightSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    attackBottomWeightSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    attackBottomWeightSlider->addListener (this);

    addAndMakeVisible (attackBottomWeightLabel = new Label ("Attack Bottom Weight Label",
                                                            TRANS("Attack Bottom Weight")));
    attackBottomWeightLabel->setFont (Font (15.00f, Font::plain));
    attackBottomWeightLabel->setJustificationType (Justification::centred);
    attackBottomWeightLabel->setEditable (false, false, false);
    attackBottomWeightLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    attackBottomWeightLabel->setColour (TextEditor::textColourId, Colours::black);
    attackBottomWeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackTopWeightSlider = new Slider ("Attack Top Weight Slider"));
    attackTopWeightSlider->setRange (0.01, 0.99, 0.01);
    attackTopWeightSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    attackTopWeightSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    attackTopWeightSlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    attackTopWeightSlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    attackTopWeightSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    attackTopWeightSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    attackTopWeightSlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    attackTopWeightSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    attackTopWeightSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    attackTopWeightSlider->addListener (this);

    addAndMakeVisible (attackTopWeightLabel = new Label ("Attack Top Weight Label",
                                                         TRANS("Attack Top Weight")));
    attackTopWeightLabel->setFont (Font (15.00f, Font::plain));
    attackTopWeightLabel->setJustificationType (Justification::centred);
    attackTopWeightLabel->setEditable (false, false, false);
    attackTopWeightLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    attackTopWeightLabel->setColour (TextEditor::textColourId, Colours::black);
    attackTopWeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    setAllSliderRanges();
    //[/UserPreSize]

    setSize (312, 296);


    //[Constructor] You can add your own custom stuff here..

    holdLevelSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    holdLevelSlider->setDoubleClickReturnValue(true, 0.0);

    attackTimeSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    attackTimeSlider->setDoubleClickReturnValue(true, 20.0);

    releaseTimeSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    releaseTimeSlider->setDoubleClickReturnValue(true, 240.0);

    attackBottomWeightSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    attackBottomWeightSlider->setDoubleClickReturnValue(true, 0.99);

    attackTopWeightSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    attackTopWeightSlider->setDoubleClickReturnValue(true, 0.01);

    releaseBottomWeightSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    releaseBottomWeightSlider->setDoubleClickReturnValue(true, 0.01);

    releaseTopWeightSlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    releaseTopWeightSlider->setDoubleClickReturnValue(true, 0.99);

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
    releaseBottomWeightSlider = nullptr;
    releaseBottomWeightLabel = nullptr;
    releaseTopWeightSlider = nullptr;
    releaseTopWeightLabel = nullptr;
    attackBottomWeightSlider = nullptr;
    attackBottomWeightLabel = nullptr;
    attackTopWeightSlider = nullptr;
    attackTopWeightLabel = nullptr;


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
    releaseBottomWeightSlider->setBounds (248, 200, 56, 96);
    releaseBottomWeightLabel->setBounds (248, 144, 56, 48);
    releaseTopWeightSlider->setBounds (184, 200, 56, 96);
    releaseTopWeightLabel->setBounds (184, 144, 56, 48);
    attackBottomWeightSlider->setBounds (249, 57, 56, 96);
    attackBottomWeightLabel->setBounds (249, 1, 56, 48);
    attackTopWeightSlider->setBounds (185, 57, 56, 96);
    attackTopWeightLabel->setBounds (185, 1, 56, 48);
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
    else if (sliderThatWasMoved == releaseBottomWeightSlider)
    {
        //[UserSliderCode_releaseBottomWeightSlider] -- add your slider handling code here..
        //[/UserSliderCode_releaseBottomWeightSlider]
    }
    else if (sliderThatWasMoved == releaseTopWeightSlider)
    {
        //[UserSliderCode_releaseTopWeightSlider] -- add your slider handling code here..
        //[/UserSliderCode_releaseTopWeightSlider]
    }
    else if (sliderThatWasMoved == attackBottomWeightSlider)
    {
        //[UserSliderCode_attackBottomWeightSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackBottomWeightSlider]
    }
    else if (sliderThatWasMoved == attackTopWeightSlider)
    {
        //[UserSliderCode_attackTopWeightSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackTopWeightSlider]
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
    setSliderRange (attackBottomWeightSlider);
    setSliderRange (attackTopWeightSlider);
    setSliderRange (releaseBottomWeightSlider);
    setSliderRange (releaseTopWeightSlider);
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
    updateSliderValue (attackBottomWeightSlider);
    updateSliderValue (attackTopWeightSlider);
    updateSliderValue (releaseBottomWeightSlider);
    updateSliderValue (releaseTopWeightSlider);
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

    if (slider == attackBottomWeightSlider)
        return mParentProcessor->attackBottomWeight;

    if (slider == attackTopWeightSlider)
        return mParentProcessor->attackTopWeight;

    if (slider == releaseBottomWeightSlider)
        return mParentProcessor->releaseBottomWeight;

    if (slider == releaseTopWeightSlider)
        return mParentProcessor->releaseTopWeight;

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
                 fixedSize="1" initialWidth="312" initialHeight="296">
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
  <SLIDER name="Release Bottom Weight Slider" id="80fa0237bc75e85e" memberName="releaseBottomWeightSlider"
          virtualName="" explicitFocusOrder="0" pos="248 200 56 96" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0.01" max="0.98999999999999999" int="0.01" style="RotaryVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Release Bottom Weight Label" id="304cf69692c9679c" memberName="releaseBottomWeightLabel"
         virtualName="" explicitFocusOrder="0" pos="248 144 56 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Release Bottom Weight"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Release Top Weight Slider" id="f95f00b752972d9e" memberName="releaseTopWeightSlider"
          virtualName="" explicitFocusOrder="0" pos="184 200 56 96" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0.01" max="0.98999999999999999" int="0.01" style="RotaryVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Release Top Weight Label" id="c7f5edd4d2cfab6f" memberName="releaseTopWeightLabel"
         virtualName="" explicitFocusOrder="0" pos="184 144 56 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Release Top Weight"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Attack Bottom Weight Slider" id="fb8f8c63bf1a7031" memberName="attackBottomWeightSlider"
          virtualName="" explicitFocusOrder="0" pos="249 57 56 96" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0.01" max="0.98999999999999999" int="0.01" style="RotaryVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Attack Bottom Weight Label" id="6713bc54cd84c4e3" memberName="attackBottomWeightLabel"
         virtualName="" explicitFocusOrder="0" pos="249 1 56 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack Bottom Weight"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Attack Top Weight Slider" id="f9dc3482a1966a27" memberName="attackTopWeightSlider"
          virtualName="" explicitFocusOrder="0" pos="185 57 56 96" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0.01" max="0.98999999999999999" int="0.01" style="RotaryVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Attack Top Weight Label" id="86eb2891b925f48" memberName="attackTopWeightLabel"
         virtualName="" explicitFocusOrder="0" pos="185 1 56 48" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack Top Weight"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
