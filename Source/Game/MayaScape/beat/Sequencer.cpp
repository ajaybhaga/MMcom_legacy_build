#include "Sequencer.h"
#include "Beat.h"

//=============================================================================
// SEQUENCER
//=============================================================================

Sequencer::Sequencer(int size_) {
    time_ = 0.0f;
    this->size_ = size_;
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
}

 Vector<Beat*> Sequencer::GetSequence() {
    return sequence_;
}
