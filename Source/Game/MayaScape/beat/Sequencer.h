#pragma once

#ifndef MM_SEQUENCER_H
#define MM_SEQUENCER_H

#include "Beat.h"
#include "Sampler.h"
#include <Urho3D/Container/Str.h>
#include <Urho3D/Container/Vector.h>

using namespace Urho3D;
class Sequencer {

protected:
    String id_;
    Vector<Beat*> sequence_;
    Sampler sampler_;

    int size_; // 8 beats

    // Current state
    int beat_; // Current beat
    float currTime_; // Current time
    float beatTime_; // Current beat time
    float barTime_; // Current bar time
    int bar_; // Current bar

    int bpm_; // Beats per minute
    int beatsPerBar_; // Beats per bar
    float beatTimeStep_; // Calculated beat time step

public:

    Sequencer();
    ~Sequencer();
    Vector<Beat*> GetSequence();
    Sampler &GetSampler();
    const String &GetId() const;
    void Reset();
    void Play(float timeStep);
    int GetSize() const;
    int GetBeat() const;
    float GetTime() const;
    int GetBpm() const;
    int GetBeatsPerBar() const;
    float GetBeatTimeStep() const;
    void SetId(const String &id);
    float GetBeatTime() const;
};


#endif //MM_SEQUENCER_H
