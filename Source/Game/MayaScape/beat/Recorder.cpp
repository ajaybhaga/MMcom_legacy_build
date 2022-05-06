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

    String dsn = "MAYASCAPE";
    db_ = GetSubsystem<Database>();
    cxn_ = db_->Connect("DSN=" + dsn);

    if (cxn_->IsConnected()) {
        URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC Connected! ** -> %s", dsn.CString());
        odbcConnected_ = true;
    }
}

Recorder::~Recorder() {
    if (playSource_)
        playSource_->ReleaseRef();
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

int Recorder::GetBufferSize() {
    return data_.Size();
}

bool Recorder::IsODBCConnected() {
    return odbcConnected_;
}
