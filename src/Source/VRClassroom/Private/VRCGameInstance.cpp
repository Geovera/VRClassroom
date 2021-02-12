// Copyright 2020 Testy


#include "VRCGameInstance.h"
#include "HttpService.h"

UVRCGameInstance::UVRCGameInstance(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	Http = NewObject<UHttpService>(UHttpService::StaticClass());
}

UHttpService* UVRCGameInstance::GetHttpService() {
	return Http;
}
