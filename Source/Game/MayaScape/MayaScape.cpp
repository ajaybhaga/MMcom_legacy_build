/*
  __   __
 /  \/  \
/__/ /__/ AYA SCAPE

     Written by Ajay Bhaga 2021-2022
*/
#include <sstream>
#include <string>
#include <iostream>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/BillboardSet.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/TerrainPatch.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/PhysicsUtils.h>
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/Connection.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>


#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/VectorBuffer.h>

#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/UI/BorderImage.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/Urho2D/ParticleEffect2D.h>
#include <Urho3D/Urho2D/ParticleEmitter2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Urho2D/TileMap2D.h>
//#include <Urho3D/Urho2D/TileMap3D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>
#include <Urho3D/Scene/ValueAnimation.h>

#include "network/Server.h"
#include "network/ClientObj.h"
#include "network/NetworkActor.h"


#include <Urho3D/Physics/RaycastVehicle.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>

#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Urho2D/TileMap2D.h>
//#include <Urho3D/Urho2D/TileMapLayer2D.h>
//#include <Urho3D/Urho2D/TileMap3D.h>
//#include <Urho3D/Urho2D/TileMapLayer3D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

#include <Urho3D/Urho2D/ParticleEffect2D.h>
#include <Urho3D/Urho2D/ParticleEmitter2D.h>


#include <Urho3D/DebugNew.h>

#include "GameController.h"
#include "Utilities2D/Mover.h"
#include "MayaScape.h"
#include <MayaScape/ai/evolution_manager.h>

//#include "RaycastVehicle.h"
#include "MayaScape/network/Vehicle.h"
#include "WheelTrackModel.h"
#include "SmoothStep.h"


// AgentSim shared libs
#include "shared_libs.h"
#include "types.h"
#include "Bullet.h"

#include "boids.h"
#include "../../Urho3D/Input/Controls.h"
#include "../../Urho3D/Scene/SplinePath.h"
#include "../../Urho3D/Resource/ResourceEvents.h"
#include "Missile.h"
#include <MayaScape/Constants.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define CSP_DEBUG

// Identifier for the chat network messages
const int MSG_CHAT = 153;
const int MSG_NODE_ERROR = 156;

#define INGAME_FONT "Fonts/m6x11.ttf"
#define INGAME_FONT2 "Fonts/SinsGold.ttf"
#define INGAME_FONT3 "Fonts/RulerGold.ttf"
#define INGAME_FONT4 "Fonts/HopeGold.ttf"


#define SHOW_STATS 1

//#define GAME_SERVER_ADDRESS "10.0.2.2" // android server address
//#define GAME_SERVER_ADDRESS "192.168.4.58" // neko
//#define GAME_SERVER_ADDRESS "192.168.4.77" // lady
// At-home local server
//#define GAME_SERVER_ADDRESS "localhost"
//#define GAME_SERVER_ADDRESS "www.monkeymaya.com"

std::vector<std::string> gameServers = {
"10.0.2.2", // android server address
"192.168.4.58", // neko (dev)
"192.168.4.77", // lady (remote local game server)
// At-home local server
"localhost", // local game server
"www.monkeymaya.com", // remote game server
};

// TODO: need to add increased move step to network actor (on remote server)

std::vector<std::string> bzRadioTracksArtistName = {
        "Bhagatriks",
        "Bhagatriks",
        "Bhagatriks",
        "Bhagatriks",
        "Bhagatriks",
        "Bhagatriks",
        "Bhagatriks",
        "MonkeyMaya"
};

std::vector<std::string> bzRadioTracksArtistLink = {
        "IG: @bhagatriks",
        "IG: @bhagatriks",
        "IG: @bhagatriks",
        "IG: @bhagatriks",
        "IG: @bhagatriks",
        "IG: @bhagatriks",
        "IG: @bhagatriks",
        "Free cruising!"
};


std::vector<std::string> bzRadioTracksTrackName = {
        "BZradio/110-walk-away.ogg",
        "BZradio/100-miami-ride.ogg",
        "BZradio/105-hotsun-lp.ogg",
        "BZradio/110-happy-saturday.ogg",
        "BZradio/120-flovibe.ogg",
        "BZradio/130-breakabeat.ogg",
        "BZradio/150-trappp.ogg",
        "BZradio/mm-theme-rp01.ogg"
};

std::vector<std::string> driveAudioEffect = {
        "drive/008157265-car-engine-start.wav",
        "drive/096202521-jeep-grand-cherokee-47-engine-.wav",
        "drive/102991590-car-skid-tires-dirt-without-en.wav",
        "drive/000788417-vintage-army-jeep.wav"
};

int currTrack_ = 0;


/// [AB] STABILITY NOTES //

// -> Added safety in engine code to detect bad population and pause evolving on bad population
// Migrate evolution code from Server base engine code
/* Genetic Algorithm throws asserts for too small population size
 * Move spawner to agent who joins and spawns
 *
 */

///

int numOfBoidsets = 10; // needs to be an even number for the boid splitting to work properly
int updateCycleIndex = 0;
BoidSet boids[10]; // 10 x 20 boids


URHO3D_DEFINE_APPLICATION_MAIN(MayaScape)

MayaScape::MayaScape(Context *context) :
        Game(context),
        networkActorNodeId_(0), vehicleNodeId_(0), lastNumNodes_(0), camSpin_(0), camSpin2_(0), camZoom_(20.0f),
        flyCam_(Vector3(0,0,0)),
        flyTargetCam_(Vector3(1.0,0,0)),
        snapCam_(Vector3(0,0,0)),
        lastPlayerStateTime_(0),
        isServer_(false),
        isSnapped_(false),
        drawDebug_(true),
        bkgMusic_(true),
        bkgMusicPlaying_(false),
        sndFx_(true),
        starAMarker_(Vector3(0,0,0)),
        starBMarker_(Vector3(0,0,0)),
        starAMarkerSet_(false),
        starBMarkerSet_(false),
        levelLoading_(false)
{

}

void MayaScape::Setup() {
    Game::Setup();
}

// SETUP AI BOTS
void MayaScape::InitEvolutionManager() {

    std::cout << "Evolution Manager -> starting..." << std::endl;
    EvolutionManager::getInstance()->startEvolution();
    EvolutionManager *evolutionManager = EvolutionManager::getInstance();

    // Create shape for each agent
    std::vector<Agent *> agents = evolutionManager->getAgents();
    std::cout << "Evolution Manager -> number of agents = " << agents.size() << std::endl;

    for (int i = 0; i < agents.size(); i++) {
        // Randomly place agents
        //       agents[i]->setPosition(cyclone::Vector3(rd(), rd(), rd()));
    }

    /*
    // Test Case 1
    auto genotype = new Genotype();
    std::cout << "Generating random genotype..." << std::endl;
    genotype = genotype->generateRandom(10, 0.4, 20.4);
    genotype->outputToConsole();
    genotype->saveToFile("genotype01.data");
    std::cout << "Genotype saved to disk." << std::endl;

    std::cout << "Loading genotype from disk..." << std::endl;
    genotype = genotype->loadFromFile("genotype01.data");
    std::cout << "Loaded genotype from disk." << std::endl;
    */

}


void MayaScape::ShowEvolutionManagerStats() {
    std::vector<Agent *> agents = EvolutionManager::getInstance()->getAgents();
    std::vector<AgentController *> controllers = EvolutionManager::getInstance()->getAgentControllers();

    char buffer[255];
    int aliveCount = EvolutionManager::getInstance()->agentsAliveCount;
    const int maxRows = 20;
    char *strText[maxRows];

    for (int i = 0; i < maxRows; i++) {
        strText[i] = new char[80];
    }

    for (int i = 0; i < maxRows; i++) {

        switch (i) {

            case maxRows - 1:
                sprintf(strText[i], "%d alive out of %d population.", aliveCount, agents.size());
                break;
            case maxRows - 2:
                sprintf(strText[i], "%d generation out of %d generations.",
                        EvolutionManager::getGeneticAlgorithm()->generationCount_, RestartAfter);
                break;
            case maxRows - 3:
                sprintf(strText[i], "======actorNode = scene_->GetChild(server->GetClientHashA().ToHash());====================================================================");
                break;
            case maxRows - 4:
                sprintf(strText[i], "agent[0].timeSinceLastCheckpoint: %f",
                        controllers[0]->getTimeSinceLastCheckpoint());
                break;
            default:
                sprintf(strText[i], "");
                break;

        }

        //       if (strText[i])
//            renderText(5, 5 + (10 * i), strText[i], NULL);

    }

    for (int i = 0; i < maxRows; i++) {
        delete strText[i];
    }
}

void MayaScape::Start() {

    for (int i = 0; i < sizeof(particlePool_) / sizeof(*particlePool_); i++) {
        particlePool_[i].used = false;
        particlePool_[i].usedBy = -1;
    }

    // Don't start until past menu
    started_ = false;

    // Execute base class startup
    Game::Start();

    // rand seed
    SetRandomSeed(Time::GetSystemTime());

    CreateServerSubsystem();

    context_->RegisterSubsystem(new GameController(context_));

    // Reset focus index
    focusIndex_ = 0;

    // Generate UI client for network management
    CreateUI();

    // Create empty scene
    CreateEmptyScene(context_);

    // Enable for 3D sounds to work (attach to camera node)
    SoundListener *listener = scene_->CreateComponent<SoundListener>(LOCAL);
    GetSubsystem<Audio>()->SetListener(listener);

    // you can set master volumes for the different kinds if sounds, 30% for music
    GetSubsystem<Audio>()->SetMasterGain(SOUND_MUSIC, 0.3);
    GetSubsystem<Audio>()->SetMasterGain(SOUND_EFFECT, 0.6);

    // Theme song
    String trackName = "Sounds/BZradio/mm-theme-rp01.ogg";
            //bzRadioTracksTrackName[7].c_str();
    PlayMusic(trackName);


    // Start in menu mode
    //UpdateUIState(false);

    /*
    // Create boids
    for (int i = 0; i < numOfBoidsets; i++)
    {
        boids[i].Initialise(cache, scene_, Vector3(0.0f, 20.0f, 0.0f));
    }*/

    // targetCameraPos_ = Vector3(0.0f, 40.0f, CAMERA_DISTANCE);
    fpsTimer_.Reset();
    framesCount_ = 0;

    // Hook up to the frame update events
    SubscribeToEvents();

    ChangeDebugHudText();

    Game::InitMouseMode(MM_FREE);
}


void MayaScape::Stop() {

    // Free evolution manager
    EvolutionManager::clean();

    // Dump engine resources
    Game::Stop();
}

void MayaScape::CreateAgents() {
    // Create initial set of agents

    for (int i = 0; i < EvolutionManager::getInstance()->getAgents().size(); i++) {
        if (!EvolutionManager::getInstance()->getNetworkActors().empty())
            EvolutionManager::getInstance()->getNetworkActors()[0]->Kill();
    }

    ResourceCache *cache = GetSubsystem<ResourceCache>();
    for (int i = 0; i < EvolutionManager::getInstance()->getAgents().size(); i++) {

        URHO3D_LOGDEBUGF("CreateAgents -> SpawnPlayer: %d", (i));
        // Spawn ai bot and generate NetworkActor
        EvolutionManager::getInstance()->getNetworkActors().push_back(SpawnPlayer(i));

    }
}

void MayaScape::CreateEmptyScene(Context* context) {
    scene_ = MakeShared<Scene>(context_);
    scene_->SetName("MainScene");
    scene_->SetUpdateEnabled(false);


    /*
    scene_->CreateComponent<Octree>();
    float minUnivSpace = -25000.0f;
    float maxUnivSpace = 25000.0f;
    scene_->GetComponent<Octree>()->SetSize(
            BoundingBox(minUnivSpace, maxUnivSpace), 3);
*/
    //DebugRenderer *dbgRenderer = scene_->CreateComponent<DebugRenderer>();
    // Server will authoratively managed physics locally
    PhysicsWorld *physicsWorld = scene_->CreateComponent<PhysicsWorld>(LOCAL);
    physicsWorld->SetFps(60);
    //physicsWorld->DrawDebugGeometry(true);
    //physicsWorld->SetDebugRenderer(dbgRenderer);
    // Disable interpolation (need determinism)
    physicsWorld->SetInterpolation(false);

    // server requires client hash and scene info
    Server *server = GetSubsystem<Server>();
    server->RegisterScene(scene_);

}

void MayaScape::UpdateUIState(bool state) {

    // Do the opposite for menu
    versionText_->SetVisible(!state);
    gameNameText_->SetVisible(!state);
    //studioText_->SetVisible(!state);
   // instructionsText_->SetVisible(!state);
  //  hudText_->SetVisible(!state);
    buttonContainer_->SetVisible(!state);

    bkgSprite_->SetVisible(!state);

    // On client
    if (!isServer_) {

        if (powerBarP1Sprite_) {
            // Create sprite and add to the UI layout
            powerBarP1Sprite_->SetVisible(state);
            powerBarBkgP1Sprite_->SetVisible(state);
            rpmBarP1Sprite_->SetVisible(state);
            rpmBarBkgP1Sprite_->SetVisible(state);
            velBarP1Sprite_->SetVisible(state);
            velBarBkgP1Sprite_->SetVisible(state);
            //miniMapP1Sprite_->SetVisible(state);
            //miniMapWPSprite_->SetVisible(state);
            //miniMapBkgSprite_->SetVisible(state);
            //markerMapBkgSprite_->SetVisible(state);
            steerWheelSprite_->SetVisible(state);
            steerActorSprite_->SetVisible(state);


            // Create the UI for displaying the remaining lifes
//    lifeUI->SetVisible(false);
//    auto *lifeText = lifeUI->CreateChild<Text>("LifeText2");

            powerBarText_->SetVisible(state);
            rpmBarText_->SetVisible(state);
            velBarText_->SetVisible(state);


            // Debug text
            for (int i = 0; i < NUM_DEBUG_FIELDS; i++) {
                debugText_[i]->SetVisible(state);
            }

            // Radio text
            for (int i = 0; i < NUM_RADIO_TRACK_FIELDS; i++) {
                radioText_[i]->SetVisible(state);
            }


            packetsIn_->SetVisible(state);
            packetsOut_->SetVisible(state);
        }

    } else {
        // On server

        // Debug text
        for (int i = 0; i < NUM_DEBUG_FIELDS; i++) {
            debugText_[i]->SetVisible(!state);
        }

        packetsIn_->SetVisible(!state);
        packetsOut_->SetVisible(!state);
    }
}

Node* MayaScape::GenerateObject(Vector3 &pos, Quaternion &rot, int type)
{
    auto *cache = GetSubsystem<ResourceCache>();
    Node* newObjNode_ = scene_->CreateChild("ServerGeneratedObject", REPLICATED);
    // model
    StaticModel* ballModel = newObjNode_->GetOrCreateComponent<StaticModel>();

    String modelStr = "";

    switch (type) {
        case 0: {
            modelStr = "Models/Sphere.mdl";
            break;
        }
        case 1: {
            modelStr = "Models/Sphere.mdl";
            break;
        }
    }

    newObjNode_->SetPosition(pos+Vector3(0,10,0));
    newObjNode_->SetRotation(rot);
    newObjNode_->SetScale(30.0f);
    ballModel->SetModel(cache->GetResource<Model>(modelStr));
    ballModel->SetCastShadows(true);


    scene_->MarkReplicationDirty(newObjNode_);

    return newObjNode_;
}

void MayaScape::PlaceObject(Camera* pCamera, int type)
{
    Vector3 hitPos;
    Drawable* hitDrawable;

    //if (Raycast(pCamera, 250.0f, hitPos, hitDrawable))

    // Not hitting anything
    if (Raycast(pCamera, 2500000.0f, hitPos, hitDrawable))
    {
        Node* targetNode = hitDrawable->GetNode();
        Quaternion q = targetNode->GetRotation();
        Node* node = GenerateObject(hitPos, q, 0);
        URHO3D_LOGDEBUGF("MayaScape::PlaceObject()->GenerateObject() @ [%f, %f, %f]", hitPos.x_, hitPos.y_, hitPos.z_);
    }
}

bool MayaScape::Raycast(Camera* pCamera, float maxDistance, Vector3& hitPos, Drawable*& hitDrawable)
{
    hitDrawable = nullptr;

    auto* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();

    auto* graphics = GetSubsystem<Graphics>();
    auto* camera = pCamera;
    // Adjust with delta for mouse

    Input *input = GetSubsystem<Input>();

    IntVector2 mouseMove = input->GetMousePosition();

    Ray cameraRay = camera->GetScreenRay((float)(mouseMove.x_) / graphics->GetWidth(), (float)(mouseMove.y_) / graphics->GetHeight());
    // Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY);


    scene_->GetComponent<Octree>()->RaycastSingle(query);

    if (results.Size())
    {
        RayQueryResult& result = results[0];
        hitPos = result.position_;
        hitDrawable = result.drawable_;
        return true;
    }

    return false;
}

void MayaScape::HandleResourceBackgroundLoaded(StringHash eventType, VariantMap& eventData) {

    using namespace ResourceBackgroundLoaded;

    String progressStr = String("Loading: ") + String(Round(scene_->GetAsyncProgress() * 100.0f));

    int sticks = Round(scene_->GetAsyncProgress() * (float) 40);
    String progressBar = "";
    for (int i = 0; i < sticks; i++) {
        progressBar += "|";
    }
    progressText_->SetText(progressBar);


    auto* resource = static_cast<Resource*>(eventData[P_RESOURCE].GetPtr());
    String resourceName = resource->GetName();
    progressResText_->SetText(progressStr + String("% ") + resourceName);
    progressResText_->SetVisible(levelLoading_);
}


void MayaScape::HandleClientResourceLoadAttempt(StringHash eventType, VariantMap& eventData) {

    using namespace LoadSucceed;

    String progressStr = String("Load: ") + String(Round(0 * 100.0f));

    int sticks = Round(0 * (float) 40);
    String progressBar = "";
    for (int i = 0; i < sticks; i++) {
        progressBar += "|";
    }
    progressText_->SetText(progressBar);


    String resourceName = eventData[P_RESOURCENAME].GetString();
    //String resourceName = resource->GetName();
    progressResText_->SetText(progressStr + String("% ") + resourceName);
    progressText_->SetVisible(true);
    progressResText_->SetVisible(true);



    if (clientLevelLoading_) {
        // Show updated frame
 //       engine_->SetPauseMinimized(true);
 //       engine_->SetPauseMinimized(true);
       // engine_->RunFrame();
        engine_->Update();
       engine_->Render();


        // Update load progress
        loadProgress_ = scene_->GetAsyncProgress();
    }




}

void MayaScape::HandleClientResourceLoadFinished(StringHash eventType, VariantMap& eventData) {

    using namespace LoadSucceed;

    String progressStr = String("Finished: ") + String(Round(1 * 100.0f));

    int sticks = Round(1 * (float) 40);
    String progressBar = "";
    for (int i = 0; i < sticks; i++) {
        progressBar += "|";
    }
    progressText_->SetText(progressBar);


    String resourceName = eventData[P_RESOURCENAME].GetString();
    //String resourceName = resource->GetName();
    progressResText_->SetText(progressStr + String("% ") + resourceName);
    progressText_->SetVisible(true);
    progressResText_->SetVisible(true);

    if (clientLevelLoading_) {
        // Show updated frame
        //engine_->SetPauseMinimized(true);
       // engine_->RunFrame();
        engine_->Update();
        engine_->Render();

        // Update load progress
        loadProgress_ = scene_->GetAsyncProgress();
    }

}



void MayaScape::HandleClientSceneLoaded(StringHash eventType, VariantMap& eventData)
{
    // SERVER CODE

    using namespace ClientSceneLoaded;
    URHO3D_LOGINFO("HandleClientSceneLoaded");
    URHO3D_LOGINFOF("Client: Scene checksum -> %s", ToStringHex(scene_->GetChecksum()).CString());

    // Client stores client object id
    auto *client = static_cast<Connection *>(eventData[P_CONNECTION].GetPtr());

    URHO3D_LOGINFOF("Client: Client info -> connected %d", client->IsConnected());

    // Once client joins start
    started_ = true;


    if (actorMap_[client]) {
        // Enable for 3D sounds to work (attach to camera node)
        SoundListener *listener = actorMap_[client]->GetNode()->CreateComponent<SoundListener>(REPLICATED);
        GetSubsystem<Audio>()->SetListener(listener);

        // you can set master volumes for the different kinds if sounds, 30% for music
        GetSubsystem<Audio>()->SetMasterGain(SOUND_MUSIC, 0.3);
        GetSubsystem<Audio>()->SetMasterGain(SOUND_EFFECT, 0.6);

    }

    // Server: send a delayed loaded message to client
    sendLoadMsg_.Push(client);


}

void MayaScape::SubscribeToEvents() {

    // Subscribe to UI element events
    //SubscribeToEvent(textEdit_, E_TEXTFINISHED, URHO3D_HANDLER(MayaScape, HandleSend));
//    SubscribeToEvent(sendButton_, E_RELEASED, URHO3D_HANDLER(MayaScape, HandleSend));

    // Last chance to update before back buffer flip
//    SubscribeToEvent(E_ENDRENDERING, URHO3D_HANDLER(MayaScape, HandleEndRendering));
    SubscribeToEvent(E_BEGINRENDERING, URHO3D_HANDLER(MayaScape, HandleEndRendering));
    //E_BEGINRENDERING

    // Server asset loading
    SubscribeToEvent(E_RESOURCEBACKGROUNDLOADED, URHO3D_HANDLER(MayaScape, HandleResourceBackgroundLoaded));

    // Client asset loading
    SubscribeToEvent(E_LOADSUCCEED, URHO3D_HANDLER(MayaScape, HandleClientResourceLoadFinished));
    SubscribeToEvent(E_LOADATTEMPT, URHO3D_HANDLER(MayaScape, HandleClientResourceLoadAttempt));

    // Subscribe to log messages so that we can pipe them to the chat window
    SubscribeToEvent(E_LOGMESSAGE, URHO3D_HANDLER(MayaScape, HandleLogMessage));

    // Subscribe to network events
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(MayaScape, HandleNetworkMessage));
    SubscribeToEvent(E_CLIENTSCENELOADED, URHO3D_HANDLER(MayaScape, HandleClientSceneLoaded));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(MayaScape, HandleClientConnected));


    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(MayaScape, HandlePostUpdate));

    // Subscribe to button actions
    SubscribeToEvent(playButton_, E_RELEASED, URHO3D_HANDLER(MayaScape, HandlePlayButton));
//    SubscribeToEvent(connectButton_, E_RELEASED, URHO3D_HANDLER(MayaScape, HandleConnect));
    SubscribeToEvent(disconnectButton_, E_RELEASED, URHO3D_HANDLER(MayaScape, HandleDisconnect));
    SubscribeToEvent(startServerButton_, E_RELEASED, URHO3D_HANDLER(MayaScape, HandleStartServer));
    SubscribeToEvent(exitButton_, E_RELEASED, URHO3D_HANDLER(MayaScape, HandleExit));

    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(MayaScape, HandleConnectionFailed));

    // Subscribe to server events
    SubscribeToEvent(E_SERVERSTATUS, URHO3D_HANDLER(MayaScape, HandleConnectionStatus));

    // Subscribe to player state events
    SubscribeToEvent(E_PLAYERSTATE, URHO3D_HANDLER(MayaScape, HandlePlayerStateUpdate));
    // Events sent between client & server (remote events) must be explicitly registered or else they are not allowed to be received
    GetSubsystem<Network>()->RegisterRemoteEvent(E_PLAYERSTATE);

    SubscribeToEvent(E_CLIENTOBJECTID, URHO3D_HANDLER(MayaScape, HandleClientObjectID));
    // Events sent between client & server (remote events) must be explicitly registered or else they are not allowed to be received
    GetSubsystem<Network>()->RegisterRemoteEvent(E_CLIENTOBJECTID);

    SubscribeToEvent(E_LOGINLISTREFRESH, URHO3D_HANDLER(MayaScape, HandleLoginListRefresh));
    // Events sent between client & server (remote events) must be explicitly registered or else they are not allowed to be received
    GetSubsystem<Network>()->RegisterRemoteEvent(E_LOGINLISTREFRESH);


    SubscribeToEvent(E_NETWORKUPDATESENT, URHO3D_HANDLER(MayaScape, HandleNetworkUpdateSent));

    // Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(MayaScape, HandlePostUpdate));

    // Subscribe to PostRenderUpdate to draw debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(MayaScape, HandlePostRenderUpdate));

  //  SubscribeToEvent(E_JOYSTICKHATMOVE, URHO3D_HANDLER(MayaScape, HandleJoystickHatMove));


    // Subscribe to fixed timestep physics updates for setting or applying controls
    SubscribeToEvent(E_PHYSICSPRESTEP, URHO3D_HANDLER(MayaScape, HandlePhysicsPreStep));
}

