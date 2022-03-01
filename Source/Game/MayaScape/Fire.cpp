#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Urho2D/Sprite2D.h>

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/CollisionCircle2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Container/Vector.h>

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>

#include <Urho3D/Math/Quaternion.h>

#include "GameObject.h"
#include "Fire.h"
#include "Toolkit.h"


Fire::Fire(Context* context) : GameObject(context)
{
	SetFuel(140.0f);
	SetSpreadRange(3.0f);
	SetDamage(20.0f);
	duration_ = 0.0f;
}

void Fire::RegisterObject(Context* context)
{
	context->RegisterFactory<Missile>();
}

void Fire::Start()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    /*
	// Scene node
	node_ = GetNode();
	/// Set sprite
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("Urho2D/missile.png");
	StaticSprite2D* staticsprite = node_->CreateComponent<StaticSprite2D>();
	staticsprite->SetSprite(sprite);
	staticsprite->SetBlendMode(BLEND_ALPHA);
	// Rigidbody
	RigidBody2D* rigidbody2d = node_->CreateComponent<RigidBody2D>();
	rigidbody2d->SetBodyType(BT_DYNAMIC);
	// The detection circle of the missile
	CollisionCircle2D* detectionCircle = node_->CreateComponent<CollisionCircle2D>();
	detectionCircle->SetRadius(GetDetectionRange());
	detectionCircle->SetTrigger(true);
	// Subscribe the collision event
	SubscribeToEvent(node_, E_NODEBEGINCONTACT2D, URHO3D_HANDLER(Missile, HandleContactBegin));
	SubscribeToEvent(node_, E_NODEENDCONTACT2D, URHO3D_HANDLER(Missile, HandleContactEnd));
*/

//    std::string nodeName = "missile";
    // Encode owner id in missile name
    node_ = GetScene()->CreateChild("missile-noname");
//    pNode_->SetPosition(Vector3(producer_->GetPosition()));
    node_->SetRotation(Quaternion(0.0f, 0.0f, 0.0f));

//    pObject_ = pNode->CreateComponent<StaticModel>();
 //   pObject->SetModel(pRes->GetResource<Model>("Models/Torus.mdl"));
  //  pObject->SetMaterial(pRes->GetResource<Material>("Materials/Stone.xml"));
   // pObject->SetCastShadows(true);
    pCollisionShape_ = node_->CreateComponent<CollisionShape>();
    pObject_ = node_->CreateComponent<StaticModel>();
    pRigidBody_ = node_->CreateComponent<RigidBody>();

    pRigidBody_->SetMass(1.0f);
    pRigidBody_->SetUseGravity(false);
    pRigidBody_->SetTrigger(true);

//    pCollisionShape = pNode->CreateComponent<CollisionShape>();
//    pCollisionShape->SetBox(Vector3::ONE);

    pRigidBody_->SetEnabled(false);
    pObject_->SetEnabled(false);

    //Node* adjNode = pNode_->CreateChild("AdjNode");
    //adjNode->SetRotation(Quaternion(0.0, 0.0, -90.0f));

//    Model *vehModel = cache->GetResource<Model>("Models/Vehicles/Offroad/Models/offroadVehicle.mdl");

    Model *projModel = cache->GetResource<Model>("Models/AssetPack/cannonball.mdl");

    pObject_->SetModel(projModel);
//    hullObject->SetMaterial(cache->GetResource<Material>("Data/Models/Vehicles/Offroad/Materials/phong1.xml"));
    pObject_->ApplyMaterialList("Models/AssetPack/cannonball.txt");

    pObject_->SetCastShadows(true);

    // set convex hull and resize local AABB.Y size
//    Model *vehColModel = cache->GetResource<Model>("Models/Vehicles/Offroad/Models/offroadVehicle.mdl");
    Model *projColModel = cache->GetResource<Model>("Models/AssetPack/cannonball.mdl");

