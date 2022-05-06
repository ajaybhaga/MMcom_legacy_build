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

    schema_ = "world1";

    id_ = "RECORDER-" + String(Random(10000,99999));
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

    // On long store, create sequence
    CreateSequence();
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
}

int Recorder::GetBufferSize() {
    return data_.Size();
}

bool Recorder::IsODBCConnected() {
    return odbcConnected_;
}

void Recorder::Persist() {
    // 2. RECORD BUFFER BLOCK INTO DATABASE (LONG STORE)

    //
    /*
     *
     *
     * INSERT INTO world1.ms_sequence (seq_id, seq_name, created) VALUES(1, 'Sequence Name 1', current_timestamp);
       INSERT INTO world1.ms_pattern (seq_id, time_code, channel, sample_idx) VALUES(1, 0.00, 0, 0);
     *
     */

    // TODO: Generate SQL insert of buffer data
    // Persist from pStartTime to pEndTime
    String sql = "";

    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
        }
    }
}

void Recorder::CreateSequence() {
    if (!cxn_)
        return;

    seqId_++;
    String seqName = id_ + "-SEQ-" + String(seqId_);
    String sql = "INSERT INTO " + schema_ + ".ms_sequence (seq_id, seq_name, created) VALUES (" + String("nextval('" + schema_ + ".ms_seq_id')") + ", '" + seqName + "', current_timestamp);";

    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }
}

void Recorder::CreateTimeCode() {
    if (!cxn_)
        return;

    seqId_++;
    String seqName = id_ + "-SEQ-" + String(seqId_);
    String sql = "INSERT INTO " + schema_ + ".ms_time_code (seq_id, seq_name, created) VALUES (" + String("nextval('" + schema_ + ".ms_seq_id')") + ", '" + seqName + "', current_timestamp);";

    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }
}
