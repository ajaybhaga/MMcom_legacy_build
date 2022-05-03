#pragma once

#ifndef MM_BEAT_H
#define MM_BEAT_H

#include "Sampler.h"


class Beat {

protected:
    float beatLength_; // Beat length (1/4, 1/8, 1/16)
    int beatSampleIdx_;
    Sampler* sampler_;
    SoundSource3D* playSource_;

public:
    Beat(float beatLength_, Sampler* sampler_, int beatSampleIdx_, SoundSource3D* playSource_);
    ~Beat();
    void Play();
};


#endif //URHO3D_BEAT_H
