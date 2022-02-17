#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include "GameObject.h"
#include "Player.h"

using namespace Urho3D;

class NetworkActor;

class Fire : public GameObject
{
	URHO3D_OBJECT(Fire, LogicComponent);

private:
	/// Fuel power of fire
	float fuel;
	/// The detection range of the missile
	float spreadRange;
	/// Boom Damage
	float damage;
	/// Fire Node
	SharedPtr<Node> node_;
    SharedPtr<RigidBody> pRigidBody_;
    SharedPtr<CollisionShape> pCollisionShape_;
    SharedPtr<StaticModel> pObject_;
    SharedPtr<ParticleEmitter> pParticleEmitter_;

    SharedPtr<Player> owner_;

	/// Target Node
	Vector<SharedPtr<Node>> targetNodes_;

	/// Owner of the Fire
	SharedPtr<Node> producer_;

	/// Owner ID of the fire
	int producerId_;
	/// Time the node has lasted for
	float duration_;

    Vector3 force_;

//    float timer;
    bool active_;

public:

    void AddTarget(SharedPtr<Node> targetnode) { targetNodes_.Push(targetnode); }

	float GetFuel() { return fuel; }
	void SetFuel(float m_fuel) { fuel = m_fuel; }
	float GetSpreadRange() { return spreadRange; }
	void SetSpreadRange(float m_spreadRange) { spreadRange = m_spreadRange; }
	float GetDamage() { return damage; }
	void SetDamage(float m_damage) { damage = m_damage; }
	int GetProducer() { return producerId_; }
    void SetProducer(int producerId) {
        producerId_ = producerId;
    }

    void AssignProducer(int producerId, Vector3 spawnLoc);

    /// Life-cycle function
	/// Construct.
	Fire(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Handle update
	void Update(float timeStep);

	/// Event handle functions
	/// When the missile has detected some heatsource, add it into the tracking queue.
//	void HandleContactBegin(StringHash eventType, VariantMap& eventData);
	/// When the missle lost the target
//	void HandleContactEnd(StringHash eventType, VariantMap& eventData);

    // Player node collision
    void HandleNodeCollision(StringHash eventType, VariantMap & eventData);
    void HandleFireCollision(StringHash eventType, VariantMap &eventData);

};