// CLIENT CODE
// Sample client input
Controls MayaScape::SampleCSPControls()
{
    auto ui = GetSubsystem<UI>();
    auto input = GetSubsystem<Input>();

    Controls controls; // Return data
    GameController *gameController = GetSubsystem<GameController>();
    // Retrieve controller inputs ** NOTE this will clear existing buttons (DO FIRST)
    gameController->UpdateControlInputs(ntwkControls_);

    // Copy mouse yaw
    controls.yaw_ = yaw_;

    // set controls and pos
    ntwkControls_.yaw_ = yaw_;

    // axis
    const StringHash axisHashList[SDL_CONTROLLER_AXIS_MAX / 2] = {VAR_AXIS_0, VAR_AXIS_1, VAR_AXIS_2};
    // left stick - vehicle
    Variant lStick = ntwkControls_.extraData_[VAR_AXIS_0];
    Vector2 lAxisVal = lStick.GetVector2();

    // right stick
    Variant rStick = ntwkControls_.extraData_[VAR_AXIS_1];
    Vector2 rAxisVal = rStick.GetVector2();

    joySteer_ = lStick.GetVector2();

    float actorAccel = rStick.GetVector2().y_ * 1.25f;

    // Set yaw to angle from axis calculation
    float joyAngle = 0;

    // Calculate joyAngle
    float theta = atan2(lAxisVal.y_,lAxisVal.x_);
    float thetaAng = theta*180.0f/M_PI;
    float delta = 0;
    float angle = 0;
    if (lAxisVal.x_ > 0) {
        if (lAxisVal.y_ < 0) {
            // x > 0 and y < 0
            delta = 360.0f;
            angle = delta + thetaAng;
        } else {
            // x > 0 and y > 0
            delta = 0;
            angle = delta + thetaAng;
        }
    } else {
        // x < 0
        if (lAxisVal.y_ < 0) {
            // x < 0 and y < 0
            delta = 360.0f;
            angle = delta + thetaAng;
        } else {
            // x < 0 and y > 0
            delta = 0;
            angle = delta + thetaAng;
        }
    }
    joyAngle = angle;

    // Rotate joy entry to align to screen
    joyAngle -= 180.0f;

    ntwkControls_.yaw_ = joyAngle;

    bool accel = (input->GetKeyDown(Urho3D::KEY_AC_FORWARD) || input->GetKeyDown(KEY_W) || ntwkControls_.IsDown(BUTTON_B) || (actorAccel < -0.9f));
    bool fire = input->GetKeyDown(KEY_SPACE) || ntwkControls_.IsDown(BUTTON_A);
    bool enter = input->GetKeyDown(KEY_F) || ntwkControls_.IsDown(BUTTON_Y);
    bool brake = (input->GetKeyDown(KEY_S) || ntwkControls_.IsDown(BUTTON_X));
    if (accel) {
        // Rev
        PlaySoundEffect(driveAudioEffect[SOUND_FX_ENGINE_REV].c_str());
    }

    if (brake) {
        // Brake
        PlaySoundEffect(driveAudioEffect[SOUND_FX_ENGINE_BRAKE].c_str());
    }

    bool left = input->GetKeyDown(KEY_A) || input->GetKeyDown(Urho3D::KEY_LEFT) || (lAxisVal.x_ < -0.4f);
    bool right = input->GetKeyDown(KEY_D) || input->GetKeyDown(Urho3D::KEY_RIGHT) || (lAxisVal.x_ > 0.4f);

    ntwkControls_.Set(NTWK_CTRL_FORWARD, accel);
    ntwkControls_.Set(NTWK_CTRL_BACK, brake);
    ntwkControls_.Set(NTWK_CTRL_LEFT, left);
    ntwkControls_.Set(NTWK_CTRL_RIGHT, right);
    ntwkControls_.Set(NTWK_CTRL_ENTER, enter);
    ntwkControls_.Set(NTWK_CTRL_FIRE, fire);

    // Set controls to updated ntwkControls
    controls = ntwkControls_;

    //csp->predict();

    return controls;
}

void MayaScape::HandleAI(float timeStep) {
    auto *input = GetSubsystem<Input>();

    // Iterate through agent controllers and apply update
    std::vector<Agent *> agents = EvolutionManager::getInstance()->getAgents();
    std::vector<AgentController *> controllers = EvolutionManager::getInstance()->getAgentControllers();

    for (int i = 0; i < EvolutionManager::getInstance()->getAgents().size(); i++) {

        bool dead = (!EvolutionManager::getInstance()->getNetworkActors()[i]);
        if (!dead) {
            String botName = EvolutionManager::getInstance()->getNetworkActors()[i]->GetUserName();
            AgentController *controller = EvolutionManager::getInstance()->getAgentControllers()[i];
            // Process sensor inputs through ffn and apply calculated inputs
            controller->update(timeStep);

            if (!controller->isAlive()) {
                if (EvolutionManager::getInstance()->getNetworkActors()[i]) {
                    EvolutionManager::getInstance()->getNetworkActors()[i]->Kill();
                    EvolutionManager::getInstance()->getNetworkActors()[i] = nullptr;
                    scene_->MarkNetworkUpdate();
                }
            }
        } else {
            // dead

            // Found a dead agent, respawn

            // Wait until time for respawn
            agents[i]->setRespawnTime(agents[i]->getRespawnTime() + timeStep);

            if (agents[i]->getRespawnTime() > 30.0f) {
                // respawn?
                URHO3D_LOGDEBUGF("CreateAgents -> SpawnPlayer: %d", (i));
                // Spawn ai bot and generate NetworkActor
                EvolutionManager::getInstance()->getNetworkActors()[i] = SpawnPlayer(i);
                agents[i]->setRespawnTime(0);
            }
        }
    }

}

void MayaScape::HandlePhysicsPreStep(StringHash eventType, VariantMap &eventData) {

    // Skip on loading
    if (levelLoading_) return;
    if (clientLevelLoading_) return;

    const float MOVE_TORQUE = 3.0f;

    using namespace Update;
    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    // This function is different on the client and server. The client collects controls (WASD controls + yaw angle)
    // and sets them to its server connection object, so that they will be sent to the server automatically at a
    // fixed rate, by default 30 FPS. The server will actually apply the controls (authoritative simulation.)
    auto network = GetSubsystem<Network>();
    auto serverConnection = network->GetServerConnection();

    RigidBody *body;
    // Rigid Body change function for applying forces
    auto change_func = [&](Vector3 force) {
        body->ApplyForce(force);
        body->ApplyTorque(force);
    };

    // Handle AI bots
    HandleAI(timeStep);

    // CLIENT CODE
    if (serverConnection)
    {
            // Predict locally
            auto applyControls = [&](const Controls& controls) {

                // Retrieve based on username
                String name = serverConnection->identity_["UserName"].GetString();

                String actorName = String("actor-") + name;
                Node *actorNode = scene_->GetChild(actorName);

                String vehicleName = String("vehicle-") + name;
                Node *vehicleNode = scene_->GetChild(vehicleName);

                    if (actorNode) {

                        // On change of controls, send update
                        serverConnection->SetControls(ntwkControls_);

                        // On change of controls, send update
                        if (lastControls_.buttons_ != ntwkControls_.buttons_) {
                            URHO3D_LOGINFOF("CLIENT: SET controls -> %s",
                                            ToStringHex(ntwkControls_.buttons_).CString());
                        }

                        // Store last control for next iteration
                        lastControls_ = ntwkControls_;


                        // Apply local predictive physics until we get next update from server

                        // CLIENT SECTION
                        // Client: collect controls
                        // Torque is relative to the forward vector
                        Quaternion rotationF(0.0f, ntwkControls_.yaw_, 0.0f);
/*
                        // Apply local physics change (Client-Side Prediction)
                        if (ntwkControls_.buttons_ & NTWK_CTRL_FORWARD)
                            change_func(rotationF * Vector3::RIGHT * MOVE_TORQUE);
                        if (ntwkControls_.buttons_ & NTWK_CTRL_BACK)
                            change_func(rotationF * Vector3::LEFT * MOVE_TORQUE);
                        if (ntwkControls_.buttons_ & NTWK_CTRL_LEFT)
                            change_func(rotationF * Vector3::FORWARD * MOVE_TORQUE);
                        if (ntwkControls_.buttons_ & NTWK_CTRL_RIGHT)
                            change_func(rotationF * Vector3::BACK * MOVE_TORQUE);*/

                    }
            };


        // In case the server wants to do position-based interest management using the NetworkPriority components,
        // we should also tell it our observer (camera) position.
        serverConnection->SetPosition(cameraNode_->GetPosition());

        if (cspClient_->currentControls == nullptr)
        {
            // Local client-side prediction
            auto controls = SampleCSPControls();

            // Predict locally
            applyControls(controls);

            // Sample controls when not running prediction
            cspClient_->addInput(controls);
        }
        else {
            // Not predicting
            applyControls(*cspClient_->currentControls);
        }
    }


    // SERVER CODE
    else if (network->IsServerRunning())
    {

        // Server: get local input and control server fly cam
        auto *input = GetSubsystem<Input>();

        float flySpeed = 6.0f;

        // Move Cam
        if (input->GetKeyDown(KEY_W)) {
            flyCam_ = flyCam_ - Vector3(flySpeed, 0, 0);
        }

        if (input->GetKeyDown(KEY_A)) {
            flyCam_ = flyCam_ - Vector3(0, 0, -flySpeed);
        }

        if (input->GetKeyDown(KEY_D)) {
            flyCam_ = flyCam_ - Vector3(0, 0, flySpeed);
        }

        if (input->GetKeyDown(KEY_S)) {
            flyCam_ = flyCam_ - Vector3(-flySpeed, 0, 0);
        }

        if (input->GetKeyDown(KEY_Q)) {
            flyCam_ = flyCam_ - Vector3(0, -flySpeed, 0);
        }

        if (input->GetKeyDown(KEY_E)) {
            flyCam_ = flyCam_ - Vector3(0, flySpeed, 0);
        }

        // Move Cam Target
        if (input->GetKeyDown(KEY_I)) {
            flyTargetCam_ = flyTargetCam_ - Vector3(flySpeed, 0, 0);
        }

        if (input->GetKeyDown(KEY_J)) {
            flyTargetCam_ = flyTargetCam_ - Vector3(0, 0, -flySpeed);
        }

        if (input->GetKeyDown(KEY_L)) {
            flyTargetCam_ = flyTargetCam_ - Vector3(0, 0, flySpeed);
        }

        if (input->GetKeyDown(KEY_K)) {
            flyTargetCam_ = flyTargetCam_ - Vector3(-flySpeed, 0, 0);
        }

        if (input->GetKeyDown(KEY_U)) {
            flyTargetCam_ = flyTargetCam_ - Vector3(0, -flySpeed, 0);
        }

        if (input->GetKeyDown(KEY_O)) {
            flyTargetCam_ = flyTargetCam_ - Vector3(0, flySpeed, 0);
        }

        // Server: apply controls to client objects
        const auto& connections = network->GetClientConnections();

        for (unsigned i = 0; i < connections.Size(); ++i)
        {
            Connection* connection = connections[i];

            //auto *actor = dynamic_cast<NetworkActor *>(actorMap_[connection].Get());

            Node* actorNode = serverObjects_[connection];
            if (!actorNode)
                continue;

            // Get the last controls sent by the client
            //const auto& controls = connection->GetControls();
            auto& controls = cspServer_->clientInputs[connection];

            // Server is direct controller of client objects

            // Server: apply controls to client objects
            const Controls &clientControls = connection->GetControls();

            // Get the object this connection is controlling
            ClientObj *actor = actorMap_[connection];

            if (!actor)
                continue;

            // Apply controls to network actor
            actor->SetControls(clientControls);

            // update last used ID
            cspServer_->clientLastIDs[connection] = controls.extraData_.Find("id")->second_.GetUInt();

            GetSubsystem<DebugHud>()->SetAppStats("num_inputs: ", ++cspServer_->usedInputs);

            // reset controls
            controls = Controls();
        }
    }
}

// CLIENT CODE
void MayaScape::HandleLoginListRefresh(StringHash eventType, VariantMap &eventData) {

    // CLIENT CODE

    auto *network = GetSubsystem<Network>();
    Connection *serverConnection = network->GetServerConnection();

    // Handle Packed String -> contains Login List

    // Client identification packet
    if (eventType == E_LOGINLISTREFRESH) {
        URHO3D_LOGINFOF("HandleLoginListRefresh -> eventType: %l -> E_LOGINLISTREFRESH", eventType.Value());
        String packedStr = eventData[LoginListRefresh::P_LOGINLIST].GetString();
        Vector<String> rcvLoginList = packedStr.Split(';');

        // Store in local login list
        loginList_.Clear();

        for (String login: rcvLoginList) {
            // Store in local login list
            loginList_.Push(login.CString());
        }
    }
}

// CLIENT CODE
void MayaScape::HandleRadioTrackNext(StringHash eventType, VariantMap &eventData) {

    // CLIENT CODE

    auto *network = GetSubsystem<Network>();
    Connection *serverConnection = network->GetServerConnection();

    // Next track on the radio
    if (eventType == E_RADIOTRACKNEXT) {
        URHO3D_LOGINFOF("HandleRadioTrackNext -> eventType: %l -> E_RADIOTRACKNEXT", eventType.Value());
        String trackArtist = eventData[RadioTrackNext::P_TRACKARTIST].GetString();
        String trackArtistLink = eventData[RadioTrackNext::P_LINKARTIST].GetString();
        String trackName = eventData[RadioTrackNext::P_TRACKNAME].GetString();

        if (bkgMusic_) {
            bkgMusicPlaying_ = true;
            PlayMusic("Sounds/" + trackName);
            RadioTrack track;
            track.trackName = trackName;
            track.artistName = trackArtist;
            track.artistLink = trackArtistLink;
            radioTrackInfoQueue_.Push(track);

            //PlaySoundEffectGlobal("BAY-r1-mono.wav");
            //int r = Random(0, bzRadioTracks.size()+1);
            //PlayMusic(bzRadioTracks[r].c_str());

        }
    }
}



void MayaScape::HandleNetworkUpdateSent(StringHash eventType, VariantMap& eventData)
{
//    URHO3D_LOGINFO("HandleNetworkUpdateSent");

    Network* network = GetSubsystem<Network>();
    Connection* serverConnection = network->GetServerConnection();

    // Client: clear controls
    if (serverConnection) {

        // CLIENT CODE

        String name = serverConnection->identity_["UserName"].GetString();

        // Locate node
        Node *node = scene_->GetChild(name);

        if (node) {

            // Retrieve NetworkActor
            ClientObj *networkActor = node->GetDerivedComponent<ClientObj>();
            if (networkActor) {
                // Clear network actor controls
                //URHO3D_LOGINFO("networkActor -> Clear Controls");
                networkActor->ClearControls();
            }
        }
    }
}


void MayaScape::HandleNodeCollision(StringHash eventType, VariantMap& eventData) {

    /*
    using namespace PhysicsBeginContact2D;

    Node* p1Node = scene_->GetChild("Bear-P1", true);
    Node* p2Node = scene_->GetChild("Bear-P2", true);

    // Get colliding node
    auto* hitNodeA = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
    auto* hitNodeB = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());

    URHO3D_LOGINFOF("hitNodeA=%d, hitNodeB=%d", hitNodeA, hitNodeB);
    URHO3D_LOGINFOF("hitNodeA id=%d, hitNodeB id=%d", hitNodeA->GetID(), hitNodeB->GetName());
        Vector2 contactPosition; 

        MemoryBuffer contacts(eventData[P_CONTACTS].GetBuffer());
        while (!contacts.IsEof()) {
            contactPosition = contacts.ReadVector2();
            auto contactNormal = contacts.ReadVector2();
            auto contactDistance = contacts.ReadFloat();
            auto contactImpulse = contacts.ReadFloat();
       //     std::cout << "contact position " << contactPosition.ToString().CString() << std::endl;
       //     std::cout << "contact normal " << contactNormal.ToString().CString() << std::endl;
       //     std::cout << "contact distance " << contactDistance << std::endl;
       //     std::cout << "contact impulse " << contactImpulse << std::endl;
        }

        std::cout << std::endl;
*/
}

void MayaScape::HandlePlayerStateUpdate(StringHash eventType, VariantMap& eventData) {

    using namespace ClientPlayerState;
    //int id = eventData[P_ID].GetUInt();
    //int vehicleId = eventData[P_VEHICLE_ID].GetUInt();

    int wheelContactsNum = eventData[P_WHEEL_CONTACTS].GetUInt();
    float noWheelContactTime = eventData[P_NO_WHEEL_CONTACT_TIME].GetFloat();
    float distance = eventData[P_DISTANCE].GetFloat();
    int life = eventData[P_LIFE].GetUInt();
    float rpm = eventData[P_RPM].GetFloat();
    float velocity = eventData[P_VELOCITY].GetFloat();
    float steer = eventData[P_STEER].GetFloat();

    URHO3D_LOGINFOF("Client -> HandlePlayerStateUpdate: %d %f, %f, %d, %f, %f, %f", wheelContactsNum, noWheelContactTime, distance, life, rpm, velocity, steer);

    // Update Client UI bars

    if (powerBarBkgP1Sprite_) {

        // Update player powerbar
        IntVector2 v = powerBarBkgP1Sprite_->GetSize();
        int power = int(((life) / 100.0f) * (float) v.x_);
        powerBarP1Sprite_->SetSize(power, v.y_);

        // Get vehicle attributes
        // Max engine force and rpm

        float maxRPM = 25000.0f;//9000.0f;
        float clampedRPM = rpm;
        if (clampedRPM > maxRPM) {
            clampedRPM = maxRPM;
        }

        v = rpmBarBkgP1Sprite_->GetSize();
        float rpm = (clampedRPM / maxRPM);

        rpmBarP1Sprite_->SetSize(v.x_, v.y_);
        //rpmBarP1Sprite_->SetFullImageRect()
        //rpmBarP1Sprite_->SetHotSpot(rpm*v.x_, 0);
        float rpmX = (rpmBarP1Sprite_->GetWidth()*0.2f) + (rpmBarP1Sprite_->GetWidth()*rpm*0.8f);

        rpmBarP1Sprite_->SetSize(rpmX, v.y_);
        //rpmBarP1Sprite_->SetImageRect(IntRect(0, 0, rpmX, rpmBarP1Sprite_->GetHeight()));



        //float maxSpeed = 400.0f; // 400 km
        float maxSpeed = 400.0f; // to limit properly
        float clampedSpeed = velocity; // velocity is storing skid
        if (clampedSpeed > maxSpeed) {
            clampedSpeed = maxSpeed;
        }

        v = velBarBkgP1Sprite_->GetSize();
        int velocity = (((maxSpeed-clampedSpeed) / maxSpeed) * v.x_);
        velBarP1Sprite_->SetSize(velocity, v.y_);

        // Set text progress bars
        int sticks = 0;
        String progressBar = "";


        sticks = Round(rpm * (float) 25);
        progressBar = "";
        for (int i = 0; i < sticks; i++) {
            progressBar += "|";
        }
        rpmBarProgBarText_->SetText(progressBar);


        float vel = (clampedSpeed / maxSpeed);
        sticks = Round(vel * (float) 25);
        progressBar = "";
        for (int i = 0; i < sticks; i++) {
            progressBar += "|";
        }
        velBarProgBarText_->SetText(progressBar);


        sticks = Round((life/100.0f) * (float) 25);
        progressBar = "";
        for (int i = 0; i < sticks; i++) {
            progressBar += "|";
        }
        powerBarProgBarText_->SetText(progressBar);




    }

}

void MayaScape::HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientConnected;

    // When client connects, assign to scene to begin scene replication
    auto* newConnection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
}



void MayaScape::HandleCollisionBegin(StringHash eventType, VariantMap &eventData) {
    // Get colliding node
    auto *hitNode = static_cast<Node *>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
    if (hitNode->GetName() == "Bear-P1")
        hitNode = static_cast<Node *>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());
    String nodeName = hitNode->GetName();
    Node *character2DNode = scene_->GetChild("Bear-P1", true);
}


void MayaScape::SetParticleEmitter(int hitId, float contactX, float contactY, int type, float timeStep) {
    // CREATE
    auto *cache = GetSubsystem<ResourceCache>();
    ParticleEffect2D *particleEffect;
    Vector2 position;

    switch (type) {
        case 0:
            particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/sun.pex");
            position.x_ = contactX;
            position.y_ = contactY;
            break;
        case 1:
            particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/power.pex");
            position.x_ = contactX;
            position.y_ = contactY;
            break;
    }

    if (!particleEffect)
        return;

    for (int i = 0; i < sizeof(particlePool_) / sizeof(*particlePool_); i++) {
        if (!particlePool_[i].used) {
            particlePool_[i].used = true;
            particlePool_[i].usedBy = hitId;
            particlePool_[i].node = scene_->CreateChild("GreenSpiral");
            auto *particleEmitter = particlePool_[i].node->CreateComponent<ParticleEmitter2D>(LOCAL);
            particleEmitter->SetEffect(particleEffect);
            particlePool_[i].node->SetPosition(Vector3(position.x_, position.y_, 0.0));
            particlePool_[i].lastEmit = timeStep;
            particlePool_[i].currEmit = 0;
            particlePool_[i].timeout = 0.8f;

            break;
        }
    }

    URHO3D_LOGINFOF("PARTICLE EMITTER CREATED used by id=%d", hitId);
}

void MayaScape::HandleUpdateParticlePool(float timeStep) {
    // CREATE
    auto *cache = GetSubsystem<ResourceCache>();
/*    auto* particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/sun.pex");
    if (!particleEffect)
        return;
*/
    for (int i = 0; i < sizeof(particlePool_) / sizeof(*particlePool_); i++) {
        if (particlePool_[i].used) {

            particlePool_[i].currEmit += timeStep;

            if (particlePool_[i].currEmit - particlePool_[i].lastEmit > particlePool_[i].timeout) {
                if (particlePool_[i].node) {
                    particlePool_[i].node->Remove();
                    particlePool_[i].used = false;
                    particlePool_[i].usedBy = -1;
                }
            }
        }
    }
}


void MayaScape::HandleCollisionEnd(StringHash eventType, VariantMap &eventData) {
    // Get colliding node
    auto *hitNode = static_cast<Node *>(eventData[PhysicsEndContact2D::P_NODEA].GetPtr());
    if (hitNode->GetName() == "Bear-P1")
        hitNode = static_cast<Node *>(eventData[PhysicsEndContact2D::P_NODEB].GetPtr());
    String nodeName = hitNode->GetName();
    Node *character2DNode = scene_->GetChild("Bear-P1", true);

}

void MayaScape::HandleRenderUpdate(StringHash eventType, VariantMap &eventData) {
    using namespace Update;
    auto *input = GetSubsystem<Input>();

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    HandleUpdateParticlePool(timeStep);

    DebugRenderer *dbgRenderer = scene_->GetComponent<DebugRenderer>(REPLICATED);

    float deltaSum;


     if (!isServer_) {

         // CLIENT CODE

         // Found network player
         if (isSnapped_) {

             String actorName = String("actor-") + clientName_;
             Node *actorNode = scene_->GetChild(actorName);

             String vehicleName = String("vehicle-") + clientName_;
             Node *vehicleNode = scene_->GetChild(vehicleName);
             //BLUE-304-vehicle

             Vector3 bodyPos;
             Quaternion rotation;

             if (actorNode) {
                 // Retrieve Actor
                 ClientObj *actor = actorNode->GetDerivedComponent<ClientObj>();

                 if (actor) {
                     NetworkActor *na = actorNode->GetDerivedComponent<NetworkActor>();
                     Vehicle *v = vehicleNode->GetDerivedComponent<Vehicle>();
                     if (na) {
                         auto *body = na->GetNode()->GetComponent<RigidBody>(true);
                         if (body) {
                             // CLIENT RIGID BODY RETRIEVED
                             bodyPos = body->GetPosition();
                             rotation = na->GetNode()->GetRotation();


                             if (na->entered_) {
                                 if (v) {
                                     float steering = v->GetSteering();
                                     if (steerWheelSprite_) {
                                         steerWheelSprite_->SetVisible(true);
                                         steerActorSprite_->SetVisible(false);
                                         steerWheelSprite_->SetRotation(360.0f * steering);
                                     }
                                 }
                             } else {
                                 if (steerActorSprite_) {
                                     steerWheelSprite_->SetVisible(false);

                                     // Detect move vector and visible only on non-zero
                                     if (joySteer_.LengthSquared() > 0) {

                                         // Joy movement


                                         steerActorSprite_->SetVisible(true);
                                         steerActorSprite_->SetRotation(body->GetRotation().YawAngle());
                                     } else {
                                         steerActorSprite_->SetVisible(false);
                                     }
                                 }
                             }

                         }
                     }
                 }
             }
         }
     }
}

