#pragma once

#ifndef MM_BEAT_H
#define MM_BEAT_H

#include "Sampler.h"

#include <Urho3D/Container/Str.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>

using namespace Urho3D;
class Beat {

protected:
    float beatLength_; // Beat length (1/4, 1/8, 1/16)
    int beatSampleIdx_;
    SharedPtr<Sampler> sampler_;
    WeakPtr<SoundSource3D> playSource_;

public:
    Beat(float beatLength_, Sampler* sampler_, int beatSampleIdx_, SoundSource3D* playSource_);
    ~Beat();
    void Play();
};


#endif //URHO3D_BEAT_H
