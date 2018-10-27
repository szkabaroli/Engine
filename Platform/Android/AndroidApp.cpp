#include "AndroidApp.h"
#include <android/native_window_jni.h>

#define OPENSLES_CALL(x) if(x != SL_RESULT_SUCCESS) __android_log_print(ANDROID_LOG_WARN, "Audio", "Error at: %d", #x);;

int32_t AndroidApp::HandleInput(android_app* app, AInputEvent* event)
{
	return 0;
}

void AndroidApp::HandleCmd(struct android_app *State, int32_t cmd)
{
    AndroidApp* App = (AndroidApp*)State->userData;

    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            //create window
            App->bHaveWindow = true;
            break;

        case APP_CMD_TERM_WINDOW:

            App->bHaveWindow = false;
            break;

        case APP_CMD_START:
            //DO nothing
            break;

        case APP_CMD_STOP:
            App->bRunning = false;
            break;

        case APP_CMD_PAUSE:
            App->bRunning = false;
            break;

        case APP_CMD_RESUME:
            App->bRunning = true;
            break;

        case APP_CMD_DESTROY:

            break;

        default:
            __android_log_print(ANDROID_LOG_WARN, "Engine", "Event not handled: %d", cmd);
    }
}

bool AndroidApp::IsRunning()
{
    return bRunning && bHaveWindow;
}

void AndroidApp::CreateAudioEngine() {

    SLresult result;

    result = slCreateEngine(&EngineObject, 0, NULL, 0, NULL, NULL);

    // realize the engine
    result = (*EngineObject)->Realize(EngineObject, SL_BOOLEAN_FALSE);

    // get the engine interface, which is needed in order to create other objects
    result = (*EngineObject)->GetInterface(EngineObject, SL_IID_ENGINE, &EngineEngine);

    // create output mix, with environmental reverb specified as a non-required interface
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    result = (*EngineEngine)->CreateOutputMix(EngineEngine, &OutputMixObject, 1, ids, req);

    // realize the output mix
    result = (*OutputMixObject)->Realize(OutputMixObject, SL_BOOLEAN_FALSE);

    // get the environmental reverb interface
    // this could fail if the environmental reverb effect is not available,
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    result = (*OutputMixObject)->GetInterface(OutputMixObject, SL_IID_ENVIRONMENTALREVERB, &OutputMixEnvironmentalReverb);

    if (SL_RESULT_SUCCESS == result) {
        result = (*OutputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(OutputMixEnvironmentalReverb, &ReverbSettings);
    }
}

void AndroidApp::CreateAudioPlayerFromManager(AAssetManager* Manager)
{
    SLresult result;
    const char* FileName = "legends.mp3";

    AAsset* Asset = AAssetManager_open(Manager, FileName, AASSET_MODE_UNKNOWN);

    if (!Asset)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Audio", "Failed to load: %d", FileName);
    }
    else
    {
        __android_log_print(ANDROID_LOG_INFO, "Audio", "Success loaded");
    }

    off_t start, length;
    int fd = AAsset_openFileDescriptor(Asset, &start, &length);
    assert(0 <= fd);
    AAsset_close(Asset);

    // configure audio source
    SLDataLocator_AndroidFD loc = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
    SLDataFormat_MIME mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_MP3};
    SLDataSource audioSrc = {&loc, &mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, OutputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};


    result= (*EngineEngine)->CreateAudioPlayer(EngineEngine, &PlayerObject, &audioSrc, &audioSnk, 3, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the player
    result = (*PlayerObject)->Realize(PlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the play interface
    result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_PLAY, &PlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the seek interface
    result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_SEEK, &PlayerSeek);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the mute/solo interface
    result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_MUTESOLO, &PlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the volume interface
    result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_VOLUME, &PlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
}

void AndroidApp::SetAudioPlayerState(bool bIsPlaying) {

    SLresult result;

    if (PlayerPlay) {
        // set the player's state
        result = (*PlayerPlay)->SetPlayState(PlayerPlay, bIsPlaying ? SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
    }
}

void AndroidApp::ReleaseAudioEngine() {
    if (PlayerObject) {
        (*PlayerObject)->Destroy(PlayerObject);
        PlayerObject = nullptr;
        PlayerPlay = nullptr;
        PlayerSeek = nullptr;
        PlayerMuteSolo = nullptr;
        PlayerVolume = nullptr;
    }

    if (OutputMixObject) {
        (*OutputMixObject)->Destroy(OutputMixObject);
        OutputMixObject = nullptr;
        OutputMixEnvironmentalReverb = nullptr;
    }

    // destroy engine object, and invalidate all associated interfaces
    if (EngineObject != nullptr) {
        (*EngineObject)->Destroy(EngineObject);
        EngineObject = nullptr;
        EngineEngine = nullptr;
    }
}
