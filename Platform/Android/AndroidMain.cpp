#include <memory>
#include <errno.h>
#include <vector>
#include <android/log.h>
#include <thread>
#include <chrono>

#include "AndroidApp.h"
#include "VulkanLoader.hpp"


void android_main(android_app* State)
{
    AndroidApp* Application = new AndroidApp;

    AAssetManager* mgr = State->activity->assetManager;

    State->userData = Application;
    State->onAppCmd = Application->HandleCmd;



    //Engine.Init();

    InitVulkan();

    Application->CreateAudioEngine();
    Application->CreateAudioPlayerFromManager(mgr);

    Application->SetAudioPlayerState(true);

    VkInstance Instance;

    std::vector<const char *> instanceExt;
    instanceExt.push_back("VK_KHR_surface");
    instanceExt.push_back("VK_KHR_android_surface");

    VkInstanceCreateInfo createInfo;
    memset(&createInfo, 0, sizeof(createInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExt.size());
    createInfo.ppEnabledExtensionNames = instanceExt.data();


    vkCreateInstance(&createInfo, nullptr, &Instance);


    while(true)
    {

        int id;
        int events;
        android_poll_source* Source;

        while((id = ALooper_pollAll( Application->IsRunning() ? 0 : -1, NULL, &events, (void**)&Source )) >= 0 )
        {
            // Process this event.
            if( Source != NULL )
                Source->process( State, Source );


            // Check if we are exiting.
            if(State->destroyRequested)
            {
                Application->ReleaseAudioEngine();
                return;
            }
        }

        if( Application->IsRunning() )
        {
            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.

            //Engine.Tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));

        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

}

