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

    // 1000 ms by beats in bar = beat time
    beatTimeStep_ = 1000.0f / beatsPerBar_;

    // 4/4 = 250 ms time segment

    sequence_.Clear();
    for (int i = 0; i < size_; i++) {
        Beat *b = new Beat(1 / beatsPerBar_);
        sequence_.Push(b);
    }

    URHO3D_LOGDEBUGF("**SEQUENCER ** -> beatTimeStep_ %f", beatTimeStep_);
}

Sequencer::~Sequencer() {

}

void Sequencer::Play(float timeStep) {
    // Play a time step
    time_ += timeStep;


    // If time accumulation is past
    if (time_ > beatTimeStep_) {
        beat_++; // Increment beat
    }

    beat_ = beat_ % size_; // Clamp by size

    URHO3D_LOGDEBUGF("**SEQUENCER ** -> time %f, beat %d", time_, (beat_ + 1));
}

 Vector<Beat*> Sequencer::GetSequence() {
    return sequence_;
}
