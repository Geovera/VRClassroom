// Copyright 2020 Testy


#include "VRCPlayerController.h"
#include "Runtime/Online/HTTP/Public/Http.h"

AVRCPlayerController::AVRCPlayerController() {

	TravelTimeout = 60.0f;
}

void AVRCPlayerController::TravelToMap(const FString& URL, const bool SeamlessTravel) {
	UE_LOG(LogTemp, Warning, TEXT("TravelToMap: %s"), *URL);
	ClientTravel(URL, TRAVEL_Absolute, false, FGuid());
}

void AVRCPlayerController::ConnectToCampus() {
	Http = &FHttpModule::Get();
	Http->SetHttpTimeout(TravelTimeout);

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AVRCPlayerController::OnConnectToCampusResponseRecieved);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	FString url = FString(VRCAPIPath + "instances/join-server");
	TArray<FStringFormatArg> FormatParams;
	FormatParams.Add(TEXT("Geo"));
	FormatParams.Add(TEXT("123"));
	FString PostParameters = FString::Format(TEXT("{\"Username\": \"{0}\", \"Pass\": \"{1}\"}"), FormatParams);

	Request->SetURL(url);
	Request->SetContentAsString(PostParameters);
	Request->ProcessRequest();
}

void AVRCPlayerController::OnConnectToCampusResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString IP = JsonObject->GetStringField("ip");
			FString PORT = JsonObject->GetStringField("port");

			FString URL = IP + FString(TEXT(":")) + PORT.Left(4);
			UE_LOG(LogTemp, Log, TEXT("OnConnectToCampus IP is %s Port %s, Both"), *IP, *PORT, *URL);

			TravelToMap(URL, false);

		}
		else {
			UE_LOG(LogTemp, Error, TEXT("OnConnectToCampus Server returned no data!"));

		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("OnConnectToCampus Error accessing server!"));
	}
}
