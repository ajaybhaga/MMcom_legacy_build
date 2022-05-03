#include "Beat.h"

//=============================================================================
// BEAT
//=============================================================================

Beat::Beat(float beatLength_, Sampler *sampler_, int beatSampleIdx_, SoundSource3D* playSource_) {
    this->beatLength_ = beatLength_;
    this->sampler_ = sampler_;
    this->beatSampleIdx_ = beatSampleIdx_;
    this->playSource_ = playSource_;
}

Beat::~Beat() {

}

void Beat::Play() {
    if (sampler_->Loaded())
        sampler_->Play(playSource_, beatSampleIdx_);
}