//
// Copyright (c) 2008-2018 the Urho3D project.
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


#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/Connection.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Scene/SmoothedTransform.h>



#include <MayaScape/ai/evolution_manager.h>
#include <Urho3D/UI/Window.h>
#include <MayaScape/network/NetworkActor.h>
#include <MayaScape/network/csp/CSP_Client.h>
#include <MayaScape/network/csp/CSP_Server.h>
#include <MayaScape/network/csp/CSP_messages.h>
#include "Game.h"
#include "MayaScape/network/Vehicle.h"
#include "Player.h"

#define APP_VERSION "MayaScape v1.0b"
#define STUDIO_VERSION "Monkey Maya Studios"


// Sound fx mappings
#define SOUND_FX_ENGINE_START 0
#define SOUND_FX_ENGINE_REV 1
#define SOUND_FX_TIRE_SKID 2
#define SOUND_FX_ENGINE_BRAKE 3
#define SOUND_FX_ENGINE_ENGINE 4


namespace Urho3D {

class Button;
class Connection;
class Scene;
class Text;
class UIElement;
class Node;
class LineEdit;
//class Controls;
class RigidBody;

// Marker Map Tokens
Vector3 bkgMarkerToken = Vector3(0.5, 1, 0.5); // Black
Vector3 trackMarkerToken = Vector3(0.500000059604645, 1, 0.643137276172638); // #494949
Vector3 treeMarkerToken = Vector3(0.5, 1, 0.594117641448975); // #303030
Vector3 waypointToken = Vector3(0.5, 1.00000035762787, 0.927451014518738); // #dadada
}

class Character2D;
class Player;
class EvolutionManager;

struct ParticlePool {
    bool used; // Is particle emitter used?
    int usedBy; // Node id using particle emitter
    SharedPtr<Node> node; // Scene node
    float lastEmit;
    float currEmit;
    float timeout;
};


class GameResourceRouter : public ResourceRouter
{
    URHO3D_OBJECT(GameResourceRouter, ResourceRouter);

    /// Construct.
    explicit GameResourceRouter(Context* context) :
        ResourceRouter(context)
    {
        //auto* cache = GetSubsystem<ResourceCache>();
        //cache->AddResourceDir("/apk/");
    }

    /// Check if request is for an resource file and reroute to mobile version if necessary.
    void Route(String& name, ResourceRequest requestType) override
    {

        String extension = GetExtension(name);
        if (extension == ".as")
        {
            auto* cache = GetSubsystem<ResourceCache>();
            String replaced = ReplaceExtension(name, ".asc");
            // Note: ResourceCache prevents recursive calls to the resource routers so this is OK, the nested Exists()
            // check does not go through the router again
            if (!cache->Exists(name) && cache->Exists(replaced))
                name = replaced;
        }
    }
};


/*
  __   __
 /  \/  \
/__/ /__/ AYA SCAPE

Written by Ajay Bhaga 2021-2022
*/
class MayaScape : public Game
{
    URHO3D_OBJECT(MayaScape, Game);
public:
    /// Construct.
    explicit MayaScape(Context* context);
    /// Setup after engine initialization and before running the main loop.
    void Start() override;
    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;
    void Stop() override;
    void MoveCamera(float timeStep);

private:

    // Network functions
    void CreateServerSubsystem();
    void CreateUI();
    void CreateClientUI();

   // void SetupViewport();
    void ChangeDebugHudText();
    Button* CreateButton(const String& text, int width);
    void UpdateButtons();

    // CLIENT CALLS
    // Process Client-side Prediction controls
    Controls SampleCSPControls();

    // SERVER CALLS
    // Raycast from mouse position
    bool Raycast(Camera* pCamera, float maxDistance, Vector3& hitPos, Drawable*& hitDrawable);
    // Place object node based on raycast
    void PlaceObject(Camera* pCamera, int type);
    // Generate object
    Node* GenerateObject(Vector3 &pos, Quaternion &rot, int type);

    // Handlers ////
    // Handle AI bots, attaches to FFN and Genetic Algorithm in Evolution Manager
    void HandleAI(float timeStep);

