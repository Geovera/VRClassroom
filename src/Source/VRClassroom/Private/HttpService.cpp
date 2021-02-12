// Copyright 2020 Testy


#include "HttpService.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"
#include "Runtime/Online/HTTP/Public/Http.h"

UHttpService::UHttpService(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/*GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("VRCAPIPath"),
		VRCAPIPath,
		GGameIni
	);*/
	VRCAPIPath = FString(TEXT("https://api.ev3.me/"));
	Http = &FHttpModule::Get();
}

void UHttpService::SetTimeout(float Timeout) {
	Http->SetHttpTimeout(Timeout);
}

bool UHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) return true;
	else {
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}

void UHttpService::SetRequestHeaders(TSharedRef<IHttpRequest>& Request) {
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	//Request->SetHeader(AuthorizationHeader, AuthorizationHash);
}

TSharedRef<IHttpRequest> UHttpService::RequestWithRoute(FString Subroute) {
	// I have to set it here because for some reason if I set it on the constructor it becomes empty when it reaches here
	// TODO: Figure out why that happens and fix it to remove this line
	VRCAPIPath = FString(TEXT("https://api.ev3.me/"));

	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	FString url = FString(VRCAPIPath + Subroute);
	Request->SetURL(url);
	
	SetRequestHeaders(Request);

	return Request;
}

TSharedRef<IHttpRequest> UHttpService::PostRequest(FString Subroute, FString ContentJsonString) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);

	return Request;
}

TSharedRef<IHttpRequest> UHttpService::GetRequest(FString Subroute) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");

	return Request;
}