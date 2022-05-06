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
    // TODO: ODBC Postgres crashing, solve after for long term storage
   // db_->Connect("DSN=MayaScapeLive");
}

Recorder::~Recorder() {
    if (playSource_)
        playSource_->ReleaseRef();
}

Vector<Sound*> Recorder::GetSampleQueue() {
    return sampleQueue_;
}

void Recorder::Reset(Context *context) {
    // Restart recording
    data_.Clear();
    // Set store context
    storeContext_ = context;

    // Create new buffer block
    SharedPtr<BufferData> bufData = context->CreateObject<BufferData>();
    data_.Push(bufData.Get());
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

void Recorder::Capture(Beat * channel1_, Beat * channel2_, Beat * channel3_, float currTime_,
                       float beatTime_, float barTime_) {

    BeatTime *t = new BeatTime(currTime_, beatTime_, barTime_);
    // Create new buffer block
    SharedPtr<BufferData> bufData = storeContext_->CreateObject<BufferData>();

    // 1. RECORD SAMPLE INTO BUFFER BLOCK (SHORT STORE)
    bufData->SetData(channel1_, channel2_, channel3_, t);

    data_.Push(bufData.Get());
    // TODO: 2. RECORD BUFFER BLOCK INTO DATABASE (LONG STORE)
}
