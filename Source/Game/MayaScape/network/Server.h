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

#pragma once

#include <Urho3D/Core/Object.h>
#include <Urho3D/Input/Controls.h>
#include "Vehicle.h"

namespace Urho3D
{
class Scene;
class Connection;
}

using namespace Urho3D;
//=============================================================================
//=============================================================================
class ClientObj;

//=============================================================================
//=============================================================================
// UDP port we will use
const unsigned short SERVER_PORT = 2345;

//=============================================================================
// SERVER EVENT MESSAGES
//=============================================================================
URHO3D_EVENT(E_SERVERSTATUS, ServerStatus)
{
	URHO3D_PARAM(P_STATUS, Status); // unsigned
}

URHO3D_EVENT(E_CLIENTOBJECTID, ClientObjectID)
{
    URHO3D_PARAM(P_NETWORKACTOR, NetworkActorID);         // unsigned
    URHO3D_PARAM(P_VEHICLE, VehicleID);         // unsigned
}

URHO3D_EVENT(E_PLAYERSPAWNED, PlayerSpawned)
{
    URHO3D_PARAM(P_PLAYERID, NetworkActorID);         // unsigned
}

URHO3D_EVENT(E_PLAYERLOADED, PlayerLoaded)
{
    URHO3D_PARAM(P_PLAYERID, NetworkActorID);         // unsigned
}


URHO3D_EVENT(E_LOGINLISTREFRESH, LoginListRefresh)
{
    URHO3D_PARAM(P_LOGINLIST, LoginList);         // String semi-colon delimited
}

URHO3D_EVENT(E_PLAYERSTATE, ClientPlayerState)
{
    URHO3D_PARAM(P_WHEEL_CONTACTS, WheelContactsNum);         // int
    URHO3D_PARAM(P_NO_WHEEL_CONTACT_TIME, NoWheelContactTime);   // float
    URHO3D_PARAM(P_DISTANCE, Distance);   // float
    URHO3D_PARAM(P_LIFE, Life);         // unsigned
    URHO3D_PARAM(P_RPM, RPM);         // float
    URHO3D_PARAM(P_VELOCITY, Velocity);     // float
    URHO3D_PARAM(P_STEER, Steering);         // float
}


//=============================================================================
//=============================================================================
class Server : public Object
{
    URHO3D_OBJECT(Server, Object);
public:

    Server(Context* context);
    virtual ~Server();
    
    void RegisterScene(Scene *scene);
    bool StartServer(unsigned short port);
   // bool Connect(const String &address, unsigned short port, const VariantMap& identity = Variant::emptyVariantMap);
    void Disconnect();

    void InitializeScene(File &file);
    void UpdateActors(float timeStep);

    HashMap<String, Connection*> GetLoginList() { return loginList_; }

    void SetAgents(Vector<String> list) {
        aiBotLoginList_ = list;
    }

    Vector<String> GetAgents() {
        return aiBotLoginList_;
    }

protected:
    void SubscribeToEvents();
    void SendStatusMsg(StringHash msg);
    void SendPlayerStateMsg(Connection* connection);
    void SendLoginListRefreshMsg(Connection* connection);

    /// Handle connection status change (just update the buttons that should be shown.)
    void HandleConnectionStatus(StringHash eventType, VariantMap& eventData);
    /// Handle a client connecting to the server.
    void HandleClientConnected(StringHash eventType, VariantMap& eventData);
    /// Handle a client disconnecting from the server.
    void HandleClientDisconnected(StringHash eventType, VariantMap& eventData);
    /// Handle remote event from server which tells our controlled object node ID.
    void HandleNetworkUpdateSent(StringHash eventType, VariantMap& eventData);
    void HandleClientObjectID(StringHash eventType, VariantMap& eventData);
    void HandleClientIdentity(StringHash eventType, VariantMap& eventData);
    void HandleClientSceneLoaded(StringHash eventType, VariantMap& eventData);

    void OutputLoginListToConsole();

protected:
    SharedPtr<Scene> scene_;
    HashMap<String, Connection*> loginList_;
    Vector<String> aiBotLoginList_;
};
