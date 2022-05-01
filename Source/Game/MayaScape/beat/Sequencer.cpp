#include "Sequencer.h"
#include "Beat.h"

#include <Urho3D/IO/Log.h>

//=============================================================================
// SEQUENCER
//=============================================================================

Sequencer::Sequencer() : size_(8) {
    // Init parameters
    Reset();

    // Quarter note by default
    beatsPerBar_ = 4;

    // 1 s = 1000 ms by beats in bar = beat time
    beatTimeStep_ = (1.0f / beatsPerBar_) * 4.0f;
    // 8/4 beats/sec -> 2 beats/sec
    // 4/4 beats/sec -> 1 beats/sec

    // 4/4 = 250 ms time segment

    sequence_.Clear();
    for (int i = 0; i < size_; i++) {
        Beat *b = new Beat(1 / beatsPerBar_);
        sequence_.Push(b);
    }

//    URHO3D_LOGDEBUGF("**SEQUENCER ** -> beatTimeStep_ %f", beatTimeStep_);
}

void Sequencer::SetId(const String &id) {
    id_ = id;
}

Sequencer::~Sequencer() {

}

void Sequencer::Reset() {
    currTime_ = 0.0f;
    beatTime_ = 0.0f;
    barTime_ = 0.0f;
    bar_ = 0;
    beat_ = 0;
    bpm_ = 90;
    URHO3D_LOGDEBUGF("**SEQUENCER [%s] ** RESTART -> time %f, bar %d, beat %d", id_.CString(), currTime_, bar_, beat_);
}

// Sequencer Play: Move forward a time step
void Sequencer::Play(float timeStep) {
    // Play a time step
    currTime_ += timeStep;
    beatTime_ += timeStep;
    barTime_ += timeStep;

    // If time accumulation is past
    if (beatTime_ >= beatTimeStep_) {
        beat_++; // Increment beat
        beatTime_ = 0.0f;

        if (beat_ > beatsPerBar_) {
            // Over bar limit
            bar_++;
            beat_ = 0;
            barTime_ = 0.0f;
        } else {
            URHO3D_LOGDEBUGF("**SEQUENCER [%s] ** -> time %f, beat time: %f, bar time: %f, bar %d, beat %d", id_.CString(), currTime_,
                             beatTime_, barTime_, bar_, beat_);
        }
    }
}

int Sequencer::GetSize() const {
    return size_;
}

int Sequencer::GetBeat() const {
    return beat_;
}

float Sequencer::GetTime() const {
    return currTime_;
}

int Sequencer::GetBpm() const {
    return bpm_;
}

int Sequencer::GetBeatsPerBar() const {
    return beatsPerBar_;
}

float Sequencer::GetBeatTimeStep() const {
    return beatTimeStep_;
}

Vector<Beat*> Sequencer::GetSequence() {
    return sequence_;
}

const String &Sequencer::GetId() const {
    return id_;
}
