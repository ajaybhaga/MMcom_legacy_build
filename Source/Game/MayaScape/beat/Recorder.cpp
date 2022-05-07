#include "Recorder.h"

#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Database/Database.h>
#include <Urho3D/Database/DatabaseEvents.h>


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

    SubscribeToEvent(E_DBCURSOR, URHO3D_HANDLER(Recorder, HandleDBCursor));
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
    CreateSequence("seq");
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

    // This can be pulled from data_ -> bufData
    CreateTimeCode(currTime_, beatTime_);
    CreatePattern(channel1_, channel2_, channel3_, currTime_, beatTime_, barTime_);
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

void Recorder::HandleDBCursor(StringHash eventType, VariantMap& eventData) {

    using namespace DbCursor;

//    URHO3D_PARAM(P_COLVALUES, ColValues);          // VariantVector
//    URHO3D_PARAM(P_COLHEADERS, ColHeaders);        // StringVector


    /*
    eventData[P_DBCONNECTION] = this;
    eventData[P_RESULTIMPL] = &result.resultImpl_;
    eventData[P_SQL] = sql;
    eventData[P_NUMCOLS] = numCols;
    eventData[P_COLVALUES] = colValues;
    eventData[P_COLHEADERS] = result.columns_;
    eventData[P_FILTER] = false;
    eventData[P_ABORT] = false;
*/

    VariantVector colValues = eventData[P_COLVALUES].GetVariantVector();
    StringVector colHeaders = eventData[P_COLHEADERS].GetStringVector();

    for (Variant h : colHeaders) {
        String header = h.GetString();
        for (Variant v : colValues) {
            String value = v.GetString();
            URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - HandleDBCursor value ** -> %s = %s", header.CString(), value.CString());
        }
    }


}

void Recorder::CreateSequence(String name) {
    if (!cxn_)
        return;

    seqId_++;
    String seqName = id_ + "-" + name + "-" + String(seqId_);
    String sql = "INSERT INTO " + schema_ + ".ms_sequence (seq_id, seq_name, created) VALUES (" + String("nextval('" + schema_ + ".ms_seq_id')") + ", '" + seqName + "', current_timestamp);";

    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            DbResult result = cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }

    currSeqId_ = GetSequence();
}

int Recorder::GetSequence() {
    if (!cxn_)
        return -1;

    String sql = "SELECT currval('" + schema_ + ".ms_seq_id');";

    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Persist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            DbResult result = cxn_->Execute(sql);
            VariantVector v = result.GetRows().At(0);

          //  int value = v.At(0).GetInt();
            String val = v.At(0).GetString();
            URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC VALUE ** -> %s", val.CString());
           /* return value;*/
          return ToInt(String(val));
        }
    }
}


void Recorder::CreateTimeCode(float timeCode, float beat) {
    if (!cxn_)
        return;

    //INSERT INTO world1.ms_time_code (time_code, beat, rec_date) VALUES(0, 0, '');
    String sql = "INSERT INTO " + schema_ + ".ms_time_code (time_code, beat, rec_date) VALUES (" + String( timeCode ) + ", '" + String( beat ) + "', current_timestamp);";

    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }
}

void Recorder::CreatePattern(Beat* channel1_, Beat* channel2_, Beat* channel3_, float currTime_, float beatTime_, float barTime_) {
    if (!cxn_)
        return;

    String sql;
    sql = "INSERT INTO " + schema_ + ".ms_pattern (seq_id, time_code, channel, sample_idx) VALUES (" + String("currval('" + schema_ + ".ms_seq_id')") + ", " + String(currTime_) + ",0," + String(channel1_->GetBeatSampleIdx()) + ");";
    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }

    sql = "INSERT INTO " + schema_ + ".ms_pattern (seq_id, time_code, channel, sample_idx) VALUES (" + String("currval('" + schema_ + ".ms_seq_id')") + ", " + String(currTime_) + ",1," + String(channel2_->GetBeatSampleIdx()) + ");";
    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }

    sql = "INSERT INTO " + schema_ + ".ms_pattern (seq_id, time_code, channel, sample_idx) VALUES (" + String("currval('" + schema_ + ".ms_seq_id')") + ", " + String(currTime_) + ",2," + String(channel3_->GetBeatSampleIdx()) + ");";
    URHO3D_LOGDEBUGF("** SEQUENCER: RECORDER - ODBC EXECUTE ** -> %s", sql.CString());
    // Pesist current buffer to long store -> ODBC Postgres
    if (cxn_) {
        if (cxn_->IsConnected()) {
            cxn_->Execute(sql);
            cxn_->Finalize();
        }
    }


}
