#include "BufferData.h"
#include "BeatTime.h"
#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>

//=============================================================================
// BUFFER DATA
//=============================================================================

void BufferData::RegisterObject(Context *context)
{
    context->RegisterFactory<BufferData>();
}

BufferData::BufferData(Context *context) : Object(context) {
    // TODO: ODBC Postgres crashing, solve after for long term storage
    // db_->Connect("DSN=MayaScapeLive");
}

BufferData::~BufferData() {

}


void BufferData::SetData(Beat *channel1_, Beat *channel2_, Beat *channel3_, BeatTime *time_) {

    Vector<Beat*> beatData;
    beatData.Push(channel1_);
    beatData.Push(channel2_);
    beatData.Push(channel3_);
    bufferBeat_.Populate(time_, beatData);

    Vector<BeatTime*> timeData;
    timeData.Push(time_);
    bufferTime_.Populate(time_, timeData);
}

void BufferData::Persist() {

}