//    hullObject->GetNode()->SetRotation(Quaternion(0.0, 180.0f, 0.0f));
//    hullObject->GetNode()->SetScale(Vector3(0.01f, 0.01f, 0.01f));
    pObject_->GetNode()->SetScale(6.0f);

   // pCollisionShape_->SetCol
    pCollisionShape_->SetConvexHull(projColModel);
    pCollisionShape_->GetNode()->SetRotation(Quaternion(0.0, 0.0f, -90.0f));
  //  pCollisionShape_->GetNode()->SetScale(Vector3(0.3f, 0.3f, 0.3f));
    pCollisionShape_->GetNode()->SetScale(6.0f);

    // particle emitter
    Node *pNodeEmitter = GetScene()->CreateChild();
//    pNodeEmitter->SetPosition( emitPos );
    pParticleEmitter_ = pNodeEmitter->CreateComponent<ParticleEmitter>();
    pParticleEmitter_->SetEffect( cache->GetResource<ParticleEffect>("Offroad/Particles/Dust.xml"));
    pParticleEmitter_->SetEmitting( false );

//    particleEmitterNodeList_.Push( pNodeEmitter );

    // node collision
    SubscribeToEvent(GetNode(), E_NODECOLLISION, URHO3D_HANDLER(Fire, HandleFireCollision));
//    SubscribeToEvent(GetNode(), E_NODECOLLISIONSTART, URHO3D_HANDLER(Missile, HandleNodeCollision));
}

void Fire::AssignProducer(int producerId, Vector3 spawnLoc) {

    // Update missile name
    Urho3D::String nodeName = Urho3D::String("missile-") + Urho3D::String(producerId);
    producerId_ = producerId;
    node_->SetName(nodeName.CString());
    //    node_->SetName("updated-missile");

//    node_->SetName("missile-" + producerId_);
    node_->SetPosition(spawnLoc);
        GetNode()->SetPosition(node_->GetPosition());
        pRigidBody_->SetPosition(node_->GetPosition());
        //		bullet0->GetComponent<RigidBody2D>()->SetLinearVelocity(Vector2(towards_.x_, towards_.y_).Normalized() * 10.0f);
        URHO3D_LOGDEBUGF("Fire::AssignProducer() -> %s, %d, [%f,%f,%f]", nodeName.CString(), producerId_, node_->GetPosition().x_,
                         node_->GetPosition().y_,
                         node_->GetPosition().z_);

        pRigidBody_->SetEnabled(true);
        pObject_->SetEnabled(true);
}

void Fire::Update(float timeStep)
{

}
/*
 * auto* const physicsWorld = GetScene()->GetComponent<PhysicsWorld>();
PODVector<RigidBody*> hitResults{};
physicsWorld->GetRigidBodies(hitResults, Sphere{ center, radius }, mask);

for (RigidBody* b: hitResults)
    b->ApplyImpulse(...);
 *
 */
void Fire::FixedUpdate(float timeStep)
{

    float MissileLife = 5.0f;
	/// Update the duration
	duration_ += timeStep;
	// Clear the missiles 
	if (duration_ > MissileLife) node_->Remove();


	Vector3 lockTarget;

    if (pRigidBody_) {

        if (targetNodes_.Empty()) return;


        pParticleEmitter_->GetNode()->SetPosition(node_->GetPosition());
        pParticleEmitter_->SetEmitting(true);

        // Set Rotation
        Vector3 velocity = Vector3(pRigidBody_->GetLinearVelocity());
      //  node_->
//edit
        //	node_->SetWorldRotation(Quaternion(Vector3::UP, velocity));
        // Apply thrust to the missile
//        pRigidBody_->ApplyForce(velocity.Normalized() * thrust);

        // Set lock target to vehicle
        lockTarget = targetNodes_[0]->GetPosition();

        // Calculate the force
        Vector3 force = lockTarget - node_->GetPosition();
        force.Normalize();
        // Track it!
        pRigidBody_->ApplyForce(force * fuel);
//            pRigidBody_->ApplyForce(velocity.Normalized()*thrust);

        // Tracking targets

        for (int i = 0; i < targetNodes_.Size(); i++) {
            //Toolkit::Print(targetnodes_[i]->GetName());


            //HeatSource *heatsource = targetnodes_[i]->GetComponent<HeatSource>();
            //float attraction = heatsource->GetAttraction();
            float attraction = 10.0f;

 //           pRigidBody_->ApplyForce(velocity.Normalized()*100.0f);


//            URHO3D_LOGDEBUGF("Missile::FixedUpdate(): pRigidBody_->ApplyForce -> [%s, %f,%f]", attraction, force);

            // If the target is in the boomrange,then boom!
            float distance = (node_->GetPosition() - targetNodes_[i]->GetPosition()).Length();
            if (distance < GetSpreadRange()) {
                GameObject *targetobject = targetNodes_[i]->GetDerivedComponent<GameObject>();

                if (targetobject) {
                    targetobject->Damaged(GetDamage());
                }
                UnsubscribeFromAllEvents();
                node_->Remove();

            }

        }
    }

}

