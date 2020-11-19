// Copyright 2020 Testy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "VRCPlayerController.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FCourse {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Course")
		int32 CourseID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Course")
		FString CourseName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Course")
		FDateTime StartDate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Course")
		FDateTime EndDate;
};

/**
 * 
 */
UCLASS()
class VRCLASSROOM_API AVRCPlayerController : public APlayerController
{
	GENERATED_BODY()

		FHttpModule* Http;

public:

	AVRCPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
		float TravelTimeout;

	UPROPERTY(BlueprintReadWrite, Category = "Config")
		FString VRCAPIPath = "http://localhost:1337/";

	UFUNCTION(BlueprintCallable, Category = "Travel")
		void ConnectToCampus();

		void OnConnectToCampusResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

		UFUNCTION(BlueprintCallable, Category = "Travel")
			void TravelToMap(const FString& URL, const bool SeamlessTravel);
	
};
