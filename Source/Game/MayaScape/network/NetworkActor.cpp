//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Network/Connection.h>
#include <Urho3D/Physics/PhysicsUtils.h>
#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Core/Variant.h>


#include "NetworkActor.h"

#include <Urho3D/DebugNew.h>
#include <MayaScape/Missile.h>

#define PI 3.1415926

/*
String mdlFile = "Models/Player/Shino/FBX/Models/Shino.mdl";
                                            //Models/Armature_idle_01_idle_01.ani
String idleAniFile = "Models/Player/Shino/FBX/Models/Armature_idle_01_idle_01.ani";
String walkAniFile = "Models/Player/Shino/FBX/Models/Armature_walk_walk.ani";
String matFile = "Models/Player/Shino/FBX/Models/Shino.txt";

*/

String mdlFile = "Models/Player/Bino/Models/f_8.mdl";
//Models/Armature_idle_01_idle_01.ani
//String idleAniFile = "Models/Player/Bino/Models/r_f_8_r_f_8_Run_r_f_8_Run.ani";
//String walkAniFile = "Models/Player/Bino/Models/r_f_8_r_f_8_Run_r_f_8_Run.ani";
String idleAniFile = "Models/Player/Bino/Models/Idle.ani";
String walkAniFile = "Models/Player/Bino/Models/Walk.ani";
String runAniFile = "Models/Player/Bino/Models/Run.ani";
String victoryAniFile = "Models/Player/Bino/Models/Victory.ani";
String defeatAniFile = "Models/Player/Bino/Models/Defeat.ani";
String matFile = "Models/Player/Bino/Models/f_8.txt";



//=============================================================================
// NETWORK ACTOR
//=============================================================================
NetworkActor::NetworkActor(Context *context)
        : ClientObj(context), mass_(10.0f),
        alive_(true),
        onVehicle_(false),
        enableControls_(false),
        initialSet_(false)
        {
      SetUpdateEventMask(USE_NO_EVENT);

    SetLife(100);
    SetSpeed(0.0f);
    SetMaxSpeed(5.0f);
    SetDamping(0.015f);
    SetAcceleration(0.03f);
    SetBrake(0.05f);
    SetTowards(Vector3(0.0f, 1.0f, 0.0f));
    SetBulletType("AP");

    lastFire_ = 0;
    toTarget_ = Vector3(0,0,0);
    targetAgentIndex_ = 0;
    disconnected_ = false;


    thrust_   = 1024.0f;
    maxSpeed_ = 1.23f;
}

NetworkActor::~NetworkActor() {

    URHO3D_LOGINFOF("**** DESTROYING NetworkActor OBJECT -> %d", this->id_);
    if (vehicle_) {
        URHO3D_LOGINFOF("**** DESTROYING CLIENT VEHICLE NODE OBJECT -> %d", this->id_);
        vehicle_->Remove();
    }


    if (node_) {
        //URHO3D_LOGINFOF("**** DESTROYING CLIENT NODE OBJECT -> %d", this->id_);
        //node_->RemoveAllChildren();
        //node_->Remove();
    }

}

void NetworkActor::Kill() {
    //SetEnabled(false);

    SetUpdateEventMask(USE_NO_EVENT);

    URHO3D_LOGINFOF("**** DESTROYING NetworkActor OBJECT -> %d", this->id_);
    if (vehicle_) {
        vehicle_->SetEnabled(false);
        vehicle_->Kill();
    }

    if (node_) {
        URHO3D_LOGINFOF("**** DESTROYING CLIENT NODE OBJECT -> %d", this->id_);
        node_->RemoveAllChildren();
        //node_->Remove();
    }

}

void NetworkActor::SetScene(Scene *scene) {
    scene_ = scene;
}

