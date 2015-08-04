#include "PluginEditor.h"
#include "FloatParameter.h"
#include "EnvelopeVoiceManager.h"

#include "PluginProcessor.h"

//==============================================================================
AlkamistSidechainCompressorAudioProcessor::AlkamistSidechainCompressorAudioProcessor()
{
    double sampleRate = getSampleRate();
    int samplesPerBlock = getBlockSize();

    addParameter (holdLevel  = new FloatParameter (this, 1.0f, -60.0f, 0.0f, "Hold Level", sampleRate, samplesPerBlock));
    addParameter (velocitySensitivity  = new FloatParameter (this, 100.0f, 0.0f, 100.0f, "Velocity Sensitivity", sampleRate, samplesPerBlock));
    addParameter (attackTime  = new FloatParameter (this, 0.0f, 0.1f, 200.0f, "Attack Time", sampleRate, samplesPerBlock));
    addParameter (holdTime  = new FloatParameter (this, 0.0f, 0.1f, 200.0f, "Hold Time", sampleRate, samplesPerBlock)); 
    addParameter (releaseTime  = new FloatParameter (this, 0.0f, 0.1f, 200.0f, "Release Time", sampleRate, samplesPerBlock));

    mEnvelopeVoiceManager = new EnvelopeVoiceManager();

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
void AlkamistSidechainCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
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
    MidiBuffer::Iterator MIDIMessagesIterator (midiMessages);
    MidiMessage currentMidiMessage;
    int midiMessageSamplePosition;

    float* leftChannel = buffer.getWritePointer (0);
    float* rightChannel = buffer.getWritePointer (1);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        MIDIMessagesIterator.setNextSamplePosition (sample);

        // Is there at least one more MIDI message in the buffer?
        if (MIDIMessagesIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition))
        {
            // Is the message we got a note on and is it in the
            // right place?
            if (currentMidiMessage.isNoteOn() 
                && midiMessageSamplePosition == sample)
            {
                mEnvelopeVoiceManager->startEnvelopeUsingAvailableVoice (currentMidiMessage);
            }
        }
 
        // Parameters
        holdLevel->processPerSample();
        attackTime->processPerSample();
        holdTime->processPerSample();
        releaseTime->processPerSample();
        velocitySensitivity->processPerSample();

        mEnvelopeVoiceManager->processPerSample();

        //float temporaryGain = mEnvelopeVoiceManager->getOutput();
        float temporaryGain = holdLevel->getValue();

        leftChannel[sample] = temporaryGain;
        rightChannel[sample] = temporaryGain;
    }
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
}

void AlkamistSidechainCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    /*mEnvelopeVoiceManager->setHoldLevel (holdLevel->getUnNormalizedValue());
    mEnvelopeVoiceManager->setVelocitySensitivity (velocitySensitivity->getUnNormalizedValue());
    mEnvelopeVoiceManager->setAttackTime (attackTime->getUnNormalizedValue());
    mEnvelopeVoiceManager->setHoldTime (holdTime->getUnNormalizedValue());
    mEnvelopeVoiceManager->setReleaseTime (releaseTime->getUnNormalizedValue());*/
}

//==============================================================================
void AlkamistSidechainCompressorAudioProcessor::parameterChange (FloatParameter* parameterThatWasChanged)
{
    if (parameterThatWasChanged == holdLevel)
    {
        mEnvelopeVoiceManager->setHoldLevel (holdLevel->getUnNormalizedValue());
    }
    if (parameterThatWasChanged == velocitySensitivity)
    {
        mEnvelopeVoiceManager->setVelocitySensitivity (velocitySensitivity->getUnNormalizedValue());
    }
    if (parameterThatWasChanged == attackTime)
    {
        mEnvelopeVoiceManager->setAttackTime (attackTime->getUnNormalizedValue());
    }
    if (parameterThatWasChanged == holdTime)
    {
        mEnvelopeVoiceManager->setHoldTime (holdTime->getUnNormalizedValue());
    }
    if (parameterThatWasChanged == releaseTime)
    {
        mEnvelopeVoiceManager->setReleaseTime (releaseTime->getUnNormalizedValue());
    }
}

void AlkamistSidechainCompressorAudioProcessor::reset()
{
    double sampleRate = getSampleRate();
    int samplesPerBlock = getBlockSize();

    mEnvelopeVoiceManager->reset (sampleRate);

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