float ticks = 0;
void MayaScape::HandleUpdate(StringHash eventType, VariantMap &eventData) {
    using namespace Update;
    auto *input = GetSubsystem<Input>();

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    ticks += timeStep;

    // Skip on loading
    if (levelLoading_) return;
    if (clientLevelLoading_) return;

    // Update timers
    lastCamRaycast += timeStep;

    HandleUpdateParticlePool(timeStep);


    auto *cache = GetSubsystem<ResourceCache>();

    UI *ui = GetSubsystem<UI>();
    Server *server = GetSubsystem<Server>();

    Vector<Urho3D::String> loginList;

    // On the client, use the local login list
    if (isServer_) {

        if (ticks > 5.0f) {
            if (!sendLoadMsg_.Empty()) {
                for (int i = 0; i < sendLoadMsg_.Size(); ++i) {
                    // Send remote event to client (after 2000 ms)
                    sendLoadMsg_[i]->SendRemoteEvent(E_PLAYERLOADED, true);
                }
                for (int i = 0; i < sendLoadMsg_.Size(); ++i) {
                    sendLoadMsg_.Erase(i);
                }

            }
            ticks = 0;
        }

        // Add connected clients
        HashMap<String, Connection *> map = server->GetLoginList();
        loginList += map.Keys();

        // Add ai bot clients
        Vector<String> botMap = server->GetAgents();
        if (!botMap.Empty()) {

            for (String bot: botMap) {
                loginList += "[BOT] " + bot;
            }
        }

        int k = 0;
        debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
        debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
        debugText_[k]->SetVisible(true);
        debugText_[k]->SetText(String("Cam Mode: ") + String(camMode_));



        float botSpeedKm = 0;
        float botAvgSpeedKm = 0;
        float botDistance = 0;
        bool onGround = false;
        float reward = 0;
        Vector3 pos;
        Quaternion rot;

        int wheelsContactNum = 0;
        float noWheelContactTime = 0;
        float wheelContactTime = 0;
        Vector<int> wheelContact;
        float turrentAngle = 0;

        // In-bot view mode (cam mode > 0)
        if (camMode_ > 0) {


            // Camera Positioning
            if (aiActorMap_[camMode_-1]) {
                    auto *actor = dynamic_cast<NetworkActor *>(aiActorMap_[camMode_-1].Get());
                    if (actor) {
                        if (actor->vehicle_) {
                            Node *node = actor->vehicle_->GetNode();

                            if (!node) return;

                            String username = actor->GetUserName();
                            botSpeedKm = round(abs(actor->vehicle_->GetRaycastVehicle()->GetSpeedKm()));
                            botDistance = actor->vehicle_->GetRaycastVehicle()->GetDistanceOnGround();
                            botAvgSpeedKm = round(abs(EvolutionManager::getInstance()->getAgentControllers()[camMode_-1]->getLastAvgSpdKm()));
                            onGround = actor->vehicle_->GetRaycastVehicle()->OnGround();
                            reward = EvolutionManager::getInstance()->getAgentControllers()[camMode_-1]->getCurrentCompletionReward();

                            // No wheel contact time
                            noWheelContactTime = EvolutionManager::getInstance()->getAgentControllers()[camMode_-1]->getTimeSinceNoWheelContact();

                            pos = actor->vehicle_->GetNode()->GetPosition();
                            rot = actor->vehicle_->GetNode()->GetRotation();

                            wheelsContactNum = actor->vehicle_->GetRaycastVehicle()->getNumWheelsPrevContact();
                            wheelContactTime = actor->vehicle_->getWheelContactTime();

                            turrentAngle = actor->vehicle_->GetTurrentAngle();

                        }
                    }

            }


            // Update debug text
            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("Speed (km/h): ") + String(botSpeedKm));

            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("Distance (km): ") + String(botDistance));


            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("Avg Speed (km/h): ") + String(botAvgSpeedKm));

            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("On Ground: ") + String(onGround));


            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("Reward: ") + String(reward));


            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("Pos: ") + String(pos) + String(", Rot: ") + String(rot));

            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("Wheel Contact -> ") + String(wheelsContactNum));


            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("wheelContactTime -> ") + String(wheelContactTime));

            k++;
            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
            debugText_[k]->SetVisible(true);
            debugText_[k]->SetText(String("GetTurrentAngle -> ") + String(turrentAngle));

            /*       k++;
                   debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                   debugText_[k]->SetPosition(10.0f, 400 + (k * 20));
                   debugText_[k]->SetVisible(true);
                   debugText_[k]->SetText(String("Wheel Contact: ") + String(wheelsContactNum));
       */

        } // camMode > 0
        else {

            // SERVER: LAST CLIENT JOINED PLAYER CAM

            // camMode = 0 (last joined player cam)

            // Camera Positioning
            if (actorMap_[lastConnection_]) {
                auto *actor = dynamic_cast<NetworkActor *>(actorMap_[lastConnection_].Get());
                if (actor) {
                        if (actor->vehicle_) {
                            Node *node = actor->vehicle_->GetNode();
                            if (!node) return;

                            String username = actor->GetUserName();
                            botSpeedKm = round(abs(actor->vehicle_->GetRaycastVehicle()->GetSpeedKm()));
                            botDistance = actor->vehicle_->GetRaycastVehicle()->GetDistanceOnGround();
                            onGround = actor->vehicle_->GetRaycastVehicle()->OnGround();

                            pos = actor->vehicle_->GetNode()->GetPosition();
                            rot = actor->vehicle_->GetNode()->GetRotation();


                            noWheelContactTime = actor->vehicle_->GetRaycastVehicle()->getNoWheelContactTime();

//                            wheelsContactNum = actor->vehicle_->GetRaycastVehicle()->getNumWheelsContact();
                            wheelsContactNum = actor->vehicle_->GetRaycastVehicle()->getNumWheelsPrevContact();


                            turrentAngle = actor->vehicle_->GetTurrentAngle();

                        }
                    }


                    // Update debug text
                    k++;
                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                    debugText_[k]->SetVisible(true);
                    debugText_[k]->SetText(String("Speed (km/h): ") + String(botSpeedKm));

                    k++;
                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                    debugText_[k]->SetVisible(true);
                    debugText_[k]->SetText(String("Distance (km): ") + String(botDistance));

/*                    k++;
                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                    debugText_[k]->SetPosition(10.0f, 400 + (k * 20));
                    debugText_[k]->SetVisible(true);
                    debugText_[k]->SetText(String("Avg Speed (km/h): ") + String(botAvgSpeedKm));
*/

                    k++;
                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                    debugText_[k]->SetVisible(true);
                    debugText_[k]->SetText(String("On Ground: ") + String(onGround));

                    k++;
                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                    debugText_[k]->SetVisible(true);
                    debugText_[k]->SetText(String("Pos: ") + String(pos) + String(", Rot: ") + String(rot));

                    k++;
                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                    debugText_[k]->SetVisible(true);
                    debugText_[k]->SetText(String("wheelsContactNum -> ") + String(wheelsContactNum));

                   k++;
                   debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                   debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                   debugText_[k]->SetVisible(true);
                   debugText_[k]->SetText(String("noWheelContactTime: ") + String(noWheelContactTime));


            }

        }

            // Show sums

            // Genetic Algorithm statistics text
            int s = 0;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(
                    String("Generation: ") + String(EvolutionManager::getInstance()->getGeneticAlgorithm()->generationCount_) + String(", ") + String("Population: ") + String(EvolutionManager::getInstance()->agentsAliveCount) + String(" out of ") + String(EvolutionManager::getInstance()->getGeneticAlgorithm()->populationSize_));

            s++;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(
            String("Genotype Param Count: ") + String(EvolutionManager::getInstance()->getGeneticAlgorithm()->genotypeParamCount_));

            // Get best agents
            float maxFitness = 0.0f;
            int bestFitIdx = -1;
            float maxEval = 0.0f;
            int bestEvalIdx = -1;

        for (int i = 0; i < EvolutionManager::getInstance()->getAgentControllers().size(); i++) {
                float fitness = EvolutionManager::getInstance()->getAgents()[i]->genotype->fitness;
                float eval = EvolutionManager::getInstance()->getAgents()[i]->genotype->evaluation;

                if (fitness > maxFitness) {
                    maxFitness = fitness;
                    bestFitIdx = i;
                }

                if (eval > maxEval) {
                    maxEval = eval;
                    bestEvalIdx = i;
                }

        } // Calculated sums

        // This is not really necessary -> the sorted previous population by fitness will by in order of highest to low.
        float prevPopMaxEval = 0.0f;
        float prevPopMaxFitness = 0.0f;

        int prevBestEvalIdx = 0;
        int prevBestFitIdx = 0;
        for (int i = 0; i < EvolutionManager::getInstance()->getGeneticAlgorithm()->getPrevPopulation().size(); i++) {
            float eval = EvolutionManager::getInstance()->getGeneticAlgorithm()->getPrevPopulation()[i]->evaluation;
            float fitness = EvolutionManager::getInstance()->getGeneticAlgorithm()->getPrevPopulation()[i]->fitness;

            if (fitness > prevPopMaxFitness) {
                prevPopMaxFitness = fitness;
                prevBestFitIdx = i;
            }

            if (eval > prevPopMaxEval) {
                prevPopMaxEval = eval;
                prevBestEvalIdx = i;
            }
        }



            s++;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(String("Best Evaluation (Current): Agent -> ") + String(bestEvalIdx) + String(", Evaluation -> ") + String(maxEval));

            s++;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(String("Previous Population (1st best): Agent -> ") + String(prevBestFitIdx) + String(", Fitness -> ") + String(prevPopMaxFitness));

            s++;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(String("Previous Population (2nd best): Agent -> ") + String(1) + String(", Fitness -> ") + String(EvolutionManager::getInstance()->getGeneticAlgorithm()->getPrevPopulation()[1]->fitness));

            s++;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(String("Previous Population (3rd best): Agent -> ") + String(2) + String(", Fitness -> ") + String(EvolutionManager::getInstance()->getGeneticAlgorithm()->getPrevPopulation()[2]->fitness));

            s++;
            genAlgStatsText_[s]->SetAlignment(HA_LEFT, VA_TOP);
            genAlgStatsText_[s]->SetPosition(10.0f, 10 + (s * 12));
            genAlgStatsText_[s]->SetVisible(true);
            genAlgStatsText_[s]->SetText(String("Previous Population: Agent -> ") + String(prevBestEvalIdx) + String(", Evaluation -> ") + String(prevPopMaxEval));

    } else {
        loginList = loginList_;
    }


    // On client
    if (!isServer_) {

        int k = 0;
        if (!radioTrackQueue_.Empty()) {

            RadioTrack currTrack = radioTrackInfoQueue_[0];
            radioText_[k]->SetText(String("Artist: ") + String(currTrack.artistName));
            k++;

            radioText_[k]->SetText(String("") + String(currTrack.artistLink));
            k++;

            radioText_[k]->SetText(String("") + String(currTrack.trackName));
            k++;
        }
        else
            radioText_[k]->SetText(String("Waiting for next track..."));
    }

    float deltaSum;


    // Toggle debug geometry with 'Z' key
    if (input->GetKeyPress(KEY_Z))
        drawDebug_ = !drawDebug_;

    // Toggle through focus objects
    if (input->GetKeyPress(KEY_T)) {

        //1448.78039550781,0,1507.31701660156
        //Vector3 trackMarkerPos = Vector3(724.390197753906,0,753.658508300781);
        // Place on at focus object
//        vehicle_->GetNode()->SetPosition(Vector3(focusObjects_[focusIndex_].x_, 500.0f, focusObjects_[focusIndex_].z_));

        // Increment focus object
        focusIndex_++;
    }




    if (input->GetKeyPress(KEY_K)) {
        if (camMode_ > 0) {
            // Switch the steer index
            int aIndex = camMode_ - 1;
            if (EvolutionManager::getInstance()->getNetworkActors()[aIndex]) {
                if (EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_) {

                    if ((EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->getSteerIndex() - 1) < 0) {

                        EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->setSteerIndex(splineSize_);

                    } else {

                        EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->setSteerIndex(
                                (EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->getSteerIndex() -
                                 1) % splineSize_);
                        EvolutionManager::getInstance()->getNetworkActors()[aIndex]->setSteerSet(false);
                    }

                }
            }
        }
    }

    if (input->GetKeyPress(KEY_L)) {
        if (camMode_ > 0) {
            // Switch the steer index
            int aIndex = camMode_ - 1;
            if (EvolutionManager::getInstance()->getNetworkActors()[aIndex]) {
                if (EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_) {
                    EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->setSteerIndex(
                            (EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->getSteerIndex() + 1)  % splineSize_);
                    EvolutionManager::getInstance()->getNetworkActors()[aIndex]->setSteerSet(false);
                }
            }
        }
    }


    if (input->GetKeyPress(KEY_N)) {
        camMode_ = camMode_ - 1;
    }

    if (input->GetKeyPress(KEY_M)) {
        camMode_ = camMode_ + 1;
    }

    if (input->GetKeyPress(KEY_F)) {
        if (isServer_) {
            if (camMode_ > 0) {
                // Flip the vehicle
                int aIndex = camMode_-1;
                if (EvolutionManager::getInstance()->getNetworkActors()[aIndex]) {
                    if (EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_) {
                        EvolutionManager::getInstance()->getNetworkActors()[aIndex]->vehicle_->Flip(timeStep);
                    }
                }
            }
        }
    }


    if (input->GetKeyPress(KEY_J)) {
        // Increment focus object
        camSpin2_ = camSpin2_ - 10.0f;
    }

    if (input->GetKeyPress(KEY_K)) {
        // Increment focus object
        camSpin2_ = camSpin2_ + 10.0f;
    }


    if (!focusObjects_.Empty()) {
        // Clamp focus index
        focusIndex_ = focusIndex_ % focusObjects_.Size();
    }



    if (input->GetKeyPress(KEY_F7))
        ReloadScene(false);


    ui = GetSubsystem<UI>();

    // Toggle physics debug geometry with space
    if (input->GetKeyPress(KEY_F5)) {
//        drawDebug_ = !drawDebug_;
        SaveScene(false);
    }


    // Check for loading / saving the scene
    if (input->GetKeyPress(KEY_K)) {
        File saveFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/MayaScape_Output.xml",
                      FILE_WRITE);
        scene_->SaveXML(saveFile);
    }

    // Call our render update
    HandleRenderUpdate(eventType, eventData);
}

void MayaScape::HandlePostUpdate(StringHash eventType, VariantMap &eventData) {

    // Skip on loading
    if (levelLoading_) return;
    if (clientLevelLoading_) return;


    if (menuScene_) {
        if (menuScene_->GetChild("menuCam", LOCAL)) {
            // Get camera
            auto *menuCam = menuScene_->GetChild("menuCam", LOCAL)->GetComponent<Camera>();

            if (menuCam) {
                using namespace Update;
                // Take the frame time step, which is stored as a float
                float timeStep = eventData[P_TIMESTEP].GetFloat();

                Vector3 pos = menuCam->GetNode()->GetPosition();
                if (pos.x_ > -6.0f) {
                    menuCam->GetNode()->SetPosition(
                            Vector3(menuCam->GetNode()->GetPosition().x_ - 0.0001f * timeStep,
                                    menuCam->GetNode()->GetPosition().y_,
                                    menuCam->GetNode()->GetPosition().z_));
                }


                auto* progressBar = menuScene_->GetChild("ProgressBar",LOCAL)->GetComponent<StaticModel>();
                progressBar->GetNode()->SetScale(Vector3(1,1,loadProgress_*200.0f));
            }
        }

    }


    if (started_) {

        loadProgress_ = Random(0.0f, 1.0f);

        if (packetsIn_) {
            if (packetCounterTimer_.GetMSec(false) > 1000 && GetSubsystem<Network>()->GetServerConnection()) {
                packetsIn_->SetText(
                        "Packets  in: " + String(GetSubsystem<Network>()->GetServerConnection()->GetPacketsInPerSec()));
                packetsOut_->SetText(
                        "Packets out: " +
                        String(GetSubsystem<Network>()->GetServerConnection()->GetPacketsOutPerSec()));
                packetCounterTimer_.Reset();
            }

            if (packetCounterTimer_.GetMSec(false) > 1000 && GetSubsystem<Network>()->GetClientConnections().Size()) {
                int packetsIn = 0;
                int packetsOut = 0;
                auto connections = GetSubsystem<Network>()->GetClientConnections();
                for (auto it = connections.Begin(); it != connections.End(); ++it) {
                    packetsIn += (*it)->GetPacketsInPerSec();
                    packetsOut += (*it)->GetPacketsOutPerSec();
                }
                packetsIn_->SetText("Packets  in: " + String(packetsIn));
                packetsOut_->SetText("Packets out: " + String(packetsOut));
                packetCounterTimer_.Reset();
            }
        }

        if (isServer_) {
            // SERVER
            Server *server = GetSubsystem<Server>();

            Vector<Vector3> camPosList;

            // Update actor marker positions
            if (GetSubsystem<Network>()->GetClientConnections().Size()) {
                auto connections = GetSubsystem<Network>()->GetClientConnections();
                for (auto it = connections.Begin(); it != connections.End(); ++it) {

                    Connection *connection = (*it);

                    auto *actor = dynamic_cast<NetworkActor *>(actorMap_[connection].Get());
                            if (actor) {

                                using namespace Update;
                                // Take the frame time step, which is stored as a float
                                float timeStep = eventData[P_TIMESTEP].GetFloat();
                                float controlYawAngle = actor->controls_.yaw_ - 90.0f;
                                float slowdown = 0.07f;

                                // Update this angle from global axis (joystick) to local (actor)
                                Quaternion actorRot;
                                Vector3 actorPos;

                                // Smooth step
                                //const float rotLerpRate = 10.0f;
                                const float rotLerpRate = 0.08f;

                                // Physics update has completed. Position camera behind vehicle

                                // Body orientation
                                actorPos = actor->GetBody()->GetPosition();
                                actorRot = actor->GetBody()->GetRotation();
                                Quaternion dir(actorRot.YawAngle(), Vector3::UP);

                                // Control rotation
                                dir = dir * Quaternion(controlYawAngle*slowdown, Vector3::UP);

                                if (!actor->entered_) {
                                    // Position dir around actor
                                    dir = SmoothStepAngle(dir, actorRot, timeStep * rotLerpRate);

                                    // On foot controls
                                    float z = controlYawAngle;
                                    if (abs(controlYawAngle) < 90.0f) {
                                        //URHO3D_LOGINFOF("z -> %f", z);

                                        // Apply rotation
                                        actor->GetBody()->GetNode()->SetRotation(dir);
                                        // Align model and apply movement to body
                                        actor->ApplyMovement(timeStep);
                                    } else {
                                        // Do not apply force
                                    }

                                }

                                String clientName = actorMap_[connection]->GetUserName();
                                String vehicleName = String("vehicle-") + clientName;
                                Node *vehicleNode = scene_->GetChild(vehicleName);

                                if (vehicleNode) {
                                    if (actor->vehicle_) {

                                        using namespace Update;
                                        // Take the frame time step, which is stored as a float
                                        float timeStep = eventData[P_TIMESTEP].GetFloat();

                                        // Add time step to player state wait
                                        lastPlayerStateTime_ += timeStep;


                                            // After wait send player state
                                        if (lastPlayerStateTime_ >= 0.45f) {

                                            // 1. Send update to client about vehicle stats
                                            using namespace ClientPlayerState;

                                            // Send the event forward
                                            VariantMap &newEventData = GetEventDataMap();


                                            newEventData[P_WHEEL_CONTACTS] = actor->vehicle_->GetRaycastVehicle()->getNumWheelsContact();
                                            newEventData[P_NO_WHEEL_CONTACT_TIME] = actor->vehicle_->GetRaycastVehicle()->getNoWheelContactTime();
                                            newEventData[P_DISTANCE] = actor->GetVehicle()->GetRaycastVehicle()->GetDistanceOnGround();

                                            newEventData[P_LIFE] = actor->GetLife();
                                            if (actor->vehicle_->GetRaycastVehicle()) {
                                                float rpm = actor->vehicle_->GetCurrentRPM();
                                                newEventData[P_RPM] = rpm;
                                                newEventData[P_VELOCITY] = actor->vehicle_->GetRaycastVehicle()->GetSpeedKm();
                                                newEventData[P_STEER] = actor->GetVehicle()->GetSteering();


                                                // Finally send the object's node ID using a remote event
                                                connection->SendRemoteEvent(E_PLAYERSTATE, true, newEventData);
                                                // Reset timer
                                                lastPlayerStateTime_ = 0.0f;
                                            }
                                        } // End of delayed send


                                        // Immediate update


                                        // Add to server cam calculation
                                        // camPos += startPos;
                                    }
                            }
                        }

//                    }
                } // End of connections loop

                // Get average position
                //camPos = camPos / GetSubsystem<Network>()->GetClientConnections().Size();
            }



            // Update AI bot marker nodes
            for (int i = 0; i < EvolutionManager::getInstance()->getAgents().size(); i++) {
                if (aiActorMap_[i]) {

                        auto *actor = dynamic_cast<NetworkActor *>(aiActorMap_[i].Get());
                        if (actor) {

                            //Vector3 camPos = actor->GetNode()->GetPosition();
                            Vector3 camPos = actor->GetBody()->GetPosition();

                            //Vector3 camPos = actor->GetNode()->GetPosition();
                            // Store ai actor vehicle position for server cam
                            camPosList.Push(camPos);



                            if (actor->vehicle_) {
                                Node *node = actor->vehicle_->GetNode();
                                //if (!node) return;

                              //  Vector3 camPos = actor->vehicle_->GetNode()->GetPosition();
                                //Vector3 camPos = actor->GetNode()->GetPosition();
                                // Store ai actor vehicle position for server cam
                            //    camPosList.Push(camPos);
                            }
                        }

                }
            }

            int numCamModes = aiActorMap_.Size(); // One cam for each ai actor
            if (numCamModes > 0) {
                camMode_ = camMode_ % numCamModes;
                if (camMode_ < 0) camMode_ = numCamModes - 1;
                switch (camMode_) {
                    case 0: {

                        // SERVER: LAST CLIENT JOINED PLAYER CAM

                        // camMode = 0 (last joined player cam)

                        if (lastConnection_) {
                            // Camera Positioning
                            // Raycast camera collision
                            if (actorMap_[lastConnection_]) {
                                auto *actor = dynamic_cast<NetworkActor *>(actorMap_[lastConnection_].Get());
                                if (actor) {

                                    String username = actor->GetUserName();
                                    float botSpeedKm = 0;
                                    Quaternion forward;

                                        float velMult = 8.0f;

                                        Vector3 cameraTargetPos;
                                        if (actor->onVehicle_ && actor->entered_) {

                                            if (actor->vehicle_) {
                                                botSpeedKm = round(
                                                        abs(actor->vehicle_->GetRaycastVehicle()->GetSpeedKm()));
                                                // Back wheel points forward
                                                forward = actor->vehicle_->GetNode()->GetRotation();
                                            }

                                            //float bodyVel = EvolutionManager::getInstance()->getAgents()[camMode_ -1]->getActor()->vehicle_->GetBody()->GetLinearVelocity().Length();
                                            botSpeedKm = Clamp(botSpeedKm, 1.0f, 2000.0f);

                                            // On vehicle

                                            // Zoom up on body velocity increase
                                            cameraTargetPos =
                                                    actor->vehicle_->GetBody()->GetPosition() + forward *
                                                                                                Vector3(actor->vehicle_->GetBody()->GetLinearVelocity().Length() *
                                                                                                        velMult,
                                                                                                        (actor->vehicle_->GetNode()->GetPosition().y_ +
                                                                                                         CAMERA_RAY_DISTANCE_LIMIT +
                                                                                                         12.0f) +
                                                                                                        (botSpeedKm *
                                                                                                         2.7),
                                                                                                        actor->vehicle_->GetBody()->GetLinearVelocity().Length() *
                                                                                                        velMult) * 0.9f;
                                        } else {
                                            // On foot
                                            botSpeedKm = 0;
                                            // Back wheel points forward
                                            forward = actor->GetNode()->GetRotation();

                                            // Zoom up on body velocity increase
                                            cameraTargetPos =
                                                    actor->GetBody()->GetPosition() + forward *
                                                                                                Vector3(actor->GetBody()->GetLinearVelocity().Length() *
                                                                                                        velMult * 0.07,
                                                                                                        CAMERA_RAY_DISTANCE_LIMIT/9,
                                                                                                        actor->GetBody()->GetLinearVelocity().Length() *
                                                                                                        velMult) * 0.06f;

                                        }
                                        Vector3 cameraStartPos = serverCam_->GetNode()->GetPosition();

                                        // Camera ray cast limiter
                                        if (lastCamRaycast > CAM_RAYCAST_TIME_WAIT) {

                                            // Raycast camera against static objects (physics collision mask 2)
                                            // and move it closer to the vehicle if something in between
                                            Ray cameraRay(cameraStartPos, cameraTargetPos - cameraStartPos);
                                            float cameraRayLength = (cameraTargetPos - cameraStartPos).Length();
                                            PhysicsRaycastResult result;

                                            bool stopMove = false;
                                            // Adjust camera up to ray length
                                            if (cameraRayLength < CAMERA_RAY_DISTANCE_LIMIT) {
                                            }

                                            if (cameraRayLength < 10.0f) {
                                                scene_->GetComponent<PhysicsWorld>()->RaycastSingle(result, cameraRay,
                                                                                                    cameraRayLength,
                                                                                                    NETWORKACTOR_COL_LAYER);
                                            } else {
                                                scene_->GetComponent<PhysicsWorld>()->RaycastSingleSegmented(result,
                                                                                                             cameraRay,
                                                                                                             cameraRayLength,
                                                                                                             NETWORKACTOR_COL_LAYER);
                                            }
                                            if (result.body_)
                                                cameraTargetPos =
                                                        cameraStartPos +
                                                        cameraRay.direction_ * (result.distance_ - 0.5f);

                                            // Reset timer for recent ray cast
                                            lastCamRaycast = 0;

                                            Vector3 lookAtObject;

                                            if (actor->onVehicle_ && actor->entered_) {
                                                lookAtObject = actor->vehicle_->GetBody()->GetPosition();
                                            } else {
                                                lookAtObject = actor->GetBody()->GetPosition();
                                            }

                                            // Set camera position and orientation
                                            float w1;
                                            float w2;

                                            if (stopMove) {
                                                w1 = 1.0f; // hold position
                                                w2 = 0.0f;
                                            } else {
                                                w1 = 0.97;
                                                w2 = 0.03;
                                            }

                                            Vector3 weightedSum =
                                                    serverCam_->GetNode()->GetPosition() * w1 + cameraTargetPos * w2;

                                            // Calculate camera distance
                                            serverCam_->GetNode()->SetPosition(weightedSum);
                                            serverCam_->GetNode()->LookAt(lookAtObject);
                                        }
                                    }
                                }
                            } else {
                                // Heli cam
                                serverCam_->GetNode()->SetRotation(Quaternion(90.0f, 0.0f, 0.0f));
                                serverCam_->GetNode()->SetPosition(heliCamView_);
                            }
                } // End of Server: Move Camera (Player Cam)
                        break;
                    case 1 ... 1000: {
                        // Server: Move Camera

                        // Camera ray cast limiter
                        if (lastCamRaycast > CAM_RAYCAST_TIME_WAIT) {

                            // AI bot cam

                            if (!camPosList.Empty()) {

                                // Raycast camera collision
                                if (aiActorMap_[camMode_ - 1]) {
                                    auto *actor = dynamic_cast<NetworkActor *>(aiActorMap_[camMode_ - 1].Get());
                                    if (actor) {
                                        if (actor->vehicle_) {
                                            String username = actor->GetUserName();
                                            float botSpeedKm = round(
                                                    abs(actor->vehicle_->GetRaycastVehicle()->GetSpeedKm()));
                                            // Back wheel points forward
                                            Quaternion forward = actor->vehicle_->GetNode()->GetRotation();


                                            //float bodyVel = EvolutionManager::getInstance()->getAgents()[camMode_ -1]->getActor()->vehicle_->GetBody()->GetLinearVelocity().Length();
                                            botSpeedKm = Clamp(botSpeedKm, 1.0f, 2000.0f);

                                            /// Update spline path
                                            SplinePath *steerSplinePath = scene_->GetComponent<SplinePath>(true);
                                            if (steerSplinePath) {
                                                // Found steer spline

                                                using namespace Update;
                                                // Take the frame time step, which is stored as a float
                                                float timeStep = eventData[P_TIMESTEP].GetFloat();


                                                // Loop back to start
                                                if (steerSplinePath->IsFinished()) { steerSplinePath->Reset(); }


                                                if (!steerSplinePath->GetControlledNode())
                                                    steerSplinePath->SetControlledNode(splineModel_->GetNode());


                                                DebugRenderer *dbgRenderer = scene_->GetComponent<DebugRenderer>(true);

                                                // Set the steering once
                                                if (!actor->isSteerSet()) {
                                                    if (steerSplinePath->getControlPoints().Size() > 3) {
                                                        Vector3 center = steerSplinePath->getControlPoints()[actor->vehicle_->getSteerIndex()]->GetWorldPosition();
                                                        actor->SetTarget(center);
                                                        actor->setSteerSet(true);
                                                        //actor->vehicle_->setDesiredSteer()
                                                    }
                                                }


                                                if (actor->isSteerSet()) {
                                                    dbgRenderer->AddLine(actor->GetPosition(), actor->getToTarget(),
                                                                         Color(1.0f, 0.0, 0.0));


                                                    // Towards steer waypoint
                                                    Vector3 towardsWaypt = (actor->GetPosition() -
                                                                            actor->getToTarget()).Normalized();


                                                    // Project towardsWaypt on vehicle steer vector (-1 left -> +1 right)

                                                    // Calculate distance to waypoint
                                                    //                                          Vector3 v = vehicle_->GetNode()->GetPosition() - toTarget_;// + Vector3(-1500,0,-1500);
//                                            float steering = v.Normalized().DotProduct((vehicle_->GetNode()->GetDirection()))+0.4f;


                                                    float steerProj = towardsWaypt.DotProduct(
                                                            actor->vehicle_->GetNode()->GetDirection());
                                                    actor->vehicle_->setDesiredSteer(steerProj);

                                                    dbgRenderer->AddLine(actor->GetPosition(), actor->GetPosition() +
                                                                                               towardsWaypt *
                                                                                               actor->vehicle_->getDesiredSteer() *
                                                                                               50.0f,
                                                                         Color(0.0f, 1.0, 0.0));


                                                }

                                                //steerPath->DrawDebugGeometry(dbgRenderer, true);
                                                // steerSplinePath->DrawDebugGeometry(dbgRenderer, true);

                                                if (steerSplinePath->getControlPoints().Size() > 3) {

                                                    /// for (int i = 0; i < steerSplinePath->getControlPoints().Size() - 1; i++) {
                                                    //Vector3 firstMark =
                                                    //Vector3 secondMark = steerPath->getControlPoints()[i]->GetWorldPosition() + steerPath->getControlPoints()[i]->Get
                                                    //                                            StaticModel* model;
                                                    //                                          StaticModel* model2;
//                                                model = steerPath->getControlPoints()[i]->GetComponent<StaticModel>(true);
                                                    //                                              model2 = steerPath->getControlPoints()[i+1]->GetComponent<StaticModel>(true);
                                                    //Vector3 center = actor->vehicle_->GetRaycastVehicle()->GetNode()->GetPosition();
                                                    // Vector3 center2 = steerSplinePath->getControlPoints()[0]->GetWorldPosition();


                                                    //   dbgRenderer->AddLine(center, center2, Color(1.0f, 0.0, 0.0));
                                                    //dbgRenderer->AddLine(steerPath->GetPoint(0.1), steerPath->GetPoint(0.2), Color(0.0f, 1.0, 0.0));
                                                    //dbgRenderer->AddLine(steerPath->GetPoint(0.2), steerPath->GetPoint(0.3), Color(0.0f, 0.0, 1.0));





//                                            }
                                                }
                                            }

                                            /*
                                            // Move time segment
                                            if (steerPath->GetControlledNode())
                                                steerPath->Move(timeStep);*/



                                            float velMult = 1.0f;

                                            // Zoom up on body velocity increase
/*                                    Vector3 cameraTargetPos =
                                            camPosList[camMode_ - 1] + forward*Vector3(actor->vehicle_->GetBody()->GetLinearVelocity().Length()*velMult, (actor->vehicle_->GetNode()->GetPosition().y_+CAMERA_RAY_DISTANCE_LIMIT+12.0f)+(botSpeedKm*2.7), actor->vehicle_->GetBody()->GetLinearVelocity().Length()*velMult)*0.9f;
*/
                                            Vector3 cameraTargetPos =
                                                    camPosList[camMode_ - 1] + forward * Vector3(1, 20.0f, 1) * 0.9f;
                                            //actor->vehicle_->GetBody()->GetLinearVelocity().Length()*velMult, actor->vehicle_->GetNode()->GetPosition().y_+(botSpeedKm*1.0), actor->vehicle_->GetBody()->GetLinearVelocity().Length()*velMult
                                            Vector3 cameraStartPos = serverCam_->GetNode()->GetPosition();

                                            // Raycast camera against static objects (physics collision mask 2)
                                            // and move it closer to the vehicle if something in between
                                            Ray cameraRay(cameraStartPos, cameraTargetPos - cameraStartPos);
                                            float cameraRayLength = (cameraTargetPos - cameraStartPos).Length();
                                            PhysicsRaycastResult result;

                                            bool stopMove = false;

                                            if (actor->onVehicle_ && actor->entered_) {

                                                // Adjust camera up to ray length
                                                if (cameraRayLength < CAMERA_RAY_DISTANCE_LIMIT) {
                                                    stopMove = true;
                                                }
                                            } else {
                                                // On foot
                                                // Adjust camera up to ray length
                                                if (cameraRayLength < CAMERA_RAY_DISTANCE_LIMIT/8) {
                                                    stopMove = true;
                                                }
                                            }

                                            if (cameraRayLength < 10.0f) {
                                                scene_->GetComponent<PhysicsWorld>()->RaycastSingle(result, cameraRay,
                                                                                                    cameraRayLength,
                                                                                                    NETWORKACTOR_COL_LAYER);
                                            } else {
                                                scene_->GetComponent<PhysicsWorld>()->RaycastSingleSegmented(result,
                                                                                                             cameraRay,
                                                                                                             cameraRayLength,
                                                                                                             NETWORKACTOR_COL_LAYER);
                                            }
                                            if (result.body_)
                                                cameraTargetPos =
                                                        cameraStartPos +
                                                        cameraRay.direction_ * (result.distance_ - 0.5f);

                                            // Reset timer for recent ray cast
                                            lastCamRaycast = 0;


                                            // Set camera position and orientation
                                            float w1;
                                            float w2;

                                            if (stopMove) {
                                                w1 = 1.0f; // hold position
                                                w2 = 0.0f;
                                            } else {
                                                w1 = 0.97;
                                                w2 = 0.03;
                                            }

                                            Vector3 weightedSum =
                                                    serverCam_->GetNode()->GetPosition() * w1 + cameraTargetPos * w2;

                                            // Calculate camera distance
                                            serverCam_->GetNode()->SetPosition(weightedSum);
                                            serverCam_->GetNode()->LookAt(camPosList[camMode_ - 1]);

                                        }
                                    }
                                } // End of Server: Move Camera


                                // Update per-BOT info

                                // FFN
                                int aIndex = camMode_ - 1;

                                Genotype *genotype = EvolutionManager::getInstance()->getAgents()[aIndex]->genotype;
                                // Retrieve parameters for genotype
                                std::vector<float> parameters = genotype->getParameterCopy();

                                // Set weights to parameter values
                                for (int p = 0; p < genotype->getParameterCount(); p++) {
                                    //EvolutionManager::getInstance()->getAgents()[i]->ffn->layers[k]->weights[i][j] = parameters[p];

                                    // Server-side view
                                    Sprite *sprite = ffnBotSprite_.Find(p)->second_;
                                    int width = 16;
                                    int height = 10;

                                    float ix = (p % width) * width;
                                    float iy = (p / width) * height;
                                    // Set logo sprite size
                                    sprite->SetAlignment(HA_LEFT, VA_TOP);
                                    sprite->SetPosition(Vector2(800.0f + ix, 10.0f + iy));
                                    sprite->SetScale(0.3f);
                                    sprite->SetOpacity(0.9f);
                                    // Set a low priority so that other UI elements can be drawn on top
                                    sprite->SetPriority(-100);
                                    sprite->SetVisible(true);

                                    sprite->SetColor(Color(Vector3(parameters[p], parameters[p], parameters[p])));


                                }


                                // Show BOT control inputs
                                float steerInput = EvolutionManager::getInstance()->getAgentControllers()[aIndex]->movement->getSteerInput();
                                float accInput = EvolutionManager::getInstance()->getAgentControllers()[aIndex]->movement->getAccelInput();
                                float action = EvolutionManager::getInstance()->getAgentControllers()[aIndex]->movement->getAction();
                                float accLimit = 1.0f;

                                steerWheelBotSprite_->SetPosition(Vector2(1000, 200));
                                steerWheelBotSprite_->SetScale(0.2f);
                                steerWheelBotSprite_->SetRotation((steerInput) * 360.0f);
                                steerWheelBotSprite_->SetVisible(true);

                                velBarBotSprite_->SetPosition(Vector2(900, 100));
                                velBarBotSprite_->SetVisible(true);

                                if (accInput > 0) {
                                    IntVector2 v = velBarBkgBotSprite_->GetSize();
                                    int power = int(((accInput) / accLimit) * (float) v.x_);
                                    velBarBotSprite_->SetSize(power, v.y_);
                                    velBarBotSprite_->SetScale(0.3f);
                                } else {
                                    IntVector2 v = velBarBkgBotSprite_->GetSize();
                                    int power = int(((-accInput) / -accLimit) * (float) v.x_);
                                    velBarBotSprite_->SetSize(power, v.y_);
                                    velBarBotSprite_->SetScale(0.3f);
                                }

                                velBarBkgBotSprite_->SetPosition(Vector2(900, 100));
                                velBarBkgBotSprite_->SetVisible(true);
                                velBarBkgBotSprite_->SetScale(0.3f);

                                /*
                                // Update player powerbar
                                IntVector2 v = powerBarBkgP1Sprite_->GetSize();
                                int power = int(((life) / 100.0f) * (float) v.x_);
                                powerBarP1Sprite_->SetSize(power, v.y_);
        */
                                /*
                                 *
                                 *  // Construct FFN from genotype
        for (int k = 0; k < NUM_NEURAL_LAYERS; k++) {

            for (int i = 0; i < ffn->layers[k]->neuronCount; i++) {
                for (int j = 0; j < ffn->layers[k]->outputCount; j++) {

                    // Retrieve parameters for genotype
                    std::vector<float> parameters = genotype->getParameterCopy();

                    // Set weights to parameter values
                    for (int p = 0; p < genotype->getParameterCount(); p++) {
                        ffn->layers[k]->weights[i][j] = parameters[p];
                    }
                }
            }
        }
                                 *
                                 */

                            }
                        } // End of Raycast limiter
                    }
                 break;
                }
            }


            // Special server input
            UI *ui = GetSubsystem<UI>();
            Input *input = GetSubsystem<Input>();

            if (input->GetMouseButtonDown(MOUSEB_LEFT)) {


                // Do aggregate based settings for server
                PlaceObject(serverCam_, 0);
            }


        } else {
                // CLIENT

                Node *actorNode = nullptr;
                Node *vehicleNode = nullptr;
                Network *network = GetSubsystem<Network>();
                auto serverConnection = network->GetServerConnection();
                using namespace Update;
                float timeStep = eventData[P_TIMESTEP].GetFloat();

                // MAIN CLIENT UPDATE


                // Apply transformations to camera
                MoveCamera(timeStep);


                instructionsText_->SetVisible(true);

                for (int i = 0; i < hudTextList_.Size(); i++) {
                    hudTextList_[i]->SetVisible(true);
                }
            }
        }
}


