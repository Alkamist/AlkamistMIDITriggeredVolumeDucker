#include "PluginEditor.h"
#include "FloatParameter.h"
#include "PluginProcessor.h"

//==============================================================================
AlkamistSidechainCompressorAudioProcessor::AlkamistSidechainCompressorAudioProcessor()
{
    double sampleRate = getSampleRate();
    int blockSize = getBlockSize();

    addParameter (holdLevel  = new FloatParameter (1.0f, -60.0f, 0.0f, "Hold Level", "dB", sampleRate, blockSize));
    addParameter (velocitySensitivity  = new FloatParameter (100.0f, 0.0f, 100.0f, "Velocity Sensitivity", "%", sampleRate, blockSize));
    addParameter (attackTime  = new FloatParameter (0.0f, 0.1f, 200.0f, "Attack Time", "ms", sampleRate, blockSize));
    addParameter (holdTime  = new FloatParameter (0.0f, 0.1f, 200.0f, "Hold Time", "ms", sampleRate, blockSize)); 
    addParameter (releaseTime  = new FloatParameter (0.0f, 0.1f, 500.0f, "Release Time", "ms", sampleRate, blockSize));

    reset (sampleRate, blockSize);
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
void AlkamistSidechainCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    reset (sampleRate, samplesPerBlock);
}

void AlkamistSidechainCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void AlkamistSidechainCompressorAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    bufferParameters();
    sendParameterBuffers();

    mEnvelopeManager.processBlock (buffer, midiMessages);

    clearParameterChanges();

    // This clears any unused channels because they may contain garbage.
    for (int index = getNumInputChannels(); index < getNumOutputChannels(); ++index)
        buffer.clear (index, 0, buffer.getNumSamples());
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
    xmlPointer->addTextElement (String (holdLevel->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("AttackTime");
    xmlPointer->addTextElement (String (attackTime->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("HoldTime");
    xmlPointer->addTextElement (String (holdTime->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("ReleaseTime");
    xmlPointer->addTextElement (String (releaseTime->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("VelocitySensitivity");
    xmlPointer->addTextElement (String (velocitySensitivity->getUnNormalizedUnSmoothedValue()));

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
                holdLevel->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("AttackTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                attackTime->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("HoldTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                holdTime->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("ReleaseTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                releaseTime->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("VelocitySensitivity"))
            {
                String text = xmlChildPointer->getAllSubText();
                velocitySensitivity->setNormalizedValue (text.getFloatValue());
            }
        }
    }
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessor::bufferParameters()
{
    holdLevel->bufferParameter();
    velocitySensitivity->bufferParameter();
    attackTime->bufferParameter();
    holdTime->bufferParameter();
    releaseTime->bufferParameter();
}

void AlkamistSidechainCompressorAudioProcessor::sendParameterBuffers()
{
    if (holdLevel->parameterChangedThisBlock()
        || holdLevel->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setHoldLevel (holdLevel->getUnNormalizedSmoothedBuffer());
    }

    if (velocitySensitivity->parameterChangedThisBlock()
        || velocitySensitivity->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setVelocitySensitivity (velocitySensitivity->getUnNormalizedSmoothedBuffer());
    }

    if (attackTime->parameterChangedThisBlock()
        || attackTime->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setAttackTime (attackTime->getUnNormalizedSmoothedBuffer());
    }

    if (holdTime->parameterChangedThisBlock()
        || holdTime->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setHoldTime (holdTime->getUnNormalizedSmoothedBuffer());
    }

    if (releaseTime->parameterChangedThisBlock()
        || releaseTime->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setReleaseTime (releaseTime->getUnNormalizedSmoothedBuffer());
    }
}

void AlkamistSidechainCompressorAudioProcessor::clearParameterChanges()
{
    holdLevel->clearParameterChange();
    velocitySensitivity->clearParameterChange();
    attackTime->clearParameterChange();
    holdTime->clearParameterChange();
    releaseTime->clearParameterChange();
}

void AlkamistSidechainCompressorAudioProcessor::reset (double inputSampleRate, int inputBlockSize)
{
    mEnvelopeManager.reset (inputSampleRate, inputBlockSize);

    // Parameters
    holdLevel->reset (inputSampleRate, inputBlockSize);
    velocitySensitivity->reset (inputSampleRate, inputBlockSize);
    attackTime->reset (inputSampleRate, inputBlockSize);
    holdTime->reset (inputSampleRate, inputBlockSize);
    releaseTime->reset (inputSampleRate, inputBlockSize);

    holdLevel->signalForParameterChange();
    velocitySensitivity->signalForParameterChange();
    attackTime->signalForParameterChange();
    holdTime->signalForParameterChange();
    releaseTime->signalForParameterChange();
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlkamistSidechainCompressorAudioProcessor();
}





