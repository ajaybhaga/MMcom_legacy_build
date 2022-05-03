#pragma once

#ifndef MM_SAMPLER_H
#define MM_SAMPLER_H

#include <Urho3D/Container/Str.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>

using namespace Urho3D;
class Sampler {
protected:
    String id_;
public:
    const String &GetId() const;

protected:
    Vector<Sound*> sampleQueue_;

    // Current state
    int playSampleIdx_; // Current beat
    float currTime_; // Current time
    float freqMod_; // Frequency modulator


public:

    Sampler();
    ~Sampler();
    Vector<Sound*> GetSampleQueue();
    void Reset();
    void Play(int sampleIdx);
    void Play(SoundSource3D *source, int sampleIdx);
    void Load(Sound* sample);
    void Stop();
};


#endif //MM_SAMPLER_H
