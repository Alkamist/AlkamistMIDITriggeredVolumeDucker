#ifndef SIDECHAINCOMPRESSORENVELOPE_H_INCLUDED
#define SIDECHAINCOMPRESSORENVELOPE_H_INCLUDED

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

class SidechainCompressorEnvelope
{
public:

    SidechainCompressorEnvelope();

    void reset (double inputSampleRate, int inputBlockSize);
    void processBlock (AudioSampleBuffer& inputAudioBuffer, MidiBuffer& inputMIDIBuffer);

    // Getters:

    // Setters:
    inline void setHoldLevel (const std::vector<float>& input) { mHoldLevel = input; };

private:

    double mSampleRate;
    int mBlockSize;

    // Buffered Parameters:
    std::vector<float> mHoldLevel;

};

#endif  // SIDECHAINCOMPRESSORENVELOPE_H_INCLUDED
