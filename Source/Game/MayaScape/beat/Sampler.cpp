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

void Sampler::Start()
{

}


void Sampler::FixedUpdate(float timeStep)
{

}

Sampler::Sampler(Context *context) : LogicComponent(context) {
    // register
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

Sampler::~Sampler() {

}

Vector<Sound*> Sampler::GetSampleQueue() {
    return sampleQueue_;
}

void Sampler::Reset() {

}

void Sampler::Play(SoundSource3D *source, int sampleIdx) {

    if (sampleQueue_.Size() <= sampleIdx)
        return;

    // Play sample
    if (sampleQueue_[sampleIdx] != nullptr) {
        if (source != nullptr) {
            source->SetAutoRemoveMode(REMOVE_COMPONENT);
            source->Play(sampleQueue_[sampleIdx]);
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