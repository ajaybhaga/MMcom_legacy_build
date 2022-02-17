//
// Copyright (c) 2008-2021 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once

#include "Vehicle.h"
#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/DecalSet.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RaycastVehicle.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>

#include "Urho3D/Input/Controls.h"
#include "Urho3D/Scene/LogicComponent.h"
#include "Urho3D/Audio/SoundSource3D.h"
#include "Urho3D/Audio/Sound.h"
#include "Urho3D/Graphics/StaticModel.h"
#include "Urho3D/Physics/CollisionShape.h"
#include "Urho3D/Network/Connection.h"

#include "ClientObj.h"

#include "../../../Urho3D/Physics/RaycastVehicleBase.h"
#include <Urho3D/Physics/RigidBody.h>
//#include "MayaScape/RaycastVehicle.h"


#include <Urho3D/Input/Controls.h>
#include <Urho3D/Physics/PhysicsUtils.h>


// Sound fx mappings
#define SOUND_FX_ENGINE_START 0
#define SOUND_FX_ENGINE_REV 1
#define SOUND_FX_TIRE_SKID 2
#define SOUND_FX_ENGINE_BRAKE 3
#define SOUND_FX_ENGINE_ENGINE 4



namespace Urho3D
{
    class Constraint;
    class Node;
    class RigidBody;
    class Controls;
}

const float CHASSIS_WIDTH = 35.0f;


using namespace Urho3D;

class WheelTrackModel;

//=============================================================================
//=============================================================================

const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float DOWN_FORCE = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;

//=============================================================================
//=============================================================================
#define KMH_TO_MPH              (1.0f/1.60934f)

//=============================================================================
// Vehicle component, responsible for physical movement according to controls.
//=============================================================================
class Vehicle : public ClientObj {
URHO3D_OBJECT(Vehicle, ClientObj)


    float lastAccel_ = 0.0f;
    float lastSteer_ = 0.0f;
public:
    /// Construct.
    explicit Vehicle(Context* context);
    /// Destruct.
    ~Vehicle() override;

    virtual void DelayedStart();
    void Create();

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Perform post-load after deserialization. Acquire the components from the scene nodes.
    void ApplyAttributes() override;

    /// Initialize the vehicle. Create rendering and physics components. Called by the application.
    //void Init();
    void Init(Node* node);


        /// Handle physics world update. Called by LogicComponent base class.
    void FixedUpdate(float timeStep) override;
    /// Updating wheel effects here.
    void PostUpdate(float timeStep) override;

    void PostUpdateSound(float timeStep);

    // Based on Lumak's example
    void UpdateGear();
    void LimitLinearAndAngularVelocity();
    void AutoCorrectPitchRoll();
    void ApplyDownwardForce();
    void ApplyAntiRollBar();

    bool ApplyStiction(float steering, float acceleration, bool braking);
    void ApplyEngineForces(float accelerator, bool braking);
    void UpdateSteering(float newSteering);
    void UpdateDrift();

    void SetTurrentAngle(float angle);
    float GetTurrentAngle();

        float GetSpeedKmH() const       { return raycastVehicle_->GetSpeedKm(); }
    float GetSpeedMPH() const       { return raycastVehicle_->GetSpeedKm()*KMH_TO_MPH; }
    int GetCurrentGear() const      { return curGearIdx_; }
    float GetCurrentRPM() const     { return curRPM_; }



    /// Get steering value.
    float GetSteering() { return steering_; }

    /// Set steering value.
    void SetSteering(float steering) { steering_ = steering; }

    /// Get wheel radius.
    float GetWheelRadius() { return wheelRadius_; }

    /// Get wheel width.
    float GetWheelWidth() { return wheelWidth_; }

    SharedPtr<RaycastVehicleBase> GetRaycastVehicle() { return raycastVehicle_; };
    SharedPtr<RigidBody> GetBody() { return body_; }

    virtual void Flip(float duration);
    virtual void Fire();
    void Kill();

private:
    /// Creates particle emitter.
    void CreateEmitter(Vector3 place);

