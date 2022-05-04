#pragma once

#ifndef MM_SAMPLER_H
#define MM_SAMPLER_H

#include <Urho3D/Container/Str.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;
class Sampler : Object {

    URHO3D_OBJECT(Sampler, Object);
public:

protected:
    String id_;
public:
    const String &GetId() const;

protected:
    Vector<Sound*> sampleQueue_;
    bool loaded_;

    // Current state
    int playSampleIdx_; // Current beat
    float currTime_; // Current time
    float freqMod_; // Frequency modulator


public:

    Sampler(Context* context);
    ~Sampler();
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    /// Handle startup. Called by LogicComponent base class.
    void Start();
    /// Handle physics world update. Called by LogicComponent base class.
    void FixedUpdate(float timeStep);

    Vector<Sound*> GetSampleQueue();
    void Reset();
    void Play(SoundSource3D *source, int sampleIdx);
    void Load(Sound* sample);
    void Stop();
    bool Loaded();
};


#endif //MM_SAMPLER_H