void MayaScape::HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData) {

    // Skip on loading
    if (levelLoading_) return;
    if (clientLevelLoading_) return;

}

void MayaScape::HandleEndRendering(StringHash eventType, VariantMap &eventData) {

    Graphics *graphics = GetSubsystem<Graphics>();
    auto *cache = GetSubsystem<ResourceCache>();

    if (levelLoading_) {
        if (scene_->GetAsyncProgress() == 1.0f) {

            // ASYNC MAP LOAD COMPLETE
            levelLoading_  = false;

        }

        int sticks = Round(scene_->GetAsyncProgress() * (float) 20);
        String progressBar = "";
        for (int i = 0; i < sticks; i++) {
            progressBar += "|";
        }
        progressText_->SetText(progressBar);
    }

    if (!clientLevelLoading_) {
        progressText_->SetVisible(levelLoading_);
        progressResText_->SetVisible(levelLoading_);
    } else {
        int b = 0;

    }


    int a = 0;
}

void MayaScape::ReloadScene(bool reInit) {
  // LOAD MAP

 auto *cache = GetSubsystem<ResourceCache>();
 //String filename = "Map1_Start_T1";
/// String filename = "Map2_Start_T1";


// LOAD BASE

 //////////
        // sub
        SubscribeToEvent(E_ASYNCLOADPROGRESS, URHO3D_HANDLER(MayaScape, HandleLoadProgress));
        SubscribeToEvent(E_ASYNCLEVELOADFINISHED, URHO3D_HANDLER(MayaScape, HandleLevelLoaded));






    levelPathName_= "Scenes/Async/";
    // load scene
    XMLFile *xmlLevel = cache->GetResource<XMLFile>("Scenes/base.xml");


    //BackgroundLoadResource -> fails
    //XMLFile *xmlLevel;
    //cache->BackgroundLoadResource<XMLFile>("Scenes/base.xml", true, xmlLevel);


    /*XMLFile *xmlLevel = cache->GetResource<XMLFile>("Scenes/" + filename + ".xml");
    //loadFile(context_, cache + "Data/Scenes/" + filename + ".xml",
     */
    if (xmlLevel) {
        scene_->LoadXML(xmlLevel->GetRoot());
    }

    /////////


   }//Map1_Start_T1.xml


   void MayaScape::LoadLevel(int id) {
       auto *cache = GetSubsystem<ResourceCache>();
       levelPathName_= "Scenes/Async/";

       // remove any existing level
       if (nextLevel_)
       {
           nextLevel_->Remove();
           nextLevel_ = NULL;
       }



       //String filename = "Map3_Start_T1";
       String filename = "Map" + String(id) + "_Start_T1";

       // async load
//    String levelPathFile = levelPathName_ + loadLevel + String(".xml");
       String loadLevel = filename;
       String levelPathFile = levelPathName_ + loadLevel + String(".xml");

       URHO3D_LOGINFO("cache file " + levelPathFile);
       XMLFile *xmlLevel  = cache->GetResource<XMLFile>(levelPathFile);

       if (xmlLevel) {
           SceneResolver resolver;
           Node *tmpNode = scene_->CreateTemporaryChild();

           URHO3D_LOGINFO("LoadXML loading " + levelPathFile);
           if (tmpNode->LoadXML(xmlLevel->GetRoot(), resolver, false)) {
               URHO3D_LOGINFO("Async loading " + levelPathFile);
               if (scene_->InstantiateXMLAsync(xmlLevel->GetRoot(), tmpNode->GetWorldPosition(),
                                               tmpNode->GetWorldRotation())) {
                   // prevent the trigger to reload while already loading
                   levelLoadPending_ = levelPathFile;
                   progressText_->SetText("");
               } else {
                   URHO3D_LOGERROR("InstantiateXMLAsync failed to init, level=" + levelPathFile);
               }
           }

       }



       // setup for async loading
       //scene_->SetAsyncLoadingMs(3);
       levelLoading_ = true;

       scene_->SetUpdateEnabled(true);
   }

   void MayaScape::PlaySoundEffect(const String &soundName) {

   /*
       if (sndFxPlay_[soundName]) {
           float f = sndFxPlay_[soundName];
           if (f > 5.0f) {
               sndFxPlay_.Erase(soundName);
           } else {
               // Skip play
               return;
           }
       }

       // TOOD: Hash map based on soundname -> playing
       Pair<String, float> p = Pair<String, float>(soundName, 0);
       sndFxPlay_.Insert(p);

       auto *cache = GetSubsystem<ResourceCache>();
       auto *sound = cache->GetResource<Sound>("Sounds/" + soundName);

       auto *source = scene_->CreateComponent<SoundSource3D>(LOCAL);
       source->SetNearDistance(1);  // distance up to where the volume is 100%
       source->SetFarDistance(1550);  // distance from where the volume is at 0%
       source->SetSoundType(SOUND_EFFECT);
       if (sound != nullptr) {
           source->SetAutoRemoveMode(REMOVE_COMPONENT);
           source->Play(sound);
       }*/
}


void MayaScape::PlayMusic(const String &soundName) {
    // CLIENT CODE

    // Play music on client

    auto *cache = GetSubsystem<ResourceCache>();
    SoundSource3D *source = scene_->CreateComponent<SoundSource3D>(LOCAL);

    source->SetNearDistance(1);  // distance up to where the volume is 100%
    source->SetFarDistance(6000);  // distance from where the volume is at 0%
    source->SetSoundType(SOUND_MUSIC);

    /*
    // If existing tracks are in the queue, stop them
    if (!radioTrackQueue_.Empty()) {
        for (int i = 0; i < radioTrackQueue_.Size(); i++) {
            if (radioTrackQueue_[i]) {
                if (radioTrackQueue_[i]->IsPlaying()) radioTrackQueue_[i]->Stop();
            }
        }
    }*/

    // Store track
    radioTrackQueue_.Push(source);


    // Play latest track
    auto *sound = cache->GetResource<Sound>(soundName);
    if (sound != nullptr) {
        source->SetAutoRemoveMode(REMOVE_COMPONENT);
        source->Play(sound);
    }
}

void MayaScape::PlaySoundEffectGlobal(const String &soundName) {

    auto *cache = GetSubsystem<ResourceCache>();
    auto *source = scene_->CreateComponent<SoundSource3D>(REPLICATED);

    source->SetNearDistance(1);  // distance up to where the volume is 100%
    source->SetFarDistance(6000);  // distance from where the volume is at 0%
    source->SetSoundType(SOUND_EFFECT);

    auto *sound = cache->GetResource<Sound>("Sounds/" + soundName);
    if (sound != nullptr) {
        source->SetAutoRemoveMode(REMOVE_COMPONENT);
        source->Play(sound);
    }
}


void MayaScape::PlaySoundEffectLocal(const String &soundName) {

    auto *cache = GetSubsystem<ResourceCache>();
    auto *source = scene_->CreateComponent<SoundSource3D>(LOCAL);

    source->SetNearDistance(1);  // distance up to where the volume is 100%
    source->SetFarDistance(6000);  // distance from where the volume is at 0%
    source->SetSoundType(SOUND_EFFECT);

    auto *sound = cache->GetResource<Sound>("Sounds/" + soundName);
    if (sound != nullptr) {
        source->SetAutoRemoveMode(REMOVE_COMPONENT);
        source->Play(sound);
    }
}

void MayaScape::HandlePlayButton(StringHash eventType, VariantMap &eventData) {

    // CLIENT CODE STARTS

    //gameServers
    Graphics *graphics = GetSubsystem<Graphics>();
    auto* renderer = GetSubsystem<Renderer>();
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    UI *ui = GetSubsystem<UI>();
    UIElement *root = ui->GetRoot();


    // Hide mouse cursor
    auto *input = GetSubsystem<Input>();
    input->SetMouseVisible(false);

    // Call on connect to server
    HandleConnect(eventType, eventData);
}

// Network functions
void MayaScape::CreateServerSubsystem() {
    context_->RegisterSubsystem(new Server(context_));

    // register client objs
    ClientObj::RegisterObject(context_);
    NetworkActor::RegisterObject(context_);
    Vehicle::RegisterObject(context_);

    Mover::RegisterObject(context_);

    RaycastVehicleBase::RegisterObject(context_);
    WheelTrackModel::RegisterObject(context_);
//    Missile::RegisterObject(context_);
    Bullet::RegisterObject(context_);

    // Client-side Prediction
    CSP_Server::RegisterObject(context_);
    CSP_Client::RegisterObject(context_);
}