void NetworkActor::RegisterObject(Context *context) {
    context->RegisterFactory<NetworkActor>();

    URHO3D_COPY_BASE_ATTRIBUTES(ClientObj);

    ClientObj::RegisterObject(context);
    //Vehicle::RegisterObject(context);


    // Network Actor Network Attributes
 //   URHO3D_ATTRIBUTE("Name", String, userName_, String::EMPTY, AM_DEFAULT | AM_NET);
 //   URHO3D_ATTRIBUTE("Color Index", int, colorIdx_, 0, AM_DEFAULT | AM_NET);

    // These macros register the class attributes to the Context for automatic load / save handling.
    // We specify the Default attribute mode which means it will be used both for saving into file, and network replication
    //URHO3D_ATTRIBUTE("Controls Yaw" int, controls_.buttons_, 0.0f, AM_DEFAULT);
    //URHO3D_ATTRIBUTE("Speed", float, speed_, 0.0f, AM_DEFAULT);
    //URHO3D_ATTRIBUTE("Turning Velocity", float, turningVelocity_, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    //    URHO3D_ATTRIBUTE("On Ground", bool, vehicle_->GetRaycastVehicle()->GetCurrentSpeedKmHour(), 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Player Name", String, name_, String::EMPTY, AM_DEFAULT | AM_NET);


}

void NetworkActor::DelayedStart()
{
    Create();
}

void NetworkActor::Init(Node* node) {

    auto* cache = GetSubsystem<ResourceCache>();

    node_ = node;
    if (node_) {

        Node* markerNode = node_->CreateChild("Marker");
        markerNode->SetScale(24.0f);
        markerNode->SetPosition(Vector3(0.0f,72.0f, -4.0f));


        Node* modelNode = node_->CreateChild("Actor", REPLICATED);
        //modelNode->SetScale(4.0f);
        modelNode->SetScale(4.0f);
        modelNode->SetPosition(Vector3(0.0f,0.0f, 0.0f));
        modelNode->SetRotation(Quaternion(0, -90, 0.0f));
        model_ = modelNode->CreateComponent<AnimatedModel>();
        body_ = modelNode->CreateComponent<RigidBody>();
        collisionShape_ = modelNode->CreateComponent<CollisionShape>();
        animCtrl_ = modelNode->CreateComponent<AnimationController>();

        model_->SetCastShadows(true);

        wpActiveIndex_ = 0;
        targetAgentIndex_ = 0;

        model_->SetModel(cache->GetResource<Model>(mdlFile));
        model_->SetCastShadows(true);
        //model_->SetMaterial(cache->GetResource<Material>(matFile));
        model_->ApplyMaterialList(matFile);

        body_->SetFriction(0.0f);
        body_->SetMass(1.0f);
        body_->SetRestitution(0.0f);
        body_->SetLinearDamping(0.88f);
        body_->SetLinearRestThreshold(0.0f);
        body_->SetAngularFactor(Vector3::ZERO);
        body_->SetAngularRestThreshold(0.0f);
        // Set rigid body kinematic mode. In kinematic mode forces are not applied to the rigid body.
        //body_->SetKinematic(true);
        collisionShape_->SetCapsule(0.42f, 0.5f, Vector3::UP * 0.3f);

        animCtrl_->PlayExclusive(walkAniFile, 0, true);
        animCtrl_->SetSpeed(walkAniFile, 0.2f);
        animCtrl_->SetStartBone(walkAniFile, "root");


        // register
        SetUpdateEventMask(USE_UPDATE | USE_FIXEDUPDATE);

        enableControls_ = true;

        // update serializable of the change
        SetAttribute("Color Index", Variant(50));
        SetAttribute("Position", Variant(node_->GetPosition()));

    }
}

void NetworkActor::Create() {

    // Update for clients replicating
    // Set node
    //node_ = this;

    node_ = GetNode();
    enableControls_ = true;



    // register
    SetUpdateEventMask(USE_UPDATE | USE_FIXEDUPDATE);


}

void NetworkActor::SetNode(Node* node)
{
    node_ = node;
}

void NetworkActor::SetConnection(Connection* connection)
{
    connection_ = connection;
}

