#include <memory>
#include <errno.h>
#include <vector>
#include <thread>
#include <chrono>

#include "AndroidApp.h"
#include "../Logger.h"
#include "../GameEngine.h"
#include "vulkan_wrapper.h"

void android_main(android_app* State)
{
    AndroidApp* Application = new AndroidApp;

    AAssetManager* mgr = State->activity->assetManager;

    State->userData = Application;
    State->onAppCmd = Application->HandleCmd;
    State->onInputEvent = Application->HandleInput;

    GameEngine* Engine = new GameEngine();

    InitVulkan();

    Engine->Init();

    Application->CreateAudioEngine();
    Application->CreateAudioPlayerFromManager(mgr);

    Application->SetAudioPlayerState(true);

    while(true)
    {

        int id;
        int events;
        android_poll_source* Source;

        while((id = ALooper_pollAll( Application->IsRunning() ? 0 : -1, NULL, &events, (void**)&Source )) >= 0 )
        {
            if( Source != NULL )
                Source->process( State, Source );

            if(State->destroyRequested)
            {
                Engine->Close();
                Application->ReleaseAudioEngine();
                return;
            }
        }

        if( Application->IsRunning() )
        {
            Engine->Tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));

        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

}

