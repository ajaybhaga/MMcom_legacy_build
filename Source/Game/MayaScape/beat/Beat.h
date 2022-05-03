#pragma once

#ifndef MM_BEAT_H
#define MM_BEAT_H


class Beat {

protected:
    float beatLength_; // Beat length (1/4, 1/8, 1/16)

public:
    Beat(float beatLength_);
    ~Beat();
};


#endif //URHO3D_BEAT_H