void NetworkActor::SwapMat() {
    ResourceCache *cache = GetSubsystem<ResourceCache>();

    int idx = Random(MAX_MAT_COUNT);
    while (idx == colorIdx_) {
        idx = Random(MAX_MAT_COUNT);
    }

    // update serializable of the change
    SetAttribute("Color Index", Variant(idx));

    String matName = ToString("NetDemo/ballmat%i.xml", colorIdx_);
    StaticModel *ballModel = node_->GetComponent<StaticModel>();
    ballModel->SetMaterial(cache->GetResource<Material>(matName));
}

void NetworkActor::SetControls(const Controls &controls) {
    controls_ = controls;
    if (vehicle_) {
        vehicle_->SetControls(controls);
    }
}

void NetworkActor::Flip() {

    float qx;
    float qy;
    float qz;
    float qw;

    // Read current transform from data frame
    btTransform trans;
    vehicle_->GetBody()->getWorldTransform(trans);
    qx = trans.getRotation().x();
    qy = trans.getRotation().y();
    qz = trans.getRotation().z();
    qw = trans.getRotation().w();
    URHO3D_LOGDEBUGF("NetworkActor::Flip() -> [q.x: %f, q.y: %f, q.z: %f, q.w: %f]", qx, qy, qz, qw);

    btTransform updateTrans = btTransform(trans.getRotation().inverse());
    //updateTrans.setRotation(btQuaternion(trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z(), trans.getRotation().w()));


    vehicle_->GetBody()->setWorldTransform(updateTrans);

    qx = updateTrans.getRotation().x();
    qy = updateTrans.getRotation().y();
    qz = updateTrans.getRotation().z();
    qw = updateTrans.getRotation().w();
    URHO3D_LOGDEBUGF("NetworkActor::Flip() AFTER -> [q.x: %f, q.y: %f, q.z: %f, q.w: %f]", qx, qy, qz, qw);
}

void NetworkActor::FindTarget() {
    Vector3 center = this->GetPosition();
    float radius = 200.0f;
    PhysicsWorld *physicsWorld = GetScene()->GetComponent<PhysicsWorld>();
    PODVector<RigidBody *> hitResults{};
    physicsWorld->GetRigidBodies(hitResults, Sphere{center, radius}, 2);

    for (RigidBody *b: hitResults) {
        Vector3 pos = b->GetNode()->GetWorldPosition();


        Vector3 delta = center-pos;
        if (delta.Length() > 10.0f) {
            toTarget_ = pos;
        }
    }
}

void NetworkActor::AlignWithMovement(float timeStep) {
    Quaternion rot{ node_->GetRotation() };

    // Next move
    move_ = move_.Normalized() * Pow(move_.Length() * 1.05f, 2.0f);
    if (move_.Length() > 1.0f)
        move_.Normalize();

    Quaternion targetRot{};
    Vector3 direction{ 0.13f * move_ + body_->GetLinearVelocity() * Vector3{ 1.0f, 0.0f, 1.0f }};

    if (direction.Length() < 0.1f)
        return;

    targetRot.FromLookRotation(direction);
    rot = rot.Slerp(targetRot, Clamp(timeStep * 5.0f, 0.0f, 1.0f));
    node_->SetRotation(rot);



    // Apply Movement

    // Apply force to rigid body of actor
    bool run = false;
    Vector3 force{ move_.Length() < 0.05f ? Vector3::ZERO : move_ * thrust_ * timeStep };
    force *= 1.0f + 0.23f * run;

    if (body_->GetLinearVelocity().Length() < (maxSpeed_ * (1.0f + 0.42f * run))
         || (body_->GetLinearVelocity().Normalized() + force.Normalized()).Length() < M_SQRT2 )
    {
        body_->ApplyForce(force);
    }

}

