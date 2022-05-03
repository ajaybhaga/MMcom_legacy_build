#include "Sequencer.h"
#include "Beat.h"

#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Resource/ResourceCache.h>

//=============================================================================
// SEQUENCER
//=============================================================================

Sequencer::Sequencer() : size_(8) {
    // Init parameters
    Reset();

    // Quarter note by default
    beatsPerBar_ = 4;

    // 1 s = 1000 ms by beats in bar = beat time
    beatTimeStep_ = (1.0f / beatsPerBar_) * 4.0f; // 60 bpm
    // 8/4 beats/sec -> 2 beats/sec
    // 4/4 beats/sec -> 1 beats/sec -> 60 beats in min -> 60 bpm

    // 4/4 = 250 ms time segment

    sequence_.Clear();
    for (int i = 0; i < size_; i++) {
        Beat *b = new Beat(1 / beatsPerBar_);
        sequence_.Push(b);
    }

    URHO3D_LOGDEBUGF("**SEQUENCER ** -> beatsPerBar_=%d,beatTimeStep_=%f", beatsPerBar_, beatTimeStep_);

    // Load default samples for sequencer
    sampler_ = Sampler();
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

        if (sampler_.Loaded())
            sampler_.Play(playSource_, 0);

        if (beat_ > beatsPerBar_) {
            // Over bar limit
            bar_++;
            beat_ = 1;
            barTime_ = 0.0f;
        } else {
 /*           URHO3D_LOGDEBUGF("**SEQUENCER [%s] ** -> time %f, beat time: %f, bar time: %f, bar %d, beat %d", id_.CString(), currTime_,
                             beatTime_, barTime_, bar_, beat_);*/
        }
    }
}

float Sequencer::GetBeatTime() const {
    return beatTime_;
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

Sampler &Sequencer::GetSampler() {
    return sampler_;
}

void Sequencer::SetPlaySource(SoundSource3D* playSource) {
    playSource_ = WeakPtr(playSource);
}
