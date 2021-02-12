// Copyright 2020 Testy

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HttpService.h"
#include "VRCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VRCLASSROOM_API UVRCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	UHttpService* Http;

public:
	UVRCGameInstance(const class FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Http")
		UHttpService* GetHttpService();

};