void NetworkActor::FixedUpdate(float timeStep) {
    if (!node_) {
        return;
    }

    // DEBUG DRAW
    DebugDraw();


    if (toTarget_ == Vector3(0,0,0)) {
        FindTarget();
    }

    // Snaps network actor to vehicle
    if (vehicle_) {

        // Set to control if actor on vehicle
        vehicle_->setEnableControls(onVehicle_);

        // Snap to vehicle once
        if (!initialSet_) {
            this->position_ = vehicle_->GetRaycastVehicle()->GetNode()->GetPosition();
            node_->SetRotation(vehicle_->GetRaycastVehicle()->GetNode()->GetRotation());
            initialSet_ = true;
        }

        // Set client object
        node_->SetPosition(GetNode()->GetPosition());
        node_->SetRotation(GetNode()->GetRotation());

        this->position_ = GetNode()->GetPosition();


        vehicle_->setActorNode(this->node_);

        // Once target found, calculate angle
        Vector3 delta = toTarget_-vehicle_->GetNode()->GetWorldPosition();
        double angleRadians = atan2(delta.z_, delta.x_);

        // The towards vector according to the angle
        //towards_ = Vector3(cos(angleRadians * PI / 180.0f), 0, sin(angleRadians * PI / 180.0f));
        //int degrees = vehicle_->GetNode()->GetRotation().y_+round((angleRadians * 180.0f / PI)-90.0f);

        // Update rotation according to direction of the player's movement.
        Vector3 velocity = body_->GetLinearVelocity();

//    Vector3 lookDirection{ velocity + 2.0f * aim_ };
//    Quaternion rotation{ node_->GetWorldRotation() };
//    Quaternion aimRotation{ rotation };
//    aimRotation.FromLookRotation(lookDirection);
//    node_->SetRotation(rotation.Slerp(aimRotation, 7.0f * timeStep * velocity.Length()));
        AlignWithMovement(timeStep);


        // Update animation
        if (velocity.Length() > 0.1f) {

            animCtrl_->PlayExclusive(walkAniFile, 1, true, 0.15f);
            animCtrl_->SetSpeed(walkAniFile, velocity.Length() * 2.3f);
            animCtrl_->SetStartBone(walkAniFile, "Ctrl_all");

        } else {

            animCtrl_->PlayExclusive(idleAniFile, 1, true, 0.15f);
            animCtrl_->SetStartBone(idleAniFile, "Ctrl_all");
        }



        int vehDegrees = vehicle_->GetNode()->GetRotation().YawAngle();
        //int degrees = round((angleRadians * 180.0f / PI));
        int theta_deg = fmod(atan2(delta.z_, delta.x_)/M_PI*180,360);
        //vehicle_->SetTurrentAngle(theta_deg-180.0f);


        vehicle_->SetTurrentAngle(turrentAngle_);

        turrentAngle_ = turrentAngle_ + 0.1f;

    }

    // update serializable of the change
    //SetAttribute("Color Index", Variant(50));
    //SetAttribute("Position", Variant(node_->GetPosition()));

    // update prev
    lastFire_ += timeStep;

        //float limit = Random(1.0f, 4.0f);
        float limit = 0.4f;
        if (lastFire_ > limit) {
            if (controls_.buttons_ & NTWK_CTRL_FIRE) {
                // FIRE to target
                Fire();
            }
            lastFire_ = 0;
        }


    if (enableControls_) {

        //URHO3D_LOGDEBUGF("**VEHICLE CONTROLS** -> %l", controls_.buttons_);

        // Read controls generate vehicle control instruction
        if (controls_.buttons_ & NTWK_CTRL_LEFT) {
            move_ = Vector3(-1.0f, 0.0f, 0.0f);
            URHO3D_LOGDEBUG("NetworkActor -> **NTWK_CTRL_LEFT**");
        }
        if (controls_.buttons_ & NTWK_CTRL_RIGHT) {
            move_ = Vector3(1.0f, 0.0f, 0.0f);
            URHO3D_LOGDEBUG("NetworkActor -> **NTWK_CTRL_RIGHT**");
        }

        if (controls_.buttons_ & NTWK_CTRL_FORWARD) {
            move_ = Vector3(0.0f, 0.0f, 100.0f);
            URHO3D_LOGDEBUG("NetworkActor -> **NTWK_CTRL_FORWARD**");
        }
        if (controls_.buttons_ & NTWK_CTRL_BACK) {
            move_ = Vector3(0.0f, 0.0f, -1.0f);
        }

        if (controls_.buttons_ & NTWK_CTRL_FLIP) {
            // FLIP CAR
            //Flip(timeStep);
        }

        if (controls_.buttons_ & NTWK_CTRL_FIRE) {
            // FIRE
            //fire = true;
            //URHO3D_LOGDEBUGF("%s -> FIRE = %l", vehicleName.CString(), controls_.buttons_);
        }
    }

}