void MayaScape::CreateUI() {

    Graphics *graphics = GetSubsystem<Graphics>();
    auto* renderer = GetSubsystem<Renderer>();

    // Viewports:
    // 0 = front view
    // 1 = rear view
    // 2 = menu view
    renderer->SetNumViewports(2);

    // Setup menu viewport
    //SetupMenuViewport();

    ResourceCache *cache = GetSubsystem<ResourceCache>();
    UI *ui = GetSubsystem<UI>();
    UIElement *root = ui->GetRoot();
    XMLFile *uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    root->SetDefaultStyle(uiStyle);


    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(uiStyle);
    ui->SetCursor(cursor);

    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);

    int textureWidth;
    int textureHeight;

    // Get logo texture
    Texture2D *bkgTexture = cache->GetResource<Texture2D>("Textures/menu-bkg.png");
    if (!bkgTexture)
        return;

    // Create bkg sprite and add to the UI layout
    bkgSprite_ = ui->GetRoot()->CreateChild<Sprite>();
    bkgAngle_ = 0.0f;

    // Set logo sprite texture
    bkgSprite_->SetTexture(bkgTexture);

    textureWidth = bkgTexture->GetWidth();
    textureHeight = bkgTexture->GetHeight();

    // Set logo sprite scale
    bkgSprite_->SetScale((256.0f / textureWidth) * 9.2f);

    // Set logo sprite size
    bkgSprite_->SetSize(textureWidth, textureHeight);

    // Set logo sprite hot spot
    bkgSprite_->SetHotSpot(textureWidth / 2, textureHeight / 2);

    // Set logo sprite alignment
    bkgSprite_->SetAlignment(HA_CENTER, VA_CENTER);
    bkgSprite_->SetPosition(0, 0);

    // Make logo not fully opaque to show the scene underneath
    bkgSprite_->SetOpacity(0.9f);

    // Set a low priority for the logo so that other UI elements can be drawn on top
    bkgSprite_->SetPriority(-100);

    // Construct the instructions text element
    versionText_ = ui->GetRoot()->CreateChild<Text>();
    versionText_->SetText(STUDIO_VERSION);
    versionText_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 25);
    versionText_->SetColor(Color::GRAY);

    auto versionText2_ = ui->GetRoot()->CreateChild<Text>();
    versionText2_->SetText(STUDIO_VERSION);
    versionText2_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 25);
    versionText2_->SetColor(Color::YELLOW);
    versionText2_->SetParent(versionText_);

    // Position the text relative to the screen center
    //versionText_->SetHorizontalAlignment(HA_CENTER);
    versionText_->SetAlignment(HA_CENTER, VA_TOP);
    versionText_->SetPosition(0, 10);
    // Hide once connected
    versionText_->SetVisible(true);

    versionText2_->SetAlignment(HA_CENTER, VA_TOP);
    versionText2_->SetPosition(0, -2);
    // Hide once connected
    versionText2_->SetVisible(true);

    // Construct the instructions text element
    gameNameText_ = ui->GetRoot()->CreateChild<Text>();
    gameNameText_->SetText(GAME_NAME);
    gameNameText_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 60);
    gameNameText_->SetColor(Color::GRAY);
    // Position the text relative to the screen center
    gameNameText_->SetAlignment(HA_CENTER, VA_TOP);
    gameNameText_->SetPosition(0, 70);
    gameNameText_->SetVisible(true);

    auto gameNameText2_ = ui->GetRoot()->CreateChild<Text>();
    gameNameText2_->SetText(GAME_NAME);
    gameNameText2_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 60);
    gameNameText2_->SetColor(Color::WHITE);
    // Position the text relative to the screen center
    gameNameText2_->SetAlignment(HA_CENTER, VA_TOP);
    gameNameText2_->SetPosition(0, -2);
    gameNameText2_->SetVisible(true);
    gameNameText2_->SetParent(gameNameText_);




    /*studioText_ = ui->GetRoot()->CreateChild<Text>();
    studioText_->SetText(STUDIO_VERSION);
    studioText_->SetFont(cache->GetResource<Font>("Fonts/CompassGold.ttf"), 26);
    studioText_->SetColor(Color::BLACK);
    // Position the text relative to the screen center
    studioText_->SetHorizontalAlignment(HA_CENTER);
    studioText_->SetPosition(0, 920);
    // Hide once connected
    studioText_->SetVisible(true);
*/


    // Construct the instructions text element
    instructionsText_ = ui->GetRoot()->CreateChild<Text>();
    instructionsText_->SetText(
            ""
            "An online open world combat racing game."
    );
    instructionsText_->SetFont(cache->GetResource<Font>(INGAME_FONT2), 24);
    instructionsText_->SetColor(Color::WHITE);
    // Position the text relative to the screen center
    instructionsText_->SetHorizontalAlignment(HA_CENTER);
    instructionsText_->SetPosition(0, 550);
    // Hide until connected
    instructionsText_->SetVisible(false);

    /*
    levelText_ = ui->GetRoot()->CreateChild<Text>();
    levelText_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 12);
    levelText_->SetTextAlignment(HA_CENTER);
    levelText_->SetColor(Color::CYAN);
    levelText_->SetPosition(graphics->GetWidth() - 100, 10);

    triggerText_ = ui->GetRoot()->CreateChild<Text>();
    triggerText_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 12);
    triggerText_->SetTextAlignment(HA_CENTER);
    triggerText_->SetColor(Color::CYAN);
    triggerText_->SetPosition(graphics->GetWidth() - 250, 10);
*/
    progressText_ = ui->GetRoot()->CreateChild<Text>();
    progressText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 21);
    progressText_->SetTextAlignment(HA_CENTER);
    progressText_->SetColor(Color::GREEN);
    progressText_->SetVerticalAlignment(VA_CENTER);
    progressText_->SetHorizontalAlignment(HA_CENTER);
    progressText_->SetPosition(0, 0);
    progressText_->SetVisible(false);

    progressResText_ = ui->GetRoot()->CreateChild<Text>();
    progressResText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 15);
    progressResText_->SetTextAlignment(HA_CENTER);
    progressResText_->SetColor(Color::GRAY);
    progressResText_->SetVerticalAlignment(VA_CENTER);
    progressResText_->SetHorizontalAlignment(HA_CENTER);
    progressResText_->SetPosition(0, 30);
    progressResText_->SetVisible(false);


    int hudTextCount = 4;
    for (int i = 0; i < hudTextCount; i++) {
        // Construct the text element
        SharedPtr<Text> hudText_ = static_cast<SharedPtr<Text>>(ui->GetRoot()->CreateChild<Text>());
        hudText_->SetText("");
        hudText_->SetFont(cache->GetResource<Font>(INGAME_FONT4), 17);
        hudText_->SetColor(Color::WHITE);
        // Position the text relative to the screen center
        hudText_->SetHorizontalAlignment(HA_CENTER);
        hudText_->SetPosition(0, 610+(i*20.0f));
        // Hide until connected
        hudText_->SetVisible(false);

        hudTextList_.Push(hudText_);
    }

    buttonContainer_ = root->CreateChild<UIElement>();
    buttonContainer_->SetFixedSize(graphics->GetWidth(), graphics->GetHeight());

    buttonContainer_->SetPosition(graphics->GetWidth()/5, graphics->GetHeight()/5);
    buttonContainer_->SetHorizontalAlignment(HA_CENTER);
    buttonContainer_->SetVerticalAlignment(VA_CENTER);

    buttonContainer_->SetLayoutMode(Urho3D::LM_VERTICAL);
    buttonContainer_->SetLayoutSpacing(10.0);
    //textEdit_ = buttonContainer_->CreateChild<LineEdit>();
    //textEdit_->SetStyleAuto();
    //textEdit_->SetVisible(false);



    gameServerDropDownList_ = static_cast<SharedPtr<DropDownList>>(ui->GetRoot()->CreateChild<DropDownList>());
    gameServerDropDownList_->SetStyleAuto();

    gameServerDropDownList_->SetFixedSize(580, 54);
    gameServerDropDownList_->SetMinWidth(580);
    for (int i = 0; i < gameServers.size(); i++) {
        Text* text = new Text(context_);
        text->SetFont(INGAME_FONT4, 24);
        text->SetText(gameServers[i].c_str());
        text->SetFixedSize(200, 50);
        text->SetColor(Color::WHITE);
        text->SetEffectStrokeThickness(2);
        gameServerDropDownList_->AddItem(text);

    }

    buttonContainer_->AddChild(gameServerDropDownList_);
    playButton_ = CreateButton("PLAY", 580);
    startServerButton_ = CreateButton("START SERVER", 580);
    exitButton_ = CreateButton("EXIT", 580);

    // Get logo texture
    Texture2D *logoTexture = cache->GetResource<Texture2D>("Textures/logo.png");
    if (!logoTexture)
        return;

    // Create logo sprite and add to the UI layout
    //logoSprite_ = ui->GetRoot()->CreateChild<Sprite>();

    // Set logo sprite texture
    //logoSprite_->SetTexture(logoTexture);

    textureWidth = logoTexture->GetWidth();
    textureHeight = logoTexture->GetHeight();

    // Set logo sprite scale
    logoSprite_->SetScale(256.0f / textureWidth);

    // Set logo sprite size
    logoSprite_->SetSize(textureWidth, textureHeight);

    // Set logo sprite hot spot
    logoSprite_->SetHotSpot(textureWidth, textureHeight);

    // Set logo sprite alignment
    logoSprite_->SetAlignment(HA_CENTER, VA_CENTER);
    logoSprite_->SetPosition(textureWidth-textureWidth/3.0f+68.0f, 41.0f);
    logoSprite_->SetScale(1.6);

    // Make logo not fully opaque to show the scene underneath
    logoSprite_->SetOpacity(0.9f);

    // Set a low priority for the logo so that other UI elements can be drawn on top
    logoSprite_->SetPriority(-100);

    auto *font = cache->GetResource<Font>(INGAME_FONT2);
    chatHistoryText_ = root->CreateChild<Text>();
    chatHistoryText_->SetFont(font, 12);
    chatHistoryText_->SetVisible(false);

    UpdateButtons();

    float rowHeight = chatHistoryText_->GetRowHeight();
    // Row height would be zero if the font failed to load
    if (rowHeight) {
        float numberOfRows = (graphics->GetHeight() - 100) / rowHeight;
        chatHistory_.Resize(static_cast<unsigned int>(numberOfRows));
    }

    // No viewports or scene is defined. However, the default zone's fog color controls the fill color
    GetSubsystem<Renderer>()->GetDefaultZone()->SetFogColor(Color(0.0f, 0.0f, 0.1f));
}

void MayaScape::InitiateViewport(Context* context, Scene* scene, Camera* camera, int id)
{
    Renderer* renderer = GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context, scene, camera));
    renderer->SetViewport(id, viewport);
}


void MayaScape::SetupMenuViewport() {
    auto* graphics = GetSubsystem<Graphics>();
    auto* renderer = GetSubsystem<Renderer>();

    // Load menu scene
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    XMLFile *xmlLevel = cache->GetResource<XMLFile>("Scenes/MayaScapeMenu.xml");
    menuScene_ = MakeShared<Scene>(context_);
    menuScene_->SetName("MenuScene");

    if (xmlLevel) {
        menuScene_->LoadXML(xmlLevel->GetRoot());
        menuScene_->SetEnabled(true);
        menuScene_->SetUpdateEnabled(true);
    }


    // Get camera
    auto* menuCam = menuScene_->GetChild("menuCam",LOCAL)->GetComponent<Camera>();
    auto* progressBar = menuScene_->GetChild("ProgressBar",LOCAL)->GetComponent<StaticModel>();
    progressBar->GetNode()->SetScale(Vector3(1,1,1));

    // The viewport index must be greater in that case, otherwise the view would be left behind
    menuViewport_ = new Viewport(context_, menuScene_, menuCam,
                                 IntRect(32, 32, graphics->GetWidth() - 32, graphics->GetHeight() - 32));
    renderer->SetViewport(2, menuViewport_);


}

void MayaScape::SetupGameViewports()
{

    auto* graphics = GetSubsystem<Graphics>();
    auto* renderer = GetSubsystem<Renderer>();

    // Viewports:
    // 0 = front view
    // 1 = rear view
    // 2 = menu view


    SharedPtr<Camera> rearCam;
    if (isServer_) {
        // SERVER CODE
        InitiateViewport(context_, scene_, serverCam_, 0);
        // Create camera opposite
        Node* node = serverCam_->GetNode()->CreateChild("RearCamera", LOCAL);
        rearCam = node->CreateComponent<Camera>();
        rearCam->GetNode()->SetRotation(Quaternion(0, 180, 0));
        rearCam->SetFarClip(48000.0f);
        rearCam->SetFillMode(Urho3D::FILL_SOLID);

    } else {
        // CLIENT CODE
        InitiateViewport(context_, scene_, clientCam_, 0);
        // Create camera opposite
        Node* node = clientCam_->GetNode()->CreateChild("RearCamera", LOCAL);
        rearCam = node->CreateComponent<Camera>();
        rearCam->GetNode()->SetRotation(Quaternion(0, 180, 0));
        rearCam->GetNode()->SetPosition(Vector3(0.0f,-0.3f,0.0f));
        rearCam->SetFarClip(48000.0f);
        rearCam->SetFillMode(Urho3D::FILL_SOLID);

    }

    // DEBUG -- disable views
//    renderer->SetViewport(0, nullptr);
//    renderer->SetViewport(1, nullptr);



    //menuCam->SetFarClip(48000.0f);
    //rearCam->SetFillMode(Urho3D::FILL_SOLID);

    // Set up the rear camera viewport on top of the front view ("rear view mirror")
    float widthHalf = 240.0f;
    float height = 120.0f;
    // The viewport index must be greater in that case, otherwise the view would be left behind
        SharedPtr<Viewport> rearViewport(new Viewport(context_, scene_, rearCam,
                                                     IntRect((graphics->GetWidth() / 2)-widthHalf, 32, (graphics->GetWidth()/2)+widthHalf - 16, 32+height)));
    renderer->SetViewport(1, rearViewport);



}


void MayaScape::ChangeDebugHudText() {
    // change profiler text
    if (GetSubsystem<DebugHud>()) {
        Text *dbgText = GetSubsystem<DebugHud>()->GetProfilerText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);

        dbgText = GetSubsystem<DebugHud>()->GetStatsText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);

        dbgText = GetSubsystem<DebugHud>()->GetMemoryText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);

        dbgText = GetSubsystem<DebugHud>()->GetModeText();
        dbgText->SetColor(Color::CYAN);
        dbgText->SetTextEffect(TE_NONE);
    }
}

Button *MayaScape::CreateButton(const String &text, int width) {
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    Font *font = cache->GetResource<Font>(INGAME_FONT4);

    Button *button = buttonContainer_->CreateChild<Button>();
    button->SetStyleAuto();
    button->SetFixedHeight(120);
    button->SetFixedWidth(width);
    //button->SetHeight(5);

    Text *buttonText = button->CreateChild<Text>();
    buttonText->SetName("text");
    buttonText->SetFont(INGAME_FONT4, 40);
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);
    buttonText->SetText(text);

    return button;
}

void MayaScape::UpdateButtons() {
    Network *network = GetSubsystem<Network>();
    Connection *serverConnection = network->GetServerConnection();
    bool serverRunning = network->IsServerRunning();


    playButton_->SetVisible(!serverConnection && !serverRunning);
    startServerButton_->SetVisible(!serverConnection && !serverRunning);
    //exitButton_->SetVisible(!serverConnection && !serverRunning);
    //  textEdit_->SetVisible(!serverConnection && !serverRunning);
}

// Manage camera movement for Client
void MayaScape::MoveCamera(float timeStep) {

    // CLIENT CODE

    // Right mouse button controls mouse cursor visibility: hide when pressed
    UI *ui = GetSubsystem<UI>();
    Input *input = GetSubsystem<Input>();
    ui->GetCursor()->SetVisible(!input->GetMouseButtonDown(MOUSEB_RIGHT));

    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;


    // smooth step
    const float rotLerpRate = 10.0f;
    const float maxVel = 50.0f;
    const float damping = 0.2f;

    int k = 0;
    if (started_) {

        // For clients
        if (!isServer_) {


            // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch and only move the camera
            // when the cursor is hidden
            if (!ui->GetCursor()->IsVisible()) {
                IntVector2 mouseMove = input->GetMouseMove();
                yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
                pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
                pitch_ = Clamp(pitch_, 1.0f, 90.0f);
            }

            if (clientCam_) {

                // Only move camera if we have a controllable object

                Network *network = GetSubsystem<Network>();
                Connection *serverConnection = network->GetServerConnection();

                if (serverConnection) {
                    int size;
                    PODVector<Node *> vec;

                    String actorName = String("actor-") + clientName_;
                    Node *actorNode = scene_->GetChild(actorName);

                    String vehicleName = String("vehicle-") + clientName_;
                    Node *vehicleNode = scene_->GetChild(vehicleName);

                    //BLUE-304-vehicle

                    Vector3 pos;
                    Quaternion rot;
                    Vector3 lVel;

                    if (actorNode) {
                        // Retrieve Actor
                        ClientObj *actor = actorNode->GetDerivedComponent<ClientObj>();

                        if (actor) {
                            NetworkActor *na = actorNode->GetDerivedComponent<NetworkActor>();
                            Vehicle *v = vehicleNode->GetDerivedComponent<Vehicle>();


                            if (na) {
                                auto *body = na->GetNode()->GetComponent<RigidBody>(true);
                                if (body) {
                                    // CLIENT RIGID BODY RETRIEVED
                                    pos = body->GetPosition();
                                    rot = body->GetRotation();
                                    lVel = body->GetLinearVelocity();
                                }
                            }

                            // Client: Move Camera
                            // Camera Positioning
                            ////

                            Vector3 lookAtObject;


                            if (na) {

                                String username = actor->GetUserName();
                                float botSpeedKm = 0;
                                Quaternion forward;

                                float velMult = 8.0f;

                                Vector3 cameraTargetPos;
                                auto *naBody = na->GetNode()->GetComponent<RigidBody>(true);
                                if (na->onVehicle_ && na->entered_) {
                                    if (naBody) {
                                        // CLIENT RIGID BODY RETRIEVED
                                        pos = naBody->GetPosition();
                                        rot = naBody->GetRotation();
                                        lVel = naBody->GetLinearVelocity();
                                    }

                                    if (v) {
                                        auto *vBody = v->GetNode()->GetComponent<RigidBody>(true);
                                        if (vBody) {
                                            // CLIENT RIGID BODY RETRIEVED
                                            pos = vBody->GetPosition();
                                            rot = vBody->GetRotation();
                                            lVel = vBody->GetLinearVelocity();
                                            lookAtObject = vBody->GetPosition();;

                                        }

                                        // Back wheel points forward
                                        forward = -vBody->GetNode()->GetRotation();
                                    }

                                    //float bodyVel = EvolutionManager::getInstance()->getAgents()[camMode_ -1]->getActor()->vehicle_->GetBody()->GetLinearVelocity().Length();
                                    botSpeedKm = Clamp(botSpeedKm, 1.0f, 2000.0f);

                                    // On vehicle
                                    float velLen = lVel.Length();


                                    // FRONT VIEW
                                    // Zoom up on body velocity increase
                                    cameraTargetPos =
                                            pos + forward *
                                            Vector3(velLen *
                                                    velMult  * 0.07,
                                                    (CAMERA_RAY_DISTANCE_LIMIT/22)*velLen,
                                                    50.0f + velLen *
                                                    velMult) * 0.6f;


                                    // REAR VIEW
                                    // Zoom up on body velocity increase
                                    cameraTargetPos =
                                            pos + forward *
                                                  Vector3(velLen *
                                                          velMult  * 0.07,
                                                          (CAMERA_RAY_DISTANCE_LIMIT/22)*velLen,
                                                          -50.0f + -velLen *
                                                                  velMult) * 0.6f;



                                } else {
                                    // On foot
                                    botSpeedKm = 0;
                                    // Back wheel points forward
                                    forward = rot;

                                    float velLen = lVel.Length();

                                    // Zoom up on body velocity increase
                                    cameraTargetPos =
                                            pos + Vector3::UP * 3.3f - forward *
                                          Vector3(0.0f + velLen *
                                                  velMult * 0.07,
                                                  CAMERA_RAY_DISTANCE_LIMIT/14,
                                                  78.0f + velLen *
                                                  velMult) * 0.11f;


                                    lookAtObject = naBody->GetPosition();

                                }
                                Vector3 cameraStartPos = clientCam_->GetNode()->GetPosition();

                                bool stopMove = false;
                                // Camera ray cast limiter
                                if (lastCamRaycast > CAM_RAYCAST_TIME_WAIT) {

                                    /*
                                 // Raycast camera against static objects (physics collision mask 2)
                                 // and move it closer to the vehicle if something in between
                                 Ray cameraRay(cameraStartPos, cameraTargetPos - cameraStartPos);
                                 float cameraRayLength = (cameraTargetPos - cameraStartPos).Length();
                                 PhysicsRaycastResult result;


                                 // Adjust camera up to ray length

                                 if (cameraRayLength < 10.0f) {
                                     scene_->GetComponent<PhysicsWorld>()->RaycastSingle(result, cameraRay,
                                                                                         cameraRayLength,
                                                                                         NETWORKACTOR_COL_LAYER);
                                 } else {
                                     scene_->GetComponent<PhysicsWorld>()->RaycastSingleSegmented(result,
                                                                                                  cameraRay,
                                                                                                  cameraRayLength,
                                                                                                  NETWORKACTOR_COL_LAYER);
                                 }

                                 if (result.body_)
                                     cameraTargetPos =
                                             cameraStartPos +
                                             cameraRay.direction_ * (result.distance_ - 0.5f);
         */
                                    // Reset timer for recent ray cast
                                    lastCamRaycast = 0;


                                    // Set camera position and orientation
                                    float w1;
                                    float w2;

                                    if (stopMove) {
                                        w1 = 1.0f; // hold position
                                        w2 = 0.0f;
                                    } else {
                                        w1 = 0.94f;
                                        w2 = 0.06f;
                                    }

                                    Vector3 weightedSum =
                                            clientCam_->GetNode()->GetPosition() * w1 + cameraTargetPos * w2;

                                    // Calculate camera distance
                                    clientCam_->GetNode()->SetPosition(weightedSum);
                                    clientCam_->GetNode()->LookAt(lookAtObject);

                                    //clientCam_->GetNode()->SetPosition(cameraTargetPos);
                                    //clientCam_->GetNode()->SetRotation(dir);
                                }
                            }
                            ////

                            // NetworkActor (Player) cam

                            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                            debugText_[k]->SetVisible(true);
                            debugText_[k]->SetText(String("Actor Pos -> ") + String(pos.ToString()));
                            k++;
                            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                            debugText_[k]->SetVisible(true);
                            debugText_[k]->SetText(String("Actor Rot -> ") + String(rot.ToString()));
                            k++;
                            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                            debugText_[k]->SetVisible(true);
                            debugText_[k]->SetText(String("Actor -> ") + String(actorName));
                            k++;

                            debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                            debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                            debugText_[k]->SetVisible(true);
                            debugText_[k]->SetText(String("ntwkControls_.yaw_ -> ") + String(ntwkControls_.yaw_));
                            k++;



                                if (v) {
                                    // Snap camera to vehicle once available
                                    Vector3 startPos = v->GetNode()->GetNetPositionAttr();
                                    MemoryBuffer buf(v->GetNode()->GetNetRotationAttr());
                                    Quaternion rotation = buf.ReadPackedQuaternion();

                                    // Show message on first snap
                                    if (!isSnapped_) {
                                        isSnapped_ = true;

                                        URHO3D_LOGDEBUG(
                                                "--- Retrieved vehicle -> can snap camera -> Actor [" +
                                                String(startPos.x_) + "," +
                                                String(startPos.y_) + "," +
                                                String(startPos.z_) + "]");
                                    }


                                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                                    debugText_[k]->SetVisible(true);
                                    debugText_[k]->SetText(String("Vehicle Pos -> ") + String(startPos.ToString()));
                                    k++;
                                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                                    debugText_[k]->SetVisible(true);
                                    debugText_[k]->SetText(String("Vehicle Rot -> ") + String(rotation.ToString()));
                                    k++;
                                    debugText_[k]->SetAlignment(HA_LEFT, VA_TOP);
                                    debugText_[k]->SetPosition(10.0f, 400 + (k * 12));
                                    debugText_[k]->SetVisible(true);
                                    debugText_[k]->SetText(String("Vehicle -> ") + String(vehicleName));
                                    k++;


                                    // Object location for camera
                                    Vector3 snap = Vector3(startPos);
                                    snap.y_ += 230.0f;
                                    snap.x_ -= 120.0f;
                                    snap.z_ -= 120.0f;
                                    //Vector3 snap = server->GetFocusObjects().Empty() ? Vector3(0, 35.0, 0) : server->GetFocusObjects()[0];

                                }
                            }

                        }

                        }
                    }
                }
            }  // End of started_
}


void MayaScape::NodeRegisterLoadTriggers(Node *node)
{
    if (node)
    {
        PODVector<Node*> result;
        node->GetChildrenWithTag(result, "levelLoadTrigger", true);

        for ( unsigned i = 0; i < result.Size(); ++i )
        {
            SubscribeToEvent(result[i], E_NODECOLLISIONSTART, URHO3D_HANDLER(MayaScape, HandleLoadTriggerEntered));
        }
    }
    else
    {
        URHO3D_LOGERROR("NodeRegisterLoadTriggers - node is NULL.");
    }
}

void MayaScape::HandleLoadTriggerEntered(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollisionStart;

    // prevent the trigger to reload while already loading
    if (!levelLoadPending_.Empty())
    {
        return;
    }

    Node *node = ((RigidBody*)eventData[P_BODY].GetVoidPtr())->GetNode();
    StringVector tagVec = node->GetTags();
    String levelName;
    String loadLevel;

    // get trigger tags
    for ( unsigned i = 0; i < tagVec.Size(); ++i )
    {
        if (tagVec[i].StartsWith("levelName="))
        {
            const unsigned nameLen = String("levelName=").Length();
            levelName = tagVec[i].Substring(nameLen, tagVec[i].Length() - nameLen);
        }
        else if (tagVec[i].StartsWith("loadLevel="))
        {
            const unsigned loadLen = String("loadLevel=").Length();
            loadLevel = tagVec[i].Substring(loadLen, tagVec[i].Length() - loadLen);
        }
    }

    if (!levelName.Empty() && !loadLevel.Empty())
    {
        levelText_->SetText(String("cur level:\n") + levelName);
        triggerText_->SetText(String("trig info:\n") + "level=" + levelName + "\nload =" + loadLevel);

        String curLevelName = curLevel_?curLevel_->GetName():String::EMPTY;
        String loadLevelName = nextLevel_?nextLevel_->GetName():String::EMPTY;

        if (curLevelName != levelName)
        {
            // swap nodes
            if (curLevelName == loadLevel && loadLevelName == levelName)
            {
                Node *tmpNode = curLevel_;
                curLevel_ = nextLevel_;
                nextLevel_ = tmpNode;
            }
            else
            {
                URHO3D_LOGERROR("Trigger level and load names out of sequence.");
            }
        }
        else if (loadLevelName != loadLevel)
        {
            // remove any existing level
            if (nextLevel_)
            {
                nextLevel_->Remove();
                nextLevel_ = NULL;
            }

            // async load
            ResourceCache* cache = GetSubsystem<ResourceCache>();
            String levelPathFile = levelPathName_ + loadLevel + String(".xml");
            URHO3D_LOGINFO("cache file " + levelPathFile);
            XMLFile *xmlLevel = cache->GetResource<XMLFile>(levelPathFile);

            if (xmlLevel)
            {
                SceneResolver resolver;
                Node *tmpNode = scene_->CreateTemporaryChild();

                URHO3D_LOGINFO("LoadXML loading " + levelPathFile);
                if (tmpNode->LoadXML(xmlLevel->GetRoot(), resolver, false))
                {
                    URHO3D_LOGINFO("Async loading " + levelPathFile);
                    if (scene_->InstantiateXMLAsync(xmlLevel->GetRoot(), tmpNode->GetWorldPosition(), tmpNode->GetWorldRotation()))
                    {
                        // prevent the trigger to reload while already loading
                        levelLoadPending_ = levelPathFile;
                        progressText_->SetText("");
                    }
                    else
                    {
                        URHO3D_LOGERROR("InstantiateXMLAsync failed to init, level=" + levelPathFile);
                    }
                }
            }
            else
            {
                URHO3D_LOGERROR("Load level file= " + levelPathFile + " not found!");
            }
        }
    }
}

void MayaScape::HandleLoadProgress(StringHash eventType, VariantMap& eventData)
{
    using namespace AsyncLoadProgress;

    float progress = eventData[P_PROGRESS].GetFloat();
    int loadedNode = eventData[P_LOADEDNODES].GetInt();
    int totalNodes = eventData[P_TOTALNODES].GetInt();
    int loadedResources = eventData[P_LOADEDRESOURCES].GetInt();
    int totalResources = eventData[P_TOTALRESOURCES].GetInt();

    String progressStr = ToString("progress=%d%%", (int)(progress * 100.0f)) +
                         ToString("\nnodes: %d/%d", loadedNode, totalNodes) +
                         ToString("\nresources: %d/%d", loadedResources, totalResources);

    //progressText_->SetText(progressStr);
}

void MayaScape::HandleLevelLoaded(StringHash eventType, VariantMap& eventData)
{
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    using namespace AsyncLevelLoadFinished;
    nextLevel_ = (Node*)eventData[P_NODE].GetVoidPtr();

    // register triggers from new level node and clear loading flag
    NodeRegisterLoadTriggers(nextLevel_);
    levelLoadPending_.Clear();


    scene_->StopAsyncLoading();

    // Initiate game map for multiplayer game
    InitiateGameMap(scene_);
    // Spawn the player to server itself
    SpawnPlayer();

    // Start in game mode
    UpdateUIState(true);

    // Attach agent bot list to server (for login list)
    Vector<String> botList;
    // Build bot list
    for (int i = 0; i < EvolutionManager::getInstance()->getAgents().size(); i++) {
        String botName = EvolutionManager::getInstance()->getNetworkActors()[i]->GetUserName();
        botList.Push(botName);
    }
    Server *server = GetSubsystem<Server>();
    server->SetAgents(botList);

    // Create sphere for camera target
    camTargetNode_ = scene_->CreateChild("CamTargetMarker");
    camTargetNode_->SetScale(38.0f);
    camTargetNode_->SetPosition(flyTargetCam_);

    // model
    StaticModel* ballModel = camTargetNode_->GetOrCreateComponent<StaticModel>();
    //ballModel->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
    //ballModel->SetCastShadows(true);


    // spline model
    splineModel_ = scene_->GetOrCreateComponent<StaticModel>();
    //splineModel_->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));

    // Post map load

    /// Update spline path
    Node* steerSpline = scene_->GetChild("SteerSpline", "true");
    PODVector<Node*> steerMarks;
    steerSpline->GetChildren(steerMarks);

    splineSize_ = steerMarks.Size();

    /// Update spline path
    SplinePath* steerSplinePath = scene_->GetComponent<SplinePath>(true);
    if (steerSplinePath) {
        // Found steer spline
        for (int i = 0; i < steerMarks.Size(); i++) {
            steerSplinePath->AddControlPoint(steerMarks[i]);
        }

        steerSplinePath->SetSpeed(3.0f);
        //botSplinePath_->SetControlledNode(bot_);[/code]
    }


    // Clear menu
    Renderer *renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(2, nullptr);

}

