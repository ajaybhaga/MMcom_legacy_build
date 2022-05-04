#pragma once

#ifndef MM_SEQUENCER_H
#define MM_SEQUENCER_H

#include "Beat.h"
#include <Urho3D/Container/Str.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;
class Sequencer : public LogicComponent {

    URHO3D_OBJECT(Sequencer, LogicComponent);
public:

protected:
    String id_;
    HashMap<String,Vector<Beat*>> sequenceByBeat_;
    HashMap<String,Beat*> sequenceByTime_;
    SharedPtr<Sampler> sampler_;
    int length_; // 16 beats
    SharedPtr<SoundSource3D> playSource_;


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

    Sequencer(Context* context);
    ~Sequencer();
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    /// Handle startup. Called by LogicComponent base class.
    void Start();
    /// Handle physics world update. Called by LogicComponent base class.
    void FixedUpdate(float timeStep);


    Vector<Beat*> GetSequence();
    Sampler *GetSampler();
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
    void SetPlaySource(SoundSource3D* playSource);

};


#endif //MM_SEQUENCER_H
