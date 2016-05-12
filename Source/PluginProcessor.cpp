#include "PluginEditor.h"
#include "FloatParameter.h"
#include "PluginProcessor.h"

//==============================================================================
AlkamistSidechainCompressorAudioProcessor::AlkamistSidechainCompressorAudioProcessor()
{
    double sampleRate = getSampleRate();
    int blockSize = getBlockSize();

    addParameter (holdLevel  = new FloatParameter (1.0f, -30.0f, 0.0f, "Gain Reduction", "dB", sampleRate, blockSize));
    addParameter (attackTime  = new FloatParameter (0.0f, 0.1f, 200.0f, "Attack Time", "ms", sampleRate, blockSize)); 
    addParameter (releaseTime  = new FloatParameter (0.0f, 0.1f, 500.0f, "Release Time", "ms", sampleRate, blockSize));
    addParameter (attackBottomWeight  = new FloatParameter (0.0f, 0.01f, 0.99f, "Attack Bottom Weight", "", sampleRate, blockSize));
    addParameter (attackTopWeight  = new FloatParameter (1.0f, 0.01f, 0.99f, "Attack Top Weight", "", sampleRate, blockSize));
    addParameter (releaseBottomWeight  = new FloatParameter (0.0f, 0.01f, 0.99f, "Release Bottom Weight", "", sampleRate, blockSize));
    addParameter (releaseTopWeight  = new FloatParameter (1.0f, 0.01f, 0.99f, "Release Top Weight", "", sampleRate, blockSize));

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

    xmlPointer = xmlRoot.createNewChildElement ("ReleaseTime");
    xmlPointer->addTextElement (String (releaseTime->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("AttackBottomWeight");
    xmlPointer->addTextElement (String (attackBottomWeight->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("AttackTopWeight");
    xmlPointer->addTextElement (String (attackTopWeight->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("ReleaseBottomWeight");
    xmlPointer->addTextElement (String (releaseBottomWeight->getUnNormalizedUnSmoothedValue()));

    xmlPointer = xmlRoot.createNewChildElement ("ReleaseTopWeight");
    xmlPointer->addTextElement (String (releaseTopWeight->getUnNormalizedUnSmoothedValue()));

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
            if(xmlChildPointer->hasTagName("ReleaseTime"))
            {
                String text = xmlChildPointer->getAllSubText();
                releaseTime->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("AttackBottomWeight"))
            {
                String text = xmlChildPointer->getAllSubText();
                attackBottomWeight->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("AttackTopWeight"))
            {
                String text = xmlChildPointer->getAllSubText();
                attackTopWeight->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("ReleaseBottomWeight"))
            {
                String text = xmlChildPointer->getAllSubText();
                releaseBottomWeight->setNormalizedValue (text.getFloatValue());
            }
            if(xmlChildPointer->hasTagName("ReleaseTopWeight"))
            {
                String text = xmlChildPointer->getAllSubText();
                releaseTopWeight->setNormalizedValue (text.getFloatValue());
            }
        }
    }
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessor::bufferParameters()
{
    holdLevel->bufferParameter();
    attackTime->bufferParameter();
    releaseTime->bufferParameter();
    attackBottomWeight->bufferParameter();
    attackTopWeight->bufferParameter();
    releaseBottomWeight->bufferParameter();
    releaseTopWeight->bufferParameter();
}

void AlkamistSidechainCompressorAudioProcessor::sendParameterBuffers()
{
    if (holdLevel->parameterChangedThisBlock()
        || holdLevel->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setHoldLevel (holdLevel->getUnNormalizedSmoothedBuffer());
    }

    if (attackTime->parameterChangedThisBlock()
        || attackTime->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setAttackTime (attackTime->getUnNormalizedSmoothedBuffer());
    }

    if (releaseTime->parameterChangedThisBlock()
        || releaseTime->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setReleaseTime (releaseTime->getUnNormalizedSmoothedBuffer());
    }

    if (attackBottomWeight->parameterChangedThisBlock()
        || attackBottomWeight->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setAttackBottomWeight (attackBottomWeight->getUnNormalizedSmoothedBuffer());
    }

    if (attackTopWeight->parameterChangedThisBlock()
        || attackTopWeight->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setAttackTopWeight (attackTopWeight->getUnNormalizedSmoothedBuffer());
    }

    if (releaseBottomWeight->parameterChangedThisBlock()
        || releaseBottomWeight->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setReleaseBottomWeight (releaseBottomWeight->getUnNormalizedSmoothedBuffer());
    }

    if (releaseTopWeight->parameterChangedThisBlock()
        || releaseTopWeight->parameterNeedsToSendFlatBuffer())
    {
        mEnvelopeManager.setReleaseTopWeight (releaseTopWeight->getUnNormalizedSmoothedBuffer());
    }
}

void AlkamistSidechainCompressorAudioProcessor::clearParameterChanges()
{
    holdLevel->clearParameterChange();
    attackTime->clearParameterChange();
    releaseTime->clearParameterChange();
    attackBottomWeight->clearParameterChange();
    attackTopWeight->clearParameterChange();
    releaseBottomWeight->clearParameterChange();
    releaseTopWeight->clearParameterChange();
}

void AlkamistSidechainCompressorAudioProcessor::reset (double inputSampleRate, int inputBlockSize)
{
    mEnvelopeManager.reset (inputSampleRate, inputBlockSize);

    // Parameters
    holdLevel->reset (inputSampleRate, inputBlockSize);
    attackTime->reset (inputSampleRate, inputBlockSize);
    releaseTime->reset (inputSampleRate, inputBlockSize);
    attackBottomWeight->reset (inputSampleRate, inputBlockSize);
    attackTopWeight->reset (inputSampleRate, inputBlockSize);
    releaseBottomWeight->reset (inputSampleRate, inputBlockSize);
    releaseTopWeight->reset (inputSampleRate, inputBlockSize);

    holdLevel->signalForParameterChange();
    attackTime->signalForParameterChange();
    releaseTime->signalForParameterChange();
    attackBottomWeight->signalForParameterChange();
    attackTopWeight->signalForParameterChange();
    releaseBottomWeight->signalForParameterChange();
    releaseTopWeight->signalForParameterChange();
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlkamistSidechainCompressorAudioProcessor();
}





