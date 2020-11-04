#pragma once

#include <stdio.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <winerror.h>
#include <system_error>

#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { \
					 printf("ERROR HRESULT: %x\n", hres); \
					 goto Exit; \
			  }
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
	void RecordAudioStream();
	void RenderAudioStream();


	//--------------------------------------------

private:

	IAudioCaptureClient* pCaptureClient1;
	IAudioCaptureClient* pCaptureClient2;
	IAudioRenderClient* pRenderClient;

};

