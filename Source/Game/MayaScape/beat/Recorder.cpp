#include "Recorder.h"

#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>


//=============================================================================
// RECORDER
//=============================================================================

void Recorder::RegisterObject(Context *context)
{
    context->RegisterFactory<Recorder>();
}

Recorder::Recorder(Context *context) : Object(context) {
    db_->Connect("wefwefw");
}

Recorder::~Recorder() {
    if (playSource_)
        playSource_->ReleaseRef();
}

Vector<Sound*> Recorder::GetSampleQueue() {
    return sampleQueue_;
}

void Recorder::Reset() {

}

void Recorder::Play(int sampleIdx) {

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

void Recorder::Load(Sound* sample) {
    // Store sample
    sampleQueue_.Push(sample);
    loaded_ = true;
}

void Recorder::Stop() {

}

bool Recorder::Loaded() {
    return loaded_;
}

void Recorder::SetPlaySource(SoundSource3D *playSource) {
    playSource_ = playSource;
}

void Recorder::Capture(Vector<Beat *> channel1_, Vector<Beat *> channel2_, Vector<Beat *> channel3_, float currTime_,
                       float beatTime_, float barTime_) {

    // TODO: 1. RECORD SAMPLE INTO BUFFER BLOCK (SHORT STORE)


    // TODO: 2. RECORD BUFFER BLOCK INTO DATABASE (LONG STORE)
}
