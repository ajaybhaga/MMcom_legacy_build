#pragma once

#ifndef URHO3D_SEQUENCER_H
#define URHO3D_SEQUENCER_H

#include "Beat.h"
#include <Urho3D/Container/Vector.h>

using namespace Urho3D;
class Sequencer {

protected:
    Vector<Beat*> sequence_;
    int size_; // 8 beats
    int beat_; // Current beat

    float time_; // Current time
    int bpm_; // Beats per minute
    int beatsPerBar_; // Beats per bar
    float beatTimeStep_; // Calculated beat time step

public:

    Sequencer();
    ~Sequencer();
    Vector<Beat*> GetSequence();
    void Play(float timeStep);
};


#endif //URHO3D_SEQUENCER_H
