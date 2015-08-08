#include "PluginEditor.h"
#include "FloatParameter.h"

#include "PluginProcessor.h"

//==============================================================================
AlkamistSidechainCompressorAudioProcessor::AlkamistSidechainCompressorAudioProcessor()
    : mParameterChangeFlag (false)
{
    double sampleRate = getSampleRate();
    int samplesPerBlock = getBlockSize();

    addParameter (holdLevel  = new FloatParameter (this, 1.0f, -60.0f, 0.0f, "Hold Level", "dB", sampleRate, samplesPerBlock));
    addParameter (velocitySensitivity  = new FloatParameter (this, 100.0f, 0.0f, 100.0f, "Velocity Sensitivity", "%", sampleRate, samplesPerBlock));
    addParameter (attackTime  = new FloatParameter (this, 0.0f, 0.1f, 200.0f, "Attack Time", "ms", sampleRate, samplesPerBlock));
    addParameter (holdTime  = new FloatParameter (this, 0.0f, 0.1f, 200.0f, "Hold Time", "ms", sampleRate, samplesPerBlock)); 
    addParameter (releaseTime  = new FloatParameter (this, 0.0f, 0.1f, 200.0f, "Release Time", "ms", sampleRate, samplesPerBlock));

    reset();
}

AlkamistSidechainCompressorAudioProcessor::~AlkamistSidechainCompressorAudioProcessor()
{
}

//==============================================================================
const String AlkamistSidechainCompressorAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String AlkamistSidechainCompressorAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool AlkamistSidechainCompressorAudioProcessor::isInputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool AlkamistSidechainCompressorAudioProcessor::isOutputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool AlkamistSidechainCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AlkamistSidechainCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AlkamistSidechainCompressorAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double AlkamistSidechainCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    reset();
}

void AlkamistSidechainCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void AlkamistSidechainCompressorAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    bool MIDIBufferIsEmpty = midiMessages.isEmpty();
    MidiBuffer::Iterator MIDIMessagesIterator (midiMessages);
    MidiMessage currentMidiMessage;
    int midiMessageSamplePosition = 0;

    if (! MIDIBufferIsEmpty)
    {
        MIDIMessagesIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition);
    }

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        if (! MIDIBufferIsEmpty)
        {
            bool alreadyHadNoteOn = false; 

            if (sample == midiMessageSamplePosition)
            {
                if (currentMidiMessage.isNoteOn()
                    && ! alreadyHadNoteOn)
                {
                    mEnvelopeVoiceManager.startNewEnvelope (currentMidiMessage);
                    alreadyHadNoteOn = true;
                }

                MIDIMessagesIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition);
            }
        }

        if (mParameterChangeFlag == true)
        {
            handleParameterChanges();
        }

        mEnvelopeVoiceManager.processPerSample();

        if (mEnvelopeVoiceManager.thereAreEnvelopesRunning())
        {
            float temporaryGain = (float) mEnvelopeVoiceManager.getOutput();

            for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
            {
                buffer.getWritePointer (channel)[sample] = temporaryGain;
            }
        }
    }

    clearParameterChanges();
    mParameterChangeFlag = false;
}

//==============================================================================
AudioProcessorEditor* AlkamistSidechainCompressorAudioProcessor::createEditor()
{
    return new AlkamistSidechainCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    // Create an outer XML element..
    XmlElement xmlRoot ("ALKAMISTSIDECHAINCOMPRESSORSETTINGS");
    XmlElement* xmlPointer;

    // Document our parameter values in XML child elements.
    xmlPointer = xmlRoot.createNewChildElement ("HoldLevel");
    xmlPointer->addTextElement (String (holdLevel->getValue()));

    xmlPointer = xmlRoot.createNewChildElement ("AttackTime");
    xmlPointer->addTextElement (String (attackTime->getValue()));

    xmlPointer = xmlRoot.createNewChildElement ("HoldTime");
    xmlPointer->addTextElement (String (holdTime->getValue()));

    xmlPointer = xmlRoot.createNewChildElement ("ReleaseTime");
    xmlPointer->addTextElement (String (releaseTime->getValue()));

    xmlPointer = xmlRoot.createNewChildElement ("VelocitySensitivity");
    xmlPointer->addTextElement (String (velocitySensitivity->getValue()));

    // Use this helper function to stuff it into the binary blob and return it.
    copyXmlToBinary (xmlRoot, destData);
}

void AlkamistSidechainCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    ScopedPointer<XmlElement> xmlPluginState (getXmlFromBinary (data, sizeInBytes));

    if (xmlPluginState != nullptr)
    {
        forEachXmlChildElement (*xmlPluginState, xmlChildPointer)
        {
            if(xmlChildPointer->hasTagName("HoldLevel"))
            {
                String text = xmlChildPointer->getAllSubText();
                holdLevel->setValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("AttackTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                attackTime->setValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("HoldTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                holdTime->setValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("ReleaseTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                releaseTime->setValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("VelocitySensitivity"))
            {
                String text = xmlChildPointer->getAllSubText();
                velocitySensitivity->setValue (text.getFloatValue());
            }
        }
    }
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessor::clearParameterChanges()
{
    holdLevel->clearParameterChangeFlag();
    attackTime->clearParameterChangeFlag();
    holdTime->clearParameterChangeFlag();
    releaseTime->clearParameterChangeFlag();
    velocitySensitivity->clearParameterChangeFlag();
}

void AlkamistSidechainCompressorAudioProcessor::handleParameterChanges()
{
    if (holdLevel->needsToChange())  
    {
        holdLevel->processPerSample();
        mEnvelopeVoiceManager.setHoldLevel (holdLevel->getUnNormalizedSmoothedValue());
    }
    if (attackTime->needsToChange())  
    {
        attackTime->processPerSample();
        mEnvelopeVoiceManager.setAttackTime (attackTime->getUnNormalizedSmoothedValue());
    }
      
    if (holdTime->needsToChange())  
    {
        holdTime->processPerSample();
        mEnvelopeVoiceManager.setHoldTime (holdTime->getUnNormalizedSmoothedValue());
    }

    if (releaseTime->needsToChange()) 
    {
        releaseTime->processPerSample();
        mEnvelopeVoiceManager.setReleaseTime (releaseTime->getUnNormalizedSmoothedValue());
    }

    if (velocitySensitivity->needsToChange())   
    {
        velocitySensitivity->processPerSample();
        mEnvelopeVoiceManager.setVelocitySensitivity (velocitySensitivity->getUnNormalizedSmoothedValue());
    }
}

void AlkamistSidechainCompressorAudioProcessor::reset()
{
    double sampleRate = getSampleRate();
    int samplesPerBlock = getBlockSize();

    mEnvelopeVoiceManager.reset (sampleRate);

    // Parameters
    holdLevel->reset (sampleRate, samplesPerBlock);
    attackTime->reset (sampleRate, samplesPerBlock);
    holdTime->reset (sampleRate, samplesPerBlock);
    releaseTime->reset (sampleRate, samplesPerBlock);
    velocitySensitivity->reset (sampleRate, samplesPerBlock);
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlkamistSidechainCompressorAudioProcessor();
}





