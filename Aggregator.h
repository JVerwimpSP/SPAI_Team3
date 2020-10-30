#pragma once

#include <stdio.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <winerror.h>

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

class Aggregator
{

public:
	//--------------------------------------------

	Aggregator();
	~Aggregator();

	//--------------------------------------------

	void ListAudioDevices();


	//--------------------------------------------

private:

	IAudioCaptureClient* pCaptureClient1;
	IAudioCaptureClient* pCaptureClient2;
	IAudioRenderClient* pRenderClient;

};