/*
//URHO3D_PARAM(2349, "extraData");
void Missile::HandleNodeCollision(StringHash eventType, VariantMap & eventData)
{
    using namespace NodeCollision;

    // increase score if missile collides with boids
    Node* collidedNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    URHO3D_LOGDEBUGF("***** Missile::HandleMissileCollision() -> collidedNode: [%s]", collidedNode->GetName().CString());


    if (collidedNode->GetName() == "boid")
    {
        // emitt particle effect when boid has been hit
        Node* particle = collidedNode->CreateChild("Particle");
        particle->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        particle->SetScale(2.0f);
        ParticleEmitter* emitter = particle->CreateComponent<ParticleEmitter>();
        emitter->SetEffect(GetSubsystem<ResourceCache>()->GetResource<ParticleEffect>("Particle/Burst.xml"));
    }
}*/

void Fire::HandleFireCollision(StringHash eventType, VariantMap & eventData)
{
    using namespace NodeCollision;

    // increase score if missile collides with boids
    Node* collidedNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    URHO3D_LOGDEBUGF("***** Missile::HandleMissileCollision() -> collidedNode: [%s]", collidedNode->GetName().CString());


    if (collidedNode->GetName() == "boid")
    {
        // emitt particle effect when boid has been hit
        Node* particle = collidedNode->CreateChild("Particle");
        particle->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        particle->SetScale(2.0f);
        ParticleEmitter* emitter = particle->CreateComponent<ParticleEmitter>();
        emitter->SetEffect(GetSubsystem<ResourceCache>()->GetResource<ParticleEffect>("Particle/Burst.xml"));
    }
}

/*
void Missile::HandleContactBegin(StringHash eventType, VariantMap& eventData)
{	
	/// Clients should not update the component on its own
	using namespace NodeBeginContact2D;	
	SharedPtr<Node>othernode(static_cast<Node*>(eventData[P_OTHERNODE].GetPtr()));
	// Do not track the launcher and the launcher's flare
	//if (othernode == GetProducer()) return;
	HeatSource* otherSource = othernode->GetComponent<HeatSource>();	
	//If the other node is not a heatsource then return
	if (!otherSource)return;
	//Toolkit::Print("Source:" + otherSource->GetNode()->GetName()+" Fighter:"+GetProducer()->GetName());
	//Toolkit::Print("target:" + String(otherSource->GetOwner()->GetID()));
	if (otherSource->GetOwner() == GetProducer()) return;	
	// If othernode is a heatsource then push it into the targetqueue;
	targetnodes_.Push(othernode);	
	//Toolkit::Print("got you!");
}

void Missile::HandleContactEnd(StringHash eventType, VariantMap& eventData)
{
	/// Clients should not update the component on its own
	Network* network = GetSubsystem<Network>();
	if (!network->IsServerRunning()) {
		return;
	}

	using namespace Urho3D;
	// If the target is out of tracking range, then erase it.
	using namespace NodeEndContact2D;
	SharedPtr<Node>othernode(static_cast<Node*>(eventData[P_OTHERNODE].GetPtr()));
	HeatSource* heatsource = othernode->GetComponent<HeatSource>();
	if (!heatsource) return;
	//4test Find it in the queue and erase it
	if(targetnodes_.Contains(othernode))	targetnodes_.Erase(	targetnodes_.Find(othernode));
	//Toolkit::Print("lost you!");
}
*/
