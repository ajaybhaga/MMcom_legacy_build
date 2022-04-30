#include "Sequencer.h"
#include "Beat.h"

#include <Urho3D/IO/Log.h>

//=============================================================================
// SEQUENCER
//=============================================================================

Sequencer::Sequencer() : size_(8) {
    time_ = 0.0f;
    beat_ = 0;

    sequence_.Clear();
    for (int i = 0; i < size_; i++) {
        Beat *b = new Beat(1 / 4); // Quarter note by default
        sequence_.Push(b);
    }
}

Sequencer::~Sequencer() {

}

void Sequencer::Play(float timeStep) {
    // Play a time step
    time_ += timeStep;
    beat_++; // Increment beat
    beat_ = beat_ % size_; // Clamp by size

    URHO3D_LOGDEBUGF("**SEQUENCER ** -> time %f, beat %d", time_, beat_);
}

 Vector<Beat*> Sequencer::GetSequence() {
    return sequence_;
}