void MayaScape::HandleConnectionFailed(StringHash eventType, VariantMap &eventData) {
    URHO3D_LOGINFO("Connection to server failed!");
    InitMsgWindow("Connection failure", "Connection to server failed!");
}

void MayaScape::HandleConnect(StringHash eventType, VariantMap &eventData) {
    static const int MAX_ARRAY_SIZE = 10;
    static String colorArray[MAX_ARRAY_SIZE] =
            {
                    "WHITE",
                    "GRAY",
                    "BLACK",
                    "RED",
                    "GREEN",
                    "BLUE",
                    "CYAN",
                    "MAGENTA",
                    "YELLOW",
                    "VEGAS GOLD"
            };

    // Client code
    isServer_ = false;
    Server *server = GetSubsystem<Server>();
//..    String address = gameServers[gameServerSelected_].c_str();

     UIElement *ui = gameServerDropDownList_->GetSelectedItem();
     auto *text = static_cast<Text *>(ui);
     String address = text->GetText();

//    String address = textEdit_->GetText().Trimmed();

    // Setup Client-Side Prediction
    cspClient_ = scene_->CreateComponent<CSP_Client>(LOCAL);

    // randomize (or customize) client info/data
    int idx = Random(MAX_ARRAY_SIZE - 1);
    char buffer[200];
    String baseName = colorArray[idx];
    sprintf(buffer, "%s-%d", baseName.CString(), Random(1, 1000));
    String name = buffer;
    URHO3D_LOGINFOF("client idx=%i, username=%s", idx, name.CString());

    VariantMap identity;
    identity["UserName"] = name;
    identity["ColorIdx"] = idx;
    identity["Position"] = Vector3(-2,-2,-2);

    Network* network = GetSubsystem<Network>();

    scene_->Clear(true, true);


    // Client connect to server
    if (network->Connect(address, SERVER_PORT, scene_, identity)) {

        // CLIENT CODE -> START CONNECT

        // Set camera node for viewport
        cameraNode_ = scene_->CreateChild("Camera", LOCAL);
        clientCam_ = cameraNode_->CreateComponent<Camera>();
        clientCam_->SetFarClip(24000.0f);
        //clientCam_->SetFillMode(Urho3D::FILL_WIREFRAME);
        cameraNode_->SetPosition(Vector3(heliCamView_));
        clientCam_->GetNode()->SetRotation(Quaternion(90.0f, 0.0f, 0.0f));

        // Setup game viewport
        SetupGameViewports();

        URHO3D_LOGINFOF("client identity name=%s", name.CString());
        URHO3D_LOGINFOF("MayaScape::HandleConnect - data: [%s, %d]", name.CString(), idx);

        // Store in local login list
        loginList_.Push(name.CString());

        // Change UI -> hide menu and show game
        UpdateButtons();
        started_ = true;
        // Set logo sprite alignment
        logoSprite_->SetAlignment(HA_RIGHT, VA_TOP);
        logoSprite_->SetPosition(-15, 200);
        logoSprite_->SetScale(0.33f);

        // Make logo not fully opaque to show the scene underneath
        logoSprite_->SetOpacity(0.5f);

        // Client startup code

        // Store name
        clientName_ = name.CString();

        String playerText = "Logged in as: " + String(clientName_.CString());
        instructionsText_->SetText(playerText);
        //instructionsText_->SetPosition(0, 730);
        instructionsText_->SetAlignment(HA_CENTER, VA_BOTTOM);
        instructionsText_->SetPosition(0, -20);

        // TODO CAN use this to get user input later for name
//        String address = textEdit_->GetText().Trimmed();
        // Empty the text edit after reading the address to connect to
//        textEdit_->SetText(String::EMPTY);

        UpdateButtons();

        URHO3D_LOGINFOF("client idx=%i, username=%s", idx, name.CString());

    } else {
        URHO3D_LOGINFOF("Connection to server failed =%s", address.CString());
        engine_->Exit();
    }

    /// Subscribe the ServerConnected Event
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(MayaScape, HandleServerConnected));
}

void MayaScape::HandleDisconnect(StringHash eventType, VariantMap &eventData) {
    Server *server = GetSubsystem<Server>();
    server->Disconnect();

    UpdateButtons();
}

void MayaScape::HandleStartServer(StringHash eventType, VariantMap &eventData) {

    // SERVER CODE STARTS

    Server *server = GetSubsystem<Server>();
    if (!server->StartServer(SERVER_PORT)) {
        engine_->Exit();
    }

    // Load base scene
    ReloadScene(true);


    // Setup Client-Side Prediction
    cspServer_ = scene_->CreateComponent<CSP_Server>(LOCAL);
    cspServer_->updateInterval_ = 1.f / 1.f;

    // Create Admin
//    CreateAdminPlayer();
    isServer_ = true;

    UpdateButtons();
    // Switch to game mode
    //UpdateUIState(true);
    started_ = true;

    // Set logo sprite alignment
    logoSprite_->SetAlignment(HA_RIGHT, VA_TOP);
    logoSprite_->SetPosition(-15, 180);
    logoSprite_->SetScale(0.33f);


    // Make logo not fully opaque to show the scene underneath
    logoSprite_->SetOpacity(0.5f);

    StartMultiplayerGameSession();

    /*
    //// DEBUG LOGGING
    int size;
    PODVector<Node*> vec;

    // Retrieve Network Actor (Client Object)
    vec = scene_->GetChildren(false);
    size = vec.Size();
    URHO3D_LOGDEBUGF(
            "Number of nodes -> %l", size);

    for (int i = 0; i < vec.Size(); i++) {
        Node *node = vec.At(i);
        if (node) {
            URHO3D_LOGDEBUGF(
                    "[SERVER] Scene: Node -> %s [%l] [%f,%f,%f] -> Is Replicated? %d", node->GetName().CString(), node->GetID(), node->GetPosition().x_, node->GetPosition().y_,
                    node->GetPosition().z_, node->IsReplicated());
        }
    }
*/
    /////

    Network *network = GetSubsystem<Network>();
    network->SetUpdateFps(30);

    // Server load level
    //LoadLevel(3);
    //LoadLevel(4);
    //LoadLevel(5);
    LoadLevel(6);

}

void MayaScape::HandleConnectionStatus(StringHash eventType, VariantMap &eventData) {
    using namespace ServerStatus;
    StringHash msg = eventData[P_STATUS].GetStringHash();

    if (msg == E_SERVERDISCONNECTED) {
        //scene_->RemoveAllChildren();
        //CreateScene();
        //SetupViewport();

        URHO3D_LOGINFO("server connection lost");
    }

    UpdateButtons();
}

void MayaScape::HandleClientObjectID(StringHash eventType, VariantMap &eventData) {
    // CLIENT CODE

    auto *network = GetSubsystem<Network>();
    Connection *serverConnection = network->GetServerConnection();



    // Handle Identification Packet (Client Object ID) -> contains Network Actor and Vehicle Node Ids

    using namespace ClientConnected;

    // Client identification packet
    if (eventType == E_CLIENTOBJECTID) {
        URHO3D_LOGINFOF("HandleClientObjectID -> eventType: %l -> E_CLIENTOBJECTID", eventType.Value());
        // SCENE: Read data and store client object id information
        networkActorNodeId_ = eventData[ClientObjectID::P_NETWORKACTOR].GetUInt();
        vehicleNodeId_ = eventData[ClientObjectID::P_VEHICLE].GetUInt();

        URHO3D_LOGINFOF(
                "Client -> MayaScape::HandleClientObjectID: networkActorNodeId_ = %l, vehicleNodeId_ = %l",
                networkActorNodeId_, vehicleNodeId_);

    }
}

void MayaScape::HandleExit(StringHash eventType, VariantMap &eventData) {
    engine_->Exit();
}

void MayaScape::StartMultiplayerGameSession()
{
    // Multiple session
    isMultiplayer_ = true;

    ResourceCache *cache = GetSubsystem<ResourceCache>();
    Network* network = GetSubsystem<Network>();
    // If we are running a server
    if (network->IsServerRunning())
    {


        // Subscribe for the newcomer recognition
        SubscribeToEvent(E_CLIENTIDENTITY, URHO3D_HANDLER(MayaScape, HandleClientIdentity));
        // Subscribe the update event for the whole logic
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(MayaScape, HandleUpdate));
        // Subscribe for the client disconnection
        SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(MayaScape, HandleClientDisconnected));

        // Register the remote event 'playerspawned'
        network->RegisterRemoteEvent(E_PLAYERSPAWNED);

        // Register the remote event
        network->RegisterRemoteEvent(E_RADIOTRACKNEXT);
    }
        // if we are running a client
    else if (network->GetServerConnection())
    {
        // Register the remote event 'player spawned'
        network->RegisterRemoteEvent(E_PLAYERSPAWNED);
        // Subscribe for the remote event 'player spawned'
        SubscribeToEvent(E_PLAYERSPAWNED, URHO3D_HANDLER(MayaScape, HandlePlayerRespawned));

        // Register the remote event 'player loaded'
        network->RegisterRemoteEvent(E_PLAYERLOADED);
        // Subscribe for the remote event 'player loaded'
        SubscribeToEvent(E_PLAYERLOADED, URHO3D_HANDLER(MayaScape, HandlePlayerLoaded));

        // Register the remote event
        network->RegisterRemoteEvent(E_RADIOTRACKNEXT);
        // Subscribe for the remote event 'player loaded'
        SubscribeToEvent(E_RADIOTRACKNEXT, URHO3D_HANDLER(MayaScape, HandleRadioTrackNext));

    }

}


void MayaScape::InitMsgWindow(String title, String message) {
    UI *ui = GetSubsystem<UI>();
    ResourceCache *cache = GetSubsystem<ResourceCache>();

    // Create the Window and add it to the UI's root node
    msgWindow_ = new Window(context_);
    ui->GetRoot()->AddChild(msgWindow_);

    // Set Window size and layout settings
    msgWindow_->SetMinWidth(384);
    msgWindow_->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    msgWindow_->SetAlignment(HA_CENTER, VA_CENTER);
    msgWindow_->SetName(message);


    // Create Window 'titlebar' container
    auto *titleBar = new UIElement(context_);
    titleBar->SetMinSize(0, 24);
    titleBar->SetVerticalAlignment(VA_TOP);
    titleBar->SetLayoutMode(LM_HORIZONTAL);

    // Create the Window title Text
    auto *windowTitle = new Text(context_);
    windowTitle->SetName("WindowTitle");
    windowTitle->SetText(title);
//    windowTitle->SetFont(cache->GetResource<Font>("Fonts/SinsGold.ttf"), 15);

    // Create the Window's close button
    auto *buttonClose = new Button(context_);
    buttonClose->SetName("CloseButton");

    // Add the controls to the title bar
    titleBar->AddChild(windowTitle);
    titleBar->AddChild(buttonClose);

    // Add the title bar to the Window
    msgWindow_->AddChild(titleBar);

    // Apply styles
    msgWindow_->SetStyleAuto();
    windowTitle->SetStyleAuto();
    buttonClose->SetStyle("CloseButton");

    // Subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, E_RELEASED, URHO3D_HANDLER(MayaScape, HandleClosePressed));

    // Subscribe also to all UI mouse clicks just to see where we have clicked
    //  SubscribeToEvent(E_UIMOUSECLICK, URHO3D_HANDLER(HelloGUI, HandleControlClicked));
}

void MayaScape::HandleClosePressed(StringHash eventType, VariantMap &eventData) {
    // Shutdown
    engine_->Exit();
}


void MayaScape::OutputLoginListToConsole() {

    URHO3D_LOGINFO("**** CLIENT: CLIENT LIST *****************************************************");

    for (int i = 0; i < loginList_.Size(); i++) {
        URHO3D_LOGINFOF("**** LOGIN: %s", loginList_.At(i).CString());
    }

    URHO3D_LOGINFO("******************************************************************************");

}


void MayaScape::ShowChatText(const String &row) {
    chatHistory_.Erase(0);
    chatHistory_.Push(row);

    // Concatenate all the rows in history
    String allRows;
    for (unsigned i = 0; i < chatHistory_.Size(); ++i)
        allRows += chatHistory_[i] + "\n";

    chatHistoryText_->SetText(allRows);
}

void MayaScape::HandleLogMessage(StringHash /*eventType*/, VariantMap &eventData) {
    using namespace LogMessage;

    ShowChatText(eventData[P_MESSAGE].GetString());
}

void MayaScape::HandleSend(StringHash /*eventType*/, VariantMap &eventData) {
    String text = textEdit_->GetText();
    if (text.Empty())
        return; // Do not send an empty message

    auto *network = GetSubsystem<Network>();
    Connection *serverConnection = network->GetServerConnection();

    if (serverConnection) {
        // A VectorBuffer object is convenient for constructing a message to send
        VectorBuffer msg;
        msg.WriteString(text);
        // Send the chat message as in-order and reliable
        serverConnection->SendMessage(MSG_CHAT, true, true, msg);
        // Empty the text edit after sending
        textEdit_->SetText(String::EMPTY);
    }
}

void MayaScape::HandleNetworkMessage(StringHash /*eventType*/, VariantMap &eventData) {
    auto *network = GetSubsystem<Network>();

    using namespace NetworkMessage;

    int msgID = eventData[P_MESSAGEID].GetInt();

    //URHO3D_LOGINFOF("HandleNetworkMessage: msgID -> %d", msgID);

    if (msgID == MSG_CHAT) {
        const PODVector<unsigned char> &data = eventData[P_DATA].GetBuffer();
        // Use a MemoryBuffer to read the message data so that there is no unnecessary copying
        MemoryBuffer msg(data);
        String text = msg.ReadString();

        // If we are the server, prepend the sender's IP address and port and echo to everyone
        // If we are a client, just display the message
        if (network->IsServerRunning()) {
            auto *sender = static_cast<Connection *>(eventData[P_CONNECTION].GetPtr());

            text = sender->ToString() + " " + text;

            VectorBuffer sendMsg;
            sendMsg.WriteString(text);
            // Broadcast as in-order and reliable
            network->BroadcastMessage(MSG_CHAT, true, true, sendMsg);
        }

        ShowChatText(text);
    }
}

String MayaScape::SaveScene(bool initial) {
    String filename = "MayaScape_sceneExport";
    if (!initial)
        filename += "InGame";
    File saveFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/" + filename + ".xml",
                  FILE_WRITE);
    scene_->SaveXML(saveFile);
    return saveFile.GetName();
}


Controls MayaScape::sample_input() {
    auto ui = GetSubsystem<UI>();
    auto input = GetSubsystem<Input>();

    Controls controls;

    // Copy mouse yaw
    controls.yaw_ = yaw_;

    // Only apply WASD controls if there is no focused UI element
    if (!ui->GetFocusElement()) {
        controls.Set(CTRL_FORWARD, input->GetKeyDown(KEY_W));
        controls.Set(CTRL_BACK, input->GetKeyDown(KEY_S));
        controls.Set(CTRL_LEFT, input->GetKeyDown(KEY_A));
        controls.Set(CTRL_RIGHT, input->GetKeyDown(KEY_D));
    }

    return controls;
}


void MayaScape::apply_input(Node *actorNode, const Controls &controls) {


}

void MayaScape::apply_input(Connection *connection, const Controls &controls) {
/*
    auto ballNode = serverObjects_[connection];
    if (!ballNode)
        return;

    apply_input(ballNode, controls);*/
}

void MayaScape::HandleClientIdentity(StringHash eventType, VariantMap& eventData) {
    // SERVER CODE
    using namespace ClientIdentity;
    // Get connection from the client
    Connection* connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());

    //if (!connection) { Toolkit::Print("Lost connection request!"); return; }
    //Toolkit::Print("Newcomer:" + String(connection->GetIdentity()["username"]));
    SpawnPlayer(connection);
    // Send scene to the client
    connection->SetScene(scene_);
    Server *server = GetSubsystem<Server>();


    /// Retrieve the username for the client
    VariantMap identity = connection->GetIdentity();
    String username = String(identity["UserName"]);

    // Store in server local login list
    loginList_.Push(username);

    // Shuffle to next track
    currTrack_ = Random(0,bzRadioTracksTrackName.size());
    // Send remote event
    connection->SendRemoteEvent(E_PLAYERSPAWNED, true); // Player spawn
    server->SendRadioTrackNextMsg(connection, bzRadioTracksArtistName[currTrack_].c_str(), bzRadioTracksArtistLink[currTrack_].c_str(), bzRadioTracksTrackName[currTrack_].c_str()); // Radio track
}

void MayaScape::HandleSceneUpdate(StringHash eventType, VariantMap &eventData) {
    // Move the camera by touch, if the camera node is initialized by descendant sample class
    if (cameraNode_) {
    }

    URHO3D_LOGINFOF("HandleSceneUpdate");

}

// Spawn Player (Admin on Server)
SharedPtr<Node> MayaScape::SpawnPlayer() {
    // SERVER CODE (ADMIN PLAYER)

    // Create a new network actor for the player
    SharedPtr<Node> networkActorNode(scene_->CreateChild("actor-SERVER"));
    NetworkActor *actor = networkActorNode->CreateComponent<NetworkActor>();
    actor->Init(networkActorNode);
    String name = String(String("actor-SERVER"));
    actor->SetClientInfo(name, 99, Vector3(0,-6,0));

    // 2. Create a new camera following the actor
    Graphics* graphics = GetSubsystem<Graphics>();
    String cameraname = "camera_actor-server";
    SharedPtr<Node>cameraNode(networkActorNode->CreateChild(cameraname));
    cameraNode->SetPosition(Vector3(0.0f, 3000.0f, 0.0f));


    // Define server cam views
    heliCamView_ = Vector3(0.0f,14000.0f,0.0f);

    // Set camera node
    cameraNode_ = scene_->CreateChild("Camera", LOCAL);
    serverCam_ = cameraNode_->CreateComponent<Camera>();
    serverCam_->GetNode()->SetRotation(Quaternion(90.0f, 0.0f, 0.0f));
    serverCam_->SetFarClip(48000.0f);
    serverCam_->SetFillMode(Urho3D::FILL_SOLID);
    //serverCam_->SetFillMode(Urho3D::FILL_WIREFRAME);
    serverCam_->GetNode()->SetPosition(heliCamView_);
    serverCam_->GetNode()->SetRotation(Quaternion(90.0f, 0.0f, 0.0f));

    // Enable for 3D sounds to work (attach to camera node)
    //SoundListener *listener = serverCam_->GetNode()->CreateComponent<SoundListener>();
    //GetSubsystem<Audio>()->SetListener(listener);

    // Setup game viewport
    SetupGameViewports();


    return networkActorNode;
}

void MayaScape::CreateClientUI() {
    clientLevelLoading_ = true;

    ResourceCache *cache = GetSubsystem<ResourceCache>();
    auto *graphics = GetSubsystem<Graphics>();

    DebugRenderer *dbgRenderer = scene_->CreateComponent<DebugRenderer>();
    // Client will non-authoratively managed physics locally based on server copy
    clientPhysicsWorld_ = scene_->CreateComponent<PhysicsWorld>(LOCAL);
    clientPhysicsWorld_->SetFps(60);
    clientPhysicsWorld_->DrawDebugGeometry(true);
    clientPhysicsWorld_->SetDebugRenderer(dbgRenderer);
    // Disable interpolation (need determinism)
    clientPhysicsWorld_->SetInterpolation(false);

    clientPhysicsWorld_->SetEnabled(false);
    clientPhysicsWorld_->SetUpdateEnabled(false);

    UI *ui = GetSubsystem<UI>();

    packetsIn_ = ui->GetRoot()->CreateChild<Text>();
    packetsIn_->SetText("Packets in : 0");
    packetsIn_->SetFont(cache->GetResource<Font>(INGAME_FONT2), 14);
    packetsIn_->SetHorizontalAlignment(HA_RIGHT);
    packetsIn_->SetVerticalAlignment(VA_CENTER);
    packetsIn_->SetPosition(-50, -5);

    packetsOut_ = ui->GetRoot()->CreateChild<Text>();
    packetsOut_->SetText("Packets out: 0");
    packetsOut_->SetFont(cache->GetResource<Font>(INGAME_FONT2), 14);
    packetsOut_->SetHorizontalAlignment(HA_RIGHT);
    packetsOut_->SetVerticalAlignment(VA_CENTER);
    packetsOut_->SetPosition(-50, 5);


    // Set the default UI style and font
    //ui->GetRoot()->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    auto *font = cache->GetResource<Font>(INGAME_FONT2);
    auto *font2 = cache->GetResource<Font>(INGAME_FONT);


    auto *font4 = cache->GetResource<Font>(INGAME_FONT4);

    // Get powerbar texture
    Texture2D *powerBarTexture = cache->GetResource<Texture2D>("Textures/powerbar.png");
    if (!powerBarTexture)
        return;

    // Get powerbar background texture
    Texture2D *powerBarBkgTexture = cache->GetResource<Texture2D>("Textures/powerbar-bk.png");
    if (!powerBarBkgTexture)
        return;

    // Get RPM bar texture
    Texture2D *rpmBarTexture = cache->GetResource<Texture2D>("Textures/rpm.png");
    if (!rpmBarTexture)
        return;

    // Get RPM bar background texture
    Texture2D *rpmBarBkgTexture = cache->GetResource<Texture2D>("Textures/powerbar-bk.png");
    if (!rpmBarBkgTexture)
        return;

    // Get velocity bar texture
    Texture2D *velBarTexture = cache->GetResource<Texture2D>("Textures/velocity.png");
    if (!rpmBarTexture)
        return;

    // Get velocity bar background texture
    Texture2D *velBarBkgTexture = cache->GetResource<Texture2D>("Textures/powerbar-bk.png");
    if (!rpmBarBkgTexture)
        return;

    // Get mini map p1 texture
    Texture2D *miniMapP1Texture = cache->GetResource<Texture2D>("Textures/minimap-p1.png");
    if (!miniMapP1Texture)
        return;

    // Get mini map waypoint texture
    Texture2D *miniMapWPTexture = cache->GetResource<Texture2D>("Textures/minimap-wp.png");
    if (!miniMapWPTexture)
        return;

    // Get mini map background texture
    Texture2D *miniMapBkgTexture = cache->GetResource<Texture2D>("Textures/minimap-bk.png");
    if (!miniMapBkgTexture)
        return;

    // Get marker map background texture
    Texture2D *markerMapBkgTexture = cache->GetResource<Texture2D>("Textures/MarkerMap.png");
    if (!markerMapBkgTexture)
        return;

    // Get genotype texture
    Texture2D *genotypeTexture = cache->GetResource<Texture2D>("Textures/genotype.png");
    if (!genotypeTexture)
        return;

    // Get genotype background texture
    Texture2D *genotypeBkgTexture = cache->GetResource<Texture2D>("Textures/genotype-bk.png");
    if (!genotypeBkgTexture)
        return;

    // Get steering wheel texture
    Texture2D *steerWheelTexture = cache->GetResource<Texture2D>("Textures/steer-wheel.png");
    if (!steerWheelTexture)
        return;

    // Get steering actor texture
    Texture2D *steerActorTexture = cache->GetResource<Texture2D>("Textures/steer-actor.png");
    if (!steerWheelTexture)
        return;


    // Create sprite and add to the UI layout
    powerBarP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    powerBarBkgP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    rpmBarP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    rpmBarBkgP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    velBarP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    velBarBkgP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    //miniMapP1Sprite_ = ui->GetRoot()->CreateChild<Sprite>();
    //miniMapWPSprite_ = ui->GetRoot()->CreateChild<Sprite>();
    //miniMapBkgSprite_ = ui->GetRoot()->CreateChild<Sprite>();
    //markerMapBkgSprite_ = ui->GetRoot()->CreateChild<Sprite>();
    steerWheelSprite_ = ui->GetRoot()->CreateChild<Sprite>();
    steerActorSprite_ = ui->GetRoot()->CreateChild<Sprite>();


    // Set sprite texture
    powerBarP1Sprite_->SetTexture(powerBarTexture);
    powerBarBkgP1Sprite_->SetTexture(powerBarBkgTexture);
    rpmBarP1Sprite_->SetTexture(rpmBarTexture);
    rpmBarBkgP1Sprite_->SetTexture(rpmBarBkgTexture);
    velBarP1Sprite_->SetTexture(velBarTexture);
    velBarBkgP1Sprite_->SetTexture(rpmBarBkgTexture);
    //miniMapP1Sprite_->SetTexture(miniMapP1Texture);
    //miniMapWPSprite_->SetTexture(miniMapWPTexture);
    //miniMapBkgSprite_->SetTexture(miniMapBkgTexture);
    //markerMapBkgSprite_->SetTexture(markerMapBkgTexture);
    steerWheelSprite_->SetTexture(steerWheelTexture);
    steerActorSprite_->SetTexture(steerActorTexture);

    float textOverlap = 245.0f;

    powerBarText_ = ui->GetRoot()->CreateChild<Text>("powerBarText");
    powerBarText_->SetAlignment(HA_LEFT, VA_TOP);
    powerBarText_->SetPosition(10.0f, 23.0);
    powerBarText_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 16);
    powerBarText_->SetTextEffect(TE_SHADOW);
    powerBarText_->SetText(String("HEALTH"));
    powerBarText_->SetVisible(true);


    powerBarProgBarText_ = ui->GetRoot()->CreateChild<Text>("powerBarText");
    powerBarProgBarText_->SetAlignment(HA_LEFT, VA_TOP);
    powerBarProgBarText_->SetPosition(90.0f, 14.0);
    powerBarProgBarText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 30);
    powerBarProgBarText_->SetTextEffect(TE_SHADOW);
    powerBarProgBarText_->SetText(String(""));
    powerBarProgBarText_->SetVisible(true);
    powerBarProgBarText_->SetColor(Color(1,1,0.4));

    int textureWidth;
    int textureHeight;

    textureWidth = powerBarTexture->GetWidth();
    textureHeight = powerBarTexture->GetHeight();

    powerBarP1Sprite_->SetScale(256.0f / textureWidth);
    powerBarP1Sprite_->SetSize(textureWidth, textureHeight);
    powerBarP1Sprite_->SetHotSpot(textureWidth, textureHeight);
    powerBarP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    powerBarP1Sprite_->SetPosition(Vector2(280.0f, 50.0f));
    powerBarP1Sprite_->SetOpacity(1.0f);
    // Set a low priority so that other UI elements can be drawn on top
    powerBarP1Sprite_->SetPriority(-100);

    powerBarBkgP1Sprite_->SetScale(256.0f / textureWidth);
    powerBarBkgP1Sprite_->SetSize(textureWidth, textureHeight);
    powerBarBkgP1Sprite_->SetHotSpot(textureWidth, textureHeight);
    powerBarBkgP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    powerBarBkgP1Sprite_->SetPosition(Vector2(280.0f, 50.0f));
    powerBarBkgP1Sprite_->SetOpacity(0.2f);
    // Set a low priority so that other UI elements can be drawn on top
    powerBarBkgP1Sprite_->SetPriority(-100);

    powerBarP1Sprite_->SetVisible(false);
    powerBarBkgP1Sprite_->SetVisible(false);

    rpmBarText_ = ui->GetRoot()->CreateChild<Text>("rpmBarText");
    rpmBarText_->SetAlignment(HA_LEFT, VA_TOP);
    rpmBarText_->SetPosition(10.0f, 122.5);
    rpmBarText_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 16);
    rpmBarText_->SetTextEffect(TE_SHADOW);
    rpmBarText_->SetText(String("RPM"));
    rpmBarText_->SetVisible(true);

    rpmBarProgBarText_ = ui->GetRoot()->CreateChild<Text>("rpmBarText");
    rpmBarProgBarText_->SetAlignment(HA_LEFT, VA_TOP);
    rpmBarProgBarText_->SetPosition(90.0f, 113);
    rpmBarProgBarText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 30);
    rpmBarProgBarText_->SetTextEffect(TE_SHADOW);
    rpmBarProgBarText_->SetText(String(""));
    rpmBarProgBarText_->SetVisible(true);
    rpmBarProgBarText_->SetColor(Color(5/255.0f,173/255.0f,219/255.0f));
