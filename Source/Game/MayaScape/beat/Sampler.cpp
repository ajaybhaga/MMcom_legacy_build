#include "Sampler.h"
#include "Sequencer.h"
#include "Beat.h"

#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>


//=============================================================================
// SAMPLER
//=============================================================================

void Sampler::RegisterObject(Context *context)
{
    context->RegisterFactory<Sampler>();
}

Sampler::Sampler(Context *context) : Object(context) {
}

Sampler::~Sampler() {
    if (playSource_)
        playSource_->ReleaseRef();
}

Vector<Sound*> Sampler::GetSampleQueue() {
    return sampleQueue_;
}

void Sampler::Reset() {

}

void Sampler::Play(int sampleIdx) {

    if (sampleQueue_.Size() <= sampleIdx)
        return;

    // Play sample
    if (sampleQueue_[sampleIdx] != nullptr) {
        if (playSource_ != nullptr) {
            playSource_->SetAutoRemoveMode(REMOVE_COMPONENT);
            playSource_->Play(sampleQueue_[sampleIdx]);
        }
    }
}

void Sampler::Load(Sound* sample) {
    // Store sample
    sampleQueue_.Push(sample);
    loaded_ = true;
}

void Sampler::Stop() {

}

bool Sampler::Loaded() {
    return loaded_;
}

void Sampler::SetPlaySource(SoundSource3D *playSource) {
    playSource_ = playSource;
}