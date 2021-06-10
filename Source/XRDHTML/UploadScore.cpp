// Fill out your copyright notice in the Description page of Project Settings.


#include "UploadScore.h"

// Sets default values
AUploadScore::AUploadScore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUploadScore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUploadScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUploadScore::AddRecord(FString record)
{
	records.Add(record);
}

FString AUploadScore::SendRecord(FString id, FString score)
{
	FString recordStr;
	for (auto record : records)
	{
		recordStr += record + "|";
	}
	FString recordUrl = FGenericPlatformHttp::UrlEncode(recordStr);
	FString idUrl = FGenericPlatformHttp::UrlEncode(id);
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	
	HttpRequest->SetURL("https://yqwu.site/app/XRD_Monitor/upload.php?key=dD999QlNCTA1yBq6&record=" + recordUrl + "&id=" + idUrl + "&score=" + score);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	//HttpRequest->OnProcessRequestComplete().BindUObject(this, &AUploadScore::OnYourFunctionCompleted);
	HttpRequest->ProcessRequest();
	return "https://yqwu.site/app/XRD_Monitor/upload.php?key=dD999QlNCTA1yBq6&record=" + recordUrl + "&id=" + idUrl + "&score=" + score;
}

void AUploadScore::OnYourFunctionCompleted(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	return;
}