//    5, 173, 219


    textureWidth = rpmBarTexture->GetWidth();
    textureHeight = rpmBarTexture->GetHeight();

    rpmBarP1Sprite_->SetScale(256.0f / textureWidth);
    rpmBarP1Sprite_->SetSize(textureWidth, textureHeight);
    rpmBarP1Sprite_->SetHotSpot(textureWidth, textureHeight);
    rpmBarP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    rpmBarP1Sprite_->SetPosition(Vector2(280.0f, 150.0f));
    rpmBarP1Sprite_->SetOpacity(1.0f);
    // Set a low priority so that other UI elements can be drawn on top
    rpmBarP1Sprite_->SetPriority(-100);

    rpmBarBkgP1Sprite_->SetScale(256.0f / textureWidth);
    rpmBarBkgP1Sprite_->SetSize(textureWidth, textureHeight);
    rpmBarBkgP1Sprite_->SetHotSpot(textureWidth, textureHeight);
    rpmBarBkgP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    rpmBarBkgP1Sprite_->SetPosition(Vector2(280.0f, 150.0f));
    rpmBarBkgP1Sprite_->SetOpacity(0.2f);
    // Set a low priority so that other UI elements can be drawn on top
    rpmBarBkgP1Sprite_->SetPriority(-100);

    rpmBarP1Sprite_->SetVisible(false);
    rpmBarBkgP1Sprite_->SetVisible(false);

    velBarText_ = ui->GetRoot()->CreateChild<Text>("velBarText");
    velBarText_->SetAlignment(HA_LEFT, VA_TOP);
    velBarText_->SetPosition(10.0f, 72.5);
    velBarText_->SetFont(cache->GetResource<Font>(INGAME_FONT3), 16);
    velBarText_->SetTextEffect(TE_SHADOW);
    velBarText_->SetText(String("SPEED"));
    velBarText_->SetVisible(true);

    velBarProgBarText_ = ui->GetRoot()->CreateChild<Text>("rpmBarText");
    velBarProgBarText_->SetAlignment(HA_LEFT, VA_TOP);
    velBarProgBarText_->SetPosition(90.0f, 65);
    velBarProgBarText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 30);
    velBarProgBarText_->SetTextEffect(TE_SHADOW);
    velBarProgBarText_->SetText(String(""));
    velBarProgBarText_->SetVisible(true);
    velBarProgBarText_->SetColor(Color(0.7,0.1,1));


    textureWidth = rpmBarTexture->GetWidth();
    textureHeight = rpmBarTexture->GetHeight();

    velBarP1Sprite_->SetScale(256.0f / textureWidth);
    velBarP1Sprite_->SetSize(textureWidth, textureHeight);
    velBarP1Sprite_->SetHotSpot(textureWidth, textureHeight);
    velBarP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    velBarP1Sprite_->SetPosition(Vector2(280.0f, 100.0f));
    velBarP1Sprite_->SetOpacity(1.0f);
    // Set a low priority so that other UI elements can be drawn on top
    velBarP1Sprite_->SetPriority(-100);

    velBarBkgP1Sprite_->SetScale(256.0f / textureWidth);
    velBarBkgP1Sprite_->SetSize(textureWidth, textureHeight);
    velBarBkgP1Sprite_->SetHotSpot(textureWidth, textureHeight);
    velBarBkgP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    velBarBkgP1Sprite_->SetPosition(Vector2(280.0f, 100.0f));
    velBarBkgP1Sprite_->SetOpacity(0.2f);
    // Set a low priority so that other UI elements can be drawn on top
    velBarBkgP1Sprite_->SetPriority(-100);

    velBarP1Sprite_->SetVisible(false);
    velBarBkgP1Sprite_->SetVisible(false);


    textureWidth = miniMapP1Texture->GetWidth();
    textureHeight = miniMapP1Texture->GetHeight();

       float miniMapP1X = 776.0f+45.0f;
       float miniMapP1Y = 300.0f-15.0f;

       /*
    miniMapP1Sprite_->SetScale(0.4);//256.0f / textureWidth);
    miniMapP1Sprite_->SetSize(textureWidth, textureHeight);
    miniMapP1Sprite_->SetHotSpot(textureWidth / 2, textureHeight / 2);
    miniMapP1Sprite_->SetAlignment(HA_LEFT, VA_TOP);
    miniMapP1Sprite_->SetPosition(Vector2(miniMapP1X-16.0f, miniMapP1Y));
//    miniMapP1Sprite_->SetPosition(Vector2(miniMapP1X+256.0f-16.0f, miniMapP1Y));

    miniMapP1Sprite_->SetOpacity(0.9f);
    // Set a low priority so that other UI elements can be drawn on top
    miniMapP1Sprite_->SetPriority(-100);


    textureWidth = miniMapWPTexture->GetWidth();
    textureHeight = miniMapWPTexture->GetHeight();

    //   float miniMapP1X = 776.0f+45.0f;
    //   float miniMapP1Y = 300.0f-15.0f;

    miniMapWPSprite_->SetScale(0.4);//256.0f / textureWidth);
    miniMapWPSprite_->SetSize(textureWidth, textureHeight);
    miniMapWPSprite_->SetHotSpot(textureWidth / 2, textureHeight / 2);
    miniMapWPSprite_->SetAlignment(HA_LEFT, VA_TOP);
//    miniMapP1Sprite_->SetPosition(Vector2(miniMapP1X-16.0f, miniMapP1Y));c
//    miniMapP1Sprite_->SetPosition(Vector2(miniMapP1X+256.0f-16.0f, miniMapP1Y));

    miniMapWPSprite_->SetOpacity(0.9f);
    // Set a low priority so that other UI elements can be drawn on top
    miniMapWPSprite_->SetPriority(-100);


    textureWidth = miniMapBkgTexture->GetWidth();
    textureHeight = miniMapBkgTexture->GetHeight();

    float miniMapX = 1000.0f + 45.0f;
    float miniMapY = 300.0f - 15.0f;

    miniMapBkgSprite_->SetScale(256.0f / textureWidth);
    miniMapBkgSprite_->SetSize(textureWidth, textureHeight);
    miniMapBkgSprite_->SetHotSpot(textureWidth, textureHeight);
    miniMapBkgSprite_->SetAlignment(HA_LEFT, VA_TOP);
    miniMapBkgSprite_->SetPosition(Vector2(miniMapX, miniMapY));
    miniMapBkgSprite_->SetOpacity(0.2f);
    // Set a low priority so that other UI elements can be drawn on top
    miniMapBkgSprite_->SetPriority(-100);

    //miniMapP1Sprite_->SetVisible(true);
    //miniMapWPSprite_->SetVisible(true);
    //miniMapBkgSprite_->SetVisible(true);
    miniMapP1Sprite_->SetVisible(false);
    miniMapWPSprite_->SetVisible(false);
    miniMapBkgSprite_->SetVisible(false);

    textureWidth = markerMapBkgTexture->GetWidth();
    textureHeight = markerMapBkgTexture->GetHeight();

    markerMapBkgSprite_->SetScale(256.0f / textureWidth);
    markerMapBkgSprite_->SetSize(textureWidth, textureHeight);
    markerMapBkgSprite_->SetHotSpot(textureWidth, textureHeight);
    markerMapBkgSprite_->SetAlignment(HA_LEFT, VA_TOP);
    markerMapBkgSprite_->SetPosition(Vector2(miniMapX, miniMapY));
    markerMapBkgSprite_->SetOpacity(0.5f);
    // Set a low priority so that other UI elements can be drawn on top
    miniMapBkgSprite_->SetPriority(-100);
    markerMapBkgSprite_->SetVisible(true);

*/
    textureWidth = steerWheelTexture->GetWidth();
    textureHeight = steerWheelTexture->GetHeight();

    float steerWheelX = 900.0f;
    float steerWheelY = 600.0f - 15.0f;

    steerWheelSprite_->SetScale(256.0f / textureWidth);
    steerWheelSprite_->SetSize(textureWidth, textureHeight);
    steerWheelSprite_->SetHotSpot(textureWidth / 2, textureHeight / 2);
    steerWheelSprite_->SetAlignment(HA_LEFT, VA_TOP);
    steerWheelSprite_->SetPosition(Vector2(steerWheelX, steerWheelY));
    steerWheelSprite_->SetOpacity(0.5f);
    // Set a low priority so that other UI elements can be drawn on top
    steerWheelSprite_->SetPriority(-100);
    steerWheelSprite_->SetVisible(true);


    steerActorSprite_->SetScale(256.0f / textureWidth);
    steerActorSprite_->SetSize(textureWidth, textureHeight);
    steerActorSprite_->SetHotSpot(textureWidth / 2, textureHeight / 2);
    steerActorSprite_->SetAlignment(HA_LEFT, VA_TOP);
    steerActorSprite_->SetPosition(Vector2(steerWheelX, steerWheelY));
    steerActorSprite_->SetOpacity(0.5f);
    // Set a low priority so that other UI elements can be drawn on top
    steerActorSprite_->SetPriority(-100);
    steerActorSprite_->SetVisible(true);


    // Debug text
    for (int i = 0; i < NUM_DEBUG_FIELDS; i++) {
        debugText_[i] = ui->GetRoot()->CreateChild<Text>("DebugText");
        debugText_[i]->SetAlignment(HA_LEFT, VA_CENTER);
        debugText_[i]->SetPosition(10.0f, 500.0 + (i * 14));
        debugText_[i]->SetFont(font, 12);
        debugText_[i]->SetTextEffect(TE_SHADOW);
        debugText_[i]->SetVisible(true);
        std::string debugData1;
        debugData1.append("-");
        debugText_[i]->SetText(debugData1.c_str());
    }

    // Music radio track text
    for (int i = 0; i < NUM_RADIO_TRACK_FIELDS; i++) {
        radioText_[i] = ui->GetRoot()->CreateChild<Text>("RadioTrackListText");

        radioText_[i]->SetAlignment(HA_RIGHT, VA_TOP);
        radioText_[i]->SetPosition(-20.0f, 20 + (i * 20));
        radioText_[i]->SetVisible(true);
        radioText_[i]->SetColor(Color(235/255.0f, 217/255.0f, 255/255));
        radioText_[i]->SetFont(font4, 19);
        radioText_[i]->SetTextEffect(TE_SHADOW);
        radioText_[i]->SetVisible(true);
        std::string debugData1;
        debugData1.append("-");
        radioText_[i]->SetText(debugData1.c_str());
    }




}

void MayaScape::DestroyPlayer(Connection *connection) {

    ResourceCache *cache = GetSubsystem<ResourceCache>();

    /// Retrieve the username for the client
    VariantMap identity = connection->GetIdentity();
    String username = String(identity["UserName"]);

    // Remove network actor from csp server
    cspServer_->snapshot.removeNode(actorMap_[connection]->GetNode());

    String playerName = actorMap_[connection]->GetUserName();
    // Store in local login list
    loginList_.Remove(playerName);

    ClientObj *actor = actorMap_[connection];
    actor->SetEnabled(false);
    actor->Remove();


    // Clear maps
    actorMap_.Erase(connection);
    actorTextMap_.Erase(connection);
    serverObjects_.Erase(connection);

    // Push update to clients
    connection->SendServerUpdate();
}

// Spawn Player (NetworkActor on Server for Client)
Node *MayaScape::SpawnPlayer(Connection *connection) {

    // Store connection as most recent client
    lastConnection_ = connection;

    ResourceCache *cache = GetSubsystem<ResourceCache>();

    /// Retrieve the username for the client
    VariantMap identity = connection->GetIdentity();
    String username = String(identity["UserName"]);
    String name = String(String("actor-") + username);
    // Create a new network actor for the player
    SharedPtr<Node> networkActorNode(scene_->CreateChild(name, REPLICATED));
    networkActorNode->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

    NetworkActor *actor = networkActorNode->CreateComponent<NetworkActor>(REPLICATED);
    actor->Init(networkActorNode);

    //actor->SetClientInfo(name, Random(1,100), Vector3(Random(-400.0f,400.0f),Random(20.0f,80.0f),Random(-400.0f,400.0f)));

    auto* body = networkActorNode->GetComponent<RigidBody>(true);



    // Set calculated network actor position

    Vector3 actorPos = Vector3(0,0,0);
    if (starAMarkerSet_) {
        Vector3 spawnDir = (starBMarker_-starAMarker_);
        Vector3 startPos = starAMarker_;

        float w = 1.2;

        //actorPos = Quaternion(0,90,0) * (startPos+spawnDir*w);
        actorPos = Quaternion(0,0,0) * (startPos+spawnDir*w);
        actor->GetBody()->SetPosition(actorPos);

        // Clamp y to start marker
        //actorPos.y_ = starAMarker_.y_;

    }

    actor->SetClientInfo(username, Random(1,100), Vector3(actor->GetPosition()));

    // Generate vehicle

    String vehicleName = "vehicle-" + username;
    // Create a new vehicle for the player
    SharedPtr<Node> vehicleNode(scene_->CreateChild(vehicleName, REPLICATED));
    //vehicleNode->SetRotation(Quaternion(0.0f, 180.0f, 0.0f));
    Vehicle *vehicle = vehicleNode->CreateComponent<Vehicle>(REPLICATED);
    vehicle->Init(vehicleNode);

    vehicleNode->SetPosition(Vector3(actor->GetBody()->GetPosition())+Vector3(0,-5,-40));
    //vehicle->GetRaycastVehicle()->GetBody()->SetPosition(Vector3(actor->GetPosition())-Vector3::UP*50.0f);
    vehicleNode->SetRotation(Quaternion(0.0f, Random(0.0f, 0.0f), 0.0f));
    // Attach vehicle to actor
    actor->vehicle_ = vehicle;

    // Create text3d client info node
    Node *plyFltTextNode = vehicleNode->CreateChild("Actor FloatText", REPLICATED);
    Text3D *plyFltText_ = plyFltTextNode->CreateComponent<Text3D>();
    actorTextMap_[connection] = plyFltText_;
    plyFltText_->SetColor(Color(77.0f/255.0f,0.0f,1.0f));
    plyFltText_->SetEffectColor(Color::BLACK);
    plyFltText_->GetNode()->SetScale(18.0f);
    plyFltText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 16);
    plyFltText_->SetFaceCameraMode(FC_ROTATE_XYZ);
    plyFltText_->GetNode()->SetPosition(Vector3(0,19.0f,-CHASSIS_WIDTH / 2.0f)*0.9f);

    //plyFltText_->GetNode()->SetPosition(actor->GetPosition() + Vector3(0,20.0f,0));
    plyFltText_->SetText(username);

    // Push the new comer into the map
    clientMap_[username] = networkActorNode;
    actorMap_[connection] = actor;
    serverObjects_[connection] = networkActorNode;

    // Add to focus map
    focusObjects_.Push(Vector3(actor->GetPosition()));
    // Increment focus object
    focusIndex_++;


    // Give the ownership to the client
    networkActorNode->SetOwner(connection);
    vehicleNode->SetOwner(connection);

    // 2. Create a new camera following the actor
    // ** THIS APPEARS TO BE CRITICAL FOR CLIENT SCENE REPLICATION TO START
    Graphics* graphics = GetSubsystem<Graphics>();
    String cameraName = "camera_" + username;
    Node* cameraNode = networkActorNode->CreateChild(cameraName, REPLICATED);
    // Set position to force update
    cameraNode->SetPosition(Vector3(0.0f, 2.0f, 0.0f));

    // Give the ownership to the client
    cameraNode->SetOwner(connection);

    // Push update to clients
    connection->SendServerUpdate();

    cspServer_->snapshot.addNode(networkActorNode);





    // smooth step
    vehicleRot_ = vehicleNode->GetRotation();
    Quaternion dir(vehicleRot_.YawAngle(), Vector3::UP);
    dir = dir * Quaternion(0, Vector3::UP);
    dir = dir * Quaternion(0, Vector3::RIGHT);
    targetCameraPos_ = vehicleNode->GetPosition() - dir * Vector3(0.0f, 0.0f, CLIENT_CAMERA_DISTANCE);

    return networkActorNode;
}

// Spawn Player (NetworkActor on Server for AI agent)
NetworkActor *MayaScape::SpawnPlayer(unsigned int id) {

    ResourceCache *cache = GetSubsystem<ResourceCache>();

    /// Retrieve the username for the ai
    String username = String(String("ai-") + String(id));

    // Locate an previous actor node
    SharedPtr<Node> prevActorNode(scene_->GetChild(username));

    // Remove previous actor
    if (prevActorNode) {
        prevActorNode->Remove();
    }

    // Create a new network actor for the player
    SharedPtr<Node> networkActorNode(scene_->CreateChild(username, REPLICATED));
    networkActorNode->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

    NetworkActor *actor = networkActorNode->CreateComponent<NetworkActor>(REPLICATED);
    actor->Init(networkActorNode);
    String name = String(String("actor-") + username);

    Vector3 actorPos = Vector3(0,0,0);
    if (starAMarkerSet_) {
        Vector3 spawnDir = (starBMarker_-starAMarker_);
        Vector3 startPos = starAMarker_;

        float w = 0.14f*id;

        //float w = 1.2;

        //actorPos = Quaternion(0,90,0) * (startPos+spawnDir*w);
//        actorPos = Quaternion(0,0,0) * (startPos+spawnDir*w);


        //actorPos = Quaternion(0,90,0) * (startPos+spawnDir*w);
        actorPos = Quaternion(0,0,0) * (startPos+spawnDir*w);
        actor->GetNode()->SetPosition(actorPos);
        // Clamp y to start marker
        //actorPos.y_ = starAMarker_.y_;

    }

    actor->SetClientInfo(name, Random(1,100), actorPos);

    String vehicleName = "vehicle-" + username;
    // Create a new vehicle for the player
    SharedPtr<Node> vehicleNode(scene_->CreateChild(vehicleName, REPLICATED));
    //vehicleNode->SetRotation(Quaternion(0.0f, 180.0f, 0.0f));
    Vehicle *vehicle = vehicleNode->CreateComponent<Vehicle>(REPLICATED);
    vehicle->Init(vehicleNode);
    actor->SetClientInfo(username, Random(1,100), Vector3(actor->GetPosition()));
    vehicleNode->SetPosition(Vector3(actor->GetPosition()));
    vehicleNode->SetRotation(Quaternion(0.0f, Random(0.0f, 360.0f), 0.0f));
    // Attach vehicle to actor
    actor->vehicle_ = vehicle;

    // Create text3d client info node
    Node *plyFltTextNode = vehicleNode->CreateChild("Actor FloatText", REPLICATED);
    Text3D *plyFltText_ = plyFltTextNode->CreateComponent<Text3D>();
    aiActorTextMap_[id] = plyFltText_;
    plyFltText_->SetColor(Color(77.0f/255.0f,0.23f,1.0f));
    plyFltText_->SetEffectColor(Color::BLACK);
    plyFltText_->GetNode()->SetScale(18.0f);
    plyFltText_->SetFont(cache->GetResource<Font>(INGAME_FONT), 16);
    plyFltText_->SetFaceCameraMode(FC_ROTATE_XYZ);
    plyFltText_->GetNode()->SetPosition(Vector3(0,19.0f,-CHASSIS_WIDTH / 2.0f)*0.9f);
    plyFltText_->SetText(username);
    //Vector3(0, 50.0f, CHASSIS_WIDTH / 2.0f));

    // Push the new comer into the map
    clientMap_[username] = networkActorNode;
    aiActorMap_[id] = actor;

    // Add to focus map
    focusObjects_.Push(Vector3(actor->GetPosition()));
    // Increment focus object
    focusIndex_++;

    // Snap to latest bot
    flyCam_ = vehicleNode->GetPosition();

    // Give the ownership to the client
    //networkActorNode->SetOwner(connection);
    //vehicleNode->SetOwner(connection);

    return actor;
}

