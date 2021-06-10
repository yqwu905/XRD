// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericPlatform/GenericPlatformHttp.h"
#include "Engine.h"
#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Misc/Base64.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UploadScore.generated.h"

UCLASS()
class XRDHTML_API AUploadScore : public AActor
{
	GENERATED_BODY()
	
public:
	FHttpModule* Http;
	TArray<FString> records;
	// Sets default values for this actor's properties
	AUploadScore();
	UFUNCTION(BlueprintCallable, Category = "Upload Score")
		void AddRecord(FString record);
	UFUNCTION(BlueprintCallable, Category = "Upload Score")
		FString SendRecord(FString id, FString score);

	void OnYourFunctionCompleted(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
