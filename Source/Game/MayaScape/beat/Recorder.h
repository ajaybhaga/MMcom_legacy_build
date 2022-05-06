#pragma once

#ifndef MM_RECORDER_H
#define MM_RECORDER_H

#include <Urho3D/Container/Str.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Database/Database.h>
#include "Beat.h"

using namespace Urho3D;

/*
  __   __
 /  \/  \
/__/ /__/ AYA SCAPE

 BEAT: RECORDER

Written by Ajay Bhaga 2022
*/
class Recorder : public Object {
URHO3D_OBJECT(Recorder, Object);
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
    SharedPtr<SoundSource3D> playSource_;

    SharedPtr<Database> db_;

public:

    Recorder(Context* context);
    ~Recorder();
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    Vector<Sound*> GetSampleQueue();
    void Reset();
    void Capture(Beat* channel1_, Beat* channel2_, Beat* channel3_, float currTime_, float beatTime_, float barTime_);
    void Play(int sampleIdx);
    void Load(Sound* sample);
    void Stop();
    bool Loaded();
    void SetPlaySource(SoundSource3D* playSource);

};


#endif //MM_RECORDER_H