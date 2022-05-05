#include "Sequencer.h"
#include "Beat.h"

#include <string>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Container/HashMap.h>

//=============================================================================
// SEQUENCER
//=============================================================================

#define SAMPLE_REST -1
#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2

std::vector<std::string> SAMPLE_PACK = {
        "samples/SAMPLE1-BASSKICK.wav",
        "samples/SAMPLE1-SNARE.wav",
        "samples/SAMPLE1-HH.wav"
};


void Sequencer::RegisterObject(Context *context)
{
    context->RegisterFactory<Sequencer>();
}

void Sequencer::Start()
{

    auto *cache = GetSubsystem<ResourceCache>();
    playSource_ = node_->CreateComponent<SoundSource3D>(LOCAL);
    playSource_->SetNearDistance(1);  // distance up to where the volume is 100%
    playSource_->SetFarDistance(6000);  // distance from where the volume is at 0%
    playSource_->SetSoundType(SOUND_MUSIC);
    sampler_->SetPlaySource(playSource_);

}


void Sequencer::FixedUpdate(float timeStep)
{
    // SERVER & CLIENT CODE

    // Sequencer update

    // Play on fixed update time step
    Play(timeStep);
}

Sequencer::Sequencer(Context *context) : LogicComponent(context), length_(16) {
    // Init parameters
    Reset();
    // Create a new sampler for client object
    sampler_ = context->CreateObject<Sampler>();

    int idx;
    // Generate sequence -> instruction set to time beat
    sequenceByBeat_.Clear();
    Vector<Beat*> channel_;
    for (int i = 0; i < length_; i++) {
        if ((i % 1) == 0) {
            idx = SAMPLE_KICK;
        } else {
            idx = SAMPLE_REST;
        }
        Beat *b = new Beat(1 / beatsPerBar_, sampler_, idx);
        channel_.Push(b);
    }
    sequenceByBeat_.Populate("KICK",channel_);

    for (int i = 0; i < length_; i++) {
        if ((i % 3) == 0) {
            idx = SAMPLE_SNARE;
        } else {
            idx = SAMPLE_REST;
        }
        Beat *b = new Beat(1 / beatsPerBar_, sampler_, idx);
        channel_.Push(b);
    }
    sequenceByBeat_.Populate("SNARE",channel_);

    for (int i = 0; i < length_; i++) {
        idx = 2;
        Beat *b = new Beat(1 / beatsPerBar_, sampler_, idx);
        channel_.Push(b);
    }
    sequenceByBeat_.Populate("HH",channel_);



    URHO3D_LOGDEBUGF("**SEQUENCER ** -> beatsPerBar_=%d,beatTimeStep_=%f", beatsPerBar_, beatTimeStep_);

    // Register
    SetUpdateEventMask(USE_FIXEDUPDATE);

    // Load default samples
    LoadSamples();
}

void Sequencer::SetId(const String &id) {
    id_ = id;
}

Sequencer::~Sequencer() {
    if (playSource_)
        playSource_->ReleaseRef();

    if (sampler_)
        sampler_->ReleaseRef();
}

void Sequencer::Reset() {
    currTime_ = 0.0f;
    beatTime_ = 0.0f;
    barTime_ = 0.0f;
    bar_ = 0;
    beat_ = 0;
    bpm_ = 90;
    URHO3D_LOGDEBUGF("**SEQUENCER [%s] ** RESTART -> time %f, bar %d, beat %d", id_.CString(), currTime_, bar_, beat_);

    // Quarter note by default
    beatsPerBar_ = 4;

    // 1 s = 1000 ms by beats in bar = beat time
    beatTimeStep_ = (1.0f / beatsPerBar_) * 4.0f; // 60 bpm
    // 8/4 beats/sec -> 2 beats/sec
    // 4/4 beats/sec -> 1 beats/sec -> 60 beats in min -> 60 bpm

    // 4/4 = 250 ms time segment
}

void Sequencer::LoadSamples() {
    // LOAD DEFAULT SAMPLES INTO SAMPLER

    // Load sequencer samples for client
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    String prefix = "Sounds/";
    String soundName;
    Sound *sample;
    soundName = SAMPLE_PACK[SAMPLE_KICK].c_str();
    sample = cache->GetResource<Sound>(prefix + soundName);
    sampler_->Load(sample);

    soundName = SAMPLE_PACK[SAMPLE_SNARE].c_str();
    sample = cache->GetResource<Sound>(prefix + soundName);
    sampler_->Load(sample);

    soundName = SAMPLE_PACK[SAMPLE_HH].c_str();
    sample = cache->GetResource<Sound>(prefix + soundName);
    sampler_->Load(sample);
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


        // Sequencer moves forward
        // Mapping of instruction set to timeStep (beat)

        // Play beat sample

        Vector<Beat*> channel_;
        // Play each channel

        // KICK
        channel_ = sequenceByBeat_.Find("KICK")->second_;
        if (channel_[beat_]->GetBeatSampleIdx() > SAMPLE_REST) {
            channel_[beat_]->Play();
        }


        // SNARE
        channel_ = sequenceByBeat_.Find("SNARE")->second_;
        if (channel_[beat_]->GetBeatSampleIdx() > SAMPLE_REST) {
            channel_[beat_]->Play();
        }

        // HI-HAT
        channel_ = sequenceByBeat_.Find("HH")->second_;
        if (channel_[beat_]->GetBeatSampleIdx() > SAMPLE_REST) {
            channel_[beat_]->Play();
        }

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
    return length_;
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

const String &Sequencer::GetId() const {
    return id_;
}

Sampler *Sequencer::GetSampler() {
    return sampler_;
}

void Sequencer::SetPlaySource(SoundSource3D* playSource) {
    playSource_ = WeakPtr(playSource);
}