/*
/* AUTO-STEERING CODE
    if (toTarget_ != Vector3::ZERO) {
        // Only pass once rigid body is setup
        if (pRigidBody_) {
            // Compute steer force
//            ComputeSteerForce();
            if (force_ != Vector3::ZERO) {

//            force_ = Vector3(1.0f, 0.0f, 1.0f);

                if (wpActiveIndex_ < 0)
                    return;

//                float wpOffsetX = -mapDim_ / 2;
//                float wpOffsetY = -mapDim_ / 2;
                // Convert marker position to world position for track
                //          float wpPosX = (((float)waypoints_->At(wpActiveIndex_).x_ / (float)miniMapWidth_)*mapDim_)+wpOffsetX;
//            float wpPosZ = (((float)waypoints_->At(wpActiveIndex_).z_ / (float)miniMapHeight_)*mapDim_)+wpOffsetY;


                //Vector3 tgt = Vector3(waypoints_->At(wpActiveIndex_).x_, waypoints_->At(wpActiveIndex_).y_, waypoints_->At(wpActiveIndex_).z_);


                // Calculate distance to waypoint
                Vector3 v = vehicle_->GetNode()->GetPosition() - toTarget_;// + Vector3(-1500,0,-1500);
                float steering = v.Normalized().DotProduct((vehicle_->GetNode()->GetDirection()))+0.4f;
/*
                if (steering > 1.0f) {
                    steering = -1.0f;
                }

                if (steering < -1.0f) {
                    steering = 1.0f;
                }
*/


/*    if (autoSteering_) {
        URHO3D_LOGINFOF("***** Player AUTO-STEERING ENABLED - Vehicle Steer [%f]", vehicle_->GetSteering());
        URHO3D_LOGINFOF("***** Player - waypoint [%d]=[%f,%f,%f,%f]", wpActiveIndex_,
                        waypoints_->At(wpActiveIndex_).x_, waypoints_->At(wpActiveIndex_).y_,
                        waypoints_->At(wpActiveIndex_).z_, steering);
        URHO3D_LOGINFOF("***** Player - target =[%f,%f,%f]", toTarget_.x_, toTarget_.y_, toTarget_.z_);

        // Enable auto-steering
        vehicle_->UpdateSteering(steering);
    }*/
//vehicle_->GetRigidBody()->
//            pRigidBody_->ApplyForce(force_);
/*

            Vector3 vel = pRigidBody_->GetLinearVelocity();

            float d = vel.Length();
            if (d < 10.0f) {
                d = 10.0f;
                pRigidBody_->SetLinearVelocity(vel.Normalized() * d);
            } else if (d > 50.0f) {
                d = 50.0f;
                pRigidBody_->SetLinearVelocity(vel.Normalized() * d);
            }

            Quaternion endRot = Quaternion(0, 0, 0);
            Vector3 nVel = vel.Normalized();
            endRot.FromLookRotation(nVel, Vector3::UP);
            endRot = endRot * Quaternion(90, 0, 0);
            pRigidBody_->SetRotation(endRot);

            Vector3 p = pRigidBody_->GetPosition();
            if (p.y_ < 10.0f) {
                p.y_ = 10.0f;
                pRigidBody_->SetPosition(p);
            } else if (p.y_ > 150.0f) {
                p.y_ = 150.0f;
                pRigidBody_->SetPosition(p);
            }
            }


        }
    }

*/
////


