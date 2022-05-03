#include "Sampler.h"
#include "Sequencer.h"
#include "Beat.h"


#include <Urho3D/IO/Log.h>


//=============================================================================
// SAMPLER
//=============================================================================
Sampler::Sampler() {

}

Sampler::~Sampler() {

}

Vector<Sound*> Sampler::GetSampleQueue() {
    return sampleQueue_;
}

void Sampler::Reset() {

}

void Sampler::Play(SoundSource3D *source, int sampleIdx) {
    // Play sample
    if (sampleQueue_[sampleIdx] != nullptr) {
        if (source) {
            source->SetAutoRemoveMode(REMOVE_COMPONENT);
            source->Play(sampleQueue_[sampleIdx]);
        }
    }
}

void Sampler::Load(Sound* sample) {

//..    sample->SetNearDistance(1);  // distance up to where the volume is 100%
 //   sample->SetFarDistance(6000);  // distance from where the volume is at 0%
  //  sample->SetSoundType(SOUND_MUSIC);

    // Store sample
    sampleQueue_.Push(sample);
}

void Sampler::Stop() {

}