#include "Sequencer.h"
#include "Beat.h"

#include <Urho3D/IO/Log.h>

//=============================================================================
// SEQUENCER
//=============================================================================

Sequencer::Sequencer() : size_(8) {
    time_ = 0.0f;
    beat_ = 0;
    bpm_ = 90;

    // Quarter note by default
    beatsPerBar_ = 4;

    // 1 s = 1000 ms by beats in bar = beat time
    beatTimeStep_ = 1.0f / beatsPerBar_;

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

// Sequencer Play: Move forward a time step
void Sequencer::Play(float timeStep) {
    // Play a time step
    time_ += timeStep;

    // If time accumulation is past
    if (time_ > beatTimeStep_) {
        beat_++; // Increment beat
        beat_ = beat_ % size_; // Clamp by size
        URHO3D_LOGDEBUGF("**SEQUENCER [%s] ** -> time %f, beat %d", id_.CString(), time_, (beat_ + 1));
    }
}

int Sequencer::GetSize() const {
    return size_;
}

int Sequencer::GetBeat() const {
    return beat_;
}

float Sequencer::GetTime() const {
    return time_;
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