void NetworkActor::ComputeSteerForce() {

    //set the force member variable to zero
    force_ = Vector3(0, 0, 0);

    if (!waypoints_)
        return;

    if ((waypoints_->Empty())) {
        return;
    }
    //Attraction force
/*
    Vector3 CoM; //centre of mass, accumulated total
    int nAttract = 0; //count number of neighbours
    //set the force member variable to zero
    force_ = Vector3(0, 0, 0);
    //Search Neighbourhood
    for (int i = 0; i < numberOfBoids; i++)
    {
        //the current boid?
        if (this == &boidList[i]) continue;
        //sep = vector position of this boid from current oid
        Vector3 sep = pRigidBody->GetPosition() - boidList[i].pRigidBody->GetPosition();
        float d = sep.Length(); //distance of boid
        if (d < Range_FAttract)
        {
            //with range, so is a neighbour
            CoM += boidList[i].pRigidBody->GetPosition();
            nAttract++;
        }
    }
    if (nAttract > 0)
    {
        CoM /= nAttract;
        Vector3 dir = (CoM - pRigidBody->GetPosition()).Normalized();
        Vector3 vDesired = dir * FAttract_Vmax;
        force += (vDesired - pRigidBody->GetLinearVelocity())*FAttract_Factor;
    }
    if (nAttract > 5)
    {
        // stop checking once 5 neighbours have been found
        return;
    }

    //seperation force
    Vector3 sepForce;
    int nRepel = 0;
    for (int i = 0; i < numberOfBoids; i++)
    {
        //the current boid?
        if (this == &boidList[i]) continue;
        //sep = vector position of this boid from current oid
        Vector3 sep = pRigidBody->GetPosition() - boidList[i].pRigidBody->GetPosition();
        float d = sep.Length(); //distance of boid
        if (d < Range_FRepel)
        {
            sepForce += (sep / sep.Length());
            nRepel++;
        }
    }
    if (nRepel > 0)
    {
        sepForce *= FRepel_Factor;
        force += sepForce;
    }
    if (nRepel > 5)
    {
        // stop checking once 5 neighbours have been found
        return;
    }
    */

    //Allignment direction
    Vector3 align;
    int nAlign = 0;


    //sep = vector position of this boid from current oid

//    Vector3 sep = pRigidBody->GetPosition() - boidList[i].pRigidBody->GetPosition();
//    float d = sep.Length(); //distance of boid
//    if (d < Range_FRepel)


    Vector3 toTarget;
    if (!waypoints_->Empty()) {

//        URHO3D_LOGDEBUGF("Player::ComputeSteerForce() waypoints -> [%d] -> set to  %d", waypoints_->Size(), wpActiveIndex_);

        // Calculate distance to waypoint
        //toTarget = vehicle_->GetNode()->GetPosition() - waypoints_->At(wpActiveIndex_);
    } else {
        return;
    }


    //    Vector3 dir = sep.Normalized();
//    float d = sep.Length(); // distance of boid

    //float steer = toTarget * speed / d;

    float speed = 1.0f;
    Vector3 desiredVelocity = toTarget.Normalized() * speed;


    /*
    if (d < Range_FAlign)
    {
        align += boidList[i].pRigidBody->GetLinearVelocity();
        nAlign++;
    }*/

//    force_ += ToVector3(ToBtVector3(desiredVelocity) - vehicle_->GetRaycastVehicle()->GetBody()->getLinearVelocity());

    /*
    if (nAlign > 0)
    {
        align /= nAlign;

        Vector3 finalVel = align;

//        force_ += (finalVel - pRigidBody_->GetLinearVelocity()) * FAlign_Factor;
    }
    if (nAlign > 5)
    {
        // stop checking once 5 neighbours have been found
        return;
    }*/
}


void NetworkActor::Fire() {
    if (vehicle_) {
        Fire(toTarget_);
    }
}