    /// Current left/right steering amount (-1 to 1.)
    float steering_;
    /// Tmp storage for steering
    float vehicleSteering_;
    int steerIndex_ = 0;
public:
    int getSteerIndex() const;

    void setSteerIndex(int steerIndex);

private:

    // Where to steer next
    float desiredSteer_;
public:
    float getDesiredSteer() const;

    void setDesiredSteer(float desiredSteer);

private:


    /// Linear momentum supplied by engine to RigidBody
    float engineForce_;
    /// Rotational momentum preventing (dampening) wheels rotation
    float brakingForce_;
    /// Maximum linear momentum supplied by engine to RigidBody
    float maxEngineForce_;
    /// Stored wheel radius
    float wheelRadius_;
    /// Suspension rest length (in meters)
    float suspensionRestLength_;
    /// Width of wheel (used only in calculation of wheel placement)
    float wheelWidth_;
    /// Suspension stiffness
    float suspensionStiffness_;
    /// Suspension damping
    float suspensionDamping_;
    /// Suspension compression
    float suspensionCompression_;
    /// Wheel friction
    float wheelFriction_;
    /// Wheel roll influence (how much car will turn sidewise)
    float rollInfluence_;


    // Lumak
    float   m_fVehicleMass;
    float   m_fEngineForce;
    float   m_fBreakingForce;

    float   m_fmaxEngineForce;
    float   m_fmaxBreakingForce;

    float   m_fVehicleSteering;
    float   m_fsteeringIncrement;
    float   m_fsteeringClamp;
    float   m_fwheelRadius;
    float   m_fwheelWidth;
    float   m_fwheelFriction;
    float   m_fsuspensionStiffness;
    float   m_fsuspensionDamping;
    float   m_fsuspensionCompression;
    float   m_frollInfluence;
    float   m_fsuspensionRestLength;

    // slip vars
    float   m_fMaxSteering;
    float   m_fsideFrictionStiffness;
    float   m_fRearSlip;

    Vector3 centerOfMassOffset_;

    // acceleration
    float currentAcceleration_;

    // ang velocity limiter
    float   m_fYAngularVelocity;
    ///

    /// Emitter data for saving.
    Vector<Node*> particleEmitterNodeList_;
    /// Value to calculate acceleration.
    Vector3 prevVelocity_;
    /// Storing points for emitters
    Vector3 connectionPoints_[4];
    /// Do not recreate emitters if they are already created.
    bool emittersCreated;


    // Network actor node
    Node* actorNode_;
public:
    Node *getActorNode() const;

    void setActorNode(Node *actorNode);

private:


    // PEER
    /// Movement controls. Assigned by the main program each physics update step.
    WeakPtr<Connection> connection_;
    Timer updateTimer_;
    ///


protected:
    void HandleVehicleCollision(StringHash eventType, VariantMap & eventData);
    void PlaySoundEffectGlobal(const String &soundName);
//
    String name_;

protected:
    SharedPtr<RaycastVehicleBase> raycastVehicle_;
    SharedPtr<RigidBody> body_;
    SharedPtr<CollisionShape> hullColShape_;
    SharedPtr<StaticModel> hullObject_;
    SharedPtr<StaticModel> hullObjectTurrent_;
    HashMap<int, WeakPtr<Node> > wheels_;

    // wheel contacts
    int numWheels_ = 0;
    int numWheelContacts_ = 0;


    bool isBraking_;
    PODVector<float> gearShiftSpeed_;
    PODVector<bool>  prevWheelInContact_;

    // gears
    float downShiftRPM_;
    float upShiftRPM_;
    int numGears_;
    int curGearIdx_;
    float curRPM_;
    float minIdleRPM_;

    // sound
    SharedPtr<Sound>         engineSnd_;
    SharedPtr<Sound>         skidSnd_;
    SharedPtr<Sound>         shockSnd_;
    SharedPtr<SoundSource3D> engineSoundSrc_;
    SharedPtr<SoundSource3D> skidSoundSrc_;
    SharedPtr<SoundSource3D> shockSoundSrc_;
    bool                     playAccelerationSoundInAir_;

};

