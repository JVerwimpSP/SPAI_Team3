#include "Aggregator.h"

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);

Aggregator::Aggregator() {}

Aggregator::~Aggregator() {}

void Aggregator::ListAudioDevices() {

	HRESULT hr;
	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDeviceCollection* pCollection = NULL;
	IMMDevice* pEndpoint = NULL;
	IPropertyStore* pProps = NULL;
	LPWSTR pwszID = NULL;

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		(void**)&pEnumerator);
	EXIT_ON_ERROR(hr);

	hr = pEnumerator->EnumAudioEndpoints(
		eAll, DEVICE_STATE_ACTIVE,
		&pCollection);
	EXIT_ON_ERROR(hr);

	UINT count;
	hr = pCollection->GetCount(&count);
	EXIT_ON_ERROR(hr);

	if (count == 0)
	{
		printf("No endpoints found.\n");
	}

	for (ULONG i = 0; i < count; i++)
	{
		// Get pointer to endpoint number i
		hr = pCollection->Item(i, &pEndpoint);
		EXIT_ON_ERROR(hr);

		// Get the endpoint ID string
		hr = pEndpoint->GetId(&pwszID);
		EXIT_ON_ERROR(hr);

		hr = pEndpoint->OpenPropertyStore(STGM_READ, &pProps);
		EXIT_ON_ERROR(hr);

		PROPVARIANT varName;
		// Initialize container for property value.
		PropVariantInit(&varName);

		// Get the endpoint's friendly-name property.
		hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
		EXIT_ON_ERROR(hr);

		// Print endpoint friendly name and endpoint ID
		printf("Endpoint %d: \"%S\" (%S)\n", i, varName.pwszVal, pwszID);

		CoTaskMemFree(pwszID);
		pwszID = NULL;
		PropVariantClear(&varName);
		SAFE_RELEASE(pProps);
		SAFE_RELEASE(pEndpoint);
	}
	SAFE_RELEASE(pEnumerator);
	SAFE_RELEASE(pCollection);
	return;

Exit:
	printf("Error!\n");
	CoTaskMemFree(pwszID);
	SAFE_RELEASE(pEnumerator);
	SAFE_RELEASE(pCollection);
	SAFE_RELEASE(pEndpoint);
	SAFE_RELEASE(pProps);

}