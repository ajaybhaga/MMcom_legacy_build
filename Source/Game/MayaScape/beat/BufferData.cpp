#include "BufferData.h"
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


void BufferData::SetData(Beat *channel1_, Beat *channel2_, Beat *channel3_, float currTime_, float beatTime_,
                         float barTime_) {

    Vector<Beat*> beatData;
    beatData.Push(channel1_);
    beatData.Push(channel2_);
    beatData.Push(channel3_);
    bufferBeat_.Populate(currTime_, beatData);

    Vector<float> timeData;
    data.Push(channel1_);
    data.Push(channel2_);
    data.Push(channel3_);
    bufferTime_.Populate(currTime_, timeData);
}