void NetworkActor::Fire(Vector3 target) {
    if (vehicle_) {
        Scene *scene = GetScene();

        SharedPtr<Node> n;
        Node *bullet0 = scene->CreateChild("bullet", REPLICATED);
        Missile *newM = bullet0->CreateComponent<Missile>();
        // Set the position and rotation of the bullet
        bullet0->SetWorldPosition(this->GetPosition() + Vector3(0,50.0f,0));
     //   bullet0->SetWorldRotation(Quaternion(Vector3::UP, towards_));
//		bullet0->GetComponent<RigidBody2D>()->SetLinearVelocity(Vector2(towards_.x_, towards_.y_).Normalized() * 10.0f);

        newM->SetProducer(vehicle_->GetNode()->GetID());


        // Store local missile list
        //missileList_.Push(vehicle_->GetNode()->GetID());

//        VariantMap& eventData = GetNode()->GetEventDataMap();
//        eventData["owner"] = SharedPtr<Player>(this);

//        eventData["missileOwner"] = this->GetID();
        //       vehicle_->SendEvent(E_NODECOLLISION, eventData);



        // Set the ownership of the bullet to the Player
//        bullet0->GetComponent<Missile>()->SetProducer(SharedPtr<Node>(vehicle_->GetNode()));

        Node *tgt = scene->CreateChild("missileTarget", REPLICATED);
        //tgt->>SetPosition(0f,0f,0f);
        tgt->SetPosition(target);
        newM->AddTarget(SharedPtr<Node>(tgt));
        // Assign the producer node
        newM->AssignProducer(vehicle_->GetNode()->GetID(),
                             vehicle_->GetRaycastVehicle()->GetNode()->GetPosition() + Vector3(40.0f, 2.0f, 0.0f));
        URHO3D_LOGDEBUGF("NetworkActor::Fire() [%d] -> [%f,%f,%f]", vehicle_->GetNode()->GetID(),
                         newM->GetNode()->GetPosition().x_,
                         newM->GetNode()->GetPosition().y_,
                         newM->GetNode()->GetPosition().z_);


        // }
    }
}


void NetworkActor::DebugDraw() {
    if (!vehicle_)
        return;

    if (GetScene()) {
        DebugRenderer *dbgRenderer = GetScene()->GetComponent<DebugRenderer>();

        if (dbgRenderer) {

            // draw compound shape bounding box (the inertia bbox)
            //Vector3 localExtents = vehicle_->GetBody()->GetCompoundLocalExtents();
            Vector3 localCenter = vehicle_->GetNode()->GetPosition();


            btTransform trans;
            vehicle_->GetBody()->getWorldTransform(trans);
            Vector3 posWS = ToVector3(trans.getOrigin());
            Vector3 centerWS = ToQuaternion(trans.getRotation()) * localCenter;
            //posWS += centerWS;
            Matrix3x4 mat34(posWS, ToQuaternion(trans.getRotation()), 1.0f);


            dbgRenderer->AddLine(posWS, (toTarget_), Color(1.0f, 1.0, 0.0));
            //dbgRenderer->AddBoundingBox(bbox, mat34, color);

            //dbgRenderer->AddLine(posWS, posWS + (node_->GetUp()*100.0f), Color(1.0f, 0.0, 0.0));
            //dbgRenderer->AddLine(posWS, posWS + (node_->GetRight()*100.0f), Color(1.0f, 0.0, 0.0));


//        vehicle_->GetRaycastVehicle()->DrawDebugGeometry(dbgRenderer, false);

//        ToQuaternion(trans.getRotation()),
            // dbgRenderer->AddBoundingBox(bbox, mat34, color);
//        dbgRenderer->AddLine(posWS, posWS + node_->R, color);
            //dbgRenderer->AddLine(posWS, posWS + this->vehicle_->GetNode()->GetDirection() * 40.0f, Color::CYAN);
            //dbgRenderer->AddLine(posWS, toTarget_, Color::YELLOW);
        }
    }
}

void NetworkActor::setSteerSet(bool steerSet) {
    steerSet_ = steerSet;
}

bool NetworkActor::isSteerSet() const {
    return steerSet_;
}

const Vector3 &NetworkActor::getToTarget() const {
    return toTarget_;
}