void MayaScape::InitiateGameMap(Scene *scene) {

    ResourceCache *cache = GetSubsystem<ResourceCache>();
    auto *graphics = GetSubsystem<Graphics>();

    UI *ui = GetSubsystem<UI>();

    packetsIn_ = ui->GetRoot()->CreateChild<Text>();
    packetsIn_->SetText("Packets in : 0");
    packetsIn_->SetFont(cache->GetResource<Font>(INGAME_FONT2), 12);
    packetsIn_->SetHorizontalAlignment(HA_RIGHT);
    packetsIn_->SetVerticalAlignment(VA_CENTER);
    packetsIn_->SetPosition(-50, -10);

    packetsOut_ = ui->GetRoot()->CreateChild<Text>();
    packetsOut_->SetText("Packets out: 0");
    packetsOut_->SetFont(cache->GetResource<Font>(INGAME_FONT2), 12);
    packetsOut_->SetHorizontalAlignment(HA_RIGHT);
    packetsOut_->SetVerticalAlignment(VA_CENTER);
    packetsOut_->SetPosition(-50, 10);

    // Debug text
    for (int i = 0; i < NUM_DEBUG_FIELDS; i++) {
        debugText_[i] = ui->GetRoot()->CreateChild<Text>("DebugText");
        debugText_[i]->SetAlignment(HA_LEFT, VA_CENTER);
        debugText_[i]->SetPosition(10.0f, 10.0 + (i * 12));
        debugText_[i]->SetFont(cache->GetResource<Font>(INGAME_FONT2), 12);
        debugText_[i]->SetTextEffect(TE_SHADOW);
        debugText_[i]->SetVisible(true);
        std::string debugData1;
        debugData1.append("-");
        debugText_[i]->SetText(debugData1.c_str());
    }


    // Genetic Algorithm statistics text
    for (int i = 0; i < NUM_STAT_FIELDS; i++) {
        genAlgStatsText_[i] = ui->GetRoot()->CreateChild<Text>("GenAlgStatsText");
        genAlgStatsText_[i]->SetAlignment(HA_LEFT, VA_TOP);
        genAlgStatsText_[i]->SetPosition(10.0f, 1.0 + (i * 12));
        genAlgStatsText_[i]->SetFont(cache->GetResource<Font>(INGAME_FONT2), 12);
        genAlgStatsText_[i]->SetTextEffect(TE_SHADOW);
        genAlgStatsText_[i]->SetVisible(false);
        std::string statData1;
        statData1.append("-");
        genAlgStatsText_[i]->SetText(statData1.c_str());
    }

    // Set the default UI style and font
    //ui->GetRoot()->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    auto *font = cache->GetResource<Font>(INGAME_FONT2);
    auto *font2 = cache->GetResource<Font>(INGAME_FONT);
    auto *font4 = cache->GetResource<Font>(INGAME_FONT4);


/*
    // Create a directional light with shadows
        Node *lightNode = scene_->CreateChild("DirectionalLight", REPLICATED);
        lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
        Light *light = lightNode->CreateComponent<Light>();
        light->SetLightType(LIGHT_DIRECTIONAL);
        light->SetCastShadows(true);
        light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
        light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
        light->SetSpecularIntensity(0.5f);
        //lightNode->SetNetPositionAttr(Vector3(20, 30, 40));
*/

        // All static scene content and the camera are also created as local,
        // so that they are unaffected by scene replication and are
        // not removed from the client upon connection.
        // Create a Zone component first for ambient lighting & fog control.

        // Create static scene content. First create a zone for ambient lighting and fog control
        Node *zoneNode = scene_->CreateChild("Zone", REPLICATED);
        Zone *zone = zoneNode->CreateComponent<Zone>();
//        zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
//        zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));


    float r1 = Random(0.01f,0.1f);
    float r2 = Random(0.01f,0.1f);
    float r3 = Random(0.01f,0.3f);
    zone->SetAmbientColor(Color(r1, r2, r3));
    zone->SetFogColor(Color(r1*2.0f, r2*2.0f, r3*2.0f));

        zone->SetFogStart(700.0f);
        zone->SetFogEnd(58000.0f);
        zone->SetBoundingBox(BoundingBox(-60000.0f, 60000.0f));
        //zoneNode->SetNetPositionAttr(Vector3(40, 50, 70));


/*

    using namespace std;

    // Create heightmap terrain with collision
    Node *terrainNode = scene_->CreateChild("Terrain", REPLICATED);
    terrainNode->SetPosition(Vector3::ZERO);

    terrain_ = terrainNode->CreateComponent<Terrain>(REPLICATED);
    terrain_->SetPatchSize(128);
    terrain_->SetSpacing(Vector3(2.8f, 0.2f, 2.8f));
//    terrain->SetSpacing(Vector3(3.0f, 0.1f, 3.0f)); // Spacing between vertices and vertical resolution of the height map
   // terrainNode->SetNetPositionAttr(Vector3::ZERO);

    //    terrain->SetHeightMap(cache->GetResource<Image>("Offroad/Terrain/HeightMapRace-257.png"));
//    terrain->SetMaterial(cache->GetResource<Material>("Offroad/Terrain/TerrainRace-256.xml"));
    //terrain_->SetMarkerMap(cache->GetResource<Image>("Textures/MarkerMap.png"));
    terrain_->SetHeightMap(cache->GetResource<Image>("Textures/HeightMap.png"));
    terrain_->SetMaterial(cache->GetResource<Material>("Materials/Terrain.xml"));
    terrain_->GetNode()->SetScale(15.0f);

    terrain_->SetOccluder(true);
*/////


    // TRACK MARKER
    // HSL -> 0.500000059604645,1,0.643137276172638
// NOT SUPPORTED -> Without legacy TileMap3D updates
    /*
    // Search for track marker
    int trackX = 0;
    int trackY = 0;
    for (int k = 0; k < terrain_->GetMarkerMap()->GetHeight(); k++) {
        for (int j = 0; j < terrain_->GetMarkerMap()->GetWidth(); j++) {
            Vector3 hsl_ = terrain_->GetMarkerMap()->GetPixel(k, j).ToHSL();
            //URHO3D_LOGINFOF("terrain marker map[x,y]=[%f,%f,%f]", j, k, hsl_.x_, hsl_.y_, hsl_.z_);


            if (hsl_ == bkgMarkerToken)
                continue;

            if (hsl_ == treeMarkerToken) {
                trees_.Push(Vector3((float) j, 0.0f, (float) k));
            } else if (hsl_ == trackMarkerToken) {
                trackX = j;
                trackY = k;
            } else if (hsl_ == waypointToken) {
                waypoints_.Push((Vector3((float) j, 0.0f, (float) k)));
            } else {
                // Store track marker
                URHO3D_LOGINFOF("***** UNKNOWN terrain marker map[%d,%d]=[%f,%f,%f]", j, k, hsl_.x_, hsl_.y_,
                                hsl_.z_);
            }

        }
    }
*/

/*
    int reduceFactor = ((float) trees_.Size() * 1.99f);
    // Drop trees to reduce saturation of trees
    int reduceSize = Min(trees_.Size(), reduceFactor);

    for (int j = 0; j < reduceSize; j++) {
        trees_.Erase(Random(0, trees_.Size()), 1);
    }

    URHO3D_LOGINFOF("***** TREE COUNT: [%d]", trees_.Size());
    URHO3D_LOGINFOF("***** WAYPOINT COUNT: [%d]", waypoints_.Size());

    RigidBody *body = terrainNode->CreateComponent<RigidBody>(REPLICATED);
    body->SetCollisionLayer(NETWORKACTOR_COL_LAYER); // Use layer bitmask 2 for static geometry
    terrainShape_ = terrainNode->CreateComponent<CollisionShape>(REPLICATED);

    // Assigns terrain collision map (calculated based on heightmap)
    terrainShape_->SetTerrain();
*/
    // Load race track at track marker

    // Convert marker position to world position for track
    int w = 64;//terrain_->GetMarkerMap()->GetWidth();
    int h = 64;//terrain_->GetMarkerMap()->GetHeight();
    int trackX = 0;
    int trackY = 0;

    float trackOffsetX = -mapSize / 2;
    float trackOffsetY = -mapSize / 2;
    float trackPosX = (((float) trackX / (float) w) * mapSize) + trackOffsetX;
    float trackPosZ = (((float) trackY / (float) h) * mapSize) + trackOffsetY;

    // Convert from mini map to world position
//    Vector3 shiftedRange = Vector3(trackPosX, 0, trackPosZ) - Vector3(mapSize/2, mapSize/2, mapSize/2);

  //  URHO3D_LOGINFOF("-----> SET RACE TRACK TO location in world space [%f,%f,%f]", trackPosX, 0.0f, trackPosZ);

    /*
    // 1600+1600
    float xRange = (shiftedRange.x_*mapSize) / miniMapWidth;
    float zRange = (shiftedRange.z_*mapSize) / miniMapHeight;
*/


    ///code/dev/MonkeyMaya_com/bin/Data/Models/logo/Models/

    Node *adjNode;
/*
    // Monkey Maya logo ////
    std::string mmlogoMdlPath = "Models/logo/Models/mm_logo.mdl";
    auto* nodeLG = scene_->CreateChild("MM Logo", REPLICATED);
    nodeLG->SetPosition(Vector3(0, 0, 0));
    nodeLG->SetScale(30.0f);
    adjNode = nodeLG->CreateChild("AdjNode");


    auto *objectLG = adjNode->CreateComponent<StaticModel>(REPLICATED);
    //std::string matPath = "Models/Tracks/Models/trackA.txt";
    auto *modelLG = cache->GetResource<Model>(mmlogoMdlPath.c_str());
    objectLG->SetModel(modelLG);
    //object->ApplyMaterialList(matPath.c_str());
    objectLG->SetCastShadows(true);
    adjNode->SetRotation(Quaternion(0.0, 0.0, 0.0f));
*/

    ////

/*
    Vector3 trackMarkPosA = Vector3(53.5f, 4.2f, -214.0f);

    nodeLG = scene_->CreateChild("MM Logo", REPLICATED);
    nodeLG->SetPosition(trackMarkPosA + Vector3(-240.0f, 0.0f, 50.0f));
    nodeLG->SetRotation(Quaternion(0.0f, 23.0f, -90.0f));
    nodeLG->SetScale(180.0f);

    auto *objectLG2 = nodeLG->CreateComponent<StaticModel>(REPLICATED);
    //std::string matPath = "Models/Tracks/Models/trackA.txt";
    auto *modelLG2 = cache->GetResource<Model>(mmlogoMdlPath.c_str());
    objectLG2->SetModel(modelLG2);
    //object->ApplyMaterialList(matPath.c_str());
    objectLG2->SetCastShadows(true);

*/


    trackPosX = -4800.0f;
    trackPosZ = 700.0f;
/*
    // RACE TRACK ////
    raceTrack_ = scene_->CreateChild("RaceTrack", REPLICATED);

    int trackNum = 1;
    StaticModel *objectRT;

    switch (trackNum) {
        case 0: {
            objectRT = adjNode->CreateComponent<StaticModel>(REPLICATED);
            std::string mdlPath0 = "Models/Tracks/Models/trackA.mdl";
            std::string matPath0 = "Models/Tracks/Models/trackA.txt";
            auto *modelRT0 = cache->GetResource<Model>(mdlPath0.c_str());
            objectRT->SetModel(modelRT0);
            objectRT->ApplyMaterialList(matPath0.c_str());
            objectRT->SetCastShadows(true);
        }
        break;

        case 1: {
            Vector3 position(trackPosX, 80.0f, trackPosZ);
            //position.y_ = terrain_->GetHeight(position) + 2.0f;
            raceTrack_->SetPosition(position);
            // Create a rotation quaternion from up vector to terrain normal
            //raceTrack_->SetRotation(Quaternion(Vector3::UP, terrain_->GetNormal(position)));
            adjNode = raceTrack_->CreateChild("AdjNode");
            adjNode->SetRotation(Quaternion(0.0, 0.0, 0.0f));

            raceTrack_->SetScale(500.0f);

            objectRT = adjNode->CreateComponent<StaticModel>(REPLICATED);
            std::string mdlPath1 = "Models/Tracks/Models/A_trk.mdl";
            std::string matPath1 = "Models/Tracks/Models/A_trk.txt";
            auto *modelRT1 = cache->GetResource<Model>(mdlPath1.c_str());
            objectRT->SetModel(modelRT1);
            objectRT->ApplyMaterialList(matPath1.c_str());
            objectRT->SetCastShadows(true);

        }
            break;


        case 2: {
            Vector3 position(200, 3000.0f, 200);
            //position.y_ = terrain_->GetHeight(position) + 2.0f;
            raceTrack_->SetPosition(position);
            // Create a rotation quaternion from up vector to terrain normal
            //raceTrack_->SetRotation(Quaternion(Vector3::UP, terrain_->GetNormal(position)));
            adjNode = raceTrack_->CreateChild("AdjNode");
            adjNode->SetRotation(Quaternion(0.0, 0.0, 0.0f));
            raceTrack_->SetScale(240.0f);

            objectRT = adjNode->CreateComponent<StaticModel>(REPLICATED);
            std::string mdlPath1 = "Models/Tracks/Models/SpinTrack.mdl";
            std::string matPath1 = "Models/Tracks/Models/SpinTrack.txt";
            auto *modelRT1 = cache->GetResource<Model>(mdlPath1.c_str());
            objectRT->SetModel(modelRT1);
            objectRT->ApplyMaterialList(matPath1.c_str());
            objectRT->SetCastShadows(true);




        }


            break;

    }


    body = adjNode->CreateComponent<RigidBody>(REPLICATED);
    body->SetCollisionLayer(2);
    trackColShape_ = adjNode->CreateComponent<CollisionShape>(REPLICATED);
    trackColShape_->SetTriangleMesh(objectRT->GetModel(), 0);

//        trackColShape_->SetConvexHull(model);

*/
    // Place trees based on markers



    // Convert from mini map to world position
//    Vector3 shiftedRange = Vector3(trackPosX, 0, trackPosZ) - Vector3(mapSize/2, mapSize/2, mapSize/2);

    //URHO3D_LOGINFOF("-----> SET RACE TRACK TO location in world space [%f,%f,%f]", trackPosX, 0.0f, trackPosZ);
/*
    // Place trees
    for (unsigned i = 0; i < trees_.Size(); ++i) {
        float treeOffsetX = -mapSize / 2;
        float treeOffsetY = -mapSize / 2;
        // Convert marker position to world position for track
        float treePosX =
                (((float) trees_[i].x_ / (float) terrain_->GetMarkerMap()->GetWidth()) * mapSize) + treeOffsetX;
        float treePosZ =
                (((float) trees_[i].z_ / (float) terrain_->GetMarkerMap()->GetHeight()) * mapSize) + treeOffsetY;

        Node *objectNode = scene_->CreateChild("Tree", REPLICATED);
        Vector3 position(treePosX, 0.0f, treePosZ);
        position.y_ = terrain_->GetHeight(position) - 0.1f;
        objectNode->SetPosition(position);
        //objectNode->SetEnabled(false);


        // Create a rotation quaternion from up vector to terrain normal
        objectNode->SetRotation(Quaternion(Vector3::UP, terrain_->GetNormal(position)));
        Node *adjNode = objectNode->CreateChild("AdjNode", REPLICATED);
        adjNode->SetRotation(Quaternion(0.0, 0.0, -90.0f));

        objectNode->SetScale(20.0f);

        auto *object = adjNode->CreateComponent<StaticModel>(REPLICATED);

        // Random
        int r = std::round(Random(0.0f, 5.0f));
        switch (r) {
            case 0:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-baobab_orange.mdl"));
                break;
            case 1:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-birch02.mdl"));
                break;
            case 2:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-elipse.mdl"));
                break;
            case 3:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-fir.mdl"));
                break;
            case 4:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-oak.mdl"));
                break;
            case 5:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-lime.mdl"));
                break;
        }

        //       object->SetMaterial(cache->GetResource<Material>("Materials/LOWPOLY_COLORS.xml")
        object->SetMaterial(cache->GetResource<Material>("Materials/LOWPOLY-COLORS.xml"));
        object->SetCastShadows(true);

        auto *body = adjNode->CreateComponent<RigidBody>(REPLICATED);
        body->SetCollisionLayer(2);
        auto *shape = objectNode->CreateComponent<CollisionShape>(REPLICATED);
        shape->SetTriangleMesh(object->GetModel(), 0);
    }

    // Place waypoints

    // Store focusObjects index for waypoint reference
    wpStartIndex_ = focusObjects_.Size() + 1;
    for (unsigned i = 0; i < waypoints_.Size(); ++i) {
        float wpOffsetX = -mapSize / 2;
        float wpOffsetY = -mapSize / 2;
        // Convert marker position to world position for track
        float wpPosX =
                (((float) waypoints_[i].x_ / (float) terrain_->GetMarkerMap()->GetWidth()) * mapSize) + wpOffsetX;
        float wpPosZ =
                (((float) waypoints_[i].z_ / (float) terrain_->GetMarkerMap()->GetHeight()) * mapSize) + wpOffsetY;
//terrain_->GetHeight(Vector3(wpPosX, 0.0f, wpPosZ))
        waypointsWorld_.Push(Vector3(wpPosX, 0, wpPosZ));

        Node *objectNode = scene_->CreateChild("Waypoint", LOCAL);
        Vector3 position(wpPosX, 0.0f, wpPosZ);
        position.y_ = terrain_->GetHeight(position) - 0.1f;
        objectNode->SetPosition(position);

        // Store tree position as focus
        //focusObjects_.Push(position);

        // Create a rotation quaternion from up vector to terrain normal
        objectNode->SetRotation(Quaternion(Vector3::UP, terrain_->GetNormal(position)));
        Node *adjNode = objectNode->CreateChild("AdjNode", LOCAL);
        adjNode->SetRotation(Quaternion(0.0, 0.0, -90.0f));

        objectNode->SetScale(20.0f);

        auto *object = adjNode->CreateComponent<StaticModel>(LOCAL);
        object->SetModel(cache->GetResource<Model>("Models/AssetPack/castle-flag.mdl"));

        //       object->SetMaterial(cache->GetResource<Material>("Materials/LOWPOLY_COLORS.xml")
        object->SetMaterial(cache->GetResource<Material>("Materials/LOWPOLY-COLORS.xml"));
        object->SetCastShadows(true);
        object->SetEnabled(false);

        auto *body = adjNode->CreateComponent<RigidBody>(LOCAL);
        body->SetCollisionLayer(2);
        auto *shape = objectNode->CreateComponent<CollisionShape>(LOCAL);
        shape->SetTriangleMesh(object->GetModel(), 0);
    }

*/


    //
/*
    // Create 1000 mushrooms in the terrain. Always face outward along the terrain normal
    const unsigned NUM_MUSHROOMS = 1000;
    for (unsigned i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node* objectNode = scene_->CreateChild("Mushroom");
        Vector3 position(Random(2000.0f) - 1000.0f, 0.0f, Random(2000.0f) - 1000.0f);
        position.y_ = terrain_->GetHeight(position) - 0.1f;
        objectNode->SetPosition(position);
        // Create a rotation quaternion from up vector to terrain normal
        objectNode->SetRotation(Quaternion(Vector3::UP, terrain_->GetNormal(position)));
        Node* adjNode = objectNode->CreateChild("AdjNode");
        adjNode->SetRotation(Quaternion(0.0, 0.0, -90.0f));

        objectNode->SetScale(3.5f);

        auto* object = adjNode->CreateComponent<StaticModel>();

        // Random
        int r = std::round(Random(0.0f, 5.0f));
        switch (r) {
            case 0:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-baobab_orange.mdl"));
                break;
            case 1:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-birch02.mdl"));
                break;
            case 2:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-elipse.mdl"));
                break;
            case 3:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-fir.mdl"));
                break;
            case 4:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-oak.mdl"));
                break;
            case 5:
                object->SetModel(cache->GetResource<Model>("Models/AssetPack/tree-lime.mdl"));
                break;
        }

 //       object->SetMaterial(cache->GetResource<Material>("Materials/LOWPOLY_COLORS.xml")
        object->SetMaterial(cache->GetResource<Material>("Materials/LOWPOLY-COLORS.xml"));
        object->SetCastShadows(true);

        auto* body = adjNode->CreateComponent<RigidBody>();
        body->SetCollisionLayer(2);
        auto* shape = objectNode->CreateComponent<CollisionShape>();
        shape->SetTriangleMesh(object->GetModel(), 0);
    }*/



    //  }

    // Setup AI
    // Initialize evolution manager
    MayaScape::InitEvolutionManager();

    // Attempt to retrieve player spawn line segment marker from pre-loaded scene
    if (!starAMarkerSet_) {
        // Locate start star marker A
        Node *starAStartNode = scene_->GetChild("start_starA", true);
        if (starAStartNode) {
            URHO3D_LOGINFOF("start_starA -> located at -> [%f,%f,%f]", starAStartNode->GetWorldPosition().x_,
                            starAStartNode->GetWorldPosition().y_, starAStartNode->GetWorldPosition().z_);
            starAMarker_ = starAStartNode->GetWorldPosition();
        }

        starAMarkerSet_ = true;
    }

    if (!starBMarkerSet_) {
        // Locate start star marker B
        Node *starBStartNode = scene_->GetChild("start_starB", true);

        if (starBStartNode) {
            URHO3D_LOGINFOF("start_starB -> located at -> [%f,%f,%f]", starBStartNode->GetWorldPosition().x_,
                            starBStartNode->GetWorldPosition().y_, starBStartNode->GetWorldPosition().z_);
            starBMarker_ = starBStartNode->GetWorldPosition();
        }
        starBMarkerSet_ = true;
    }

    // Locate track
    Node *track1Node = scene_->GetChild("track1", true);

    // Set collision map for track
    if (track1Node) {
        StaticModel *model = track1Node->GetComponent<StaticModel>(REPLICATED);
        RigidBody *body = track1Node->GetComponent<RigidBody>(REPLICATED);
       // body->SetCollisionLayer(2);
        CollisionShape *trackColShape_ = track1Node->GetComponent<CollisionShape>(REPLICATED);
       // trackColShape_->SetTriangleMesh(model->GetModel(), 0);

//                trackColShape_->SetConvexHull(model->GetModel());
    }

    // Locate Earth
    Node *earth1Node = scene_->GetChild("earth-land", true);

    if (earth1Node) {
        StaticModel *model = earth1Node->GetComponent<StaticModel>(REPLICATED);
        RigidBody *body = earth1Node->GetComponent<RigidBody>(REPLICATED);
        //body->SetCollisionLayer(2);
        CollisionShape *colShape_ = earth1Node->GetComponent<CollisionShape>(REPLICATED);
        // trackColShape_->SetTriangleMesh(model->GetModel(), 0);

//                trackColShape_->SetConvexHull(model->GetModel());
    }


    // Spawn the ai bot players
    CreateAgents();

    //for (int i = 0; i < EvolutionManager::getInstance()->getAgents().size(); i++) {
    // Grab ffn count from agent 1

    Sprite *sprite;
    Texture2D *texture;
    int i = 0;
    int numWeights = EvolutionManager::getInstance()->getAgents()[i]->ffn->weightCount;

        for (int j = 0; j < numWeights; j++) {
            // Create sprite for each node of ffn
            sprite = ui->GetRoot()->CreateChild<Sprite>();
            // Get neural net node texture
            texture = cache->GetResource<Texture2D>("Textures/nn-node.png");
            if (!texture)
                return;
            // Set sprite texture
            sprite->SetTexture(texture);
            // Set logo sprite scale
            //logoSprite_->SetScale(256.0f / textureWidth);
            // Set logo sprite size
            sprite->SetSize(texture->GetWidth(), texture->GetHeight());
            sprite->SetAlignment(HA_LEFT, VA_TOP);
            sprite->SetPosition(Vector2(700.0f, 30.0f));
            sprite->SetOpacity(0.8f);
            // Set a low priority so that other UI elements can be drawn on top
            sprite->SetPriority(-100);
            sprite->SetVisible(false);

            // Server-side view
            ffnBotSprite_.Insert(Pair<int, Sprite *>(j, sprite));
        }

    // Create sprite
    sprite = ui->GetRoot()->CreateChild<Sprite>();
    // Get steering wheel texture
    texture = cache->GetResource<Texture2D>("Textures/steer-wheel.png");
    if (!texture)
        return;
    // Set sprite texture
    sprite->SetTexture(texture);
    //sprite->SetScale(256.0f / texture->GetWidth());
    // Set logo sprite size
    sprite->SetSize(texture->GetWidth(), texture->GetHeight());
    sprite->SetAlignment(HA_LEFT, VA_TOP);
    sprite->SetHotSpot(texture->GetWidth()/2, texture->GetHeight()/2);
    sprite->SetPosition(Vector2(700.0f, 500.0f));
    sprite->SetOpacity(0.8f);
    // Set a low priority so that other UI elements can be drawn on top
    sprite->SetPriority(-100);
    sprite->SetVisible(false);
    steerWheelBotSprite_ = sprite;

    // Create sprite
    sprite = ui->GetRoot()->CreateChild<Sprite>();
    // Get velocity bar texture
    texture = cache->GetResource<Texture2D>("Textures/velocity.png");
    if (!texture)
        return;
    // Set sprite texture
    sprite->SetTexture(texture);
    sprite->SetScale(256.0f / texture->GetWidth());
    // Set logo sprite size
    sprite->SetSize(texture->GetWidth(), texture->GetHeight());
    sprite->SetAlignment(HA_LEFT, VA_TOP);
    sprite->SetPosition(Vector2(700.0f, 700.0f));
    sprite->SetOpacity(0.8f);
    // Set a low priority so that other UI elements can be drawn on top
    sprite->SetPriority(-100);
    sprite->SetVisible(false);
    velBarBotSprite_ = sprite;


    // Create sprite
    sprite = ui->GetRoot()->CreateChild<Sprite>();
    // Get velocity bar background texture
    texture = cache->GetResource<Texture2D>("Textures/powerbar-bk.png");
    if (!texture)
        return;

    // Set sprite texture
    sprite->SetTexture(texture);
    // Set logo sprite size
    sprite->SetSize(texture->GetWidth(), texture->GetHeight());
    sprite->SetScale(256.0f / texture->GetWidth());
    sprite->SetAlignment(HA_LEFT, VA_TOP);
    sprite->SetPosition(Vector2(700.0f, 700.0f));
    sprite->SetOpacity(0.8f);
    // Set a low priority so that other UI elements can be drawn on top
    sprite->SetPriority(-100);
    sprite->SetVisible(false);
    velBarBkgBotSprite_ = sprite;



    //}

}

void MayaScape::HandleClientDisconnected(StringHash eventType, VariantMap &eventData) {
    using namespace ClientConnected;
    Connection* client = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    String username = String(client->GetIdentity()["UserName"]);

    // Clear client on disconnect
    DestroyPlayer(client);

}


void MayaScape::HandleServerConnected(StringHash eventType, VariantMap& eventData)
{
    StartMultiplayerGameSession();
    // Start in game mode
    UpdateUIState(true);

    // For safe
    UnsubscribeFromEvent(E_SERVERCONNECTED);
}

void MayaScape::HandleServerDisconnected(StringHash eventType, VariantMap& eventData)
{

}

void MayaScape::HandlePlayerRespawned(StringHash eventType, VariantMap& eventData)
{

    // CLIENT CODE

    Network* network = GetSubsystem<Network>();
    Connection* connection = network->GetServerConnection();

    // Create client UI once we have spawned
    CreateClientUI();

    // Subscribe the update event for the whole logic
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(MayaScape, HandleUpdate));

    // UnScribeRemoteEvents
    UnsubscribeFromEvent(E_PLAYERSPAWNED);

    // Send remote event
    //network->GetServerConnection()->SendRemoteEvent(E_PLAYERSPAWNED, true);
    // Create camera and define viewport. We will be doing load / save, so it's convenient to create the camera outside the scene,
    // so that it won't be destroyed and recreated, and we don't have to redefine the viewport on load


    // Enable for 3D sounds to work (attach to camera node)
    SoundListener *listener = clientCam_->GetNode()->CreateComponent<SoundListener>();
    GetSubsystem<Audio>()->SetListener(listener);


    clientLevelLoading_ = false;

    // Start engine
    PlaySoundEffectLocal(driveAudioEffect[SOUND_FX_ENGINE_START].c_str());
}

void MayaScape::HandlePlayerLoaded(StringHash eventType, VariantMap &eventData) {

    // CLIENT CODE

    clientPhysicsWorld_->SetEnabled(true);
    clientPhysicsWorld_->SetUpdateEnabled(true);
    scene_->SetUpdateEnabled(true);
    scene_->SetEnabled(true);

    // Clear menu
    Renderer *renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(2, nullptr);

    URHO3D_LOGINFOF("HandlePlayerLoaded");

}
