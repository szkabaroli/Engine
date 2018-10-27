#pragma once

#include <memory>
#include <android_native_app_glue.h>
#include <android/log.h>

#include <android/asset_manager.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class AndroidApp 
{
public:
	static int32_t HandleInput(android_app* app, AInputEvent* event);
	static void HandleCmd( struct android_app* app, int32_t cmd);

	void CreateAudioEngine();
	void CreateAudioPlayerFromManager(AAssetManager* mgr);
	void SetAudioPlayerState(bool bIsPlaying);
	void ReleaseAudioEngine();

    bool IsRunning();

	bool bRunning = false;
    bool bHaveWindow = false;
private:
    SLObjectItf EngineObject;
    SLEngineItf EngineEngine;

    SLObjectItf OutputMixObject;
    SLEnvironmentalReverbItf OutputMixEnvironmentalReverb;
    SLEnvironmentalReverbSettings ReverbSettings;

    SLObjectItf PlayerObject;
    SLPlayItf PlayerPlay;
    SLSeekItf PlayerSeek;
    SLMuteSoloItf PlayerMuteSolo;
    SLVolumeItf PlayerVolume;
};