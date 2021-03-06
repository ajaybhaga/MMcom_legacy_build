#pragma once

#include <Urho3D/UI/Text3D.h>
#include "ClientObj.h"
#include "Vehicle.h"
#include <MayaScape/beat/Sequencer.h>

#include "../GameController.h"
#include "../../../Urho3D/Graphics/AnimatedModel.h"
#include "../../../Urho3D/Graphics/AnimationController.h"

namespace Urho3D
{
class Controls;
class Node;
class RigidBody;
class Connection;
}

using namespace Urho3D;
//=============================================================================
//=============================================================================
static const unsigned NTWK_CTRL_BACK = (1<<0);
static const unsigned NTWK_CTRL_FORWARD    = (1<<1);
static const unsigned NTWK_CTRL_LEFT    = (1<<2);
static const unsigned NTWK_CTRL_RIGHT   = (1<<3);
static const unsigned NTWK_CTRL_ENTER     = (1<<5);
static const unsigned NTWK_CTRL_FIRE     = (1<<7);
static const unsigned NTWK_CTRL_JUMP     = (1<<8);


static const unsigned NETWORKACTOR_COL_LAYER = 2;
static const int MAX_MAT_COUNT = 9;

//=============================================================================
//=============================================================================
class NetworkActor : public ClientObj
{
    URHO3D_OBJECT(NetworkActor, ClientObj)

public:
    NetworkActor(Context* context);
    ~NetworkActor();
   
    static void RegisterObject(Context* context);

    void DebugDraw();
    void ComputeSteerForce();

    virtual void DelayedStart();
    virtual void SetControls(const Controls &controls);

    void Create();
    void SetConnection(Connection* connection);
    void Init(Node* node);

    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    const WeakPtr<Connection> GetConnection() const { return connection_; }
    void SetNode(Node* node);
//    const Node* GetNode() const { return node_; };

    /// Parameter function
    int GetLife() { return life_; }
    void SetLife(int m_life) { life_ = m_life; }

    void SetWaypoints(const Vector<Vector3>* waypoints) {

        if (waypoints_) {
            delete waypoints_;
            waypoints_ = nullptr;
        }

        Vector<Vector3>* newWPs = new Vector<Vector3>();
        // Copy waypoints into local list
        for (int i = 0; i < waypoints->Size(); i++) {
            newWPs->Push(Vector3(waypoints->At(i)));
        }

        waypoints_ = newWPs;
    }

    void SetTarget(Vector3 toTarget) {
        toTarget_ = toTarget;
    }

    int getAgentIndex() const {
        return agentIndex;
    }

    float GetLastFire() { return lastFire_; }
    void SetLastFire(float lastFire) { lastFire_ = lastFire; };

    float GetMass() { return mass_; }
    void SetMass(float m_mass) { mass_ = m_mass; }
    SharedPtr<RigidBody> GetBody() { return body_; }

    Controls GetControls() { return controls_; }


    float GetSpeed() { return speed_; }
    void SetSpeed(float m_speed) { speed_ = m_speed; }

    float GetMaxSpeed() { return maxSpeed_; }
    void SetMaxSpeed(float m_maxSpeed) { maxSpeed_ = m_maxSpeed; }

    float GetDamping() { return damping_; }
    void SetDamping(float m_damping) { damping_ = m_damping; }
    void Damping() { speed_ -= damping_; if (speed_ <= 0) speed_ = 0; }

    float GetAcceleration() { return acceleration_; }
    void SetAcceleration(float m_acceleration) { acceleration_ = m_acceleration; }
    void Accelerate() { speed_ += acceleration_; if (speed_ > maxSpeed_) speed_ = maxSpeed_; }

    float GetBrake() { return brake_; }
    void SetBrake(float m_brake) { brake_ = m_brake; }
    void Brake() { speed_ -= brake_; if (speed_ < 0) speed_ = 0; }

    Vector3 GetTowards() { return towards_; }
    void SetTowards(Vector3 m_towards) { towards_ = m_towards; }

    String GetBulletType() { return bulletType_; }
    void SetBulletType(String m_bulletType) { bulletType_ = m_bulletType; }

    void Flip();
    void EnterVehicle();

    SharedPtr<Vehicle> GetVehicle() { return vehicle_; }

    void FindTarget();

        /// Fight
    void Fire(Vector3 target);
    void Fire();

    void Kill();

    void Run();
    void Walk();
    void Jump();

    void ApplyMovement(float timeStep);
    void ApplyThrust(float timeStep);

    /// Grounded flag for movement.
    bool onGround_;
    /// Jump flag.
    bool okToJump_;
    /// In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
    float inAirTimer_;


public:
    void SwapMat();
    virtual void SetScene(Scene *scene);
    virtual void FixedUpdate(float timeStep);
    // Mark NetworkActor disconnected, clean-up delayed
    void MarkDisconnected() { disconnected_ = true; }
    //Sequencer &GetSequencer();

        // PEER
    /// Movement controls. Assigned by the main program each physics update step.
    bool disconnected_;
    Controls controls_;
    WeakPtr<Connection> connection_;
    WeakPtr<Scene> scene_;
    Timer updateTimer_;
    ///

    /// Flag when player is dead.
    bool killed_;
    bool isAI_;
    int agentIndex;
    int id_;
    int type_;
    unsigned int wpActiveIndex_;
    int targetAgentIndex_;


    /// Bullets
    String bulletType_;
    Vector<Vector3>* waypoints_ = nullptr;
    Vector3 toTarget_ = Vector3::ZERO;

    const Vector3 &getToTarget() const;

    bool steerSet_;

    bool isSteerSet() const;

    void setSteerSet(bool steerSet);


    /// parameter

    float mass_;
    float speed_;
    float maxSpeed_;
    float thrust_;
    float damping_;
    float acceleration_;
    float brake_;
    Vector3 towards_;

    bool enableControls_;
    Vector3 move_;
    float upThrust_;

    const Vector3 &getMove() const;

    void setMove(const Vector3 &move);

    bool initialSet_;


    float lastEnter_;
    float lastFire_;
    float heading_;
    bool isReady_;
    int life_;
    int score_;
    int health_;

    Vector3 force_;
    Vector3 offset_;

    float changeTargetTime_;
    bool autoSteering_;

    bool doJump_;

    // Marker
    Vector<StaticModel*> markers_;
    // Animated model
    AnimatedModel* model_;
    // Rigid body
    SharedPtr<RigidBody> body_;
    // Collision shape
    CollisionShape* collisionShape_;
    // Animation controller
    AnimationController* animCtrl_;

    // Player state variables
    bool alive_;
    bool onVehicle_;
    bool canEnter_;
    bool entered_;
    bool showMarker_;
    int markType_;
    Vector3 lastImpulse_;
    Vector3 lastContactNorm_;


    String name_;
    Vector3 vehiclePos_;
//    WeakPtr<Node> nodeInfo_;
//    Controls prevControls_;


    /// The controllable vehicle component.
    SharedPtr<Vehicle> vehicle_;
    SharedPtr<Text3D> floatingText_;

    float turrentAngle_ = 0;

};