    void HandlePhysicsPreStep(StringHash eventType, VariantMap &eventData);
    void HandleLoginListRefresh(StringHash eventType, VariantMap &eventData);
    void HandleConnect(StringHash eventType, VariantMap& eventData);
    void HandleDisconnect(StringHash eventType, VariantMap& eventData);
    void HandleStartServer(StringHash eventType, VariantMap& eventData);
    void HandleConnectionStatus(StringHash eventType, VariantMap& eventData);
    void HandleClientObjectID(StringHash eventType, VariantMap& eventData);
    void HandleClientIdentity(StringHash eventType, VariantMap& eventData);
    void HandleExit(StringHash eventType, VariantMap& eventData);
    void HandleConnectionFailed(StringHash eventType, VariantMap &eventData);
    void HandleClientDisconnected(StringHash eventType, VariantMap& eventData);
    void HandleServerConnected(StringHash eventType, VariantMap& eventData);
    void HandleServerDisconnected(StringHash eventType, VariantMap& eventData);
    void HandlePlayerRespawned(StringHash eventType, VariantMap& eventData);
    void HandlePlayerLoaded(StringHash eventType, VariantMap& eventData);
    /// Handle log message event; pipe it also to the chat display.
    void HandleLogMessage(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the send button.
    void HandleSend(StringHash eventType, VariantMap& eventData);
    /// Handle an incoming network message.
    void HandleNetworkMessage(StringHash eventType, VariantMap& eventData);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandleRenderUpdate(StringHash eventType, VariantMap &eventData);
    /// Handle the logic post update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    void HandleJoystickHatMove(StringHash eventType, VariantMap &eventData);
    /// Handle the end rendering event.
    void HandleSceneRendered(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    /// Handle the contact begin event (Box2D contact listener).
    void HandleCollisionBegin(StringHash eventType, VariantMap& eventData);
    /// Handle the contact end event (Box2D contact listener).
    void HandleCollisionEnd(StringHash eventType, VariantMap& eventData);
    /// Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle a client connecting to the server.
    void HandleClientConnected(StringHash eventType, VariantMap& eventData);
    /// Handle remote event from server which tells our controlled object node ID.
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    /// Handle 'PLAY' button released event.
    void HandlePlayButton(StringHash eventType, VariantMap& eventData);
    void HandleClosePressed(StringHash eventType, VariantMap& eventData);
    void HandleClientSceneLoaded(StringHash eventType, VariantMap& eventData);
    void HandlePlayerStateUpdate(StringHash eventType, VariantMap& eventData);
    void HandleNetworkUpdateSent(StringHash eventType, VariantMap& eventData);
    void HandleUpdateParticlePool(float timeStep);

    void ShowChatText(const String& row);

    // Creates ////
    /// Construct the scene content.
    //void CreateScene();
    void CreateEmptyScene(Context* context);
    // Viewport
    void InitiateViewport(Context* context, Scene* scene, Camera* camera);
    // Game Map
    void InitiateGameMap(Scene* scene);
    // Init Genetic Algorithm generator: Evolution Manager
    static void InitEvolutionManager();


    SharedPtr<Node> SpawnPlayer(); // Spawn local
    Node* SpawnPlayer(Connection* connection); // Spawn with connection
    NetworkActor* SpawnPlayer(unsigned int id); // Spawn for ai bot
    void DestroyPlayer(Connection* connection); // Clean player with connection

    void StartMultiplayerGameSession();
    bool isMultiplayer_;

    void CreateAgents();

    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();


    /// Handle reloading the scene.
    void ReloadScene(bool reInit);
    void PlaySoundEffect(const String& soundName);
    void PlaySoundEffectGlobal(const String& soundName);
    void PlayMusic(const String &soundName);

    HashMap<String, float> sndFxPlay_;

    void SetParticleEmitter(int hitId, float contactX, float contactY, int type, float timeStep);


    // Update menu state (change visibility of buttons)
    void UpdateUIState(bool state);


    // Display Genetic Algorithm Evolution Manager statistics
    void ShowEvolutionManagerStats();

    void InitMsgWindow(String title, String message);

    void OutputLoginListToConsole();

    String SaveScene(bool initial);

    Controls sample_input();
    void apply_input(Node* playerNode, const Controls& controls);
    void apply_input(Connection* connection, const Controls& controls);

    void UpdateClientObjects();

    String clientName_;

    // Network Actor Hash Maps
    HashMap<Connection*, WeakPtr<ClientObj>> actorMap_;
    HashMap<unsigned int, WeakPtr<ClientObj>> aiActorMap_;
    Connection *lastConnection_; // More recent connected client

    bool started_; // Is Game started?
    Vector<Urho3D::String> loginList_;

    Controls ntwkControls_;
    Controls lastControls_;

    SharedPtr<Window> msgWindow_;

    SharedPtr<Terrain> terrain_;
    Vector<Vector3> trees_;

    Vector<Vector3> waypoints_;
    Vector<Vector3> waypointsWorld_;
    unsigned int wpStartIndex_;

    #define CAMERA_RAY_DISTANCE_LIMIT 70.0f
    // Camera objects
    SharedPtr<Camera> serverCam_;
    SharedPtr<Camera> clientCam_;

    SharedPtr<CollisionShape> terrainShape_;

    Vector<Connection*> sendLoadMsg_;

    // Client-side Prediction
    SharedPtr<CSP_Client> cspClient_;
    SharedPtr<PhysicsWorld> clientPhysicsWorld_;
    SharedPtr<CSP_Server> cspServer_;

    // Camera attributes
    float camSpin_;
    float camSpin2_;
    float camZoom_;

    int camMode_;

    Vector3 heliCamView_; // Helicopter view

    Vector3 flyCam_; // Fly camera position
    Vector3 flyTargetCam_; // Fly camera target position
    Vector3 snapCam_; // Vehicle snap camera position
    SharedPtr<Node> camTargetNode_;

    Vector<Vector3> focusObjects_;
    unsigned int focusIndex_;
    double lastPlayerStateTime_;

    //WeakPtr<TileMap3D> tileMap_;

    /// Flag for drawing debug geometry.
    bool drawDebug_{};
    bool doSpecial_{};
    /// Scaling factor based on tiles' aspect ratio.
    float moveSpeedScale_{};

    SharedPtr<Text> versionText_;
    SharedPtr<Text> studioText_;

    SharedPtr<Text> healthText_;
    SharedPtr<Text> powerBarText_;
    SharedPtr<Text> rpmBarText_;
    SharedPtr<Text> velBarText_;


    /// Strings printed so far.
    Vector<String> chatHistory_;
    /// Chat text element.
    SharedPtr<Text> chatHistoryText_;
    /// Server address / chat message line editor element.
    SharedPtr<LineEdit> textEdit_;

    // Menu background sprite.
    SharedPtr<Sprite> bkgSprite_;
    float bkgAngle_;

    /// Health sprite.
    SharedPtr<Sprite> HealthSprite_;

    /// Powerbar P1 sprite.
    SharedPtr<Sprite> powerBarP1Sprite_;
    /// Powerbar Bkg P1 sprite.
    SharedPtr<Sprite> powerBarBkgP1Sprite_;

    /// RPM P1 sprite.
    SharedPtr<Sprite> rpmBarP1Sprite_;
    /// RPM Bkg P1 sprite.
    SharedPtr<Sprite> rpmBarBkgP1Sprite_;

    /// Velocity P1 sprite.
    SharedPtr<Sprite> velBarP1Sprite_;
    /// Velocity Bkg P1 sprite.
    SharedPtr<Sprite> velBarBkgP1Sprite_;

    /// Mini-map P1 sprite.
    SharedPtr<Sprite> miniMapP1Sprite_;

    /// Mini-map waypoint sprite.
    SharedPtr<Sprite> miniMapWPSprite_;

    /// Mini-map Bkg sprite.
    SharedPtr<Sprite> miniMapBkgSprite_;
    /// Marker map Bkg sprite.
    SharedPtr<Sprite> markerMapBkgSprite_;

    /// Steering wheel
    SharedPtr<Sprite> steerWheelSprite_;

    // BOTS
    // Sprite map of ffn
    HashMap<int, Sprite*> ffnBotSprite_;
    /// Steering wheel
    SharedPtr<Sprite> steerWheelBotSprite_;
    /// Velocity sprite.
    SharedPtr<Sprite> velBarBotSprite_;
    /// Velocity Bkg sprite.
    SharedPtr<Sprite> velBarBkgBotSprite_;

    /// Particle pool
    ParticlePool particlePool_[20];

    #define NUM_DEBUG_FIELDS 16
    // Debug text
    Text* debugText_[NUM_DEBUG_FIELDS];

    #define NUM_STAT_FIELDS 8
    Text* genAlgStatsText_[NUM_STAT_FIELDS];

    WeakPtr<Node> raceTrack_;
    WeakPtr<CollisionShape> trackColShape_;

    WeakPtr<Text>  textKmH_;

    // smooth step
    Quaternion     vehicleRot_;
    Vector3        targetCameraPos_;
    float          springVelocity_;

    // dbg
    WeakPtr<Text>  textStatus_;
    Timer          fpsTimer_;
    int            framesCount_;

    // Network objects
    HashMap<Connection*, WeakPtr<Node> > serverObjects_;
    SharedPtr<UIElement> buttonContainer_;
    SharedPtr<Button> playButton_;
    SharedPtr<Button> disconnectButton_;
    SharedPtr<Button> startServerButton_;
    SharedPtr<Button> exitButton_;

    SharedPtr<Text> instructionsText_;
    Vector<SharedPtr<Text>> hudTextList_;

    VariantMap clientMap_;

    HashMap<Connection*, WeakPtr<Text3D>> actorTextMap_;
    HashMap<unsigned int, WeakPtr<Text3D>> aiActorTextMap_;

    // Line segment for spawning players on track
    Vector3 starAMarker_;
    bool starAMarkerSet_;
    Vector3 starBMarker_;
    bool starBMarkerSet_;


    unsigned int networkActorNodeId_;
    unsigned int vehicleNodeId_;
    bool isServer_;
    int lastNumNodes_;
    bool isSnapped_;

    int splineSize_ = 0;
    SharedPtr<StaticModel> splineModel_;

    bool bkgMusicPlaying_;
    bool bkgMusic_;
    bool sndFx_;

    /// Packets in per second
    SharedPtr<Text> packetsIn_;
    /// Packets out per second
    SharedPtr<Text> packetsOut_;
    /// Packet counter UI update timer
    Timer packetCounterTimer_;

};
